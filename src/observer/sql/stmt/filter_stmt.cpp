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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <common/type/date_type.h>

FilterStmt::~FilterStmt() {
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const ConditionSqlNode *conditions,
                      int condition_num, FilterStmt *&stmt, std::unordered_map<string, string> alias_map,
                      std::unordered_map<string, Table *> table_map) {
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();

  // 遍历全部谓词
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;

    // 创建单个筛选条件
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit, alias_map, table_map);

    // 查错
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }

    // 插入到筛选单元
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, Expression *expression, Table *&table,
                       const FieldMeta *&field, bool &from_father,
                       std::unordered_map<string, string> alias_map = std::unordered_map<string, string>(),
                       std::unordered_map<string, Table *> table_map = std::unordered_map<string, Table *>()) {
  UnboundFieldExpr *field_expr = static_cast<UnboundFieldExpr *>(expression);
  string relation_name = field_expr->table_name();
  string attribute_name = field_expr->field_name();

  // 如果存在别名，还原
  if (alias_map.count(relation_name)) {
    field_expr->set_table_alias(relation_name);
    field_expr->set_table_name(alias_map[relation_name]);
    relation_name = field_expr->table_name();
  }

  if (common::is_blank(relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(relation_name.c_str());
  }
  if (nullptr == table) {
    // 没找到表格，试图从父查询中寻找
    if (table_map.count(relation_name)) {
      table = table_map[relation_name];

      // 表格是从父查询传下来的，需要转化成子查询
      from_father = true;
    } else
      return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::bind_filter_expr(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, unique_ptr<Expression> &expr,
                                std::unordered_map<string, string> alias_map, std::unordered_map<string, Table *> table_map) {
  if (expr == nullptr) return RC::INVALID_ARGUMENT;

  // TODO 直接使用 expression_binder 中的函数进行

  switch (expr->type()) {
    case ExprType::VALUE: {
      Value value;
      RC rc = expr->try_get_value(value);
      if (rc != RC::SUCCESS) return rc;
      if (value.attr_type() == AttrType::DATE && !DateType::check_date(&value)) return RC::INVALID_ARGUMENT;
    } break;
    case ExprType::VALUELIST: {
      std::vector<Value> value_list;
      RC rc = expr->get_value_list(value_list);
      if (rc != RC::SUCCESS) return rc;
      for (auto it : value_list)
        if (it.attr_type() == AttrType::DATE && !DateType::check_date(&it)) return RC::INVALID_ARGUMENT;
    } break;
    case ExprType::SUBQUERY: {
      vector<vector<Value>> tuple_list;
      RC rc = expr->try_get_tuple_list(tuple_list);
      if (rc != RC::SUCCESS) return rc;
    } break;
    case ExprType::UNBOUND_FIELD: {
      Table *table = nullptr;
      const FieldMeta *field = nullptr;
      bool from_father = false;
      RC rc = get_table_and_field(db, default_table, tables, expr.get(), table, field, from_father, alias_map, table_map);
      if (rc != RC::SUCCESS) return rc;
      // 需要转化成子查询
      if (from_father == true) {
        SelectSqlNode select_sql_node;
        select_sql_node.relations.emplace_back(make_unique<UnboundTableExpr>(table->name()));
        select_sql_node.expressions.emplace_back(make_unique<UnboundFieldExpr>(table->name(), field->name()));
        Stmt *sub_query_stmt = nullptr;
        rc = SelectStmt::create(db, select_sql_node, sub_query_stmt);
        if (rc != RC::SUCCESS) return rc;
        auto *sub_select_stmt = dynamic_cast<SelectStmt *>(sub_query_stmt);
        expr = std::make_unique<SubQueryExpr>(sub_select_stmt, true);
      } else
        expr = std::make_unique<FieldExpr>(table, field);
    } break;
    case ExprType::ARITHMETIC: {
      RC rc = RC::SUCCESS;
      ArithmeticExpr *arith_expr = static_cast<ArithmeticExpr *>(expr.get());
      if (arith_expr->left() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, arith_expr->left(), alias_map, table_map);
      }
      if (rc != RC::SUCCESS) return rc;
      if (arith_expr->right() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, arith_expr->right(), alias_map, table_map);
      }
      if (rc != RC::SUCCESS) return rc;
    } break;
    case ExprType::VECFUNC: {
      RC rc = RC::SUCCESS;
      VecFuncExpr *vec_func_expr = static_cast<VecFuncExpr *>(expr.get());
      if (vec_func_expr->child_left() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, vec_func_expr->child_left(), alias_map, table_map);
      }
      if (rc != RC::SUCCESS) return rc;
      if (vec_func_expr->child_right() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, vec_func_expr->child_right(), alias_map, table_map);
      }
      if (rc != RC::SUCCESS) return rc;
    } break;
    case ExprType::UNBOUND_AGGREGATION: {
      RC rc = RC::SUCCESS;
      auto unbound_aggregate_expr = static_cast<UnboundAggregateExpr *>(expr.get());
      string name = unbound_aggregate_expr->name();
      const char *aggregate_name = unbound_aggregate_expr->aggregate_name();

      AggregateExpr::Type aggregate_type;
      rc = AggregateExpr::type_from_string(aggregate_name, aggregate_type);
      if (rc != RC::SUCCESS) return rc;

      unique_ptr<Expression> &child_expr = unbound_aggregate_expr->child();

      if (child_expr == nullptr) return RC::INVALID_ARGUMENT;

      if (child_expr->type() == ExprType::STAR && aggregate_type == AggregateExpr::Type::COUNT) {
        ValueExpr *value_expr = new ValueExpr(Value(1));
        child_expr.reset(value_expr);
      } else {
        rc = bind_filter_expr(db, default_table, tables, child_expr, alias_map, table_map);
        if (rc != RC::SUCCESS) return rc;
      }

      // TODO 校验聚合表达式
      expr = make_unique<AggregateExpr>(aggregate_type, std::move(child_expr));
      expr->set_name(name);
    } break;
    default:
      return RC::INVALID_ARGUMENT;
      break;
  }
  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const ConditionSqlNode &condition,
                                  FilterUnit *&filter_unit, std::unordered_map<string, string> alias_map,
                                  std::unordered_map<string, Table *> table_map) {
  RC rc = RC::SUCCESS;

  // 拿到比较符并且判断其合法性
  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  std::unique_ptr<Expression> left_expr(condition.left_expression);
  std::unique_ptr<Expression> right_expr(condition.right_expression);

  // 构造子查询表达式
  if (condition.left_is_sub_query) left_expr = make_unique<SubQueryExpr>(condition.left_sub_query_stmt);
  if (condition.right_is_sub_query) right_expr = make_unique<SubQueryExpr>(condition.right_sub_query_stmt);

  // 绑定表达式
  rc = bind_filter_expr(db, default_table, tables, left_expr, alias_map, table_map);
  if (rc != RC::SUCCESS) return rc;
  rc = bind_filter_expr(db, default_table, tables, right_expr, alias_map, table_map);
  if (rc != RC::SUCCESS) return rc;

  FilterObj left_obj;
  left_obj.init(std::move(left_expr));
  FilterObj right_obj;
  right_obj.init(std::move(right_expr));

  filter_unit->set_left(left_obj);
  filter_unit->set_right(right_obj);

  // 设置比较符
  filter_unit->set_comp(comp);

  return rc;
}