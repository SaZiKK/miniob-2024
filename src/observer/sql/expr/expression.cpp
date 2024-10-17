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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "common/type/attr_type.h"
#include "sql/expr/tuple.h"
#include "sql/expr/arithmetic_operator.hpp"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/trx/trx.h"
#include "common/type/date_type.h"
#include <cmath>

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const { return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value); }

bool FieldExpr::equal(const Expression &other) const {
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::FIELD) {
    return false;
  }
  const auto &other_field_expr = static_cast<const FieldExpr &>(other);
  return table_name() == other_field_expr.table_name() && field_name() == other_field_expr.field_name();
}

// TODO: 在进行表达式计算时，`chunk` 包含了所有列，因此可以通过 `field_id`
// 获取到对应列。 后续可以优化成在 `FieldExpr` 中存储 `chunk` 中某列的位置信息。
RC FieldExpr::get_column(Chunk &chunk, Column &column) {
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    column.reference(chunk.column(field().meta()->field_id()));
  }
  return RC::SUCCESS;
}

bool ValueExpr::equal(const Expression &other) const {
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::VALUE) {
    return false;
  }
  const auto &other_value_expr = static_cast<const ValueExpr &>(other);
  return value_.compare(other_value_expr.get_value()) == 0;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const {
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::get_column(Chunk &chunk, Column &column) {
  column.init(value_);
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type) {}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const {
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  rc = Value::cast_to(value, cast_type_, cast_value);
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &result) const {
  Value value;
  RC rc = child_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC CastExpr::try_get_value(Value &result) const {
  Value value;
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC SubQueryExpr::get_value(const Tuple &tuple, Value &value) const {
  LOG_WARN("invalid operation. cannot get single value from subquery expression");
  return RC::INVALID_ARGUMENT;
}

RC SubQueryExpr::get_value_list(std::vector<Value> &value_list) {
  LogicalPlanGenerator generator;
  SelectStmt *selectstmt = this->sub_query_;
  Trx *trx = nullptr;  // todo: 暂时使用临时创建的trx

  if (selectstmt == nullptr) {
    LOG_WARN("subquery is null");
    return RC::INVALID_ARGUMENT;
  }

  // // 如果之前没有生成过逻辑计划，那么生成逻辑计划
  // if (logical_operator == nullptr) {
  //   RC rc = create_sub_logical_plan(selectstmt, logical_operator);
  //   if (rc != RC::SUCCESS) {
  //     LOG_WARN("failed to create sub logical plan. rc=%s", strrc(rc));
  //     return rc;
  //   }
  // }

  // // 如果之前没有生成过物理计划，那么生成物理计划
  // if (physical_operator == nullptr) {
  //   RC rc = generate_sub_physical_plan(logical_operator, physical_operator);
  //   if (rc != RC::SUCCESS) {
  //     LOG_WARN("failed to create sub physical plan. rc=%s", strrc(rc));
  //     return rc;
  //   }
  // }

  // 初始化物理算子
  RC rc = physical_operator->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open sub physical operator. rc=%s", strrc(rc));
    return rc;
  }

  // 将查表结果放入value_list
  while (RC::SUCCESS == (rc = physical_operator->next())) {
    Tuple *tuple = physical_operator->current_tuple();
    Value value;
    RC rc = tuple->cell_at(0, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get tuple cell value. rc=%s", strrc(rc));
      return rc;
    }
    value_list.push_back(value);
  }

  rc = physical_operator->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close sub physical operator. rc=%s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

// RC SubQueryExpr::create_sub_logical_plan(SelectStmt *selectstmt, std::unique_ptr<LogicalOperator, void (*)(LogicalOperator *)> &logical_operator) {
//   LogicalPlanGenerator generator;
//   std::unique_ptr<LogicalOperator> temp_logical;
//   RC rc = generator.create(selectstmt, temp_logical);
//   if (rc == RC::SUCCESS && temp_logical) {
//     logical_operator = std::unique_ptr<LogicalOperator, void (*)(LogicalOperator *)>(
//         temp_logical.release(), [](LogicalOperator *ptr) { delete ptr; }  // 使用 lambda 作为删除器
//     );
//   }
//   return rc;
// }

// RC SubQueryExpr::generate_sub_physical_plan(std::unique_ptr<LogicalOperator, void (*)(LogicalOperator *)> &logical_operator,
//                                             std::unique_ptr<PhysicalOperator, void (*)(PhysicalOperator *)> &physical_operator) {
//   RC rc = RC::SUCCESS;
//   PhysicalPlanGenerator physical_plan_generator;
//   std::unique_ptr<PhysicalOperator> temp_physical;
//   rc = physical_plan_generator.create(*logical_operator, temp_physical);
//   if (rc == RC::SUCCESS && temp_physical) {
//     physical_operator = std::unique_ptr<PhysicalOperator, void (*)(PhysicalOperator *)>(
//         temp_physical.release(), [](PhysicalOperator *ptr) { delete ptr; }  // 使用 lambda 作为删除器
//     );
//   }
//   if (rc != RC::SUCCESS) {
//     LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
//   }
//   return rc;
// }

void SubQueryExpr::set_logical_operator(std::unique_ptr<LogicalOperator, void (*)(LogicalOperator *)> logical_op) {
  logical_operator = std::move(logical_op);
}

void SubQueryExpr::set_physical_operator(std::unique_ptr<PhysicalOperator, void (*)(PhysicalOperator *)> physical_op) {
  physical_operator = std::move(physical_op);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right)) {}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, const std::vector<Value> left_list, const std::vector<Value> right_list,
                                 bool &result, bool left_is_value, bool right_is_value) const {
  RC rc = RC::SUCCESS;
  result = false;
  if ((left.get_null() || right.get_null()) && (comp_ != CompOp::XXX_IS_NULL && comp_ != CompOp::XXX_IS_NOT_NULL)) return RC::SUCCESS;
  if (!left_is_value && !right_is_value) {
    LOG_WARN("both left and right are not value");
    return RC::INVALID_ARGUMENT;
  }
  // if (!left_is_value && right_is_value && left_list.size() > 1) {
  //   LOG_WARN("比较符号左边是list，右边是value，但是左边有多个值");
  //   return RC::INVALID_ARGUMENT;
  // }
  // if (left_is_value && !right_is_value && right_list.size() > 1) {
  //   LOG_WARN("比较符号左边是value，右边是list，但是右边有多个值");
  //   return RC::INVALID_ARGUMENT;
  // }
  switch (comp_) {
    case EQUAL_TO: {
      // 有一个不等于就返回false
      result = true;
      if (!left_is_value && right_is_value) {
        for (auto it : left_list) {
          if (0 != it.compare(right)) {
            result = false;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        for (auto it : right_list) {
          if (0 != left.compare(it)) {
            result = false;
            break;
          }
        }
      } else {
        int cmp_result = left.compare(right);
        result = (0 == cmp_result);
      }
    } break;
    case LESS_EQUAL: {
      // 返回所有小于等于 ，注意左边是list的时候，也就是左边是子查询的时候符号反向
      if (!left_is_value && right_is_value) {
        for (auto it : left_list) {
          if (0 >= it.compare(right)) {
            result = true;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        for (auto it : right_list) {
          if (0 >= left.compare(it)) {
            result = true;
            break;
          }
        }
      } else {
        int cmp_result = left.compare(right);
        result = (0 >= cmp_result);
      }
    } break;
    case NOT_EQUAL: {
      // 有一个相等就返回false
      result = true;
      if (!left_is_value && right_is_value) {
        for (auto it : left_list) {
          if (0 == it.compare(right)) {
            result = false;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        for (auto it : right_list) {
          if (0 == left.compare(it)) {
            result = false;
            break;
          }
        }
      } else {
        int cmp_result = left.compare(right);
        result = (0 != cmp_result);
      }
    } break;
    case LESS_THAN: {
      // 返回所有小于 ，注意左边是list的时候，也就是左边是子查询的时候符号反向
      if (!left_is_value && right_is_value) {
        for (auto it : left_list) {
          if (0 > it.compare(right)) {
            result = true;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        for (auto it : right_list) {
          if (0 > left.compare(it)) {
            result = true;
            break;
          }
        }
      } else {
        int cmp_result = left.compare(right);
        result = (0 > cmp_result);
      }
    } break;
    case GREAT_EQUAL: {
      // 返回所有大于等于 ，注意左边是list的时候，也就是左边是子查询的时候符号反向
      if (!left_is_value && right_is_value) {
        for (auto it : left_list) {
          if (0 <= it.compare(right)) {
            result = true;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        for (auto it : right_list) {
          if (0 <= left.compare(it)) {
            result = true;
            break;
          }
        }
      } else {
        int cmp_result = left.compare(right);
        result = (0 <= cmp_result);
      }
    } break;
    case GREAT_THAN: {
      // 返回所有大于 ，注意左边是list的时候，也就是左边是子查询的时候符号反向
      if (!left_is_value && right_is_value) {
        for (auto it : left_list) {
          if (0 < it.compare(right)) {
            result = true;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        for (auto it : right_list) {
          if (0 < left.compare(it)) {
            result = true;
            break;
          }
        }
      } else {
        int cmp_result = left.compare(right);
        result = (0 < cmp_result);
      }
    } break;
    case LIKE_XXX: {
      result = ComparisonExpr::likeMatch(left.get_string(), right.get_string());
    } break;
    case NOT_LIKE_XXX: {
      result = !ComparisonExpr::likeMatch(left.get_string(), right.get_string());
    } break;
    case IN_XXX: {
      if (!left_is_value && right_is_value) {
        for (const Value &value : left_list) {
          if (0 == value.compare(right)) {
            result = true;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        for (const Value &value : right_list) {
          if (0 == left.compare(value)) {
            result = true;
            break;
          }
        }
      } else {
        LOG_WARN("unsupported comparison. %d", comp_);
        rc = RC::INTERNAL;
      }
    } break;
    case NOT_IN_XXX: {
      if (!left_is_value && right_is_value) {
        result = true;
        for (const Value &value : left_list) {
          if (0 == value.compare(right)) {
            result = false;
            break;
          }
        }
      } else if (!right_is_value && left_is_value) {
        result = true;
        for (const Value &value : right_list) {
          if (0 == left.compare(value)) {
            result = false;
            break;
          }
        }
      } else {
        LOG_WARN("unsupported comparison. %d", comp_);
        rc = RC::INTERNAL;
      }
    } break;
    case XXX_EXISTS: {
      if (!left_is_value && right_is_value) {
        result = !left_list.empty();
      } else if (!right_is_value && left_is_value) {
        result = !right_list.empty();
      }
    } break;
    case XXX_NOT_EXISTS: {
      if (!left_is_value && right_is_value) {
        result = left_list.empty();
      } else if (!right_is_value && left_is_value) {
        result = right_list.empty();
      }
    } break;
    case XXX_IS_NULL: {
      if (left_is_value) {
        result = left.get_null();
      } else {
        result = false;
      }
    } break;
    case XXX_IS_NOT_NULL: {
      if (left_is_value) {
        result = !left.get_null();
      } else {
        result = true;
      }
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

bool ComparisonExpr::likeMatch(const string &str, const string &pattern) {
  int s = 0, p = 0;
  int starIdx = -1, sTmpIdx = -1;

  while (s < (int)str.length()) {
    // 如果字符匹配或者模式是'_'，两个指针都前进
    if (p < (int)pattern.length() && (pattern[p] == '_' || str[s] == pattern[p])) {
      ++s;
      ++p;
    }
    // 如果模式是'%'，记录'%'的位置和当前字符串的位置
    else if (p < (int)pattern.length() && pattern[p] == '%') {
      starIdx = p;
      sTmpIdx = s;
      ++p;
    }
    // 如果之前遇到过'%'，回溯
    else if (starIdx != -1) {
      p = starIdx + 1;
      s = ++sTmpIdx;
    }
    // 不匹配
    else {
      return false;
    }
  }

  // 处理模式串末尾的'%'
  while (p < (int)pattern.length() && pattern[p] == '%') {
    ++p;
  }

  return p == (int)pattern.length();
}

RC ComparisonExpr::try_get_value(Value &cell) const {
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();
    std::vector<Value> left_list;
    std::vector<Value> right_list;
    bool left_is_value = true;
    bool right_is_value = true;  // todo 这里暂时没考虑是list的情况

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, left_list, right_list, value, left_is_value, right_is_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const {
  Value left_value;
  Value right_value;
  vector<Value> right_values;
  vector<Value> left_values;
  bool left_is_value = false;
  bool right_is_value = false;
  RC rc = RC::EMPTY;

  // 特判子查询，进入特殊处理函数获取数据
  if (left_->value_type() == AttrType::SUB_QUERY || left_->type() == ExprType::VALUELIST) {
    rc = left_->get_value_list(left_values);
  } else {
    rc = left_->get_value(tuple, left_value);
    left_is_value = true;
  }

  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_->value_type() == AttrType::SUB_QUERY || right_->type() == ExprType::VALUELIST) {
    rc = right_->get_value_list(right_values);
  } else {
    rc = right_->get_value(tuple, right_value);
    right_is_value = true;
  }

  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;

  rc = compare_value(left_value, right_value, left_values, right_values, bool_value, left_is_value, right_is_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select) {
  RC rc = RC::SUCCESS;
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  if (left_column.attr_type() != right_column.attr_type()) {
    LOG_WARN("cannot compare columns with different types");
    return RC::INTERNAL;
  }
  if (left_column.attr_type() == AttrType::INTS) {
    rc = compare_column<int>(left_column, right_column, select);
  } else if (left_column.attr_type() == AttrType::FLOATS) {
    rc = compare_column<float>(left_column, right_column, select);
  } else {
    // TODO: support string compare
    LOG_WARN("unsupported data type %d", left_column.attr_type());
    return RC::INTERNAL;
  }
  return rc;
}

template <typename T>
RC ComparisonExpr::compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const {
  RC rc = RC::SUCCESS;

  bool left_const = left.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    compare_result<T, true, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else if (left_const && !right_const) {
    compare_result<T, true, false>((T *)left.data(), (T *)right.data(), right.count(), result, comp_);
  } else if (!left_const && right_const) {
    compare_result<T, false, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else {
    compare_result<T, false, false>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children) : conjunction_type_(type), children_(std::move(children)) {}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const {
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right) : arithmetic_type_(type), left_(left), right_(right) {}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right)) {}

bool ArithmeticExpr::equal(const Expression &other) const {
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &other_arith_expr = static_cast<const ArithmeticExpr &>(other);
  return arithmetic_type_ == other_arith_expr.arithmetic_type() && left_->equal(*other_arith_expr.left_) && right_->equal(*other_arith_expr.right_);
}
AttrType ArithmeticExpr::value_type() const {
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS && arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const {
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  value.set_type(target_type);

  switch (arithmetic_type_) {
    case Type::ADD: {
      Value::add(left_value, right_value, value);
    } break;

    case Type::SUB: {
      Value::subtract(left_value, right_value, value);
    } break;

    case Type::MUL: {
      Value::multiply(left_value, right_value, value);
    } break;

    case Type::DIV: {
      Value::divide(left_value, right_value, value);
    } break;

    case Type::NEGATIVE: {
      Value::negative(left_value, value);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
RC ArithmeticExpr::execute_calc(const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const {
  RC rc = RC::SUCCESS;
  switch (type) {
    case Type::ADD: {
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, AddOperator>((int *)left.data(), (int *)right.data(), (int *)result.data(),
                                                                         result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, AddOperator>((float *)left.data(), (float *)right.data(), (float *)result.data(),
                                                                           result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
    } break;
    case Type::SUB:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, SubtractOperator>((int *)left.data(), (int *)right.data(), (int *)result.data(),
                                                                              result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, SubtractOperator>((float *)left.data(), (float *)right.data(), (float *)result.data(),
                                                                                result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::MUL:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, MultiplyOperator>((int *)left.data(), (int *)right.data(), (int *)result.data(),
                                                                              result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, MultiplyOperator>((float *)left.data(), (float *)right.data(), (float *)result.data(),
                                                                                result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::DIV:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, DivideOperator>((int *)left.data(), (int *)right.data(), (int *)result.data(),
                                                                            result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, DivideOperator>((float *)left.data(), (float *)right.data(), (float *)result.data(),
                                                                              result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::NEGATIVE:
      if (attr_type == AttrType::INTS) {
        unary_operator<LEFT_CONSTANT, int, NegateOperator>((int *)left.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        unary_operator<LEFT_CONSTANT, float, NegateOperator>((float *)left.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    default:
      rc = RC::UNIMPLEMENTED;
      break;
  }
  if (rc == RC::SUCCESS) {
    result.set_count(result.capacity());
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const {
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::get_column(Chunk &chunk, Column &column) {
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
    return rc;
  }
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_column(left_column, right_column, column);
}

RC ArithmeticExpr::calc_column(const Column &left_column, const Column &right_column, Column &column) const {
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  column.init(target_type, left_column.attr_len(), std::max(left_column.count(), right_column.count()));
  bool left_const = left_column.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right_column.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    column.set_column_type(Column::Type::CONSTANT_COLUMN);
    rc = execute_calc<true, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (left_const && !right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<true, false>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (!left_const && right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, false>(left_column, right_column, column, arithmetic_type_, target_type);
  }
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const {
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////

UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, Expression *child) : aggregate_name_(aggregate_name), child_(child) {}

////////////////////////////////////////////////////////////////////////////////
AggregateExpr::AggregateExpr(Type type, Expression *child) : aggregate_type_(type), child_(child) {}

AggregateExpr::AggregateExpr(Type type, unique_ptr<Expression> child) : aggregate_type_(type), child_(std::move(child)) {}

RC AggregateExpr::get_column(Chunk &chunk, Column &column) {
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    rc = RC::INTERNAL;
  }
  return rc;
}

bool AggregateExpr::equal(const Expression &other) const {
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const AggregateExpr &other_aggr_expr = static_cast<const AggregateExpr &>(other);
  return aggregate_type_ == other_aggr_expr.aggregate_type() && child_->equal(*other_aggr_expr.child());
}

unique_ptr<Aggregator> AggregateExpr::create_aggregator() const {
  unique_ptr<Aggregator> aggregator;
  switch (aggregate_type_) {
    case Type::SUM: {
      aggregator = make_unique<SumAggregator>();
      break;
    }
    case Type::MAX: {
      aggregator = make_unique<MaxAggregator>();
      break;
    }
    case Type::MIN: {
      aggregator = make_unique<MinAggregator>();
      break;
    }
    case Type::AVG: {
      aggregator = make_unique<AvgAggregator>();
      break;
    }
    case Type::COUNT: {
      aggregator = make_unique<CountAggregator>();
      break;
    }
    default: {
      ASSERT(false, "unsupported aggregate type");
      break;
    }
  }
  return aggregator;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value) const { return tuple.find_cell(TupleCellSpec(name()), value); }

RC AggregateExpr::type_from_string(const char *type_str, AggregateExpr::Type &type) {
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "count")) {
    type = Type::COUNT;
  } else if (0 == strcasecmp(type_str, "sum")) {
    type = Type::SUM;
  } else if (0 == strcasecmp(type_str, "avg")) {
    type = Type::AVG;
  } else if (0 == strcasecmp(type_str, "max")) {
    type = Type::MAX;
  } else if (0 == strcasecmp(type_str, "min")) {
    type = Type::MIN;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
FuncExpr::FuncExpr(FuncType type, unique_ptr<Expression> target_num, unique_ptr<Expression> target_format, std::unique_ptr<Expression> child)
    : type_(type), child_(std::move(child)) {
  RC rc = RC::INVALID_ARGUMENT;

  Value round_value;
  if (target_num != nullptr) rc = target_num->try_get_value(round_value);
  if (rc != RC::SUCCESS) round_value = Value((float)-1);

  rc = RC::INVALID_ARGUMENT;
  Value format_value;
  if (target_format != nullptr) rc = target_format->try_get_value(format_value);
  if (rc != RC::SUCCESS) format_value = Value("");

  target_num_ = round_value.get_float();
  target_format_ = format_value.get_string();
};

FuncExpr::FuncExpr(FuncType type, Expression *target_num, Expression *target_format, Expression *child) : type_(type), child_(child) {
  RC rc = RC::INVALID_ARGUMENT;

  Value round_value;
  if (target_num != nullptr) rc = target_num->try_get_value(round_value);
  if (rc != RC::SUCCESS) round_value = Value((float)-1);

  rc = RC::INVALID_ARGUMENT;
  Value format_value;
  if (target_format != nullptr) rc = target_format->try_get_value(format_value);
  if (rc != RC::SUCCESS) format_value = Value("");

  target_num_ = round_value.get_float();
  target_format_ = format_value.get_string();
};

AttrType FuncExpr::value_type() const {
  switch (type_) {
    case FuncType::LENGTH:
      return AttrType::INTS;
    case FuncType::ROUND:
      return AttrType::FLOATS;
    case FuncType::DATE_FORMAT:
      return AttrType::CHARS;
    default:
      return AttrType::UNDEFINED;
  }
  return AttrType::UNDEFINED;
}

RC FuncExpr::get_value(const Tuple &tuple, Value &value) const {
  // 获取子表达式的值
  Value child_value;
  if (child_ == nullptr) return RC::INVALID_ARGUMENT;
  RC rc = child_->try_get_value(child_value);
  if (rc != RC::SUCCESS) return rc;

  // 根据不同的函数类型处理子表达式的值
  switch (type_) {
    case FuncType::LENGTH:
      rc = FuncExpr::func_length(child_value, value);
      break;
    case FuncType::ROUND:
      rc = FuncExpr::func_round(child_value, target_num_, value);
      break;
    case FuncType::DATE_FORMAT:
      rc = FuncExpr::func_date_format(child_value, target_format_, value);
      break;
    default:
      rc = RC::INVALID_ARGUMENT;
      break;
  }
  return rc;
}

// 处理函数 LENGTH 的计算
RC FuncExpr::func_length(const Value value, Value &result) {
  // 强制转换成 CHARS 类型
  Value real_val;
  RC rc = Value::cast_to(value, AttrType::CHARS, real_val);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 计算结果
  int length = real_val.get_string().length();
  result = Value(length);
  return RC::SUCCESS;
}

// 处理函数 ROUND 的计算
RC FuncExpr::func_round(const Value value, int target_num, Value &result) {
  // 参数合法性
  if (target_num < 0) return RC::INVALID_ARGUMENT;

  // 强制转换成 FLOATS 类型
  Value real_val;
  RC rc = Value::cast_to(value, AttrType::FLOATS, real_val);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 计算结果
  // 计算 10 的 target_num 次方
  float factor = std::pow(10.0f, target_num);
  // 先乘以因子再四舍五入，然后再除以因子
  float answer = std::round(real_val.get_float() * factor) / factor;
  result = Value(answer);
  return RC::SUCCESS;
}

// 处理函数 DATE_FORMAT 的计算
RC FuncExpr::func_date_format(const Value value, string target_format, Value &result) {
  if (value.attr_type() != AttrType::DATE) {
    return RC::INVALID_ARGUMENT;
  }
  string date = to_string(value.get_int());
  int idx = target_format.find("%Y");  // 四位数年份
  if (idx >= 0) {
    target_format.replace(idx, 2, DateType::get_year(date));
  }
  idx = target_format.find("%y");  // 两位数年份
  if (idx >= 0) {
    target_format.replace(idx, 2, DateType::get_year(date).substr(2, 2));
  }
  idx = target_format.find("%M");  // 月份英文
  if (idx >= 0) {
    target_format.replace(idx, 2, DateType::get_month_inEnglish(date));
  }
  idx = target_format.find("%m");  // 月份
  if (idx >= 0) {
    target_format.replace(idx, 2, DateType::get_month(date));
  }
  // idx = target_format.find("%D");  // 日期英文
  // if (idx >= 0) {
  //   target_format.replace(idx, 2, DateType::get_day_inEnglish(date));
  // }
  idx = target_format.find("%d");  // 日期
  if (idx >= 0) {
    target_format.replace(idx, 2, DateType::get_day(date));
  }

  result = Value(target_format.c_str());
  return RC::SUCCESS;
}

RC FuncExpr::try_get_value(Value &value) const {
  // 获取子表达式的值
  Value child_value;
  if (child_ == nullptr) return RC::INVALID_ARGUMENT;
  RC rc = child_->try_get_value(child_value);
  if (rc != RC::SUCCESS) return rc;

  // 根据不同的函数类型处理子表达式的值
  switch (type_) {
    case FuncType::LENGTH:
      rc = FuncExpr::func_length(child_value, value);
      break;
    case FuncType::ROUND:
      rc = FuncExpr::func_round(child_value, target_num_, value);
      break;
    case FuncType::DATE_FORMAT:
      rc = FuncExpr::func_date_format(child_value, target_format_, value);
      break;
    default:
      rc = RC::INVALID_ARGUMENT;
      break;
  }
  return rc;
}
