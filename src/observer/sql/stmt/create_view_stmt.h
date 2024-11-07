#pragma once

#include <string>
#include <vector>

#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/tuple.h"

class CreateViewStmt : public Stmt {
 public:
  CreateViewStmt(const std::string &view_name, std::vector<Table *> tables, FilterStmt *filter_stmt, std::vector<ViewAttrInfoSqlNode> attr_infos)
      : view_name_(view_name), tables_(tables), filter_stmt_(filter_stmt) {}

  const std::string &view_name() const { return view_name_; }

  const std::vector<Table *> &tables() const { return tables_; }

  FilterStmt *filter_stmt() const { return filter_stmt_; }

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  void set_is_allow_insert(bool is_allow_insert) { is_allow_insert_ = is_allow_insert; }
  bool is_allow_insert() const { return is_allow_insert_; }

  static RC create(Db *db, CreateViewSqlNode &create_view, Stmt *&stmt);

 private:
  std::string view_name_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;  // 过滤条件, view需要记录

  bool is_allow_insert_ = false;
};