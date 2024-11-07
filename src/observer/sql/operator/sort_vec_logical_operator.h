#pragma once

#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"

class SortVecLogicalOperator : public LogicalOperator {
 public:
  SortVecLogicalOperator(Field *left_field, Field *right_field, Value *left_value, Value *right_value, VecFuncExpr::VecFuncType distance_func,
                         int limit_num);
  virtual ~SortVecLogicalOperator() = default;

  Field *left_field() const { return left_field_; }
  Field *right_field() const { return right_field_; }

  Value *left_value() const { return left_value_; }
  Value *right_value() const { return right_value_; }

  VecFuncExpr::VecFuncType distance_func() const { return distance_func_; }
  int limit_num() const { return limit_num_; }

  LogicalOperatorType type() const override { return LogicalOperatorType::SORTVEC; }

 private:
  Field *left_field_ = nullptr;
  Field *right_field_ = nullptr;
  Value *left_value_ = nullptr;
  Value *right_value_ = nullptr;

  VecFuncExpr::VecFuncType distance_func_;
  int limit_num_;
};
