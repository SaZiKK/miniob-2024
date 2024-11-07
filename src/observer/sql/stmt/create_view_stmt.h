#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "sql/expr/tuple.h"

class CreateViewStmt : public Stmt {
 public:
  CreateViewStmt(const std::string &view_name, const std::string &query) : view_name_(view_name), query_(query) {}

  const std::string &view_name() const { return view_name_; }
  const std::string &query() const { return query_; }

 private:
  std::string view_name_;
  std::vector<Table *> tables_;
  std::string query_;
  bool is_complex_ = false;
};