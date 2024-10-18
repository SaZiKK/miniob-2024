/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>
#include <memory>

#include "common/type/attr_type.h"
#include "sql/expr/expression.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"

#include "sql/optimizer/physical_plan_generator.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

#include "sql/expr/expression_iterator.h"

using namespace std;
using namespace common;

class UpdateTarget;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator) {
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    // 添加 update 对应分支
    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);

      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLEMENTED;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  unique_ptr<LogicalOperator> *last_oper = nullptr;

  unique_ptr<LogicalOperator> table_oper(nullptr);
  last_oper = &table_oper;

  // 获取涉及表格并遍历
  const std::vector<Table *> &tables = select_stmt->tables();
  for (Table *table : tables) {
    // 创建 TableGet 逻辑算子
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    // 第一张表格
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    }
    // 之后的表格，创建 Join 算子
    else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  // 创建 Predicate 逻辑算子
  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  // 创建 GroupBy 逻辑算子
  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }

  // 创建 Projection 逻辑算子
  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  RC rc = RC::SUCCESS;
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    unique_ptr<Expression> left(filter_obj_left.is_attr        ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                : filter_obj_left.is_value     ? static_cast<Expression *>(new ValueExpr(filter_obj_left.value))
                                : filter_obj_left.is_sub_query ? static_cast<Expression *>(new SubQueryExpr(filter_obj_left.sub_query))
                                                               : static_cast<Expression *>(new ValueListExpr(filter_obj_left.value_list)));

    unique_ptr<Expression> right(filter_obj_right.is_attr        ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
                                 : filter_obj_right.is_value     ? static_cast<Expression *>(new ValueExpr(filter_obj_right.value))
                                 : filter_obj_right.is_sub_query ? static_cast<Expression *>(new SubQueryExpr(filter_obj_right.sub_query))
                                                                 : static_cast<Expression *>(new ValueListExpr(filter_obj_right.value_list)));

    bool need_value_cast = left->value_type() != AttrType::SUB_QUERY && right->value_type() != AttrType::SUB_QUERY &&
                           left->type() != ExprType::VALUELIST && right->type() != ExprType::VALUELIST &&
                           filter_unit->comp() != CompOp::XXX_IS_NULL && filter_unit->comp() != CompOp::XXX_IS_NOT_NULL;

    // 如果左右两边的类型不一致，需要先计算转换开销，再进行隐式类型转换，同时要排除有子查询的情况
    if (need_value_cast) {
      Value left_value, right_value;
      left->try_get_value(left_value);
      right->try_get_value(right_value);
      if (!left_value.get_null() && !right_value.get_null() && left->value_type() != right->value_type()) {
        auto left_to_right_cost = implicit_cast_cost(left->value_type(), right->value_type());
        auto right_to_left_cost = implicit_cast_cost(right->value_type(), left->value_type());
        if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
          ExprType left_type = left->type();

          // 特殊判断，如果为 INTS 和 CHARS 比较大小，均转换成 FLOATS 类型
          unique_ptr<CastExpr> cast_expr;
          if (left->value_type() == AttrType::CHARS && right->value_type() == AttrType::INTS)
            cast_expr = make_unique<CastExpr>(std::move(left), AttrType::FLOATS);
          else
            cast_expr = make_unique<CastExpr>(std::move(left), right->value_type());
          if (left_type == ExprType::VALUE) {
            Value left_val;
            if (OB_FAIL(rc = cast_expr->try_get_value(left_val))) {
              LOG_WARN("failed to get value from left child", strrc(rc));
              return rc;
            }
            left = make_unique<ValueExpr>(left_val);
          } else {
            left = std::move(cast_expr);
          }
        } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
          ExprType right_type = right->type();

          // 特殊判断，如果为 INTS 和 CHARS 比较大小，均转换成 FLOATS 类型
          unique_ptr<CastExpr> cast_expr;
          if (left->value_type() == AttrType::INTS && right->value_type() == AttrType::CHARS)
            cast_expr = make_unique<CastExpr>(std::move(right), AttrType::FLOATS);
          else
            cast_expr = make_unique<CastExpr>(std::move(right), left->value_type());

          if (right_type == ExprType::VALUE) {
            Value right_val;
            if (OB_FAIL(rc = cast_expr->try_get_value(right_val))) {
              LOG_WARN("failed to get value from right child", strrc(rc));
              return rc;
            }
            right = make_unique<ValueExpr>(right_val);
          } else {
            right = std::move(cast_expr);
          }
        } else if (filter_unit->comp() == CompOp::LIKE_XXX || filter_unit->comp() == CompOp::NOT_LIKE_XXX) {
          ExprType right_type = right->type();

          // 如果执行LIKE运算符，把右边转化成CHARS类型
          unique_ptr<CastExpr> cast_expr;
          cast_expr = make_unique<CastExpr>(std::move(right), AttrType::CHARS);

          if (right_type == ExprType::VALUE) {
            Value right_val;
            if (OB_FAIL(rc = cast_expr->try_get_value(right_val))) {
              LOG_WARN("failed to get value from right child", strrc(rc));
              return rc;
            }
            right = make_unique<ValueExpr>(right_val);
          } else {
            right = std::move(cast_expr);
          }
        } else {
          rc = RC::UNSUPPORTED;
          LOG_WARN("unsupported cast from %s to %s", attr_type_to_string(left->value_type()), attr_type_to_string(right->value_type()));
          return rc;
        }
      }
    }
    if (filter_obj_right.is_sub_query) {
      // 创建右子查询的逻辑算子
      LogicalPlanGenerator sub_logical_plan_generator_;
      PhysicalPlanGenerator sub_physical_plan_generator_;
      unique_ptr<LogicalOperator> temp_sub_logical_operator;
      unique_ptr<PhysicalOperator> temp_sub_physical_operator;
      SelectStmt *sub_stmt = filter_obj_right.sub_query;
      // 创建子查询的逻辑算子，这里实际上是递归的创建
      RC rc = sub_logical_plan_generator_.create(sub_stmt, temp_sub_logical_operator);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create sub logical plan. rc=%s", strrc(rc));
        return rc;
      }
      // 创建子查询的物理算子
      rc = sub_physical_plan_generator_.create(*temp_sub_logical_operator, temp_sub_physical_operator);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create sub physical plan. rc=%s", strrc(rc));
        return rc;
      }
      // 创建带有自定义删除器的 unique_ptr
      auto sub_logical_operator =
          std::unique_ptr<LogicalOperator, void (*)(LogicalOperator *)>(temp_sub_logical_operator.release(), [](LogicalOperator *p) { delete p; });
      auto sub_physical_operator = std::unique_ptr<PhysicalOperator, void (*)(PhysicalOperator *)>(temp_sub_physical_operator.release(),
                                                                                                   [](PhysicalOperator *p) { delete p; });
      // 把父类对象强转一下，方便我调用子类专属的方法
      unique_ptr<SubQueryExpr> sub_query_expr(dynamic_cast<SubQueryExpr *>(right.release()));
      // 设置逻辑和物理操作符
      sub_query_expr->set_logical_operator(std::move(sub_logical_operator));
      sub_query_expr->set_physical_operator(std::move(sub_physical_operator));
      // 归还所有权，便于下一步操作
      right = std::move(sub_query_expr);
    }
    if (filter_obj_left.is_sub_query) {
      // 创建左子查询的逻辑算子
      LogicalPlanGenerator sub_logical_plan_generator_;
      PhysicalPlanGenerator sub_physical_plan_generator_;
      unique_ptr<LogicalOperator> temp_sub_logical_operator;
      unique_ptr<PhysicalOperator> temp_sub_physical_operator;
      SelectStmt *sub_stmt = filter_obj_left.sub_query;
      // 创建子查询的逻辑算子，这里实际上是递归的创建
      RC rc = sub_logical_plan_generator_.create(sub_stmt, temp_sub_logical_operator);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create sub logical plan. rc=%s", strrc(rc));
        return rc;
      }
      // 创建子查询的物理算子
      rc = sub_physical_plan_generator_.create(*temp_sub_logical_operator, temp_sub_physical_operator);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create sub physical plan. rc=%s", strrc(rc));
        return rc;
      }
      // 创建带有自定义删除器的 unique_ptr
      auto sub_logical_operator =
          std::unique_ptr<LogicalOperator, void (*)(LogicalOperator *)>(temp_sub_logical_operator.release(), [](LogicalOperator *p) { delete p; });
      auto sub_physical_operator = std::unique_ptr<PhysicalOperator, void (*)(PhysicalOperator *)>(temp_sub_physical_operator.release(),
                                                                                                   [](PhysicalOperator *p) { delete p; });
      // 把父类对象强转一下，方便我调用子类专属的方法
      unique_ptr<SubQueryExpr> sub_query_expr(dynamic_cast<SubQueryExpr *>(left.release()));
      sub_query_expr->set_logical_operator(std::move(sub_logical_operator));
      sub_query_expr->set_physical_operator(std::move(sub_physical_operator));
      // 归还所有权，便于下一步操作
      left = std::move(sub_query_expr);
    }

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return rc;
}

int LogicalPlanGenerator::implicit_cast_cost(AttrType from, AttrType to) {
  if (from == to) {
    return 0;
  }
  return DataType::type_instance(from)->cast_cost(to);
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Table *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  Table *table = delete_stmt->table();
  FilterStmt *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  // 拿到相关变量
  Table *table = update_stmt->table();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();

  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;
  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 创建逻辑算子
  std::vector<std::pair<Value, FieldMeta>> update_map;
  for (int i = 0; i < (int)update_stmt->update_targets().size(); i++) {
    Value value = update_stmt->update_targets()[i].value;
    FieldMeta field_meta = update_stmt->field_metas()[i];
    update_map.push_back(make_pair(value, field_meta));
  }
  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, update_map));
  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_group_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  vector<unique_ptr<Expression>> &group_by_expressions = select_stmt->group_by();
  vector<Expression *> aggregate_expressions;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  function<RC(std::unique_ptr<Expression> &)> collector = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression> &)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(i);
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

  bool found_unbound_column = false;
  function<RC(std::unique_ptr<Expression> &)> find_unbound_column = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    } else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  if (found_unbound_column) {
    LOG_WARN(
        "column must appear in the GROUP BY clause or must be part of an "
        "aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper = make_unique<GroupByLogicalOperator>(std::move(group_by_expressions), std::move(aggregate_expressions));
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}