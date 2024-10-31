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
#include "common/value.h"
#include "sql/expr/tuple.h"
#include "sql/expr/arithmetic_operator.hpp"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/trx/trx.h"
#include "common/type/date_type.h"
#include "sql/optimizer/optimize_stage.h"
#include "common/type/float_type.h"
#include <cmath>
#include <iomanip>

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

////////////////////////////////////////////////////////////////////////////////

RC SubQueryExpr::get_tuple_list(const Tuple *main_tuple, std::vector<std::vector<Value>> &tuple_list) {
  if (sub_query_ == nullptr) return RC::INVALID_ARGUMENT;
  if (use_father_table_ == false) return try_get_tuple_list(tuple_list);

  TupleSchema tuple_schema;
  RC rc = OptimizeStage::handle_sub_stmt(sub_query_, tuple_list, tuple_schema, main_tuple);
  if (rc == RC::SUCCESS) {
    tuple_list_ = tuple_list;
  }
  return rc;
}

RC SubQueryExpr::try_get_tuple_list(std::vector<std::vector<Value>> &tuple_list) {
  if (sub_query_ == nullptr) return RC::INVALID_ARGUMENT;
  if (use_father_table_ == true) return RC::INVALID_ARGUMENT;

  if (has_calculated_ == false) {
    TupleSchema tuple_schema;
    RC rc = OptimizeStage::handle_sub_stmt(sub_query_, tuple_list, tuple_schema);
    if (rc == RC::SUCCESS) {
      tuple_list_ = tuple_list;
      has_calculated_ = true;
    }
    return rc;
  }
  tuple_list = tuple_list_;
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right)) {}

ComparisonExpr::~ComparisonExpr() {}

int basicCompare(CompType type_, const Value &left, const Value &right, const std::vector<Value> left_list, const std::vector<Value> right_list,
                 const std::vector<std::vector<Value>> left_tuple_list, const std::vector<std::vector<Value>> right_tuple_list) {
  int cmp_result = INT32_MAX;
  Value value;
  if (!right_tuple_list.empty() && type_ == CompType::VAL_TUPLES) {
    if (!right_tuple_list[0][0].get_null()) cmp_result = left.compare(right_tuple_list[0][0]);
  }
  if (!left_tuple_list.empty() && type_ == CompType::TUPLES_VAL) {
    if (!left_tuple_list[0][0].get_null()) cmp_result = left_tuple_list[0][0].compare(right);
  }
  if (!left_list.empty() && type_ == CompType::LIST_VAL) {
    value = left_list[0];
    cmp_result = value.compare(right);
  }
  if (!right_list.empty() && type_ == CompType::VAL_LIST) {
    value = right_list[0];
    cmp_result = value.compare(right);
  }
  if (type_ == CompType::VAL_VAL) {
    if (!left.get_null() && !right.get_null()) cmp_result = left.compare(right);
  }
  if (!left_tuple_list.empty() && !right_tuple_list.empty() && type_ == CompType::TUPLES_TUPLES) {
    cmp_result = left_tuple_list[0][0].compare(right_tuple_list[0][0]);
  }
  return cmp_result;
}

bool IN_Compare(CompType type_, const Value &left, const Value &right, const std::vector<Value> left_list, const std::vector<Value> right_list,
                const std::vector<std::vector<Value>> left_tuple_list, const std::vector<std::vector<Value>> right_tuple_list) {
  if (type_ == CompType::VAL_TUPLES) {
    for (const std::vector<Value> &vec : right_tuple_list)
      if (0 == left.compare(vec[0])) return true;
  } else if (type_ == CompType::VAL_LIST) {
    for (const Value &value : right_list)
      if (0 == left.compare(value)) return true;
  }
  return false;
}

bool EXSIT_Compare(CompType type_, const Value &left, const Value &right, const std::vector<Value> left_list, const std::vector<Value> right_list,
                   const std::vector<std::vector<Value>> left_tuple_list, const std::vector<std::vector<Value>> right_tuple_list) {
  return !right_tuple_list.empty();
}

bool IS_NULL_Compare(CompType type_, const Value &left, const Value &right, const std::vector<Value> left_list, const std::vector<Value> right_list,
                     const std::vector<std::vector<Value>> left_tuple_list, const std::vector<std::vector<Value>> right_tuple_list) {
  if (type_ == CompType::VAL_LIST || type_ == CompType::VAL_VAL || type_ == CompType::VAL_TUPLES) {
    return left.get_null();
  }
  if (!left_list.empty() && type_ == CompType::LIST_VAL) {
    return left_list[0].get_null();
  }
  if (!left_tuple_list.empty() && type_ == CompType::TUPLES_VAL) {
    return left_tuple_list[0][0].get_null();
  }
  return false;
}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, const std::vector<Value> left_list, const std::vector<Value> right_list,
                                 bool &result, const std::vector<std::vector<Value>> left_tuple_list,
                                 const std::vector<std::vector<Value>> right_tuple_list) const

{
  RC rc = RC::SUCCESS;
  result = false;

  // -------------------------处理比较是否合法----------------------

  // 排除暂不支持的比较
  /*
   * LIST_LIST
   * TUPLES_LIST
   * LIST_TUPLES
   */

  CompOp comp_ = comp();
  CompType type_ = comp_type();
  // 如果左右值存在 NULL 并且不是 NULL 的专属运算，默认 false
  if ((left.get_null() || right.get_null()) && (comp_ != CompOp::XXX_IS_NULL && comp_ != CompOp::XXX_IS_NOT_NULL)) return RC::SUCCESS;

  // 暂不支持多值之间比较
  if (type_ == CompType::LIST_LIST || type_ == CompType::TUPLES_LIST || type_ == CompType::LIST_TUPLES) {
    LOG_WARN("both left and right are not value");  // todo 支持单tuple比较
    return RC::INVALID_ARGUMENT;
  }

  // 排除对于SQL语法不支持的比较
  switch (comp_) {
    case CompOp::EQUAL_TO:  // tips：只有前六种情况支持左边子查询
    case CompOp::NOT_EQUAL:
    case CompOp::LESS_THAN:
    case CompOp::LESS_EQUAL:
    case CompOp::GREAT_THAN:
    case CompOp::GREAT_EQUAL: {
      // 列表只能有一个值
      if (type_ == CompType::VAL_LIST && right_list.size() > 1) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      } else if (type_ == CompType::LIST_VAL && left_list.size() > 1) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      }
      // 子查询结果（元组列）只能有一个值（一行一列）
      if (type_ == CompType::VAL_TUPLES) {
        if ((!right_tuple_list.empty() && right_tuple_list.front().size() > 1) || (!right_tuple_list.empty() && right_tuple_list.size() > 1)) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      } else if (type_ == CompType::TUPLES_VAL) {
        if ((!left_tuple_list.empty() && left_tuple_list.front().size() > 1) || (!left_tuple_list.empty() && left_tuple_list.size() > 1)) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      } else if (type_ == CompType::TUPLES_TUPLES) {
        if (left_tuple_list.size() > 1 || right_tuple_list.size() > 1) return RC::INVALID_ARGUMENT;
        if ((!left_tuple_list.empty() && left_tuple_list[0].size() != 1) || (!right_tuple_list.empty() && right_tuple_list[0].size() != 1))
          return RC::INVALID_ARGUMENT;
      }
    } break;
    case CompOp::LIKE_XXX:
    case CompOp::NOT_LIKE_XXX: {
      // LIKE 和 NOT LIKE 只能单个值比较
      if (type_ != CompType::VAL_VAL) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      }
    } break;
    case CompOp::IN_XXX:
    case CompOp::NOT_IN_XXX: {
      // IN 和 NOT IN 不支持左子查询和左LIST
      if (type_ == CompType::LIST_VAL || type_ == CompType::TUPLES_VAL) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      }
      // 子查询结果最多一列
      if (type_ == CompType::VAL_TUPLES) {
        if (!right_tuple_list.empty() && right_tuple_list.front().size() > 1) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      }
    } break;
    case CompOp::XXX_EXISTS:
    case CompOp::XXX_NOT_EXISTS: {
      if (type_ != CompType::VAL_TUPLES) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      }
    } break;
    case CompOp::XXX_IS_NULL:
    case CompOp::XXX_IS_NOT_NULL: {
      // EXISTS 和 IS NULL 不关心左侧以及右侧数据格式
      rc = RC::SUCCESS;
    } break;
    default:
      LOG_WARN("unsupported comparison. %d", type_);
      rc = RC::INTERNAL;
  }

  // -------------------------处理比较结果--------------------------

  int cmp_result = INT32_MAX;
  switch (comp_) {
    case EQUAL_TO:
      cmp_result = basicCompare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      result = cmp_result != INT32_MAX && (0 == cmp_result);
      break;
    case LESS_EQUAL:
      cmp_result = basicCompare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      result = cmp_result != INT32_MAX && (0 >= cmp_result);
      break;
    case NOT_EQUAL:
      cmp_result = basicCompare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      result = cmp_result != INT32_MAX && (0 != cmp_result);
      break;
    case LESS_THAN:
      cmp_result = basicCompare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      result = cmp_result != INT32_MAX && (0 > cmp_result);
      break;
    case GREAT_EQUAL:
      cmp_result = basicCompare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      result = cmp_result != INT32_MAX && (0 <= cmp_result);
      break;
    case GREAT_THAN:
      cmp_result = basicCompare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      result = cmp_result != INT32_MAX && (0 < cmp_result);
      break;
    case LIKE_XXX:
      result = ComparisonExpr::likeMatch(left.get_string(), right.get_string());
      break;
    case NOT_LIKE_XXX:
      result = !ComparisonExpr::likeMatch(left.get_string(), right.get_string());
      break;
    case IN_XXX:
      result = IN_Compare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      break;
      break;
    case NOT_IN_XXX:
      result = !IN_Compare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      break;
    case XXX_EXISTS:
      result = EXSIT_Compare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      break;
    case XXX_NOT_EXISTS:
      result = !EXSIT_Compare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      break;
    case XXX_IS_NULL:
      result = IS_NULL_Compare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      break;
    case XXX_IS_NOT_NULL:
      result = !IS_NULL_Compare(type_, left, right, left_list, right_list, left_tuple_list, right_tuple_list);
      break;
      break;
    default:
      rc = RC::INTERNAL;
      break;
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
  // value
  Value left_value;
  Value right_value;

  // value list
  std::vector<Value> left_list;
  std::vector<Value> right_list;

  // tuple_list
  std::vector<std::vector<Value>> left_tuple_list;
  std::vector<std::vector<Value>> right_tuple_list;

  bool success_left = left_->try_get_value(left_value) == RC::SUCCESS || left_->get_value_list(left_list) == RC::SUCCESS ||
                      left_->try_get_tuple_list(left_tuple_list) == RC::SUCCESS;
  bool success_right = right_->try_get_value(right_value) == RC::SUCCESS || right_->get_value_list(right_list) == RC::SUCCESS ||
                       right_->try_get_tuple_list(right_tuple_list) == RC::SUCCESS;

  if (success_left == false || success_right == false) return RC::UNIMPLEMENTED;

  set_comp_type_by_verilog();

  bool result = false;
  RC rc = compare_value(left_value, right_value, left_list, right_list, result, left_tuple_list, right_tuple_list);
  if (rc != RC::SUCCESS) return rc;
  cell.set_boolean(result);
  return RC::SUCCESS;

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::set_comp_type_by_verilog() const {
  AttrType left_type_ = left_->value_type();
  AttrType right_type_ = right_->value_type();

  int left_type = left_type_ == AttrType::VALUE_LIST ? 1 : left_type_ == AttrType::TUPLES ? 3 : 0;

  int right_type = right_type_ == AttrType::VALUE_LIST ? 1 : right_type_ == AttrType::TUPLES ? 3 : 0;

  switch (left_type << 2 | right_type) {
    case 0b0000:
      this->set_comp_type(CompType::VAL_VAL);
      break;
    case 0b0001:
      this->set_comp_type(CompType::VAL_LIST);
      break;
    case 0b0010:
      this->set_comp_type(CompType::VAL_TUPLE);
      break;
    case 0b0011:
      this->set_comp_type(CompType::VAL_TUPLES);
      break;
    case 0b0100:
      this->set_comp_type(CompType::LIST_VAL);
      break;
    case 0b0101:
      this->set_comp_type(CompType::LIST_LIST);
      break;
    case 0b0110:
      this->set_comp_type(CompType::LIST_TUPLE);
      break;
    case 0b0111:
      this->set_comp_type(CompType::LIST_TUPLES);
      break;
    case 0b1000:
      this->set_comp_type(CompType::TUPLE_VAL);
      break;
    case 0b1001:
      this->set_comp_type(CompType::TUPLE_LIST);
      break;
    case 0b1010:
      this->set_comp_type(CompType::TUPLE_TUPLE);
      break;
    case 0b1011:
      this->set_comp_type(CompType::TUPLE_TUPLES);
      break;
    case 0b1100:
      this->set_comp_type(CompType::TUPLES_VAL);
      break;
    case 0b1101:
      this->set_comp_type(CompType::TUPLES_LIST);
      break;
    case 0b1110:
      this->set_comp_type(CompType::TUPLES_TUPLE);
      break;
    case 0b1111:
      this->set_comp_type(CompType::TUPLES_TUPLES);
      break;
    default: {
      return RC::INTERNAL;
    }
  }
  return RC::SUCCESS;
}

RC ComparisonExpr::check_value() const {
  Value left_value;
  Value right_value;
  vector<Value> right_list;
  vector<Value> left_list;
  std::vector<std::vector<Value>> left_tuples;
  std::vector<std::vector<Value>> right_tuples;

  left_->try_get_value(left_value);
  left_->get_value_list(left_list);
  left_->try_get_tuple_list(left_tuples);

  right_->try_get_value(right_value);
  right_->get_value_list(right_list);
  right_->try_get_tuple_list(right_tuples);

  RC rc = set_comp_type_by_verilog();

  if (rc != RC::SUCCESS) return rc;

  // -------------------------处理比较是否合法----------------------

  // 排除暂不支持的比较
  /*
   * LIST_LIST
   * TUPLES_LIST
   * LIST_TUPLES
   * TUPLES_TUPLES
   */
  if ((left_value.get_null() || right_value.get_null()) && (comp_ != CompOp::XXX_IS_NULL && comp_ != CompOp::XXX_IS_NOT_NULL)) return RC::SUCCESS;
  if (type_ == CompType::LIST_LIST || type_ == CompType::TUPLES_LIST || type_ == CompType::LIST_TUPLES) {
    LOG_WARN("both left and right are not value");  // todo 支持单tuple比较
    return RC::INVALID_ARGUMENT;
  }

  // 排除对于SQL语法不支持的比较
  switch (comp_) {
    case CompOp::EQUAL_TO:  // tips：只有前六种情况支持左边子查询
    case CompOp::NOT_EQUAL:
    case CompOp::LESS_THAN:
    case CompOp::LESS_EQUAL:
    case CompOp::GREAT_THAN:
    case CompOp::GREAT_EQUAL: {
      // 列表只能有一个值
      if (type_ == CompType::VAL_LIST) {
        if (right_list.size() > 1) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      } else if (type_ == CompType::LIST_VAL) {
        if (left_list.size() > 1) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      } else if (type_ == CompType::TUPLES_TUPLES) {
        if (left_tuples.size() > 1 || right_tuples.size() > 1) return RC::INVALID_ARGUMENT;
        if ((!left_tuples.empty() && left_tuples[0].size() != 1) || (!right_tuples.empty() && right_tuples[0].size() != 1))
          return RC::INVALID_ARGUMENT;
      }
      // 子查询结果（元组列）只能有一个值（一行一列）
      if (type_ == CompType::VAL_TUPLES) {
        if ((right_tuples.size() > 1) || (!right_tuples.empty() && right_tuples.front().size() > 1)) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      } else if (type_ == CompType::TUPLES_VAL) {
        if ((left_tuples.size() > 1) || (!left_tuples.empty() && left_tuples.front().size() > 1)) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      }
    } break;
    case CompOp::LIKE_XXX:
    case CompOp::NOT_LIKE_XXX: {
      // LIKE 和 NOT LIKE 只能单个值比较
      if (type_ != CompType::VAL_VAL) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      }
    } break;
    case CompOp::IN_XXX:
    case CompOp::NOT_IN_XXX: {
      // IN 和 NOT IN 不支持左子查询和左LIST
      if (type_ == CompType::LIST_VAL || type_ == CompType::TUPLES_VAL) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      }
      // 子查询结果最多一列
      if (type_ == CompType::VAL_TUPLES) {
        if (!right_tuples.empty() && right_tuples.front().size() > 1) {
          LOG_WARN("invaild comparison. %d", type_);
          return RC::INVALID_ARGUMENT;
        }
      }
    } break;
    case CompOp::XXX_EXISTS:
    case CompOp::XXX_NOT_EXISTS: {
      if (type_ != CompType::VAL_TUPLES) {
        LOG_WARN("invaild comparison. %d", type_);
        return RC::INVALID_ARGUMENT;
      }
    } break;
    case CompOp::XXX_IS_NULL:
    case CompOp::XXX_IS_NOT_NULL: {
      // EXISTS 和 IS NULL 不关心左侧以及右侧数据格式
      rc = RC::SUCCESS;
    } break;
    default:
      LOG_WARN("unsupported comparison. %d", type_);
      rc = RC::INTERNAL;
  }

  return rc;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const {
  Value left_value;
  Value right_value;
  vector<Value> right_list;
  vector<Value> left_list;
  std::vector<std::vector<Value>> left_tuples;
  std::vector<std::vector<Value>> right_tuples;

  left_->get_value(tuple, left_value);
  left_->get_value_list(left_list);
  left_->get_tuple_list(&tuple, left_tuples);

  right_->get_value(tuple, right_value);
  right_->get_value_list(right_list);
  right_->get_tuple_list(&tuple, right_tuples);

  RC rc = set_comp_type_by_verilog();
  if (rc != RC::SUCCESS) return rc;

  bool bool_value = false;

  rc = compare_value(left_value, right_value, left_list, right_list, bool_value, left_tuples, right_tuples);
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

string ArithmeticExpr::type_to_string() const {
  switch (arithmetic_type_) {
    case Type::ADD:
      return "+";
    case Type::SUB:
      return "-";
    case Type::MUL:
      return "*";
    case Type::DIV:
      return "/";
    case Type::NEGATIVE:
      return "-";
    default:
      break;
  }
  return "invalid";
}

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

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS) {
    if (arithmetic_type_ != Type::DIV)
      return AttrType::INTS;
    else
      return AttrType::FLOATS;
  }

  if (left_->value_type() == AttrType::VECTORS && right_->value_type() == AttrType::VECTORS) return AttrType::VECTORS;

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

  if (left_ != nullptr) {
    rc = left_->get_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  if (right_ != nullptr) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
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

////////////////////////////////////////////////////////////////////////////////

VecFuncExpr::VecFuncExpr(VecFuncType type, unique_ptr<Expression> child_left, unique_ptr<Expression> child_right)
    : type_(type), child_left_(std::move(child_left)), child_right_(std::move(child_right)) {}
VecFuncExpr::VecFuncExpr(VecFuncType type, Expression *child_left, Expression *child_right)
    : type_(type), child_left_(child_left), child_right_(child_right) {}

RC VecFuncExpr::get_value(const Tuple &tuple, Value &value) const {
  RC rc = RC::SUCCESS;

  if (child_left_ == nullptr || child_right_ == nullptr) return RC::INVALID_ARGUMENT;

  Value left_value;
  Value right_value;

  rc = child_left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) return rc;

  rc = child_right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) return rc;

  // 为了迎合 ckk 的狗屎 check_value
  if (left_value.attr_type() == AttrType::UNDEFINED && right_value.attr_type() == AttrType::UNDEFINED) return RC::SUCCESS;

  switch (type_) {
    case VecFuncType::L2_DISTANCE:
      rc = VecFuncExpr::L2_DISTANCE_FUNC(left_value, right_value, value);
      break;
    case VecFuncType::COSINE_DISTANCE:
      rc = VecFuncExpr::COSINE_DISTANCE_FUNC(left_value, right_value, value);
      break;
    case VecFuncType::INNER_PRODUCT:
      rc = VecFuncExpr::INNER_PRODUCT_FUNC(left_value, right_value, value);
      break;
    default:
      rc = RC::INVALID_ARGUMENT;
      break;
  }
  return rc;
}

RC VecFuncExpr::try_get_value(Value &value) const {
  RC rc = RC::SUCCESS;

  if (child_left_ == nullptr || child_right_ == nullptr) return RC::INVALID_ARGUMENT;

  Value left_value;
  Value right_value;

  rc = child_left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) return rc;

  rc = child_right_->try_get_value(right_value);
  if (rc != RC::SUCCESS) return rc;

  switch (type_) {
    case VecFuncType::L2_DISTANCE:
      rc = VecFuncExpr::L2_DISTANCE_FUNC(left_value, right_value, value);
      break;
    case VecFuncType::COSINE_DISTANCE:
      rc = VecFuncExpr::COSINE_DISTANCE_FUNC(left_value, right_value, value);
      break;
    case VecFuncType::INNER_PRODUCT:
      rc = VecFuncExpr::INNER_PRODUCT_FUNC(left_value, right_value, value);
      break;
    default:
      rc = RC::INVALID_ARGUMENT;
      break;
  }
  return rc;
}

RC VecFuncExpr::L2_DISTANCE_FUNC(const Value left, const Value right, Value &result) {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS || left.get_vector_size() != right.get_vector_size())
    return RC::INVALID_ARGUMENT;
  float sum = 0;
  int size = (int)left.get_vector_size();
  vector<float> left_vec = left.get_vector();
  vector<float> right_vec = right.get_vector();
  for (int i = 0; i < size; i++) {
    sum += pow((left_vec[i] - right_vec[i]), 2);
  }
  sum = sqrt(sum);
  result.set_float(FloatType::formatFloat(sum, 2));
  return RC::SUCCESS;
}
RC VecFuncExpr::COSINE_DISTANCE_FUNC(const Value left, const Value right, Value &result) {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS || left.get_vector_size() != right.get_vector_size())
    return RC::INVALID_ARGUMENT;

  int size = (int)left.get_vector_size();
  vector<float> left_vec = left.get_vector();
  vector<float> right_vec = right.get_vector();

  // A * B
  float sum_up = 0;
  for (int i = 0; i < size; i++) sum_up += left_vec[i] * right_vec[i];

  // A 平方和开根号
  float sum_down_left = 0;
  for (int i = 0; i < size; i++) sum_down_left += left_vec[i] * left_vec[i];
  sum_down_left = sqrt(sum_down_left);

  // B 平方和开根号
  float sum_down_right = 0;
  for (int i = 0; i < size; i++) sum_down_right += right_vec[i] * right_vec[i];
  sum_down_right = sqrt(sum_down_right);

  float sum = 1 - (sum_up) / (sum_down_left * sum_down_right);
  result.set_float(FloatType::formatFloat(sum, 2));
  return RC::SUCCESS;
}
RC VecFuncExpr::INNER_PRODUCT_FUNC(const Value left, const Value right, Value &result) {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS || left.get_vector_size() != right.get_vector_size())
    return RC::INVALID_ARGUMENT;

  int size = (int)left.get_vector_size();
  vector<float> left_vec = left.get_vector();
  vector<float> right_vec = right.get_vector();

  // A * B
  float sum = 0;
  for (int i = 0; i < size; i++) sum += left_vec[i] * right_vec[i];

  result.set_float(FloatType::formatFloat(sum, 2));
  return RC::SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
RC Expression::copy_expr(const std::unique_ptr<Expression> &expr_src, std::unique_ptr<Expression> &expr_dst) {
  RC rc = RC::SUCCESS;
  switch (expr_src->type()) {
    case ExprType::FIELD: {
      FieldExpr *field_expr = static_cast<FieldExpr *>(expr_src.get());
      expr_dst = make_unique<FieldExpr>(field_expr->field());
    } break;
    case ExprType::ARITHMETIC: {
      ArithmeticExpr *arith_expr = static_cast<ArithmeticExpr *>(expr_src.get());
      std::unique_ptr<Expression> left_expr;
      std::unique_ptr<Expression> right_expr;
      rc = Expression::copy_expr(arith_expr->left(), left_expr);
      rc = Expression::copy_expr(arith_expr->right(), right_expr);
      if (rc != RC::SUCCESS) return rc;
      expr_dst = make_unique<ArithmeticExpr>(arith_expr->arithmetic_type(), std::move(left_expr), std::move(right_expr));
    } break;
    default:
      return RC::INTERNAL;
  }
  expr_dst->set_name(expr_src->name());
  return RC::SUCCESS;
}