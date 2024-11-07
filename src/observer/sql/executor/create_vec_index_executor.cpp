#include "sql/executor/create_vec_index_executor.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/create_vec_index_stmt.h"
#include "storage/table/table.h"

RC CreateVecIndexExecutor::execute(SQLStageEvent *sql_event) {
  Stmt *stmt = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_VEC_INDEX, "create index executor can not run this command: %d", static_cast<int>(stmt->type()));

  CreateVecIndexStmt *create_vec_index_stmt = static_cast<CreateVecIndexStmt *>(stmt);

  Trx *trx = session->current_trx();
  Table *table = create_vec_index_stmt->table();
  RC rc = table->create_vec_index(trx, create_vec_index_stmt->field_meta()[0], create_vec_index_stmt->index_name().c_str(),
                                  create_vec_index_stmt->distance_name(), create_vec_index_stmt->lists(), create_vec_index_stmt->probes());
  return rc;
}