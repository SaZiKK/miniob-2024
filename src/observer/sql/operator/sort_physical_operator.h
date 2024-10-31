
#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "storage/record/record_manager.h"
#include "storage/table/table.h"
#include <vector>

/**
 * @brief 聚合函数物理算子
 * @ingroup PhysicalOperator
 */
class SortPhysicalOperator : public PhysicalOperator {
 public:
  SortPhysicalOperator(std::vector<Field> order_by_fields);

  virtual ~SortPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::SORT; }

  Tuple *current_tuple() override;

  RC open(Trx *trx) override;
  RC next(const Tuple *main_tuple = nullptr) override;
  RC close() override;

 private:
  Trx *trx = nullptr;

  std::vector<Field> order_by_fields_;            // 排序依靠的 Field
  std::vector<int> order_by_indexes_;             // 排序依靠的 Field 在下层 Tuple 中的位置
  std::vector<bool> order_by_flags_;              // 排序依靠的 Field 是升序还是降序
  std::vector<ValueListTuple> valueList_tuples_;  // 存储的 TupleList
  bool has_collected = false;                     // 是否排序过
  int cur_index = -1;                             // 上层算子当前拿走的 Tuple 的下标
};