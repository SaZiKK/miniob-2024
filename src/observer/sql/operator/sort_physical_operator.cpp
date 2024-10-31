#include "sql/operator/sort_physical_operator.h"
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

void SortByPriority(std::vector<ValueListTuple> &nums, const std::vector<int> &indexes, const std::vector<bool> &flags) {
  auto comparator = [&](ValueListTuple a, ValueListTuple b) {
    for (size_t i = 0; i < indexes.size(); ++i) {
      int index = indexes[i];

      Value left_value;
      Value right_value;
      a.cell_at(index, left_value);
      b.cell_at(index, right_value);

      if (left_value.get_null() && right_value.get_null()) continue;
      int result = left_value.compare(right_value);
      if (result != 0) return flags[i] ? (result == -1) : (result == 1);
    }
    return false;
  };

  std::stable_sort(nums.begin(), nums.end(), comparator);
}

SortPhysicalOperator::SortPhysicalOperator(std::vector<Field> order_by_fields) : order_by_fields_(order_by_fields) {
  order_by_indexes_.resize(order_by_fields.size());
  order_by_flags_.resize(order_by_fields.size());
}

RC SortPhysicalOperator::open(Trx *trx, const Tuple *main_tuple) {
  if (children_.empty()) return RC::INTERNAL;
  return children_[0]->open(trx, main_tuple);
}

RC SortPhysicalOperator::next(const Tuple *main_tuple) {
  RC rc = RC::SUCCESS;
  cur_index++;
  if (has_collected == false) {
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

    if (!valueList_tuples_.empty()) {
      std::unordered_map<string, int> fields_map;
      for (int i = 0; i < valueList_tuples_[0].cell_num(); i++) {
        TupleCellSpec spec;
        valueList_tuples_[0].spec_at(i, spec);

        string str = string(spec.table_name()) + string(spec.field_name());
        fields_map.insert(std::make_pair(str, i));
      }

      for (size_t i = 0; i < order_by_fields_.size(); i++) {
        if (!order_by_fields_[i].is_asc()) return RC::INVALID_ARGUMENT;
        order_by_flags_[i] = order_by_fields_[i].is_asc() == 1 ? true : false;
        string str = string(order_by_fields_[i].table_name()) + string(order_by_fields_[i].field_name());

        if (!fields_map.count(str)) return RC::INVALID_ARGUMENT;

        order_by_indexes_[i] = fields_map[str];
      }
    }

    // sort
    SortByPriority(valueList_tuples_, order_by_indexes_, order_by_flags_);
    has_collected = true;
  }
  if (cur_index >= (int)valueList_tuples_.size()) {
    order_by_fields_.clear();
    order_by_fields_.resize(0);
    order_by_indexes_.clear();
    order_by_indexes_.resize(0);
    order_by_flags_.clear();
    order_by_flags_.resize(0);
    valueList_tuples_.clear();
    valueList_tuples_.resize(0);
    has_collected = false;
    cur_index = -1;
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

Tuple *SortPhysicalOperator::current_tuple() { return &valueList_tuples_[cur_index]; }

RC SortPhysicalOperator::close() { return children_[0]->close(); }