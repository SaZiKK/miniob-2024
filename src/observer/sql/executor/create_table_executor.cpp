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

#include "sql/executor/create_table_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"

RC CreateTableExecutor::execute(SQLStageEvent *sql_event) {
  Stmt *stmt = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_TABLE, "create table executor can not run this command: %d", static_cast<int>(stmt->type()));

  CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);

  const char *table_name = create_table_stmt->table_name().c_str();
  std::vector<AttrInfoSqlNode> attr_infos = create_table_stmt->attr_infos();
  if (create_table_stmt->use_select()) {
    // 如果不是自定义表头，需要使用 Select 子句的表头
    if (attr_infos.empty()) {
      for (size_t i = 0; i < create_table_stmt->query_expressions().size(); i++) {
        AttrInfoSqlNode attr_info;
        if (create_table_stmt->query_expressions()[i]->type() == ExprType::FIELD) {
          FieldExpr *field_expr = static_cast<FieldExpr *>(create_table_stmt->query_expressions()[i].get());
          Field field = field_expr->field();
          attr_info.can_be_null = field.meta()->can_be_null();
          attr_info.name = field.meta()->name();
          attr_info.type = field.meta()->type();
          attr_info.length = field.meta()->len();
          attr_infos.push_back(attr_info);
        } else {
          attr_info.can_be_null = false;
          attr_info.name = create_table_stmt->query_expressions()[i]->name();
          attr_info.type = create_table_stmt->query_expressions()[i]->value_type();
          attr_info.length = create_table_stmt->query_expressions()[i]->value_length();
          attr_infos.push_back(attr_info);
        }
      }
    }
  }

  RC rc = session->get_current_db()->create_table(table_name, attr_infos, create_table_stmt->storage_format());
  if (rc != RC::SUCCESS) return rc;

  // insert part
  Table *table_ = session->get_current_db()->find_table(table_name);
  if (create_table_stmt->use_select()) {
    for (size_t i = 0; i < create_table_stmt->tuple_list().size(); i++) {
      Record record;
      std::vector<Value> values = create_table_stmt->tuple_list()[i];
      rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
      if (rc != RC::SUCCESS) return rc;
      rc = table_->insert_record(record);
    }
  }

  return rc;
}