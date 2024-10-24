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

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, std::unordered_map<string, string> father_alias) {
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;

  // 将节点中的 join 添加到 conditions 以及 relations 当中
  std::reverse(select_sql.join.begin(), select_sql.join.end());
  for (int i = 0; i < (int)select_sql.join.size(); i++) {
    JoinTableExpr *join_table_expr = static_cast<JoinTableExpr *>(select_sql.join[i].get());
    UnboundTableExpr *table_expr = static_cast<UnboundTableExpr *>(join_table_expr->child().get());
    std::unique_ptr<Expression> temp = make_unique<UnboundTableExpr>(table_expr->table_name(), table_expr->table_alias());
    select_sql.relations.emplace_back(std::move(temp));
    for (auto condition : join_table_expr->conditions()) select_sql.conditions.emplace_back(condition);
  }

  /*
  导入全部别名(包括父亲别名)，并将别名还原成原名
  别名的使用只会在 查询的表达式 expressions + 查询的表格 relations 中
  relations 中的别名是表格的别名
  expressions 中的别名是属性的别名
  */
  vector<Table *> tables;
  unordered_map<string, Table *> table_map;

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    UnboundTableExpr *expr = static_cast<UnboundTableExpr *>(select_sql.relations[i].get());
    const char *table_name = expr->table_name();
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

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    UnboundTableExpr *expr = static_cast<UnboundTableExpr *>(select_sql.relations[i].get());
    const char *table_name = expr->table_name();
    const char *table_alias_name = expr->table_alias();

    // 存在别名
    if (expr->has_table_alias()) {
      // 如果有重复别名
      unordered_map<string, string> alias_and_name = binder_context.alias_and_name();
      if (alias_and_name.count(table_alias_name)) return RC::INVALID_ARGUMENT;
      binder_context.add_alias_and_name(make_pair(table_alias_name, table_name));
    }
  }

  unordered_map<string, string> alias_and_name = binder_context.alias_and_name();
  // 导入父亲别名 <alias, name>
  for (auto it : father_alias) {
    // 如果父查询的表格原名出现在子查询当中，并且子查询没有单独起别名
    if (table_map.count(it.second) && !alias_and_name.count(it.first)) binder_context.add_father_alias_and_name(it);
  }
  // 如果别名和涉及的表名重复
  for (auto it = alias_and_name.begin(); it != alias_and_name.end(); it++) {
    if (table_map.count(it->first)) return RC::INVALID_ARGUMENT;
  }

  // 传给子查询的别名字典
  std::unordered_map<string, string> for_son;
  for (auto it : binder_context.alias_and_name()) for_son.insert(it);
  for (auto it : father_alias) for_son.insert(it);

  // 检测右侧子查询 STMT
  for (size_t i = 0; i < select_sql.conditions.size(); i++) {
    if (select_sql.conditions[i].right_is_sub_query) {
      auto right_sub_query = select_sql.conditions[i].right_sub_query;

      // 右子查询目前必须是 SELECT 节点
      if (right_sub_query->flag != SCF_SELECT) {
        LOG_WARN("invalid argument. sub query is not select. index=%d", i);
        return RC::INVALID_ARGUMENT;
      }

      Stmt *right_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, right_sub_query->selection, right_sub_query_stmt, for_son);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create right sub query stmt. index=%d", i);
        return rc;
      }

      // 把生成的stmt回传给上一级ConditonSqlNode
      auto *sub_select_stmt = dynamic_cast<SelectStmt *>(right_sub_query_stmt);
      select_sql.conditions[i].right_sub_query_stmt = sub_select_stmt;
    }

    // 检测左侧子查询 STMT
    if (select_sql.conditions[i].left_is_sub_query) {
      auto left_sub_query = select_sql.conditions[i].left_sub_query;
      // 左子查询目前必须是select
      if (left_sub_query->flag != SCF_SELECT) {
        LOG_WARN("invalid argument. sub query is not select. index=%d", i);
        return RC::INVALID_ARGUMENT;
      }

      Stmt *left_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, left_sub_query->selection, left_sub_query_stmt, for_son);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create right sub query stmt. index=%d", i);
        return rc;
      }

      // 把生成的stmt回传给上一级ConditonSqlNode
      auto *sub_select_stmt = dynamic_cast<SelectStmt *>(left_sub_query_stmt);
      select_sql.conditions[i].left_sub_query_stmt = sub_select_stmt;
    }
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
