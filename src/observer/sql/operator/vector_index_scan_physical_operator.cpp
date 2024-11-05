#include "sql/operator/vector_index_scan_physical_operator.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

VecIndexScanPhysicalOperator::VecIndexScanPhysicalOperator(Table *table, int limit, DistanceFuncType type, Value value)
    : table_(table), limit_(limit), type_(type), value_(value) {}

RC VecIndexScanPhysicalOperator::open(Trx *trx, const Tuple *main_tuple) {
  RC rc = RC::SUCCESS;
  trx_ = trx;
  rc = table_->get_record_scanner(record_scanner_, trx, mode_);
  if (rc == RC::SUCCESS) tuple_.set_schema(table_, table_->table_meta().field_metas());
  KMEANS kmeans = table_->kmeans();
  vector<RID> results;
  kmeans.searchVector(value_, limit_, results);

  for (size_t i = 0; i < results.size(); i++) {
    Record record;
    rc = table_->get_record(results[i], record);
    records_.push_back(record);
    if (rc != RC::SUCCESS) return rc;
  }
  return RC::SUCCESS;
}

RC VecIndexScanPhysicalOperator::next(const Tuple *main_tuple) {
  curIndex++;
  if (curIndex >= (int)records_.size()) return RC::RECORD_EOF;
  return RC::SUCCESS;
}

RC VecIndexScanPhysicalOperator::close() {
  records_.clear();
  records_.resize(0);
  return RC::SUCCESS;
}

Tuple *VecIndexScanPhysicalOperator::current_tuple() {
  tuple_.set_record(&records_[curIndex]);
  return &tuple_;
}

string VecIndexScanPhysicalOperator::param() const {
  string index_name = table_->kmeans().index_name_;
  string table_name = table_->name();

  return index_name + " ON " + table_name;
}