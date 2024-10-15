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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/temp_table_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/table/table.h"

using namespace std;

RC TempTablePhysicalOperator::open(Trx *trx) {
  if (attr_names_.size() != values_.size() || attr_names_.size() == 0) {
    return RC::INVALID_ARGUMENT;
  }
  num = 0;
  return RC::SUCCESS;
}

RC TempTablePhysicalOperator::next() {
  num++;
  if (num > 1) return RC::INVALID_ARGUMENT;
  return RC::SUCCESS;
}

RC TempTablePhysicalOperator::close() { return RC::SUCCESS; }

RC TempTablePhysicalOperator::tuple_schema(TupleSchema &schema) const {
  for (auto it : attr_names_) schema.append_cell(TupleCellSpec("", it.c_str(), it.c_str()));
  return RC::SUCCESS;
}

Tuple *TempTablePhysicalOperator::current_tuple() { return &tuple_; }
