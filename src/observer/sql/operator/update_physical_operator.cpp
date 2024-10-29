#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  child->close();

  if (records_.empty()) {
    LOG_WARN("no records to update");
  }

  std::vector<char *> backup_datas;
  for (Record &record : records_) {
    Record backup_record;
    char *old_data = record.data();
    char *backup_data = (char *)malloc(record.len());
    memcpy(backup_data, old_data, record.len());

    backup_datas.push_back(backup_data);
  }

  int update_num = 0;

  // 先收集记录再更新
  // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  for (Record &record : records_) {
    rc = trx_->update_records(table_, record, update_map_);
    ++update_num;
    if (rc != RC::SUCCESS) {
      // 如果更新失败，需要回滚
      assert(backup_datas.size() == records_.size());  // 确保两个 vector 长度相等
      for (int i = 0; i < update_num; ++i) {
        char *backup_data = backup_datas[i];
        Record &record = records_[i];

        record.set_data(backup_data);
        table_->record_handler()->update_record(&record);
      }
      LOG_WARN("failed to update record, recovering. table=%s, rc=%d:%s", table_->name(), rc, strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }
