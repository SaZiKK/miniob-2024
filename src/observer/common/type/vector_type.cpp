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
#include "common/type/vector_type.h"
#include "common/type/float_type.h"
#include "common/value.h"

int VectorType::compare(const Value &left, const Value &right) const {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS || left.get_vector_size() != right.get_vector_size())
    return INT32_MAX;
  int size = (int)left.get_vector_size();
  int result = 0;
  for (int i = 0; i < size; i++) {
    if (left.get_vector()[i] > right.get_vector()[i]) {
      result = 1;
      break;
    } else if (left.get_vector()[i] < right.get_vector()[i]) {
      result = -1;
      break;
    }
  }
  return result;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS || left.get_vector_size() != right.get_vector_size())
    return RC::INVALID_ARGUMENT;
  int size = (int)left.get_vector_size();
  vector<float> answer(size, 0);
  for (int i = 0; i < size; i++) answer[i] = left.get_vector()[i] + right.get_vector()[i];
  result.set_vector(answer);
  return RC::SUCCESS;
}
RC VectorType::subtract(const Value &left, const Value &right, Value &result) const {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS || left.get_vector_size() != right.get_vector_size())
    return RC::INVALID_ARGUMENT;
  int size = (int)left.get_vector_size();
  vector<float> answer(size, 0);
  for (int i = 0; i < size; i++) answer[i] = left.get_vector()[i] - right.get_vector()[i];
  result.set_vector(answer);
  return RC::SUCCESS;
}
RC VectorType::multiply(const Value &left, const Value &right, Value &result) const {
  if (left.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS || left.get_vector_size() != right.get_vector_size())
    return RC::INVALID_ARGUMENT;
  int size = (int)left.get_vector_size();
  float sum = 0;
  for (int i = 0; i < size; i++) sum += left.get_vector()[i] * right.get_vector()[i];
  result.set_float(sum);
  return RC::SUCCESS;
}

RC VectorType::to_string(const Value &val, string &result) const {
  if (val.attr_type() != AttrType::VECTORS) return RC::INVALID_ARGUMENT;

  result = "[";
  for (auto it : val.get_vector()) {
    it = FloatType::formatFloat(it, 2);
    string str = std::to_string(it);
    str = FloatType::formatFloat_s(it, 2);

    // 去除后导零
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') {
      str.pop_back();
    }
    result += str;
    result += ',';
  }
  if ((int)result.length() > 1) result.pop_back();
  result += "]";

  return RC::SUCCESS;
}