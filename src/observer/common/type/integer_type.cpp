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
#include "common/type/integer_type.h"
#include "common/value.h"

int IntegerType::compare(const Value &left, const Value &right) const {
  ASSERT(left.attr_type() == AttrType::INTS, "left type is not integer");

  Value real_left_value = left;
  Value real_right_value = right;
  Value::cast_to(left, AttrType::FLOATS, real_left_value);
  Value::cast_to(right, AttrType::FLOATS, real_right_value);

  float left_val = real_left_value.get_float();
  float right_val = real_right_value.get_float();
  return common::compare_float((void *)&left_val, (void *)&right_val);
}

RC IntegerType::add(const Value &left, const Value &right, Value &result) const {
  result.set_int(left.get_int() + right.get_int());
  return RC::SUCCESS;
}

RC IntegerType::subtract(const Value &left, const Value &right, Value &result) const {
  result.set_int(left.get_int() - right.get_int());
  return RC::SUCCESS;
}

RC IntegerType::multiply(const Value &left, const Value &right, Value &result) const {
  result.set_int(left.get_int() * right.get_int());
  return RC::SUCCESS;
}

RC IntegerType::negative(const Value &val, Value &result) const {
  result.set_int(-val.get_int());
  return RC::SUCCESS;
}

RC IntegerType::set_value_from_str(Value &val, const string &data) const {
  RC rc = RC::SUCCESS;
  stringstream deserialize_stream;
  deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
  deserialize_stream.str(data);
  int int_value;
  deserialize_stream >> int_value;
  if (!deserialize_stream || !deserialize_stream.eof()) {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else {
    val.set_int(int_value);
  }
  return rc;
}

RC IntegerType::to_string(const Value &val, string &result) const {
  stringstream ss;
  ss << val.value_.int_value_;
  result = ss.str();
  return RC::SUCCESS;
}

RC IntegerType::cast_to(const Value &val, AttrType type, Value &result) const {
  switch (type) {
    // INTS => FLOATS
    case (AttrType::FLOATS): {
      float target = (float)val.get_int();
      result.set_float(target);
    } break;

    // INTS => CHARS
    case (AttrType::CHARS): {
      string target;
      to_string(val, target);
      result.set_string(target.c_str());
    } break;
    case (AttrType::INTS): {
      result = val;
    } break;
    default:
      return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

// FLOATS > INTS > BOOLEANS > CHARS
int IntegerType::cast_cost(AttrType type) {
  switch (type) {
    case (AttrType::FLOATS):
      return 1;

    case (AttrType::CHARS):
      return 2;

    case (AttrType::BOOLEANS):
      return 2;

    case (AttrType::INTS):
      return 0;

    default:
      return INT32_MAX;
  }
  return INT32_MAX;
}