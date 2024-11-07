#include "sql/operator/sort_vec_physical_operator.h"
#include "vectorIndex/Kmeans.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "common/value.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <memory>
#include <algorithm>
#include <vector>

SortVecPhysicalOperator::SortVecPhysicalOperator(Field *left_field, Field *right_field, Value *left_value, Value *right_value,
                                                 VecFuncExpr::VecFuncType distance_func, int limit_num)
    : left_field_(left_field),
      right_field_(right_field),
      left_value_(left_value),
      right_value_(right_value),
      distance_func_(distance_func),
      limit_num_(limit_num) {}

float SortVecPhysicalOperator::Distance(Value v1, Value v2, VecFuncExpr::VecFuncType distance_func) {
  vector<float> vec1 = v1.get_vector();
  vector<float> vec2 = v2.get_vector();
  switch (distance_func) {
    case VecFuncExpr::VecFuncType::COSINE_DISTANCE:
      return KMEANS::COSINE_DISTANCE(vec1, vec2);
    case VecFuncExpr::VecFuncType::INNER_PRODUCT:
      return KMEANS::INNER_PRODUCT(vec1, vec2);
    case VecFuncExpr::VecFuncType::L2_DISTANCE:
      return KMEANS::L2_DISTANCE(vec1, vec2);
  }
  return 0;
}

void SortByFieldAndField(int index1, int index2, vector<ValueListTuple> &valueList_tuples, VecFuncExpr::VecFuncType type) {
  auto comparator = [&](ValueListTuple a, ValueListTuple b) {
    Value left_value1;
    Value right_value1;
    Value left_value2;
    Value right_value2;
    a.cell_at(index1, left_value1);
    a.cell_at(index2, right_value1);
    b.cell_at(index1, left_value2);
    b.cell_at(index2, right_value2);
    return SortVecPhysicalOperator::Distance(left_value1, right_value1, type) < SortVecPhysicalOperator::Distance(left_value2, right_value2, type);
  };

  std::stable_sort(valueList_tuples.begin(), valueList_tuples.end(), comparator);
}

void SortByValueAndField(int index, Value value, vector<ValueListTuple> &valueList_tuples, VecFuncExpr::VecFuncType type) {
  auto comparator = [&](ValueListTuple a, ValueListTuple b) {
    Value left_value1;
    Value left_value2;
    a.cell_at(index, left_value1);
    b.cell_at(index, left_value2);
    return SortVecPhysicalOperator::Distance(left_value1, value, type) < SortVecPhysicalOperator::Distance(left_value2, value, type);
  };

  std::stable_sort(valueList_tuples.begin(), valueList_tuples.end(), comparator);
}

RC SortVecPhysicalOperator::SortByDistanceFunc() {
  RC rc = RC::SUCCESS;

  // ? 11 - ff  10 - fv  01 - vf
  int flag = (left_field_ != nullptr) * 10 + (right_field_ != nullptr);

  switch (flag) {
    case 00:
      return RC::INVALID_ARGUMENT;
      break;
    case 10:
      SortByValueAndField(left_index_, *right_value_, valueList_tuples_, distance_func_);
      break;
    case 01:
      SortByValueAndField(right_index_, *left_value_, valueList_tuples_, distance_func_);
      break;
    case 11:
      SortByFieldAndField(left_index_, right_index_, valueList_tuples_, distance_func_);
      break;
    default:
      rc = RC::INTERNAL;
  }
  return rc;
}

RC SortVecPhysicalOperator::open(Trx *trx, const Tuple *main_tuple) {
  RC rc = RC::SUCCESS;
  if (children_.empty()) return RC::INTERNAL;

  rc = children_[0]->open(trx, main_tuple);
  if (rc != RC::SUCCESS) return rc;

  valueList_tuples_.clear();
  valueList_tuples_.resize(0);
  while ((rc = children_[0]->next(main_tuple)) == RC::SUCCESS) {
    // 获取下层算子的元组，并存储起来
    Tuple *tuple = children_[0]->current_tuple();
    std::vector<Value> values;
    std::vector<TupleCellSpec> specs;
    for (int i = 0; i < tuple->cell_num(); i++) {
      Value value;
      tuple->cell_at(i, value);
      values.push_back(value);

      TupleCellSpec spec;
      tuple->spec_at(i, spec);
      specs.push_back(spec);
    }
    ValueListTuple value_list_tuple;
    value_list_tuple.set_cells(values);
    value_list_tuple.set_names(specs);
    valueList_tuples_.push_back(value_list_tuple);
  }
  for (int i = 0; i < valueList_tuples_[0].cell_num(); i++) {
    TupleCellSpec spec;
    valueList_tuples_[0].spec_at(i, spec);

    if (left_field_ != nullptr && strcmp(left_field_->field_name(), spec.field_name()) == 0) left_index_ = i;
    if (right_field_ != nullptr && strcmp(right_field_->field_name(), spec.field_name()) == 0) right_index_ = i;
  }
  SortByDistanceFunc();
  return RC::SUCCESS;
}

RC SortVecPhysicalOperator::next(const Tuple *main_tuple) {
  cur_index++;
  if (cur_index >= limit_num_ || cur_index >= (int)valueList_tuples_.size()) {
    valueList_tuples_.clear();
    valueList_tuples_.resize(0);
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

Tuple *SortVecPhysicalOperator::current_tuple() { return &valueList_tuples_[cur_index]; }

RC SortVecPhysicalOperator::close() { return children_[0]->close(); }