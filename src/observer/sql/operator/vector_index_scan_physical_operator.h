#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"

/**
 * @brief 向量索引扫描物理算子
 * @ingroup PhysicalOperator
 */
class VecIndexScanPhysicalOperator : public PhysicalOperator {
 public:
  VecIndexScanPhysicalOperator(Table *table, int limit, DistanceFuncType type, Value value);

  virtual ~VecIndexScanPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::VEC_INDEX_SCAN; }

  std::string param() const override;

  RC open(Trx *trx, const Tuple *main_tuple = nullptr) override;
  RC next(const Tuple *main_tuple = nullptr) override;
  RC close() override;

  Tuple *current_tuple() override;

 private:
  // get table data
  Trx *trx_ = nullptr;
  Table *table_ = nullptr;
  ReadWriteMode mode_ = ReadWriteMode::READ_WRITE;
  RecordFileScanner record_scanner_;

  // get tuple
  int curIndex = -1;
  RowTuple tuple_;

  // vec para
  int limit_;
  DistanceFuncType type_;
  Value value_;

  // records
  vector<Record> records_;
};
