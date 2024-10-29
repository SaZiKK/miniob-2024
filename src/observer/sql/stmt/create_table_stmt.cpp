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
// Created by Wangyunlai on 2023/6/13.
//

#include "common/log/log.h"
#include "common/lang/string.h"
#include "common/types.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"

RC CreateTableStmt::create(Db *db, CreateTableSqlNode &create_table, Stmt *&stmt) {
  StorageFormat storage_format = StorageFormat::UNKNOWN_FORMAT;
  if (create_table.storage_format.length() == 0) {
    storage_format = StorageFormat::ROW_FORMAT;
  } else {
    storage_format = CreateTableStmt::get_storage_format(create_table.storage_format.c_str());
  }
  if (storage_format == StorageFormat::UNKNOWN_FORMAT) {
    return RC::INVALID_ARGUMENT;
  }

  vector<vector<Value>> tuple_list;
  TupleSchema tuple_schema;
  Stmt *temp = nullptr;
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  // 涉及到 create table 语句
  if (create_table.use_sub_select) {
    RC rc = SelectStmt::create(db, create_table.sub_select->selection, temp);
    if (temp != nullptr) {
      SelectStmt *select_stmt = dynamic_cast<SelectStmt *>(temp);
      for (auto &it : select_stmt->query_expressions()) {
        std::unique_ptr<Expression> expr;
        rc = Expression::copy_expr(it, expr);
        query_expressions_.emplace_back(std::move(expr));
      }
    }
    rc = OptimizeStage::handle_sub_stmt(temp, tuple_list, tuple_schema);
    if (rc != RC::SUCCESS) return RC::INVALID_ARGUMENT;
  }

  CreateTableStmt *create_stmt =
      new CreateTableStmt(create_table.relation_name, create_table.attr_infos, storage_format, tuple_schema, tuple_list, create_table.use_sub_select);

  for (auto &it : query_expressions_) create_stmt->query_expressions_.emplace_back(std::move(it));

  stmt = create_stmt;

  return RC::SUCCESS;
}

StorageFormat CreateTableStmt::get_storage_format(const char *format_str) {
  StorageFormat format = StorageFormat::UNKNOWN_FORMAT;
  if (0 == strcasecmp(format_str, "ROW")) {
    format = StorageFormat::ROW_FORMAT;
  } else if (0 == strcasecmp(format_str, "PAX")) {
    format = StorageFormat::PAX_FORMAT;
  } else {
    format = StorageFormat::UNKNOWN_FORMAT;
  }
  return format;
}
