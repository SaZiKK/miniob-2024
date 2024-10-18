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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class Table;
class FilterStmt;
class FieldMeta;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt {
 public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, FilterStmt *filter_stmt, std::vector<FieldMeta> field_metas, std::vector<UpdateTarget> update_targets)
      : table_(table), filter_stmt_(filter_stmt), field_metas_(field_metas), update_targets_(update_targets) {}
  ~UpdateStmt() override;

 public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);
  StmtType type() const override { return StmtType::UPDATE; }

 public:
  Table *table() const { return table_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  std::vector<FieldMeta> field_metas() const { return field_metas_; }
  std::vector<UpdateTarget> update_targets() const { return update_targets_; }

 private:
  Table *table_ = nullptr;
  FilterStmt *filter_stmt_ = nullptr;
  std::vector<FieldMeta> field_metas_;
  std::vector<UpdateTarget> update_targets_;
};
