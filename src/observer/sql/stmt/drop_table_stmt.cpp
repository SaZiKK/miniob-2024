#include "sql/stmt/drop_table_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

// 创建 drop table 对应的 Stmt 对象
RC DropTableStmt::create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt) {
  // 目标表格不存在检查
  if (!db->find_table(drop_table.relation_name.c_str())) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // 创建 DropTableStmt 对象
  stmt = new DropTableStmt(drop_table.relation_name);
  return RC::SUCCESS;
}