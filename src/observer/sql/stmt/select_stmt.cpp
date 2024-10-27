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

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, std::unordered_map<string, string> father_alias,
                      std::unordered_map<string, Table *> father_tables) {
  if (nullptr == db) return RC::INVALID_ARGUMENT;

  // * 将节点中的 join 反转并添加到 conditions 以及 relations 当中
  // *    在之后的处理中，如果查询的表格有多个，就会计算全部表格的笛卡尔积
  // *    join 等价于先求笛卡尔积，然后进行选择运算
  // *    所以需要将选择条件也加进 conditions 中(目前全是 AND 运算，所以可以这么处理)
  std::reverse(select_sql.relations.begin(), select_sql.relations.end());
  std::reverse(select_sql.join.begin(), select_sql.join.end());
  for (int i = 0; i < (int)select_sql.join.size(); i++) {
    JoinTableExpr *join_table_expr = static_cast<JoinTableExpr *>(select_sql.join[i].get());
    UnboundTableExpr *table_expr = static_cast<UnboundTableExpr *>(join_table_expr->child().get());
    std::unique_ptr<Expression> temp = make_unique<UnboundTableExpr>(table_expr->table_name(), table_expr->table_alias());
    select_sql.relations.emplace_back(std::move(temp));
    for (auto condition : join_table_expr->conditions()) select_sql.conditions.emplace_back(condition);
  }

  // * 将 relatinos 中的全部表格信息录入
  // *
  // *
  // *

  vector<Table *> tables;
  unordered_map<string, Table *> table_map;
  BinderContext binder_context;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    UnboundTableExpr *expr = static_cast<UnboundTableExpr *>(select_sql.relations[i].get());
    const char *table_name = expr->table_name();
    if (nullptr == table_name) return RC::INVALID_ARGUMENT;

    // 根据表格名称找到表格，并且完成插入
    Table *table = db->find_table(table_name);
    if (nullptr == table) return RC::SCHEMA_TABLE_NOT_EXIST;

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
  }

  // 设置主表格
  Table *default_table = nullptr;
  if (tables.size() == 1) default_table = tables[0];

  // * 将 relatinos 中的全部表格别名录入
  // *
  // *
  // *

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

  // * 将父查询传递下来的全部表格别名录入
  // *
  // *
  // *

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

  // * 处理传递给子查询的 表格别名字典 + Table 字典
  // *
  // *
  // *

  // 传给子查询的别名字典
  std::unordered_map<string, string> alias_for_son;
  for (auto it : binder_context.alias_and_name()) alias_for_son.insert(it);
  for (auto it : father_alias) alias_for_son.insert(it);

  // 传给子查询的表格
  std::unordered_map<string, Table *> tables_for_son;
  for (auto it : table_map) tables_for_son.insert(it);
  for (auto it : father_tables) tables_for_son.insert(it);

  // * 构建子查询(如果有)的 STMT 对象
  // *
  // *
  // *
  // 检测右侧子查询 STMT
  for (size_t i = 0; i < select_sql.conditions.size(); i++) {
    if (select_sql.conditions[i].right_is_sub_query) {
      auto right_sub_query = select_sql.conditions[i].right_sub_query;

      // 右子查询目前必须是 SELECT 节点
      if (right_sub_query->flag != SCF_SELECT) return RC::INVALID_ARGUMENT;

      Stmt *right_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, right_sub_query->selection, right_sub_query_stmt, alias_for_son, tables_for_son);
      if (rc != RC::SUCCESS) return rc;

      // 把生成的stmt回传给上一级ConditonSqlNode
      auto *sub_select_stmt = dynamic_cast<SelectStmt *>(right_sub_query_stmt);
      select_sql.conditions[i].right_sub_query_stmt = sub_select_stmt;
    }

    // 检测左侧子查询 STMT
    if (select_sql.conditions[i].left_is_sub_query) {
      auto left_sub_query = select_sql.conditions[i].left_sub_query;
      // 左子查询目前必须是select
      if (left_sub_query->flag != SCF_SELECT) return RC::INVALID_ARGUMENT;

      Stmt *left_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, left_sub_query->selection, left_sub_query_stmt, alias_for_son, tables_for_son);
      if (rc != RC::SUCCESS) return rc;

      // 把生成的stmt回传给上一级ConditonSqlNode
      auto *sub_select_stmt = dynamic_cast<SelectStmt *>(left_sub_query_stmt);
      select_sql.conditions[i].left_sub_query_stmt = sub_select_stmt;
    }
  }

  // * 绑定查询表达式 expression
  // *
  // *
  // *

  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);

  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (rc != RC::SUCCESS) return rc;
  }

  // * 绑定 group by 表达式
  // *
  // *
  // *

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (rc != RC::SUCCESS) return rc;
  }

  // * 处理 order by 表达式
  // *    一开始的想法是，将 order by 的表达式视作 expressions 中的一员，在向父算子传递元组的时候额外做一步投影操作
  // *    但是发现目前阶段所有排序字段都是表格存在的属性，先简单写
  // *    由于有别名的影响，还需要提前将别名还原成原来的名字
  // *    当然，如果发现同一表达式被指认多次排序，取最后的指定；如果表达式不合法，报错
  std::vector<std::unique_ptr<Expression>> order_by_expressions;

  // 去除重复指定
  // std::unordered_map<string, int> check_order_by;
  // for (size_t i = 0; i < select_sql.order_by.size(); i++)
  // {
  //   auto &it = select_sql.order_by[i];
  //   if (check_order_by.count(it->name()))
  //   {
  //     select_sql.order_by.erase(select_sql.order_by.begin() + check_order_by[it->name()]);
  //     i--;
  //   }
  //   check_order_by[it->name()] = i;
  // }

  // 绑定排序表达式中的 UnboundField 表达式
  std::reverse(select_sql.order_by.begin(), select_sql.order_by.end());
  std::unordered_map<string, string> fields_alias_map = expression_binder.context().fields_alias_and_name();
  for (size_t i = 0; i < select_sql.order_by.size(); i++) {
    OrderByExpr *order_by_expr = static_cast<OrderByExpr *>(select_sql.order_by[i].get());
    UnboundFieldExpr *unbound_field_expr = static_cast<UnboundFieldExpr *>(order_by_expr->child().get());

    // 创建一个 FieldExpr
    const char *table_name = unbound_field_expr->table_name();
    const char *field_name = unbound_field_expr->field_name();

    if (is_blank(table_name)) {
      if (tables.size() != 1) return RC::SCHEMA_TABLE_NOT_EXIST;

      table_name = tables[0]->name();
      unbound_field_expr->set_table_name(table_name);
    }

    Table *table = table_map[table_name];

    if (table == nullptr) return RC::INVALID_ARGUMENT;

    const FieldMeta *field_meta = table->table_meta().field(field_name);

    if (field_meta == nullptr) {
      // 还原别名
      if (fields_alias_map.count(field_name)) {
        field_name = fields_alias_map[field_name].c_str();
        field_meta = table->table_meta().field(field_name);
      }
      if (field_meta == nullptr) return RC::INVALID_ARGUMENT;
    }

    Field *field = new Field(table, field_meta);
    field->set_asc_or_desc(order_by_expr->flag());
    std::unique_ptr<FieldExpr> field_expr = make_unique<FieldExpr>(*field);

    order_by_expressions.emplace_back(std::move(field_expr));
  }

  // * 创建选择运算的 Filter STMT 对象
  // *
  // *
  // *

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, default_table, &table_map, select_sql.conditions.data(), static_cast<int>(select_sql.conditions.size()), filter_stmt,
                             alias_for_son, tables_for_son);
  if (rc != RC::SUCCESS) return rc;

  // * 创建最终的 Select STMT 对象
  // *
  // *
  // *

  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_expressions);
  stmt = select_stmt;

  return RC::SUCCESS;
}