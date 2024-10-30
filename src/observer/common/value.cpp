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
// Created by WangYunlai on 2023/06/28.
//

#include "common/value.h"

#include "common/lang/comparator.h"
#include "common/lang/exception.h"
#include "common/lang/sstream.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/type/attr_type.h"
#include "common/type/float_type.h"

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) {
  vector<float> value_vector;
  RC rc = Value::string_to_vector(s, value_vector);
  if (rc == RC::SUCCESS)
    set_vector(value_vector);
  else
    set_string(s, len);
}

Value::Value(std::vector<float> value_vector) { set_vector(value_vector); }

Value::Value(string ckk, int num) { this->is_null_ = true; }

Value::Value(int val, bool is_date) {
  if (is_date) {
    set_date(val);
  } else {
    set_int(val);
  }
}

Value::Value(const Value &other) {
  this->attr_type_ = other.attr_type_;
  this->length_ = other.length_;
  this->own_data_ = other.own_data_;
  this->is_null_ = other.is_null_;
  switch (this->attr_type_) {
    case AttrType::CHARS: {
      set_string_from_other(other);
    } break;
    case AttrType::VECTORS: {
      set_vector(other.value_vector_);
    } break;
    default: {
      this->value_ = other.value_;
    } break;
  }
}

Value::Value(Value &&other) {
  this->attr_type_ = other.attr_type_;
  this->length_ = other.length_;
  this->own_data_ = other.own_data_;
  this->value_ = other.value_;
  this->value_vector_ = other.value_vector_;
  this->is_null_ = other.is_null_;
  other.own_data_ = false;
  other.length_ = 0;
}

Value &Value::operator=(const Value &other) {
  if (this == &other) {
    return *this;
  }
  reset();
  this->attr_type_ = other.attr_type_;
  this->length_ = other.length_;
  this->own_data_ = other.own_data_;
  this->is_null_ = other.is_null_;
  switch (this->attr_type_) {
    case AttrType::CHARS: {
      set_string_from_other(other);
    } break;
    case AttrType::VECTORS: {
      set_vector(other.value_vector_);
    } break;
    default: {
      this->value_ = other.value_;
    } break;
  }
  return *this;
}

Value &Value::operator=(Value &&other) {
  if (this == &other) {
    return *this;
  }
  reset();
  this->attr_type_ = other.attr_type_;
  this->length_ = other.length_;
  this->own_data_ = other.own_data_;
  this->value_ = other.value_;
  this->value_vector_ = other.value_vector_;
  this->is_null_ = other.is_null_;
  other.own_data_ = false;
  other.length_ = 0;
  return *this;
}

bool Value::operator<(const Value &other) const { return compare(other) < 0; }

bool Value::operator>(const Value &other) const { return compare(other) > 0; }

void Value::reset() {
  switch (attr_type_) {
    case AttrType::CHARS:
      if (own_data_ && value_.pointer_value_ != nullptr) {
        delete[] value_.pointer_value_;
        value_.pointer_value_ = nullptr;
      }
      break;
    case AttrType::TEXT:
      if (own_data_ && value_.pointer_value_ != nullptr) {
        delete[] value_.pointer_value_;
        value_.pointer_value_ = nullptr;
      }
      break;
    default:
      break;
  }

  attr_type_ = AttrType::UNDEFINED;
  value_vector_.clear();
  value_vector_.resize(0);
  length_ = 0;
  own_data_ = false;
  is_null_ = false;
}

void Value::set_data(char *data, int length) {
  switch (attr_type_) {
    case AttrType::CHARS: {
      set_string(data, length);
    } break;
    case AttrType::INTS: {
      value_.int_value_ = *(int *)data;
      length_ = length;
    } break;
    case AttrType::FLOATS: {
      value_.float_value_ = *(float *)data;
      length_ = length;
    } break;
    case AttrType::BOOLEANS: {
      value_.bool_value_ = *(int *)data != 0;
      length_ = length;
    } break;
    case AttrType::DATE: {
      value_.int_value_ = *(int *)data;
      length_ = length;
    } break;
    case AttrType::VECTORS: {
      size_t element_size = sizeof(int);
      size_t num_elements = length / element_size;

      // 使用 memcpy 将数据复制回 vector
      value_vector_.resize(num_elements);
      memcpy(value_vector_.data(), data, length);
      length_ = length;
    } break;
    case AttrType::TEXT: {
      set_text(data);
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}

void Value::set_int(int val) {
  reset();
  attr_type_ = AttrType::INTS;
  value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_float(float val) {
  reset();
  attr_type_ = AttrType::FLOATS;
  value_.float_value_ = val;
  length_ = sizeof(val);
}
void Value::set_boolean(bool val) {
  reset();
  attr_type_ = AttrType::BOOLEANS;
  value_.bool_value_ = val;
  length_ = sizeof(val);
}

void Value::set_string(const char *s, int len /*= 0*/) {
  reset();
  attr_type_ = AttrType::CHARS;
  if (s == nullptr) {
    value_.pointer_value_ = nullptr;
    length_ = 0;
  } else {
    own_data_ = true;
    if (len > 0) {
      len = strnlen(s, len);
    } else {
      len = strlen(s);
    }
    value_.pointer_value_ = new char[len + 1];
    length_ = len;
    memcpy(value_.pointer_value_, s, len);
    value_.pointer_value_[len] = '\0';
  }
}

void Value::update_text_data(const char *s, int len) {
  reset();
  attr_type_ = AttrType::CHARS;
  if (s == nullptr) {
    value_.pointer_value_ = nullptr;
    length_ = 0;
  } else {
    own_data_ = true;
    value_.pointer_value_ = new char[len + 1];
    length_ = len;
    memcpy(value_.pointer_value_, s, length_);
    value_.pointer_value_[length_] = '\0';
  }
}

void Value::set_text(const char *s) {
  reset();
  attr_type_ = AttrType::TEXT;
  if (s == nullptr) {
    value_.pointer_value_ = nullptr;
    length_ = 0;
  } else {
    own_data_ = true;
    if (length_ > 0) {
      length_ = strnlen(s, length_);
    } else {
      length_ = strlen(s);
    }
    value_.pointer_value_ = new char[length_ + 1];
    memcpy(value_.pointer_value_, s, length_);
    value_.pointer_value_[length_] = '\0';
  }
}

void Value::set_date(int val) {
  reset();
  attr_type_ = AttrType::DATE;
  value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_null(bool flag) { is_null_ = flag; }

void Value::set_value(const Value &value) {
  switch (value.attr_type_) {
    case AttrType::INTS: {
      set_int(value.get_int());
    } break;
    case AttrType::FLOATS: {
      set_float(value.get_float());
    } break;
    case AttrType::CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case AttrType::BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case AttrType::DATE: {
      set_date(value.get_date());
    } break;
    case AttrType::VECTORS: {
      set_vector(value.get_vector());
    } break;
    default: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

void Value::set_string_from_other(const Value &other) {
  ASSERT(attr_type_ == AttrType::CHARS, "attr type is not CHARS");
  if (own_data_ && other.value_.pointer_value_ != nullptr && length_ != 0) {
    this->value_.pointer_value_ = new char[this->length_ + 1];
    memcpy(this->value_.pointer_value_, other.value_.pointer_value_, this->length_);
    this->value_.pointer_value_[this->length_] = '\0';
  }
}

const char *Value::data() const {
  switch (attr_type_) {
    case AttrType::TEXT: {
      return value_.pointer_value_;
    } break;
    case AttrType::CHARS: {
      return value_.pointer_value_;
    } break;
    case AttrType::VECTORS: {
      return (const char *)(value_vector_.data());
    }
    default: {
      return (const char *)&value_;
    } break;
  }
}

string Value::to_string() const {
  if (is_null_ == true) return string("NULL");
  string res;
  RC rc = DataType::type_instance(this->attr_type_)->to_string(*this, res);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to convert value to string. type=%s", attr_type_to_string(this->attr_type_));
    return "";
  }
  return res;
}

int Value::compare(const Value &other) const {
  if (is_null_) return -1;
  if (other.get_null()) return 1;
  return DataType::type_instance(this->attr_type_)->compare(*this, other);
}

int Value::get_int() const {
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return (int)(std::stol(value_.pointer_value_));
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return 0;
      }
    }
    case AttrType::INTS: {
      return value_.int_value_;
    }
    case AttrType::FLOATS: {
      return (int)(value_.float_value_);
    }
    case AttrType::BOOLEANS: {
      return (int)(value_.bool_value_);
    }
    case AttrType::DATE: {
      return (int)(value_.int_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const {
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return std::stof(value_.pointer_value_);
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return 0.0;
      }
    } break;
    case AttrType::INTS: {
      return float(value_.int_value_);
    } break;
    case AttrType::FLOATS: {
      return value_.float_value_;
    } break;
    case AttrType::BOOLEANS: {
      return float(value_.bool_value_);
    } break;
    case AttrType::DATE: {
      return float(value_.int_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const {
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        float val = std::stof(value_.pointer_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(value_.pointer_value_);
        if (int_val != 0) {
          return true;
        }

        return value_.pointer_value_ != nullptr;
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return value_.pointer_value_ != nullptr;
      }
    } break;
    case AttrType::INTS: {
      return value_.int_value_ != 0;
    } break;
    case AttrType::FLOATS: {
      float val = value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case AttrType::BOOLEANS: {
      return value_.bool_value_;
    } break;
    case AttrType::DATE: {
      return value_.int_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

int Value::get_date() const {
  switch (attr_type_) {
    case AttrType::DATE: {
      return value_.int_value_;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return INT32_MAX;
    }
  }
}

bool Value::get_null() const { return is_null_; }

///////////////////////////////////////////////////////////////////////////
// vector part

// 用于检查输入字符串是否符合 vector 的格式
bool Value::isValidFormat(const char *input) {
  // 检查是否为空或长度小于2（必须至少包含 "[]")
  if (input == nullptr || strlen(input) < 2) {
    return false;
  }

  // 检查首尾是否分别为 '[' 和 ']'
  if (input[0] != '[' || input[strlen(input) - 1] != ']') {
    return false;
  }

  // 剔除 '[' 和 ']'，从第二个字符开始检查
  std::string content(input + 1, strlen(input) - 2);

  // 删除多余的空格
  content.erase(std::remove(content.begin(), content.end(), ' '), content.end());

  // 使用逗号分割内容
  std::istringstream ss(content);
  std::string token;
  std::vector<std::string> tokens;

  // 分割内容并检查每个部分
  while (std::getline(ss, token, ',')) {
    if (!isValidNumber(token)) {
      return false;  // 如果某个部分不是有效的数字，返回 false
    }
  }

  return true;  // 所有部分都是有效的数字
}

// 用于检查一个字符串是否是整数或浮点数
bool Value::isValidNumber(const std::string &s) {
  std::istringstream stream(s);
  float number;
  stream >> number;
  // 检查是否成功解析为数字，并且没有多余字符
  return stream.eof() && !stream.fail();
}

RC Value::string_to_vector(string str, vector<float> &result) {
  if (!Value::isValidFormat(str.c_str())) return RC::INVALID_ARGUMENT;

  // 剔除 '[' 和 ']'，从第二个字符开始检查
  str = str.substr(1, (int)str.size() - 2);

  // 去除多余空格
  str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

  // 使用逗号分割内容
  std::istringstream ss(str);
  std::string token;
  std::vector<std::string> tokens;

  // 分割内容并检查每个部分
  while (std::getline(ss, token, ',')) {
    result.push_back(FloatType::formatFloat(std::stof(token), 2));
  }
  return RC::SUCCESS;
}

void Value::set_vector(std::vector<float> value_vector) {
  attr_type_ = AttrType::VECTORS;
  is_null_ = false;
  value_vector_ = value_vector;
  length_ = value_vector.size() * sizeof(float);
}

vector<float> Value::get_vector() const { return value_vector_; }

int Value::get_vector_size() const { return (int)value_vector_.size(); }

Value Value::max_value(AttrType type) {
  switch (type) {
    case AttrType::INTS: {
      return Value(INT32_MAX);
    }
    case AttrType::FLOATS: {
      return Value(float(3.40282e+038));
    }
    case AttrType::DATE: {
      return Value(99991231, true);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", type);
      return Value();
    }
  }
}
Value Value::min_value(AttrType type) {
  switch (type) {
    case AttrType::INTS: {
      return Value(-INT32_MAX - 1);
    }
    case AttrType::FLOATS: {
      return Value(float(-3.40282e+038));
    }
    case AttrType::DATE: {
      return Value(10000101, true);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", type);
      return Value();
    }
  }
}