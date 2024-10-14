#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Value *values, FieldMeta *fields) : table_(table), values_(values), fields_(fields){};
