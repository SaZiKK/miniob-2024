#pragma once

#include <string>

#include "sql/stmt/stmt.h"

struct CreateVecIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 创建向量索引的语句
 * @ingroup Statement
 */
class CreateVecIndexStmt : public Stmt {
 public:
  CreateVecIndexStmt(Table *table, vector<FieldMeta> field_meta, string index_name, string distance_name, string type_name, int lists, int probes)
      : table_(table),
        field_meta_(field_meta),
        index_name_(index_name),
        distance_name_(distance_name),
        type_name_(type_name),
        lists_(lists),
        probes_(probes) {}

  virtual ~CreateVecIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VEC_INDEX; }

  Table *table() const { return table_; }
  const vector<FieldMeta> field_meta() const { return field_meta_; }
  const std::string &index_name() const { return index_name_; }

  string distance_name() const { return distance_name_; }
  string type_name() const { return type_name_; }
  int lists() const { return lists_; }
  int probes() const { return probes_; }

 public:
  static RC create(Db *db, CreateVecIndexSqlNode &create_vec_index, Stmt *&stmt);

 private:
  Table *table_ = nullptr;
  vector<FieldMeta> field_meta_;
  std::string index_name_;

  // para part
  string distance_name_;
  string type_name_;
  int lists_;
  int probes_;
};
