#include "common/rc.h"
#include "common/type/data_type.h"

class DateType : public DataType {
 public:
  DateType() : DataType(AttrType::DATE) {}

  virtual ~DateType() = default;

  int compare(const Value &left, const Value &right) const override;

  RC cast_to(const Value &val, AttrType type, Value &result) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  int cast_cost(AttrType type) override;

  RC to_string(const Value &val, string &result) const override;

  static bool check_date(const Value *value);
  static bool check_date(int date);

  static string get_year(string date);
  static string get_month(string date);
  static string get_day(string date);

  static string get_month_inEnglish(string date);
};