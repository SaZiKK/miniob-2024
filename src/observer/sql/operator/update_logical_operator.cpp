#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<std::pair<Value, FieldMeta>> update_map)
    : table_(table), update_map_(update_map) {}
