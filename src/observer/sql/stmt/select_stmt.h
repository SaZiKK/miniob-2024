/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt {
 public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

 public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, bool &use_father_table_flags,
                   std::unordered_map<string, string> father_alias = std::unordered_map<string, string>(),
                   std::unordered_map<string, Table *> father_tables = std::unordered_map<string, Table *>());

 public:
  const std::vector<Table *> &tables() const { return tables_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  FilterStmt *having_filter_stmt() const { return having_filter_stmt_; }

  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }
  std::vector<std::unique_ptr<Expression>> &order_by() { return order_by_; }

 private:
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;
  FilterStmt *having_filter_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> group_by_;
  std::vector<std::unique_ptr<Expression>> order_by_;
};
