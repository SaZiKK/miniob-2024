#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include "common/value.h"
#include <sstream>

static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int DateType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::DATE && right.attr_type() == AttrType::DATE, "not type DATE");
  int left_val  = left.get_int();
  int right_val = right.get_int();
  return common::compare_float((void *)&left_val, (void *)&right_val);
}

RC DateType::cast_to(const Value &val, AttrType type, Value &result) const { return RC::INVALID_ARGUMENT; }

RC DateType::set_value_from_str(Value &val, const string &data) const
{
  std::stringstream ss(data);
  int               numbers[3];
  string            token;
  for (int i = 0; i < 3; ++i) {
    if (getline(ss, token, '-')) {
      numbers[i] = std::stoi(token);
    } else {
      return RC::INVALID_ARGUMENT;
    }
  }

  int y = numbers[0], m = numbers[1], d = numbers[2];
  val.set_int(y * 10000 + m * 100 + d);
  return RC::SUCCESS;
}

int DateType::cast_cost(AttrType type)
{
  if (type == AttrType::DATE)
    return 0;
  return INT32_MAX;
}

RC DateType::to_string(const Value &val, string &result) const
{
  if (val.attr_type() != AttrType::DATE)
    return RC::INVALID_ARGUMENT;

  result = std::to_string(val.get_int());
  return RC::SUCCESS;
}

bool DateType::check_date(int y, int m, int d)
{
  bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

bool DateType::check_date(string date_str)
{
  std::stringstream ss(date_str);
  int               numbers[3];
  string            token;
  for (int i = 0; i < 3; ++i) {
    if (getline(ss, token, '-')) {
      numbers[i] = std::stoi(token);
    } else {
      return false;
    }
  }

  int  y = numbers[0], m = numbers[1], d = numbers[2];
  bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

bool DateType::check_date(const Value *value) { return false; }