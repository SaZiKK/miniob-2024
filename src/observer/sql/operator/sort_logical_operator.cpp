#include "sql/operator/sort_logical_operator.h"

SortLogicalOperator::SortLogicalOperator(std::vector<Field> order_by_fields) : order_by_fields_(order_by_fields) {}