#include "sql/executor/drop_table_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"

RC DropTableExecutor::execute(SQLStageEvent *sql_event) {
  // 拿到 Stmt 对象以及 Session 对象
  Stmt *stmt = sql_event->stmt();
  Session *session = sql_event->session_event()->session();

  // 检查 SQL 命令是否为 drop table
  ASSERT(stmt->type() == StmtType::DROP_TABLE, "drop table executor can not run this command: %d", static_cast<int>(stmt->type()));

  // 强制类型转换 (从基类到派生类)
  DropTableStmt *drop_table_stmt = static_cast<DropTableStmt *>(stmt);

  // 拿到目标表格名称
  const char *table_name = drop_table_stmt->table_name().c_str();

  // 调用 Db 对应的函数来删除表格
  RC rc = session->get_current_db()->drop_table(table_name);
  return rc;
}