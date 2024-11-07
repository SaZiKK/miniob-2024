#include "storage/table/view_meta.h"

ViewMeta::ViewMeta(const ViewMeta &other)
    : view_id_(other.view_id_), name_(other.name_), tables_(other.tables_), fields_(other.fields_), record_size_(other.record_size_) {}

int ViewMeta::view_id() const { return view_id_; }

const char *ViewMeta::name() const { return name_.c_str(); }

const std::vector<Table> &ViewMeta::tables() const { return tables_; }

const std::vector<FieldMeta> &ViewMeta::fields() const { return fields_; }

int ViewMeta::record_size() const { return record_size_; }

RC ViewMeta::init() {
  //
  return RC::UNIMPLEMENTED;
}