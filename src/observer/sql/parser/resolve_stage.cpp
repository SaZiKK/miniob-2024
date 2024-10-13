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

#include <string.h>
#include <string>

#include "resolve_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/stmt.h"

using namespace common;

RC ResolveStage::handle_request(SQLStageEvent *sql_event) {
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();

  // SQL 语句执行结果，包括错误信息
  SqlResult *sql_result = session_event->sql_result();

  // 获取到目标表格对应的 Db 对象
  Db *db = session_event->session()->get_current_db();

  // 空 Db 检查
  if (nullptr == db) {
    LOG_ERROR("cannot find current db");
    rc = RC::SCHEMA_DB_NOT_EXIST;
    sql_result->set_return_code(rc);
    sql_result->set_state_string("no db selected");
    return rc;
  }

  // 获取到 Parse 模块解析的结果
  ParsedSqlNode *sql_node = sql_event->sql_node().get();

  // 准备创建 Stmt 对象
  Stmt *stmt = nullptr;

  // 根据 Parse 模块解析的结果，创建对应的 Stmt 对象
  rc = Stmt::create_stmt(db, *sql_node, stmt);

  // 创建 Stmt 失败检查
  if (rc != RC::SUCCESS && rc != RC::UNIMPLEMENTED) {
    LOG_WARN("failed to create stmt. rc=%d:%s", rc, strrc(rc));
    sql_result->set_return_code(rc);
    return rc;
  }

  // 将创建好的 Stmt 对象写入 sql_event，进入下一模块
  sql_event->set_stmt(stmt);

  return rc;
}
