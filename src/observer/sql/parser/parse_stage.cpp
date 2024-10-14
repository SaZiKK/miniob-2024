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

#include "parse_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "sql/parser/parse.h"

using namespace common;

RC ParseStage::handle_request(SQLStageEvent *sql_event) {
  RC rc = RC::SUCCESS;

  // SQL 语句执行结果，包括错误信息
  SqlResult *sql_result = sql_event->session_event()->sql_result();
  // 获取字符串形式的 SQL 语句
  const std::string &sql = sql_event->sql();

  ParsedSqlResult parsed_sql_result;

  // SQL 语句的解析过程，解析器在 yacc_sql 中实现
  parse(sql.c_str(), &parsed_sql_result);

  // 空 SQL 语句检查
  if (parsed_sql_result.sql_nodes().empty()) {
    sql_result->set_return_code(RC::SUCCESS);
    sql_result->set_state_string("");
    return RC::INTERNAL;
  }

  // 多条 SQL 语句检查
  if (parsed_sql_result.sql_nodes().size() > 1) {
    sql_debug("multi sql commands not finished yet");
    LOG_WARN("got multi sql commands but only 1 will be handled");
  }

  std::unique_ptr<ParsedSqlNode> sql_node = std::move(parsed_sql_result.sql_nodes().front());

  // 编译错误检查
  if (sql_node->flag == SCF_ERROR) {
    // set error information to event
    rc = RC::SQL_SYNTAX;
    sql_result->set_return_code(rc);
    sql_result->set_state_string("Failed to parse sql");
    return rc;
  }

  // 记录 Parse 模块处理完毕的 SQL 节点
  sql_event->set_sql_node(std::move(sql_node));

  return RC::SUCCESS;
}
