#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include "common/value.h"
#include <sstream>

static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static string monEng[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int DateType::compare(const Value &left, const Value &right) const {
  int left_val = left.get_date();
  int right_val = right.get_date();
  return common::compare_int((void *)&left_val, (void *)&right_val);
}

RC DateType::cast_to(const Value &val, AttrType type, Value &result) const {
  switch (type) {
    case AttrType::DATE:
      result = val;
      break;
    case AttrType::CHARS:
      result.set_string(val.to_string().c_str());
      break;
    default:
      return RC::UNSUPPORTED;
  }
  return RC::SUCCESS;
}

RC DateType::set_value_from_str(Value &val, const string &data) const {
  std::stringstream ss(data);
  int numbers[3];
  string token;
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

int DateType::cast_cost(AttrType type) {
  if (type == AttrType::DATE) return 0;
  return INT32_MAX;
}

RC DateType::to_string(const Value &val, string &result) const {
  if (val.attr_type() != AttrType::DATE) return RC::INVALID_ARGUMENT;

  string str = std::to_string(val.get_int());
  result = str.substr(0, 4) + '-' + str.substr(4, 2) + '-' + str.substr(6, 2);
  return RC::SUCCESS;
}

bool DateType::check_date(const Value *value) {
  if (value->attr_type() != AttrType::DATE) {
    return false;
  }
  int date = value->get_int();
  int y = date / 10000;
  int m = date % 10000 / 100;
  int d = date % 100;
  bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

bool DateType::check_date(int date) {
  int y = date / 10000;
  int m = date % 10000 / 100;
  int d = date % 100;
  bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

string DateType::get_year(string date) { return date.substr(0, 4); }
string DateType::get_month(string date) { return date.substr(4, 2); }
string DateType::get_day(string date) { return date.substr(6, 2); }
string DateType::get_month_inEnglish(string date) { return monEng[std::stoi(get_month(date))]; }