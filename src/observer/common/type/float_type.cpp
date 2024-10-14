/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/float_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include "common/value.h"
#include <cmath>

int FloatType::compare(const Value &left, const Value &right) const {
  ASSERT(left.attr_type() == AttrType::FLOATS, "left type is not integer");
  float left_val = left.get_float();

  Value real_value = right;
  if (right.attr_type() != AttrType::FLOATS) {
    Value::cast_to(right, AttrType::FLOATS, real_value);
  }

  float right_val = real_value.get_float();
  return common::compare_float((void *)&left_val, (void *)&right_val);
}

RC FloatType::add(const Value &left, const Value &right, Value &result) const {
  result.set_float(left.get_float() + right.get_float());
  return RC::SUCCESS;
}
RC FloatType::subtract(const Value &left, const Value &right, Value &result) const {
  result.set_float(left.get_float() - right.get_float());
  return RC::SUCCESS;
}
RC FloatType::multiply(const Value &left, const Value &right, Value &result) const {
  result.set_float(left.get_float() * right.get_float());
  return RC::SUCCESS;
}

RC FloatType::divide(const Value &left, const Value &right, Value &result) const {
  if (right.get_float() > -EPSILON && right.get_float() < EPSILON) {
    // NOTE:
    // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
    result.set_float(numeric_limits<float>::max());
  } else {
    result.set_float(left.get_float() / right.get_float());
  }
  return RC::SUCCESS;
}

RC FloatType::negative(const Value &val, Value &result) const {
  result.set_float(-val.get_float());
  return RC::SUCCESS;
}

RC FloatType::set_value_from_str(Value &val, const string &data) const {
  RC rc = RC::SUCCESS;
  stringstream deserialize_stream;
  deserialize_stream.clear();
  deserialize_stream.str(data);

  float float_value;
  deserialize_stream >> float_value;
  if (!deserialize_stream || !deserialize_stream.eof()) {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else {
    val.set_float(float_value);
  }
  return rc;
}

RC FloatType::to_string(const Value &val, string &result) const {
  stringstream ss;
  ss << common::double_to_str(val.value_.float_value_);
  result = ss.str();
  return RC::SUCCESS;
}

RC FloatType::cast_to(const Value &val, AttrType type, Value &result) const {
  switch (type) {
    // FLOATS => INTS
    case (AttrType::INTS): {
      int32_t target = std::round(val.get_float());
      result.set_int(target);
    } break;

    // FLOATS => CHARS
    case (AttrType::CHARS): {
      string target;
      to_string(val, target);
      result.set_string(target.c_str());
    } break;

    case (AttrType::FLOATS): {
      result = val;
    } break;

    default:
      return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

// FLOATS > INTS > BOOLEANS > CHARS
int FloatType::cast_cost(AttrType type) {
  switch (type) {
    case (AttrType::INTS):
      return 2;

    case (AttrType::CHARS):
      return 2;

    case (AttrType::BOOLEANS):
      return 2;

    case (AttrType::FLOATS):
      return 0;

    default:
      return INT32_MAX;
  }
  return INT32_MAX;
}