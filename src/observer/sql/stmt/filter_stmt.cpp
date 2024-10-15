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

  Expression *left_expr = condition.left_expression;
  Expression *right_expr = condition.right_expression;

  Value left_value, right_value;
  bool left_is_value = false, right_is_value = false;

  ///////////////////////////////////////////////////////////////////
  // left_expr 为 UnboundFieldExpr 时，代表该表达式为属性
  // 此时，try_get_value() 返回 RC::UNIMPLEMENTED
  //
  // left_expr 为 其他表达式 时，代表该表达式最终算出来的是一个 Value
  // 此时，try_get_value() 可以拿到算出来的 Value 对象
  ///////////////////////////////////////////////////////////////////

  // 左侧不是子查询
  if (condition.left_is_sub_query == 0 && condition.left_expression != nullptr && condition.left_expression->type() != ExprType::VALUELIST) {
    left_is_value = OB_SUCC(condition.left_expression->try_get_value(left_value));
  }

  // 右侧不是子查询
  if (condition.right_is_sub_query == 0 && condition.right_expression->type() != ExprType::VALUELIST) {
    right_is_value = OB_SUCC(right_expr->try_get_value(right_value));
  }

  // 判断日期合法性
  if (left_is_value && left_value.attr_type() == AttrType::DATE) {
    if (!DateType::check_date(left_value.get_date())) return RC::INVALID_ARGUMENT;
  }
  if (right_is_value && right_value.attr_type() == AttrType::DATE) {
    if (!DateType::check_date(right_value.get_date())) return RC::INVALID_ARGUMENT;
  }

  // 创建左 filterObj
  // sub_select
  if (condition.left_is_sub_query) {
    FilterObj filter_obj;
    filter_obj.init_sub_query(condition.left_sub_query_stmt);
    filter_unit->set_left(filter_obj);
  }
  // Value
  else if (left_is_value) {
    FilterObj filter_obj;
    filter_obj.init_value(left_value);
    filter_unit->set_left(filter_obj);
  }
  // list
  else if (left_expr->type() == ExprType::VALUELIST) {
    FilterObj filter_obj;
    std::vector<Value> value_list;
    condition.left_expression->get_value_list(value_list);
    filter_obj.init_list(value_list);
    filter_unit->set_left(filter_obj);
  }
  // Attribute
  else {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, left_expr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }

    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
  }

  // 创建右 filterObj
  // sub_select
  if (condition.right_is_sub_query) {
    FilterObj filter_obj;
    filter_obj.init_sub_query(condition.right_sub_query_stmt);
    filter_unit->set_right(filter_obj);
  }
  // Value
  else if (right_is_value) {
    FilterObj filter_obj;
    filter_obj.init_value(right_value);
    filter_unit->set_right(filter_obj);
  }
  // list
  else if (right_expr->type() == ExprType::VALUELIST) {
    FilterObj filter_obj;
    std::vector<Value> value_list;
    condition.right_expression->get_value_list(value_list);
    filter_obj.init_list(value_list);
    filter_unit->set_right(filter_obj);
  }
  // Attribute
  else {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, right_expr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }

    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
  }

  // 设置比较符
  filter_unit->set_comp(comp);

  return rc;
}