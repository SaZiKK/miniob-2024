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
// Created by WangYunlai on 2022/11/18.
//

#include "sql/executor/sql_result.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "session/session.h"
#include "storage/trx/trx.h"

SqlResult::SqlResult(Session *session) : session_(session) {}

void SqlResult::set_tuple_schema(const TupleSchema &schema) { tuple_schema_ = schema; }

RC SqlResult::open() {
  if (nullptr == operator_) {
    return RC::INVALID_ARGUMENT;
  }

  Trx *trx = session_->current_trx();
  trx->start_if_need();
  return operator_->open(trx);
}

RC SqlResult::close() {
  if (nullptr == operator_) {
    return RC::INVALID_ARGUMENT;
  }
  RC rc = operator_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close operator. rc=%s", strrc(rc));
  }

  operator_.reset();

  if (session_ && !session_->is_trx_multi_operation_mode()) {
    if (rc == RC::SUCCESS) {
      rc = session_->current_trx()->commit();
    } else {
      RC rc2 = session_->current_trx()->rollback();
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("rollback failed. rc=%s", strrc(rc2));
      }
    }
  }
  return rc;
}

// 获取"下一个"元组
RC SqlResult::next_tuple(Tuple *&tuple) {
  // 每想获取一个元组，都调用当前物理算子的 next 函数，然后当前物理算子的元组就会变成"下一个"元组
  RC rc = operator_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  tuple = operator_->current_tuple();
  return rc;
}

RC SqlResult::next_chunk(Chunk &chunk) {
  RC rc = operator_->next(chunk);
  return rc;
}

void SqlResult::set_operator(std::unique_ptr<PhysicalOperator> oper) {
  ASSERT(operator_ == nullptr, "current operator is not null. Result is not closed?");
  operator_ = std::move(oper);
  operator_->tuple_schema(tuple_schema_);
}
