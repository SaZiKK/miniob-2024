
#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "storage/record/record_manager.h"
#include "storage/table/table.h"
#include <vector>

/**
 * @brief 向量排序物理算子
 * @ingroup PhysicalOperator
 */
class SortVecPhysicalOperator : public PhysicalOperator {
 public:
  SortVecPhysicalOperator(Field *left_field, Field *right_field, Value *left_value, Value *right_value, VecFuncExpr::VecFuncType distance_func,
                          int limit_num);

  virtual ~SortVecPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::SORTVEC; }

  Tuple *current_tuple() override;

  RC SortByDistanceFunc();
  static float Distance(Value v1, Value v2, VecFuncExpr::VecFuncType distance_func);

  RC open(Trx *trx, const Tuple *main_tuple = nullptr) override;
  RC next(const Tuple *main_tuple = nullptr) override;
  RC close() override;

 private:
  Trx *trx = nullptr;

  std::vector<ValueListTuple> valueList_tuples_;  // 存储的 TupleList
  int left_index_ = -1;                           // 左侧 Field 下标
  int right_index_ = -1;                          // 右侧 Field 下标
  int cur_index = -1;                             // 上层算子当前拿走的 Tuple 的下标

  // para part
  Field *left_field_ = nullptr;
  Field *right_field_ = nullptr;
  Value *left_value_ = nullptr;
  Value *right_value_ = nullptr;

  VecFuncExpr::VecFuncType distance_func_;
  int limit_num_;
};