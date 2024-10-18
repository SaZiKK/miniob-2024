#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;
class FieldMeta;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator {
 public:
  UpdatePhysicalOperator(Table *table, std::vector<std::pair<Value, FieldMeta>> update_map) : table_(table), update_map_(update_map) {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

 private:
  Table *table_ = nullptr;
  Trx *trx_ = nullptr;
  std::vector<std::pair<Value, FieldMeta>> update_map_;
  std::vector<Record> records_;
};
