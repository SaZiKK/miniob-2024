/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
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
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, Value *values, int value_amount, FilterStmt *filter_stmt, FieldMeta *field_meta)
      : table_(table), values_(values), value_amount_(value_amount), filter_stmt_(filter_stmt), field_meta_(field_meta)
  {}
  ~UpdateStmt() override;

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);
  StmtType  type() const override { return StmtType::UPDATE; }

public:
  Table      *table() const { return table_; }
  Value      *values() const { return values_; }
  int         value_amount() const { return value_amount_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  FieldMeta  *field_meta() const { return field_meta_; }

private:
  Table      *table_        = nullptr;  // 目标表格名称
  Value      *values_       = nullptr;  // 更新字段
  int         value_amount_ = 0;        // 更新属性
  FilterStmt *filter_stmt_  = nullptr;  // 筛选条件
  FieldMeta  *field_meta_   = nullptr;  // 更新域
};
