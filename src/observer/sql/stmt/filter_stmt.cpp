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
                      int condition_num, FilterStmt *&stmt) {
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();

  // 遍历全部谓词
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;

    // 创建单个筛选条件
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);

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
                       const FieldMeta *&field) {
  UnboundFieldExpr *field_expr = static_cast<UnboundFieldExpr *>(expression);
  string relation_name = field_expr->table_name();
  string attribute_name = field_expr->field_name();

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
    LOG_WARN("No such table: attr.relation_name: %s", relation_name.c_str());
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

RC FilterStmt::bind_filter_expr(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, unique_ptr<Expression> &expr) {
  if (expr == nullptr) return RC::INVALID_ARGUMENT;

  /*
  对于简单的 Value ValueList 表达式，不需要绑定，只需要检验日期合法性即可
  对于简单的 SubQuery 表达式，不需要绑定
  对于简单的 UnBoundField 表达式，将其绑定成 Field 表达式
  对于算术表达式，递归绑定左右两侧的表达式
  出现上述四种情况之外的情况均为非法情况
  */

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
      RC rc = expr->get_tuple_list(tuple_list);
      if (rc != RC::SUCCESS) return rc;
    } break;
    case ExprType::UNBOUND_FIELD: {
      Table *table = nullptr;
      const FieldMeta *field = nullptr;
      RC rc = get_table_and_field(db, default_table, tables, expr.get(), table, field);
      if (rc != RC::SUCCESS) return rc;
      expr = std::make_unique<FieldExpr>(table, field);
    } break;
    case ExprType::ARITHMETIC: {
      RC rc = RC::SUCCESS;
      ArithmeticExpr *arith_expr = static_cast<ArithmeticExpr *>(expr.get());
      if (arith_expr->left() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, arith_expr->left());
      }
      if (rc != RC::SUCCESS) return rc;
      if (arith_expr->right() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, arith_expr->right());
      }
      if (rc != RC::SUCCESS) return rc;
    } break;
    case ExprType::VECFUNC: {
      RC rc = RC::SUCCESS;
      VecFuncExpr *vec_func_expr = static_cast<VecFuncExpr *>(expr.get());
      if (vec_func_expr->child_left() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, vec_func_expr->child_left());
      }
      if (rc != RC::SUCCESS) return rc;
      if (vec_func_expr->child_right() != nullptr) {
        rc = bind_filter_expr(db, default_table, tables, vec_func_expr->child_right());
      }
      if (rc != RC::SUCCESS) return rc;
    } break;
    default:
      return RC::INVALID_ARGUMENT;
      break;
  }
  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const ConditionSqlNode &condition,
                                  FilterUnit *&filter_unit) {
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
  rc = bind_filter_expr(db, default_table, tables, left_expr);
  if (rc != RC::SUCCESS) return rc;
  rc = bind_filter_expr(db, default_table, tables, right_expr);
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