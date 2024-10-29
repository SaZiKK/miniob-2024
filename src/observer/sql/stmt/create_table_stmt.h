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
// Created by Wangyunlai on 2023/6/13.
//

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "sql/expr/tuple.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateTableStmt : public Stmt {
 public:
  CreateTableStmt(const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos, StorageFormat storage_format,
                  TupleSchema tuple_schema, std::vector<std::vector<Value>> tuple_list, bool use_select = false)
      : table_name_(table_name),
        attr_infos_(attr_infos),
        storage_format_(storage_format),
        tuple_schema_(tuple_schema),
        tuple_list_(tuple_list),
        use_select_(use_select) {}
  virtual ~CreateTableStmt() = default;

  StmtType type() const override { return StmtType::CREATE_TABLE; }

  const std::string &table_name() const { return table_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  const StorageFormat storage_format() const { return storage_format_; }

  TupleSchema tuple_schema() const { return tuple_schema_; }
  std::vector<std::vector<Value>> tuple_list() const { return tuple_list_; }
  bool use_select() const { return use_select_; }
  const std::vector<std::unique_ptr<Expression>> &query_expressions() const { return query_expressions_; }

  static RC create(Db *db, CreateTableSqlNode &create_table, Stmt *&stmt);
  static StorageFormat get_storage_format(const char *format_str);

 private:
  std::string table_name_;
  std::vector<AttrInfoSqlNode> attr_infos_;
  StorageFormat storage_format_;

  // create select 部分
  TupleSchema tuple_schema_;
  std::vector<std::vector<Value>> tuple_list_;
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  bool use_select_ = false;
};