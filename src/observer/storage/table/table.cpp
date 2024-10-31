/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <vector>

#include "common/defs.h"
#include "common/lang/string.h"
#include "common/lang/span.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/buffer/page.h"
#include "storage/db/db.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/field/field_meta.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/index/index.h"
#include "storage/record/record_manager.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

Table::~Table() {
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir, span<const AttrInfoSqlNode> attributes,
                 StorageFormat storage_format) {
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attributes.size() == 0) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  const vector<FieldMeta> *trx_fields = db->trx_kit().trx_fields();
  if ((rc = table_meta_.init(table_id, name, trx_fields, attributes, storage_format)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  fstream fs;
  fs.open(path, ios_base::out | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  db_ = db;
  base_dir_ = base_dir;

  string data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm = db->buffer_pool_manager();
  rc = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::open(Db *db, const char *meta_file, const char *base_dir) {
  // 加载元数据文件
  fstream fs;
  string meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, ios_base::in | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  db_ = db;
  base_dir_ = base_dir;

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const std::vector<FieldMeta> *field_meta = table_meta_.field_metas();
    if (field_meta == nullptr) {
      LOG_ERROR(
          "Found invalid index meta info which has a non-exists field. "
          "table=%s, index=%s, field=%s",
          name(), index_meta->name(), index_meta->field().c_str());
      // skip cleanup
      //  do all cleanup action in destructive Table function
      return RC::INTERNAL;
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    string index_file = table_index_file(base_dir, name(), index_meta->name());

    rc = index->open(this, index_file.c_str(), *index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s", name(), index_meta->name(), index_file.c_str(), strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  return rc;
}

RC Table::insert_record(Record &record) {
  RC rc = RC::SUCCESS;
  rc = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR(
          "Failed to rollback index data when insert index entries failed. "
          "table name=%s, rc=%d:%s",
          name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC(
          "Failed to rollback record data when insert index entries failed. "
          "table name=%s, rc=%d:%s",
          name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

RC Table::visit_record(const RID &rid, function<bool(Record &)> visitor) { return record_handler_->visit_record(rid, visitor); }

RC Table::get_record(const RID &rid, Record &record) {
  RC rc = record_handler_->get_record(rid, record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name(), strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::recover_insert_record(Record &record) {
  RC rc = RC::SUCCESS;
  rc = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR(
          "Failed to rollback index data when insert index entries failed. "
          "table name=%s, rc=%d:%s",
          name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC(
          "Failed to rollback record data when insert index entries failed. "
          "table name=%s, rc=%d:%s",
          name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

const char *Table::name() const { return table_meta_.name(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::make_record(int value_num, const Value *values, Record &record) {
  RC rc = RC::SUCCESS;
  // 检查属性数量是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);
  memset(record_data, 0, record_size);

  for (int i = 0; i < value_num && OB_SUCC(rc); i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    Value value = values[i];

    // 当插入数据 NULL 时，做一次检验
    if (value.get_null()) {
      if (field->can_be_null() == false) {
        LOG_WARN("failed to insert NULL to NOT_NULL field");
        return RC::INVALID_ARGUMENT;
      }
      rc = set_value_to_record(record_data, value, field, i);
    } else if (field->type() != value.attr_type()) {
      Value real_value;
      rc = Value::cast_to(value, field->type(), real_value);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to cast value. table name:%s,field name:%s,value:%s ", table_meta_.name(), field->name(), value.to_string().c_str());
        break;
      }
      rc = set_value_to_record(record_data, real_value, field, i);
    } else {
      rc = set_value_to_record(record_data, value, field, i);
    }
  }
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to make record. table name:%s", table_meta_.name());
    free(record_data);
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::set_value_to_record(char *record_data, Value &value, const FieldMeta *field, int index) {
  size_t copy_len = field->len();
  size_t data_len = value.length();

  if (value.attr_type() == AttrType::VECTORS && copy_len != (size_t)data_len) return RC::INVALID_ARGUMENT;

  // 如果是 TEXT 类型，在这里就要写入页中
  if (field->type() == AttrType::TEXT) {
    int offset = 0;
    vector<PageNum> page_nums;
    for (int i = 0; i < BP_MAX_TEXT_PAGES && offset < value.length(); i++) {
      Frame *frame = nullptr;
      RC rc = RC::SUCCESS;
      rc = data_buffer_pool_->allocate_page(&frame);
      data_buffer_pool_->mark_text_page(frame->page_num(), true);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to allocate page for text field. table name=%s, field name=%s, rc=%d:%s", table_meta_.name(), field->name(), rc, strrc(rc));
        return rc;
      }
      auto data = frame->page().data;
      memset(data, 0, BP_PAGE_DATA_SIZE);
      int len = std::min(value.length() - offset, BP_PAGE_DATA_SIZE);
      memcpy(data, value.data() + offset, len);
      offset += len;
      page_nums.push_back(frame->page_num());
      frame->dirty();
      data_buffer_pool_->unpin_page(frame);
    }
    char *data = new char[BP_MAX_TEXT_RECORD_SIZE];
    memset(data, 0, BP_MAX_TEXT_RECORD_SIZE);
    offset = 0;
    int length = value.length();
    memcpy(data, &length, 4);
    offset += 4;
    for (int i = 0; i < (int)page_nums.size(); i++) {
      memcpy(data + offset, &page_nums[i], 4);
      offset += 4;
    }
    for (int i = page_nums.size(); i < BP_MAX_TEXT_PAGES; i++) {
      memset(data + offset, 0, 4);
      offset += 4;
    }
    value.set_type(AttrType::CHARS);
    value.update_text_data(data, BP_MAX_TEXT_RECORD_SIZE);
    delete[] data;
  }

  if (field->type() == AttrType::CHARS) {
    if (copy_len > data_len) {
      data_len = value.length();
      copy_len = data_len + 1;
    }
  }

  memcpy(record_data + field->offset(), value.data(), copy_len);

  // null bitmap
  const char *bit = value.get_null() ? "0" : "1";
  memcpy(record_data + index, bit, 1);

  // TODO delete
  if (value.get_null()) {
    const char *flag = "ÿ";
    memcpy(record_data + field->offset(), flag, 1);
  }
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir) {
  string data_file = table_data_file(base_dir, table_meta_.name());

  BufferPoolManager &bpm = db_->buffer_pool_manager();
  RC rc = bpm.open_file(db_->log_handler(), data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler(table_meta_.storage_format());

  rc = record_handler_->init(*data_buffer_pool_, db_->log_handler(), &table_meta_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, ReadWriteMode mode) {
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, db_->log_handler(), mode, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::get_chunk_scanner(ChunkFileScanner &scanner, Trx *trx, ReadWriteMode mode) {
  RC rc = scanner.open_scan_chunk(this, *data_buffer_pool_, db_->log_handler(), mode);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::create_index(Trx *trx, const vector<FieldMeta> &fieldmetas, const char *index_name, bool is_unique) {
  if (common::is_blank(index_name) || fieldmetas.empty()) {
    LOG_INFO(
        "Invalid input arguments, table name is %s, index_name is blank or "
        "attribute_name is blank",
        name());
    return RC::INVALID_ARGUMENT;
  }

  IndexMeta new_index_meta;

  RC rc = new_index_meta.init(index_name, fieldmetas);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s", name(), index_name);
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  string index_file = table_index_file(base_dir_.c_str(), name(), index_name);

  rc = index->create(this, index_file.c_str(), new_index_meta, fieldmetas, is_unique);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  if (rc != RC::SUCCESS) {
    LOG_WARN(
        "failed to create scanner while creating index. table=%s, index=%s, "
        "rc=%s",
        name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    // 创建索引的时候，把原有的数据插入到索引中
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN(
          "failed to insert record into index while creating index. table=%s, "
          "index=%s, rc=%s",
          name(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN(
        "failed to insert record into index while creating index. table=%s, "
        "index=%s, rc=%s",
        name(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR(
        "Failed to rename tmp meta file (%s) to normal meta file (%s) while "
        "creating index (%s) on table (%s). "
        "system error=%d:%s",
        tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::delete_record(const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = get_record(rid, record);
  if (OB_FAIL(rc)) {
    return rc;
  }

  return delete_record(record);
}

RC Table::delete_record(const Record &record) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record.data(), &record.rid());
    ASSERT(RC::SUCCESS == rc,
           "failed to delete entry from index. table name=%s, index name=%s, "
           "rid=%s, rc=%s",
           name(), index->index_meta().name(), record.rid().to_string().c_str(), strrc(rc));
  }
  // 处理TEXT的删除
  const int field_num = table_meta_.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field = table_meta_.field(i);
    if (field->type() == AttrType::TEXT) {
      const char *data = record.data() + field->offset();
      int len = *(int *)data;
      int offset = 4;
      for (int i = 0; i < len / BP_PAGE_SIZE + 1; i++) {
        PageNum page_num = *(PageNum *)(data + offset);
        if (page_num <= 0) {
          break;
        }
        offset += 4;
        Frame *frame = nullptr;
        RC rc = RC::SUCCESS;
        rc = data_buffer_pool_->get_this_page(page_num, &frame);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Failed to get page for text field. table name=%s, field name=%s, rc=%d:%s", table_meta_.name(), field->name(), rc, strrc(rc));
          return rc;
        }
        while (frame->pin_count() > 0) {
          data_buffer_pool_->unpin_page(frame);
        }
        rc = data_buffer_pool_->dispose_page(page_num);
        data_buffer_pool_->mark_text_page(page_num, false);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Failed to delete page for text field. table name=%s, field name=%s, rc=%d:%s", table_meta_.name(), field->name(), rc, strrc(rc));
          return rc;
        }
      }
    }
  }
  rc = record_handler_->delete_record(&record.rid());
  return rc;
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}

Index *Table::find_index_by_fields(const std::vector<const char *> field_name) const {
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_fields(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}
// 单个字段的索引查找
Index *Table::find_index_by_field(const char *field_name) const {
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

RC Table::sync() {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s", name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }

  rc = data_buffer_pool_->flush_all_pages();
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

///////////////////////////////////////////////////////////////////////
// 删除一个表
RC Table::drop() {
  // 需要删除 data + index + meta
  // 函数 table_data_file  table_index_file  table_meta_file
  // 可以根据表格名和根目录 (索引名)，找到对应文件名称

  // 删除数据文件 data_file
  string data_file = table_data_file(base_dir_.c_str(), table_meta_.name());
  unlink(data_file.c_str());

  // 删除索引文件 index_file
  int indexNum = table_meta_.index_num();
  for (int i = 0; i < indexNum; i++) {
    auto *index_meta = table_meta_.index(i);
    string index_file = table_index_file(base_dir_.c_str(), table_meta_.name(), index_meta->name());
    unlink(index_file.c_str());
  }

  // 删除元文件 meta_file
  string meta_file = table_meta_file(base_dir_.c_str(), table_meta_.name());
  unlink(meta_file.c_str());

  return RC::SUCCESS;
}

// 检查所有更新字段是否全部有效
RC Table::update_records(Record &record, std::vector<std::pair<Value, FieldMeta>> update_map_) {
  // 遍历表格的全部域，找到目标域
  const int sys_field_num = table_meta_.sys_field_num();
  const int user_field_num = table_meta_.field_num() - sys_field_num;
  FieldMeta *targetFiled = nullptr;

  for (auto it : update_map_) {
    for (int i = 0; i < user_field_num; i++) {
      const FieldMeta *field_meta = table_meta_.field(sys_field_num + i);
      const char *field_name = field_meta->name();

      // 找到目标域
      if (strcmp(field_name, it.second.name()) == 0) {
        // 判断 NULL 值
        if (it.first.get_null()) {
          if (field_meta->can_be_null() == false) return RC::INVALID_ARGUMENT;
        }
        // 类型匹配检查
        else if (field_meta->type() != it.first.attr_type()) {
          Value real_value;
          RC rc = Value::cast_to(it.first, field_meta->type(), real_value);
          if (OB_FAIL(rc)) return rc;
        }

        // 拿到目标域
        targetFiled = (FieldMeta *)field_meta;
        break;
      }
    }

    // 域存在检查
    if (nullptr == targetFiled) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }

  // 暂时备份旧数据
  char *old_data = record.data();
  char *backup_data = (char *)malloc(record.len());
  memcpy(backup_data, old_data, record.len());

  // 所有字段均可更新，开始更新
  for (auto it : update_map_) {
    RC rc = update_record(record, it.second.name(), &it.first);
    if (rc != RC::SUCCESS) return rc;
  }

  // 如果有索引，更新索引，顺便检查如果是唯一索引，那么是否有重复
  std::vector<const char *> update_fields;
  for (auto &it : update_map_) {
    update_fields.push_back(it.second.name());
  }
  Index *index = this->find_index_by_fields(update_fields);
  // 只检查多索引，单列索引交给 update_record 处理
  if (index != nullptr && update_fields.size() > 1) {
    RC rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS && strcmp(old_data, backup_data) != 0) {
      LOG_ERROR("Failed to update data, recovering. table=%s, rc=%d:%s", name(), rc, strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}

// 更新一个字段
RC Table::update_record(Record &record, const char *attr_name, Value *value) {
  // 遍历表格的全部域，找到目标域
  const int sys_field_num = table_meta_.sys_field_num();
  const int user_field_num = table_meta_.field_num() - sys_field_num;
  FieldMeta *targetFiled = nullptr;

  int i = 0;
  for (; i < user_field_num; i++) {
    const FieldMeta *field_meta = table_meta_.field(sys_field_num + i);
    const char *field_name = field_meta->name();

    // 找到目标域
    if (strcmp(field_name, attr_name) == 0) {
      // 判断 NULL 值
      if (value->get_null()) {
        if (field_meta->can_be_null() == false) return RC::INVALID_ARGUMENT;
      }
      // 类型匹配检查
      else if (field_meta->type() != value->attr_type()) {
        Value real_value;
        RC rc = Value::cast_to(*value, field_meta->type(), real_value);
        if (OB_FAIL(rc)) return rc;
        *value = std::move(real_value);
      }

      // 拿到目标域
      targetFiled = (FieldMeta *)field_meta;
      break;
    }
  }

  // 域存在检查
  if (nullptr == targetFiled) {
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  int field_offset = targetFiled->offset();
  int field_length = targetFiled->len();

  // 修改旧数据
  char *old_data = record.data();

  // 暂时备份旧数据
  char *backup_data = (char *)malloc(record.len());
  memcpy(backup_data, old_data, record.len());

  // 对于 CHARS 这种不定长的记录，如果更新的元素大于原来的长度，需要截断
  if (value->length() > field_length) {
    memcpy(old_data + field_offset, value->data(), field_length);
  } else if (targetFiled->type() == AttrType::TEXT) {
    // 先删除原有的 TEXT
    if (targetFiled->type() == AttrType::TEXT) {
      const char *data = record.data() + targetFiled->offset();
      int len = *(int *)data;
      int offset = 4;
      for (int i = 0; i < len / BP_PAGE_SIZE + 1; i++) {
        PageNum page_num = *(PageNum *)(data + offset);
        if (page_num <= 0) {
          break;
        }
        offset += 4;
        Frame *frame = nullptr;
        RC rc = RC::SUCCESS;
        rc = data_buffer_pool_->get_this_page(page_num, &frame);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Failed to get page for text field. table name=%s, field name=%s, rc=%d:%s", table_meta_.name(), targetFiled->name(), rc,
                    strrc(rc));
          return rc;
        }
        while (frame->pin_count() > 0) {
          data_buffer_pool_->unpin_page(frame);
        }
        rc = data_buffer_pool_->dispose_page(page_num);
        data_buffer_pool_->mark_text_page(page_num, false);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Failed to delete page for text field. table name=%s, field name=%s, rc=%d:%s", table_meta_.name(), targetFiled->name(), rc,
                    strrc(rc));
          return rc;
        }
      }
    }
    int offset = 0;
    vector<PageNum> page_nums;
    for (int i = 0; i < BP_MAX_TEXT_PAGES && offset < value->length(); i++) {
      Frame *frame = nullptr;
      RC rc = RC::SUCCESS;
      rc = data_buffer_pool_->allocate_page(&frame);
      data_buffer_pool_->mark_text_page(frame->page_num(), true);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to allocate page for text field. table name=%s, field name=%s, rc=%d:%s", table_meta_.name(), targetFiled->name(), rc,
                  strrc(rc));
        return rc;
      }
      auto data = frame->page().data;
      memset(data, 0, BP_PAGE_DATA_SIZE);
      int len = std::min(value->length() - offset, BP_PAGE_DATA_SIZE);
      memcpy(data, value->data() + offset, len);
      offset += len;
      page_nums.push_back(frame->page_num());
      frame->dirty();
      data_buffer_pool_->unpin_page(frame);
    }
    char *data = new char[BP_MAX_TEXT_RECORD_SIZE];
    memset(data, 0, BP_MAX_TEXT_RECORD_SIZE);
    offset = 0;
    int length = value->length();
    memcpy(data, &length, 4);
    offset += 4;
    for (int i = 0; i < (int)page_nums.size(); i++) {
      memcpy(data + offset, &page_nums[i], 4);
      offset += 4;
    }
    for (int i = page_nums.size(); i < BP_MAX_TEXT_PAGES; i++) {
      memset(data + offset, 0, 4);
      offset += 4;
    }
    value->set_type(AttrType::CHARS);
    value->update_text_data(data, BP_MAX_TEXT_RECORD_SIZE);
    delete[] data;
    memcpy(old_data + targetFiled->offset(), value->data(), value->length() + 1);
  }
  // 对于 CHARS
  // 这种不定长的记录，如果更新的元素小于原来的长度，需要额外抹去原有元素
  else {
    memcpy(old_data + field_offset, value->data(), value->length());
    memset(old_data + field_offset + value->length(), 0, field_length - value->length());
  }
  // null part
  const char *flag = value->get_null() ? "0" : "1";
  memcpy(old_data + i, flag, 1);

  // TODO delete
  if (value->get_null()) {
    const char *flag = "&";
    memcpy(old_data + field_offset, flag, 1);
  }

  record.set_data(old_data);

  Index *index = this->find_index_by_field(targetFiled->name());

  // 单字段索引更新和检查
  if (index != nullptr) {
    RC rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS && strcmp(old_data, backup_data) != 0) {
      LOG_ERROR("Failed to update data, recovering. table=%s, rc=%d:%s", name(), rc, strrc(rc));
      return rc;
    }
  }

  record_handler_->update_record(&record);
  // delete old_data;
  return RC::SUCCESS;
}