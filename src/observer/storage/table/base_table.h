/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#pragma once

#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/types.h"
#include "common/lang/span.h"
#include "common/lang/functional.h"

struct RID;
class Record;
class DiskBufferPool;
class RecordFileHandler;
class RecordFileScanner;
class ChunkFileScanner;
class ConditionFilter;
class DefaultConditionFilter;
class Index;
class IndexScanner;
class RecordDeleter;
class Trx;
class Db;

/**
 * @brief 视图和表的基类
 *
 */
class BaseTable {
 public:
  BaseTable() = default;
  ~BaseTable();

  /**
   * 创建一个表/视图
   * @param path 元数据保存的文件(完整路径)
   * @param name 表名
   * @param base_dir 表数据存放的路径
   * @param attribute_count 字段个数
   * @param attributes 字段
   */
  virtual RC create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir, span<const AttrInfoSqlNode> attributes,
            StorageFormat storage_format) { return RC::UNIMPLEMENTED; }

  /**
   * 打开一个表/视图
   * @param meta_file 保存表元数据的文件完整路径
   * @param base_dir 表所在的文件夹，表记录数据文件、索引数据文件存放位置
   */
  virtual RC open(Db *db, const char *meta_file, const char *base_dir) { return RC::UNIMPLEMENTED; }

  /**
   * @brief 根据给定的字段生成一个记录/行，检查字段类型，是否为NULL等，并复制数据到record中
   * @details 通常是由用户传过来的字段，按照schema信息组装成一个record。
   * @param value_num 字段的个数
   * @param values    每个字段的值
   * @param record    生成的记录数据
   */
  virtual RC make_record(int value_num, const Value *values, Record &record) { return RC::UNIMPLEMENTED; }

  /**
   * @brief 在当前的表中插入一条记录
   * @details
   * 在表文件和索引中插入关联数据。这里只管在表中插入数据，不关心事务相关操作。
   * @param record[in/out] 传入的数据包含具体的数据，插入成功会通过此字段返回RID
   */
  virtual RC insert_record(Record &record);
  virtual RC delete_record(const Record &record);
  virtual RC delete_record(const RID &rid);
  virtual RC update_record(Record &record, const char *attr_name, Value *value);
  virtual RC update_records(Record &record, std::vector<std::pair<Value, FieldMeta>> update_map_);
  virtual RC get_record(const RID &rid, Record &record);

  // 删除表格函数
  virtual RC drop();

  virtual RC recover_insert_record(Record &record);

  // TODO refactor
  virtual RC create_index(Trx *trx, const std::vector<FieldMeta> &fieldmetas, const char *index_name, bool is_unique);

  virtual RC get_record_scanner(RecordFileScanner &scanner, Trx *trx, ReadWriteMode mode);

  virtual RC get_chunk_scanner(ChunkFileScanner &scanner, Trx *trx, ReadWriteMode mode);

  virtual RecordFileHandler *record_handler() const = 0;

  /**
   * @brief 可以在页面锁保护的情况下访问记录
   * @details 当前是在事务中访问记录，为了提供一个“原子性”的访问模式
   * @param rid
   * @param visitor
   * @return RC
   */
  virtual RC visit_record(const RID &rid, function<bool(Record &)> visitor);

 public:
  virtual int32_t table_id() const = 0;
  virtual const char *name() const;

  virtual Db *db() const = 0;

  virtual const TableMeta &table_meta() const;

  virtual RC sync();

  virtual DiskBufferPool *data_buffer_pool() const = 0;

 private:
  virtual RC insert_entry_of_indexes(const char *record, const RID &rid);
  virtual RC delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists);
  virtual RC set_value_to_record(char *record_data, Value &value, const FieldMeta *field, int index);

 private:
  virtual RC init_record_handler(const char *base_dir);

 public:
  virtual Index *find_index(const char *index_name) const;
  virtual Index *find_index_by_field(const char *field_name) const;
  virtual Index *find_index_by_fields(const std::vector<const char *> field_name) const;
};
