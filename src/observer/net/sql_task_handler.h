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
// Created by Wangyunlai on 2024/01/10.
//

#pragma once

#include "common/rc.h"
#include "session/session_stage.h"
#include "sql/executor/execute_stage.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/parser/parse_stage.h"
#include "sql/parser/resolve_stage.h"
#include "sql/query_cache/query_cache_stage.h"

class Communicator;
class SQLStageEvent;

/**
 * @brief SQL请求的处理器
 * @ingroup SQL
 */
class SqlTaskHandler {
 public:
  SqlTaskHandler() = default;
  virtual ~SqlTaskHandler() = default;

  /**
   * @brief 指定连接上有数据可读时就读取消息然后处理
   * @details 步骤包含接收请求、处理请求，然后返回应答
   * @param communicator 连接对象
   * @return RC 如果返回失败，就要断开连接
   */
  RC handle_event(Communicator *communicator);

  RC handle_sql(SQLStageEvent *sql_event);

 private:
  SessionStage session_stage_;         /// 会话阶段
  QueryCacheStage query_cache_stage_;  /// 查询缓存阶段
  ParseStage parse_stage_;             /// 解析阶段。将SQL解析成语法树 ParsedSqlNode
  ResolveStage resolve_stage_;         /// 解析阶段。将语法树解析成Stmt(statement)
  OptimizeStage optimize_stage_;       /// 优化阶段。将语句优化成执行计划，包含规则优化和物理优化
  ExecuteStage execute_stage_;         /// 执行阶段
};