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
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"
#include <cmath>
#include <sstream>

int CharType::compare(const Value &left, const Value &right) const {
  ASSERT(left.attr_type() == AttrType::CHARS, "invalid type");

  Value real_value = right;
  if (right.attr_type() != AttrType::CHARS) {
    Value::cast_to(right, AttrType::CHARS, real_value);
  }

  return common::compare_string((void *)left.value_.pointer_value_, left.length_, (void *)real_value.value_.pointer_value_, real_value.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const {
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const {
  switch (type) {
    // CHARS => INTS
    case (AttrType::INTS): {
      string val_str = val.get_string();

      // 如果不存在合法前缀，返回0
      if (val_str.empty() || !isdigit(val_str[0])) {
        result.set_int(0);
      } else {
        // 构造转换后数字
        int32_t target = stoi(val.get_string());
        result.set_int(target);
      }
    } break;

    // CHARS => FLOATS
    case (AttrType::FLOATS): {
      string val_str = val.get_string();

      // 如果不存在合法前缀，返回0
      if (val_str.empty() || !isdigit(val_str[0])) {
        result.set_float(0);
      } else {
        // 构造转换后数字
        float target = stof(val.get_string());
        result.set_float(target);
      }
    } break;
    case (AttrType::CHARS): {
      result = val;
    } break;
    default:
      return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

// FLOATS > INTS > BOOLEANS > CHARS
int CharType::cast_cost(AttrType type) {
  switch (type) {
    case (AttrType::FLOATS):
      return 1;

    case (AttrType::BOOLEANS):
      return 1;

    case (AttrType::INTS):
      return 1;

    case (AttrType::CHARS):
      return 0;

    default:
      return INT32_MAX;
  }
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const {
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}