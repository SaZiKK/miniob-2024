#pragma once

#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"

class SortLogicalOperator : public LogicalOperator {
 public:
  SortLogicalOperator(std::vector<Field> order_by_fields);
  virtual ~SortLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::SORT; }

  std::vector<Field> order_by_fields() const { return order_by_fields_; }

 private:
  std::vector<Field> order_by_fields_;
};
