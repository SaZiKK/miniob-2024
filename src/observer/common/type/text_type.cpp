

#include <cassert>
#include "common/log/log.h"
#include "common/value.h"
#include "common/type/text_type.h"
#include "common/lang/comparator.h"

// 只是比较字符串长度
int TextType::compare(const Value &left, const Value &right) const {
  ASSERT(left.attr_type() == AttrType::TEXT, "invalid type");

  Value real_value = right;
  if (right.attr_type() != AttrType::TEXT) {
    Value::cast_to(right, AttrType::TEXT, real_value);
  }

  return common::compare_string((void *)left.value_.pointer_value_, left.length_, (void *)real_value.value_.pointer_value_, real_value.length_);
};

RC TextType::set_value_from_str(Value &val, const string &data) const {
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

//
RC TextType::cast_to(const Value &val, AttrType type, Value &result) const {
  switch (type) {
    // TEXT => INTS
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

    // TEXT => FLOATS
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
    case (AttrType::TEXT): {
      result = val;
    } break;
    case (AttrType::CHARS): {
      result.set_string(val.get_string().c_str());
    } break;
    default:
      return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

// FLOATS > INTS > BOOLEANS > CHARS
int TextType::cast_cost(AttrType type) {
  switch (type) {
    case (AttrType::CHARS):
      return 0;
    default:
      return INT32_MAX;
  }
  return INT32_MAX;
}

RC TextType::to_string(const Value &val, string &result) const {
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}