#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "storage/table/table.h"

class ViewMeta {
 public:
  ViewMeta() = default;
  virtual ~ViewMeta() = default;

  ViewMeta(const ViewMeta &other);

  RC init();  // TODO: implement

  int view_id() const;

  const char *name() const;

  const std::vector<Table> &tables() const;

  const std::vector<FieldMeta> &fields() const;

  int record_size() const;

 protected:
  int32_t view_id_ = -1;
  std::string name_;
  std::vector<Table> tables_;
  std::vector<FieldMeta> fields_;
  map<string, string> fields_owner_;
  int record_size_ = 0;
};