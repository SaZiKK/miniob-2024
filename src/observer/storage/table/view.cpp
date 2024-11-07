#include "storage/table/view.h"
#include <cstdint>
#include "common/log/log.h"

RC View::create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir, span<const AttrInfoSqlNode> attributes,
                StorageFormat storage_format) {
  LOG_WARN("use Table::create on a View");
  return RC::UNIMPLEMENTED;
}

RC View::open(Db *db, const char *meta_file, const char *base_dir) {
  LOG_WARN("use Table::open on a View");
  return RC::UNIMPLEMENTED;
}

RC View::insert_record(Record &record) {
  // TODO: implement
  LOG_WARN("use Table::insert_record on a View");
  return RC::SUCCESS;
}

RC View::make_record(int value_num, const Value *values, Record &record) {
  // TODO: implement
  LOG_WARN("use Table::make_record on a View");
  return RC::UNIMPLEMENTED;
}

RC View::delete_record(const RID &rid) {
  // TODO: implement
  LOG_WARN("use Table::delete_record on a View");
  return RC::UNIMPLEMENTED;
}

RC View::delete_record(const Record &record) {
  // TODO: implement
  LOG_WARN("use Table::delete_record on a View");
  return RC::UNIMPLEMENTED;
}

RC View::update_records(Record &record, std::vector<std::pair<Value, FieldMeta>> update_map_) {
  // TODO: implement
  LOG_WARN("use Table::update_records on a View");
  return RC::UNIMPLEMENTED;
}

RC View::update_record(Record &record, const char *attr_name, Value *value) {
  // TODO: implement
  LOG_WARN("use Table::update_record on a View");
  return RC::UNIMPLEMENTED;
}

RC View::get_record(const RID &rid, Record &record) {
  // TODO: implement
  LOG_WARN("use Table::get_record on a View");
  return RC::UNIMPLEMENTED;
}

RC View::drop() {
  // TODO: implement
  return RC::UNIMPLEMENTED;
}

RC View::recover_insert_record(Record &record) {
  // TODO: implement
  LOG_WARN("use Table::recover_insert_record on a View");
  return RC::UNIMPLEMENTED;
}

RC View::get_record_scanner(RecordFileScanner &scanner, Trx *trx, ReadWriteMode mode) {
  // TODO: implement
  LOG_WARN("use Table::get_record_scanner on a View");
  return RC::UNIMPLEMENTED;
}

RC View::get_chunk_scanner(ChunkFileScanner &scanner, Trx *trx, ReadWriteMode mode) {
  // TODO: implement
  LOG_WARN("use Table::get_chunk_scanner on a View");
  return RC::UNIMPLEMENTED;
}

RC View::visit_record(const RID &rid, function<bool(Record &)> visitor) {
  // TODO: implement
  LOG_WARN("use Table::visit_record on a View");
  return RC::UNIMPLEMENTED;
}

int32_t View::table_id() const {
  // TODO: implement
  LOG_WARN("use Table::table_id on a View");
  return -1;
}
