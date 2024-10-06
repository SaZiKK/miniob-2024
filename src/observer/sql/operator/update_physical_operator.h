#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;
class FieldMeta;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, FieldMeta *field_meta, Value *value)
      : table_(table), field_meta_(field_meta), value_(value)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table              *table_      = nullptr;
  Trx                *trx_        = nullptr;
  FieldMeta          *field_meta_ = nullptr;
  Value              *value_      = nullptr;
  std::vector<Record> records_;
};
