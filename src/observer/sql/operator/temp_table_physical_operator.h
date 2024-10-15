#pragma once

#include "common/rc.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"
#include "common/types.h"

class Table;

/**
 * @brief 临时表物理算子
 * @ingroup PhysicalOperator
 */
class TempTablePhysicalOperator : public PhysicalOperator {
 public:
  TempTablePhysicalOperator(std::vector<std::string> attr_names, std::vector<Value> values)
      : tuple_(values), attr_names_(attr_names), values_(values) {}

  virtual ~TempTablePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::TEMP_TABLE; }
  RC tuple_schema(TupleSchema &schema) const override;
  RC open(Trx *trx) override;

  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

 private:
  int num;
  FakeTuple tuple_;
  std::vector<std::string> attr_names_;
  std::vector<Value> values_;
};
