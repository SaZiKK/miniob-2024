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

// ? 相较于原本的 create 函数新增加了两个参数，father_alias 代表父查询中定义的别名，father_tables 代表父查询中包含的表格
// ? 表格在父查询中定义和在子查询中定义是不一样的
RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, bool &use_father_table_flags, unordered_map<string, string> father_alias,
                      unordered_map<string, Table *> father_tables) {
  if (nullptr == db) return RC::INVALID_ARGUMENT;

  // *****************************************************************************
  // * 将节点中的 join 反转并添加到 conditions 以及 relations 当中
  // *    在之后的处理中，如果查询的表格有多个，就会计算全部表格的笛卡尔积
  // *    join 等价于先求笛卡尔积，然后进行选择运算
  // *    所以需要将选择条件也加进 conditions 中(目前全是 AND 运算，所以可以这么处理)

  // TODO DANNGER JOIN 支持别名
  for (size_t i = 0; i < select_sql.join.size(); i++) {
    JoinTableExpr *join_table_expr = static_cast<JoinTableExpr *>(select_sql.join[i].get());
    UnboundTableExpr *table_expr = static_cast<UnboundTableExpr *>(join_table_expr->child().get());
    unique_ptr<Expression> temp = make_unique<UnboundTableExpr>(table_expr->table_name(), table_expr->table_alias());
    select_sql.relations.emplace_back(move(temp));
    for (auto condition : join_table_expr->conditions()) select_sql.conditions.emplace_back(condition);
  }

  // *****************************************************************************
  // * 将 relatinos 中的全部表格信息录入
  // * 将 relations 中的全部表格别名录入
  // * 对于不合法的别名进行判断
  // *

  vector<Table *> tables;
  unordered_map<string, Table *> table_map;
  BinderContext binder_context;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    Expression *expr = select_sql.relations[i].get();
    if (expr == nullptr) return RC::INVALID_ARGUMENT;

    // ? 对于表格表达式，目前只可能出现 ALIAS UNBOUNDTABLE 两种表达式，分别对应有别名的表格和无别名的表格
    // ? 如果不属于任何一种表达式，报错
    string table_alias_name;
    string table_name;
    if (expr->type() == ExprType::ALIAS) {
      AliasExpr *alias_expr = static_cast<AliasExpr *>(expr);
      UnboundTableExpr *table_expr = static_cast<UnboundTableExpr *>(alias_expr->child().get());

      table_alias_name = alias_expr->alias_name();
      table_name = table_expr->table_name();

      if (binder_context.t_alias().count(table_alias_name)) return RC::INVALID_ARGUMENT;
      if (table_map.count(table_alias_name)) return RC::INVALID_ARGUMENT;
      binder_context.add_t_alias(make_pair(table_alias_name, table_name));
    } else if (expr->type() == ExprType::UNBOUND_TABLE) {
      UnboundTableExpr *table_expr = static_cast<UnboundTableExpr *>(select_sql.relations[i].get());
      table_name = table_expr->table_name();
    } else
      return RC::INVALID_ARGUMENT;
    if (table_name.empty()) return RC::INVALID_ARGUMENT;

    Table *table = db->find_table(table_name.c_str());
    if (nullptr == table) return RC::SCHEMA_TABLE_NOT_EXIST;

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
  }

  Table *default_table = nullptr;
  if (tables.size() == 1) default_table = tables[0];

  // *****************************************************************************
  // * 将父查询传递下来的全部表格别名录入
  // *
  // *
  // *

  unordered_map<string, string> alias_and_name = binder_context.t_alias();
  for (auto it : father_alias) {
    // ? 如果父查询的表格原名出现在子查询中，并且子查询没有单独起别名
    // ? 注意，这里只能单纯继承父查询的表格别名，并不能满足复杂子查询中的关联问题，也即没办法传递实际的表格
    if (table_map.count(it.second) && !alias_and_name.count(it.first)) binder_context.add_fa_t_alias(it);
  }

  // *****************************************************************************
  // * 处理传递给子查询的 表格别名字典 + Table 字典
  // *
  // *
  // *

  // ? table alias
  unordered_map<string, string> alias_for_son;
  for (auto it : binder_context.t_alias()) alias_for_son.insert(it);
  for (auto it : father_alias) alias_for_son.insert(it);

  // ? table self
  unordered_map<string, Table *> tables_for_son;
  for (auto it : table_map) tables_for_son.insert(it);
  for (auto it : father_tables) tables_for_son.insert(it);

  // *****************************************************************************
  // * 构建子查询(如果有)的 STMT 对象
  // *
  // *
  // *

  // ? 父查询相关标志
  bool left_flag = false;
  bool right_flag = false;
  for (size_t i = 0; i < select_sql.conditions.size(); i++) {
    // ? right sub select stmt
    if (select_sql.conditions[i].right_is_sub_query) {
      auto right_sub_query = select_sql.conditions[i].right_sub_query;

      if (right_sub_query->flag != SCF_SELECT) return RC::INVALID_ARGUMENT;

      Stmt *right_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, right_sub_query->selection, right_sub_query_stmt, right_flag, alias_for_son, tables_for_son);
      if (rc != RC::SUCCESS) return rc;

      // ? 把生成的 Stmt 回传给上一级 ConditonSqlNode
      auto sub_select_stmt = dynamic_cast<SelectStmt *>(right_sub_query_stmt);
      select_sql.conditions[i].right_sub_query_stmt = sub_select_stmt;
    }

    // ? left sub select stmt
    if (select_sql.conditions[i].left_is_sub_query) {
      auto left_sub_query = select_sql.conditions[i].left_sub_query;

      if (left_sub_query->flag != SCF_SELECT) return RC::INVALID_ARGUMENT;

      Stmt *left_sub_query_stmt = nullptr;
      RC rc = SelectStmt::create(db, left_sub_query->selection, left_sub_query_stmt, left_flag, alias_for_son, tables_for_son);
      if (rc != RC::SUCCESS) return rc;

      // ? 把生成的 Stmt 回传给上一级 ConditonSqlNode
      auto sub_select_stmt = dynamic_cast<SelectStmt *>(left_sub_query_stmt);
      select_sql.conditions[i].left_sub_query_stmt = sub_select_stmt;
    }
    select_sql.conditions[i].left_use_father = left_flag;
    select_sql.conditions[i].right_use_father = right_flag;
  }

  // *****************************************************************************
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

  // *****************************************************************************
  // * 绑定 group by 表达式
  // *
  // *
  // *

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (rc != RC::SUCCESS) return rc;
  }

  // *****************************************************************************
  // * 处理 order by 表达式
  // *    一开始的想法是，将 order by 的表达式视作 expressions 中的一员，在向父算子传递元组的时候额外做一步投影操作
  // *    但是发现目前阶段所有排序字段都是表格存在的属性，先简单写
  // *    由于有别名的影响，还需要提前将别名还原成原来的名字
  // *    当然，如果发现同一表达式被指认多次排序，取最后的指定；如果表达式不合法，报错

  vector<unique_ptr<Expression>> order_by_expressions;

  // TODO INFO 去除重复指定

  unordered_map<string, string> fields_alias_map = expression_binder.context().f_alias();
  unordered_map<string, string> tables_alias_map = expression_binder.context().t_alias();
  for (size_t i = 0; i < select_sql.order_by.size(); i++) {
    OrderByExpr *order_by_expr = static_cast<OrderByExpr *>(select_sql.order_by[i].get());
    Expression *expr = order_by_expr->child().get();

    // ? 同样的，对于排序字段，只能是 ALIAS UNBOUNDFIELD 两种表达式类型
    string table_name;
    string field_name;

    UnboundFieldExpr *unbound_field_expr;

    if (expr->type() == ExprType::ALIAS) {
      AliasExpr *alias_expr = static_cast<AliasExpr *>(expr);
      unbound_field_expr = static_cast<UnboundFieldExpr *>(alias_expr->child().get());
      table_name = unbound_field_expr->table_name();
      field_name = unbound_field_expr->field_name();
    } else if (expr->type() == ExprType::UNBOUND_FIELD) {
      unbound_field_expr = static_cast<UnboundFieldExpr *>(expr);
      table_name = unbound_field_expr->table_name();
      field_name = unbound_field_expr->field_name();
    } else
      return RC::INVALID_ARGUMENT;

    // ? 还原表格和属性的名称
    if (fields_alias_map.count(field_name)) {
      field_name = fields_alias_map[field_name];
    }
    if (tables_alias_map.count(table_name)) {
      table_name = tables_alias_map[table_name];
    }

    if (is_blank(table_name.c_str())) {
      if (tables.size() != 1) return RC::SCHEMA_TABLE_NOT_EXIST;

      table_name = tables[0]->name();
      unbound_field_expr->set_table_name(table_name);
    }

    Table *table = table_map[table_name];

    if (table == nullptr) return RC::INVALID_ARGUMENT;

    const FieldMeta *field_meta = table->table_meta().field(field_name.c_str());

    if (field_meta == nullptr) return RC::INVALID_ARGUMENT;

    Field *field = new Field(table, field_meta);
    field->set_asc_or_desc(order_by_expr->flag());
    unique_ptr<FieldExpr> field_expr = make_unique<FieldExpr>(*field);

    order_by_expressions.emplace_back(move(field_expr));
  }

  // *****************************************************************************
  // * 创建选择运算的 Filter STMT 对象
  // *
  // *
  // *

  FilterStmt *filter_stmt = nullptr;
  FilterStmt *having_fliter_stmt = nullptr;
  RC rc = FilterStmt::create(db, default_table, &table_map, select_sql.conditions.data(), static_cast<int>(select_sql.conditions.size()), filter_stmt,
                             use_father_table_flags, alias_for_son, tables_for_son);
  if (rc != RC::SUCCESS) return rc;

  rc = FilterStmt::create(db, default_table, &table_map, select_sql.having_conditions.data(), static_cast<int>(select_sql.having_conditions.size()),
                          having_fliter_stmt, use_father_table_flags, alias_for_son, tables_for_son);
  if (rc != RC::SUCCESS) return rc;

  // *****************************************************************************
  // * 创建最终的 Select STMT 对象
  // *
  // *
  // *

  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->having_filter_stmt_ = having_fliter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_expressions);
  stmt = select_stmt;

  return RC::SUCCESS;
}