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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt() {
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt) {
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;

  // 将节点中的 join 添加到 conditions 以及 relations 当中
  vector<JoinSqlNode> join = select_sql.join;
  std::reverse(join.begin(), join.end());
  for (auto it : join) {
    select_sql.relations.emplace_back(it.relation);
    for (auto condition : it.conditions) select_sql.conditions.emplace_back(condition);
  }

  // 检测并递归生成右子查询stmt  //
  // todo：支持左子查询以及除了select之外的其他查询
  for (size_t i = 0; i < select_sql.conditions.size(); ++i) {
    if (select_sql.conditions[i].right_is_sub_query) {
      auto right_sub_query = select_sql.conditions[i].right_sub_query;
      // 右子查询目前必须是select
      if (right_sub_query->flag != SCF_SELECT) {
        LOG_WARN("invalid argument. sub query is not select. index=%d", i);
        return RC::INVALID_ARGUMENT;
      }

      Stmt *right_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, right_sub_query->selection, right_sub_query_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create right sub query stmt. index=%d", i);
        return rc;
      }

      // 把生成的stmt回传给上一级ConditonSqlNode
      auto *sub_select_stmt = dynamic_cast<SelectStmt *>(right_sub_query_stmt);
      select_sql.conditions[i].right_sub_query_stmt = sub_select_stmt;
    }
    if (select_sql.conditions[i].left_is_sub_query) {
      auto left_sub_query = select_sql.conditions[i].left_sub_query;
      // 左子查询目前必须是select
      if (left_sub_query->flag != SCF_SELECT) {
        LOG_WARN("invalid argument. sub query is not select. index=%d", i);
        return RC::INVALID_ARGUMENT;
      }

      Stmt *left_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, left_sub_query->selection, left_sub_query_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create right sub query stmt. index=%d", i);
        return rc;
      }

      // 把生成的stmt回传给上一级ConditonSqlNode
      auto *sub_select_stmt = dynamic_cast<SelectStmt *>(left_sub_query_stmt);
      select_sql.conditions[i].left_sub_query_stmt = sub_select_stmt;
    }
  }

  // 找到全部目标表格
  vector<Table *> tables;
  unordered_map<string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    // 根据表格名称找到表格，并且完成插入
    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
  }

  // 解析查询表达式，将其以及其子表达式统一加入 bound_expressions 中
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);

  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  // 解析 GROUP BY 表达式，将其以及其子表达式统一加入 group_by_expressions 中
  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  // 设置主表格？
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // 创建筛选对应的 STMT 对象
  FilterStmt *filter_stmt = nullptr;
  RC rc =
      FilterStmt::create(db, default_table, &table_map, select_sql.conditions.data(), static_cast<int>(select_sql.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // 创建 SELECT 对应的 STMT 对象
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  stmt = select_stmt;
  return RC::SUCCESS;
}
