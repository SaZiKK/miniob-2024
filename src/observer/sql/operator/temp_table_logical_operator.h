#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"
#include "common/types.h"

/**
 * @brief 表示创建一张临时的表格的物理算子
 * @details 表格不实际存在于文件系统当中，只用来临时打印输出
 * @ingroup LogicalOperator
 */
class TempTableLogicalOperator : public LogicalOperator {
 public:
  TempTableLogicalOperator(std::vector<std::string> attr_names, std::vector<Value> values) : attr_names_(attr_names), values_(values) {}
  virtual ~TempTableLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::TEMP_TABLE; }

  const std::vector<std::string> &attr_names() const { return attr_names_; }
  const std::vector<Value> &values() const { return values_; }

 private:
  std::vector<std::string> attr_names_;
  std::vector<Value> values_;
};
