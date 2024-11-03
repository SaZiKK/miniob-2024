#include "sql/operator/sort_vec_logical_operator.h"

SortVecLogicalOperator::SortVecLogicalOperator(Field *left_field, Field *right_field, Value *left_value, Value *right_value,
                                               VecFuncExpr::VecFuncType distance_func, int limit_num)
    : left_field_(left_field),
      right_field_(right_field),
      left_value_(left_value),
      right_value_(right_value),
      distance_func_(distance_func),
      limit_num_(limit_num){};