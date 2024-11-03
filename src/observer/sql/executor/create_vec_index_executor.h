#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief 创建向量索引的执行器
 * @ingroup Executor
 * @note
 * 创建索引时不能做其它操作。MiniOB当前不完善，没有对一些并发做控制，包括schema的并发。
 */
class CreateVecIndexExecutor {
 public:
  CreateVecIndexExecutor() = default;
  virtual ~CreateVecIndexExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};