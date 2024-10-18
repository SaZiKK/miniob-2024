/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "common/type/date_type.h"

using namespace std;
using namespace common;

UpdateStmt::~UpdateStmt() {
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt) {
  // 拿到目标表格以及名称以及修改域
  const char *table_name = update.relation_name.c_str();
  Table *table = db->find_table(table_name);

  // 目标表格不存在检查
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // 参数非法检查
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // 拿到全部修改域
  std::vector<FieldMeta> field_metas;
  for (auto it : update.update_targets) {
    FieldMeta *field_meta = (FieldMeta *)table->table_meta().field(it.attribute_name.c_str());
    // 修改域检查
    if (nullptr == field_meta) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    field_metas.push_back(*field_meta);
  }

  // 创建筛选 STMT 对象
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);

  // 谓词语句合法检查
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // check date validity
  for (auto it : update.update_targets) {
    Value value = it.value;
    if (value.attr_type() == AttrType::DATE) {
      if (!DateType::check_date(value.get_date())) {
        return RC::INVALID_ARGUMENT;
      }
    }
  }

  // 创建 update 的 STMT 对象
  stmt = new UpdateStmt(table, filter_stmt, field_metas, update.update_targets);
  return RC::SUCCESS;
}
