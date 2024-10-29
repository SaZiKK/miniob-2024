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
// Created by Wangyunlai on 2024/05/29.
//

#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/expression_binder.h"
#include "sql/expr/expression_iterator.h"

using namespace std;
using namespace common;

Table *BinderContext::find_table(const char *table_name) const {
  auto pred = [table_name](Table *table) { return 0 == strcasecmp(table_name, table->name()); };
  auto iter = ranges::find_if(query_tables_, pred);
  if (iter == query_tables_.end()) {
    return nullptr;
  }
  return *iter;
}

////////////////////////////////////////////////////////////////////////////////
static void wildcard_fields(Table *table, vector<unique_ptr<Expression>> &expressions) {
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    Field field(table, table_meta.field(i));
    FieldExpr *field_expr = new FieldExpr(field);
    field_expr->set_name(field.field_name());
    expressions.emplace_back(field_expr);
  }
}

RC ExpressionBinder::bind_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  switch (expr->type()) {
    case ExprType::STAR: {
      return bind_star_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_FIELD: {
      return bind_unbound_field_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_AGGREGATION: {
      return bind_aggregate_expression(expr, bound_expressions);
    } break;

    case ExprType::FIELD: {
      return bind_field_expression(expr, bound_expressions);
    } break;

    case ExprType::VALUE: {
      return bind_value_expression(expr, bound_expressions);
    } break;

    case ExprType::CAST: {
      return bind_cast_expression(expr, bound_expressions);
    } break;

    case ExprType::COMPARISON: {
      return bind_comparison_expression(expr, bound_expressions);
    } break;

    case ExprType::CONJUNCTION: {
      return bind_conjunction_expression(expr, bound_expressions);
    } break;

    case ExprType::ARITHMETIC: {
      return bind_arithmetic_expression(expr, bound_expressions);
    } break;

    case ExprType::AGGREGATION: {
      ASSERT(false, "shouldn't be here");
    } break;

    case ExprType::FUNC: {
      return bind_func_expression(expr, bound_expressions);
    } break;

    case ExprType::VECFUNC: {
      return bind_vec_func_expression(expr, bound_expressions);
    } break;

    default: {
      LOG_WARN("unknown expression type: %d", static_cast<int>(expr->type()));
      return RC::INTERNAL;
    }
  }
  return RC::INTERNAL;
}

RC ExpressionBinder::bind_star_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto star_expr = static_cast<StarExpr *>(expr.get());

  vector<Table *> tables_to_wildcard;

  const char *table_name = star_expr->table_name();
  if (!is_blank(table_name) && 0 != strcmp(table_name, "*")) {
    Table *table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables_to_wildcard.push_back(table);
  } else {
    const vector<Table *> &all_tables = context_.query_tables();
    tables_to_wildcard.insert(tables_to_wildcard.end(), all_tables.begin(), all_tables.end());
  }

  for (Table *table : tables_to_wildcard) {
    wildcard_fields(table, bound_expressions);
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_unbound_field_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expr.get());

  const char *table_name = unbound_field_expr->table_name();
  const char *field_name = unbound_field_expr->field_name();
  const char *field_alias = unbound_field_expr->field_alias();

  if (unbound_field_expr->has_field_alias()) context_.add_fields_alias_and_name(std::make_pair(field_alias, field_name));

  Table *table = nullptr;
  // 如果属性列表不是 table_name.attr_name
  // 的形式，table_name 为空，此时如果目标表格为多个则返回错误结果
  if (is_blank(table_name)) {
    if (context_.query_tables().size() != 1) {
      LOG_INFO("cannot determine table for field: %s", field_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    table = context_.query_tables()[0];
  }
  // 如果属性列表是 table_name.attr_name 的形式，table_name
  // 不为空，此时如果目标表格中不存在 table_name 则返回错误结果
  else {
    std::unordered_map<std::string, std::string> alias_map = context_.alias_and_name();
    std::unordered_map<std::string, std::string> father_alias_map = context_.father_alias_and_name();
    // table_name 实际上是别名，需要还原
    if (alias_map.count(table_name)) {
      unbound_field_expr->set_table_alias(table_name);
      unbound_field_expr->set_table_name(alias_map[table_name]);
      table_name = unbound_field_expr->table_name();
    } else if (father_alias_map.count(table_name)) {
      unbound_field_expr->set_table_alias(table_name);
      unbound_field_expr->set_table_name(father_alias_map[table_name]);
      table_name = unbound_field_expr->table_name();
    } else {
      // 如果当前层有别名但是不用，返回错误
      for (auto it = alias_map.begin(); it != alias_map.end(); it++)
        if (it->second == table_name) return RC::INVALID_ARGUMENT;
    }
    table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  }

  // 如果属性列表是通配符，则遍历表格的全部属性
  if (0 == strcmp(field_name, "*")) {
    wildcard_fields(table, bound_expressions);
  } else {
    // 根据 Field 的名称找到对应的 FieldMeta 对象
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_INFO("no such field in table: %s.%s", table_name, field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // 通过表格和 FieldMeta 对象创建 Field 对象，进而创建 FieldExpr 表达式
    Field field(table, field_meta);
    // 设置别名信息
    if (unbound_field_expr->has_field_alias()) field.set_field_alias(unbound_field_expr->field_alias());
    if (unbound_field_expr->has_table_alias()) field.set_table_alias(unbound_field_expr->table_alias());

    FieldExpr *field_expr = new FieldExpr(field);
    // 需要同时输出表格名称和属性名称
    if ((int)context_.query_tables().size() > 1) {
      string result;
      // 有表格别名?
      result += field.has_table_alias() ? string(field.table_alias()) : string(field.table_name());
      result += '.';
      // 有属性别名?
      result += field.has_field_alias() ? string(field.field_alias()) : string(field.field_name());
      field_expr->set_name(result.c_str());
    }
    // 只用输出属性名称
    else {
      string result;
      // 有属性别名?
      result += field.has_field_alias() ? string(field.field_alias()) : string(field.field_name());
      field_expr->set_name(result.c_str());
    }
    bound_expressions.emplace_back(field_expr);
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_field_expression(unique_ptr<Expression> &field_expr, vector<unique_ptr<Expression>> &bound_expressions) {
  bound_expressions.emplace_back(std::move(field_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_value_expression(unique_ptr<Expression> &value_expr, vector<unique_ptr<Expression>> &bound_expressions) {
  bound_expressions.emplace_back(std::move(value_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_cast_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto cast_expr = static_cast<CastExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression> &child_expr = cast_expr->child();

  RC rc = bind_expression(child_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid children number of cast expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &child = child_bound_expressions[0];
  if (child.get() == child_expr.get()) {
    return RC::SUCCESS;
  }

  child_expr.reset(child.release());
  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_comparison_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression> &left_expr = comparison_expr->left();
  unique_ptr<Expression> &right_expr = comparison_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) {
    right_expr.reset(right.release());
  }

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_conjunction_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  vector<unique_ptr<Expression>> &children = conjunction_expr->children();

  for (unique_ptr<Expression> &child_expr : children) {
    child_bound_expressions.clear();

    RC rc = bind_expression(child_expr, child_bound_expressions);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of conjunction expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    unique_ptr<Expression> &child = child_bound_expressions[0];
    if (child.get() != child_expr.get()) {
      child_expr.reset(child.release());
    }
  }

  bound_expressions.emplace_back(std::move(expr));

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_arithmetic_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto arithmetic_expr = static_cast<ArithmeticExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression> &left_expr = arithmetic_expr->left();
  unique_ptr<Expression> &right_expr = arithmetic_expr->right();
  string op = arithmetic_expr->type_to_string();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (left_expr != nullptr && child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (right_expr != nullptr && child_bound_expressions.size() != 1) {
    LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) {
    right_expr.reset(right.release());
  }

  string left_name = left_expr == nullptr ? "" : string(left_expr->name()) + " ";
  string right_name = right_expr == nullptr ? "" : " " + string(right_expr->name());
  expr->set_name(left_name + op + right_name);

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC check_aggregate_expression(AggregateExpr &expression) {
  // 必须有一个子表达式
  Expression *child_expression = expression.child().get();
  if (nullptr == child_expression) {
    LOG_WARN("child expression of aggregate expression is null");
    return RC::INVALID_ARGUMENT;
  }

  // 校验数据类型与聚合类型是否匹配
  AggregateExpr::Type aggregate_type = expression.aggregate_type();
  AttrType child_value_type = child_expression->value_type();
  switch (aggregate_type) {
    case AggregateExpr::Type::SUM:
    case AggregateExpr::Type::AVG: {
      // 仅支持数值类型
      if (child_value_type != AttrType::INTS && child_value_type != AttrType::FLOATS) {
        LOG_WARN("invalid child value type for aggregate expression: %d", static_cast<int>(child_value_type));
        return RC::INVALID_ARGUMENT;
      }
    } break;

    case AggregateExpr::Type::COUNT:
    case AggregateExpr::Type::MAX:
    case AggregateExpr::Type::MIN: {
      // 任何类型都支持
    } break;
  }

  // 子表达式中不能再包含聚合表达式
  function<RC(std::unique_ptr<Expression> &)> check_aggregate_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      LOG_WARN("aggregate expression cannot be nested");
      return RC::INVALID_ARGUMENT;
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, check_aggregate_expr);
    return rc;
  };

  RC rc = ExpressionIterator::iterate_child_expr(expression, check_aggregate_expr);

  return rc;
}

RC ExpressionBinder::bind_aggregate_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  // 拿到聚合表达式 UnboundAggregateExpr
  auto unbound_aggregate_expr = static_cast<UnboundAggregateExpr *>(expr.get());

  // 拿到聚合表达式中的聚合函数名
  const char *aggregate_name = unbound_aggregate_expr->aggregate_name();

  // 聚合函数名转换为聚合类型
  AggregateExpr::Type aggregate_type;
  RC rc = AggregateExpr::type_from_string(aggregate_name, aggregate_type);
  if (OB_FAIL(rc)) {
    LOG_WARN("invalid aggregate name: %s", aggregate_name);
    return rc;
  }

  // 拿到聚合表达式中的子表达式
  unique_ptr<Expression> &child_expr = unbound_aggregate_expr->child();
  vector<unique_ptr<Expression>> child_bound_expressions;

  // 如果子表达式为空指针，返回错误结果
  if (child_expr == nullptr) return RC::INVALID_ARGUMENT;

  // 如果子表达式为通配符并且聚合函数为 COUNT
  if (child_expr->type() == ExprType::STAR && aggregate_type == AggregateExpr::Type::COUNT) {
    ValueExpr *value_expr = new ValueExpr(Value(1));
    child_expr.reset(value_expr);
  }
  // 其他情况
  else {
    // 递归绑定其他子表达式
    rc = bind_expression(child_expr, child_bound_expressions);
    if (OB_FAIL(rc)) {
      return rc;
    }

    // 如果子表达式过多或过少，返回错误信息
    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of aggregate expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    // 如果子表达式不为原子表达式，重置子表达式并释放原子表达式对应部分
    if (child_bound_expressions[0].get() != child_expr.get()) {
      child_expr.reset(child_bound_expressions[0].release());
    }
  }

  // 创建聚合表达式
  auto aggregate_expr = make_unique<AggregateExpr>(aggregate_type, std::move(child_expr));
  aggregate_expr->set_name(unbound_aggregate_expr->name());

  // 校验聚合表达式
  rc = check_aggregate_expression(*aggregate_expr);
  if (OB_FAIL(rc)) {
    return rc;
  }

  // 将聚合表达式添加到输出参数
  bound_expressions.emplace_back(std::move(aggregate_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_func_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  // 将 FUNC 表达式计算出来，生成 Value 表达式
  FuncExpr *func_expr = static_cast<FuncExpr *>(expr.get());
  Value target;
  RC rc = func_expr->try_get_value(target);
  if (rc != RC::SUCCESS) return rc;

  unique_ptr<Expression> value_expr(new ValueExpr(target));
  value_expr.get()->set_name(target.to_string());

  return bind_value_expression(value_expr, bound_expressions);
}

RC ExpressionBinder::bind_vec_func_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }
  VecFuncExpr *vec_func_expr = static_cast<VecFuncExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression> &left_expr = vec_func_expr->child_left();
  unique_ptr<Expression> &right_expr = vec_func_expr->child_right();

  // left
  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) return rc;
  if (left_expr != nullptr && child_bound_expressions.size() != 1) return RC::INVALID_ARGUMENT;

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) left_expr.reset(left.release());

  // right
  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) return rc;

  if (right_expr != nullptr && child_bound_expressions.size() != 1) return RC::INVALID_ARGUMENT;

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) right_expr.reset(right.release());

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}
