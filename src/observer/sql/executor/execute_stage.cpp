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
// Created by Longda on 2021/4/13.
//

#include <sstream>
#include <string>

#include "sql/executor/execute_stage.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "sql/executor/command_executor.h"
#include "sql/operator/calc_physical_operator.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/default/default_handler.h"

using namespace std;
using namespace common;

RC ExecuteStage::handle_request(SQLStageEvent *sql_event) {
  RC rc = RC::SUCCESS;

  // 根据物理算子决定执行的两条路径
  const unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();

  // 如果存在物理算子
  if (physical_operator != nullptr) {
    return handle_request_with_physical_operator(sql_event);
  }

  // 如果不存在物理算子
  SessionEvent *session_event = sql_event->session_event();

  // 拿到 Resolver 模块创建的 Stmt 对象
  Stmt *stmt = sql_event->stmt();
  if (stmt != nullptr) {
    // 处理 SQL 语句的执行模块，一些 SQL 语句不会生成对应的执行计划，直接使用
    // Executor 来执行
    CommandExecutor command_executor;
    rc = command_executor.execute(sql_event);

    // 设置结束信息
    session_event->sql_result()->set_return_code(rc);
  } else {
    return RC::INTERNAL;
  }
  return rc;
}

RC ExecuteStage::handle_request_with_physical_operator(SQLStageEvent *sql_event) {
  RC rc = RC::SUCCESS;

  // 拿出物理算子
  unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  ASSERT(physical_operator != nullptr, "physical operator should not be null");

  SqlResult *sql_result = sql_event->session_event()->sql_result();
  sql_result->set_operator(std::move(physical_operator));
  return rc;
}
