#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/stmt/create_vec_index_stmt.h"

using namespace std;
using namespace common;

RC CreateVecIndexStmt::create(Db *db, CreateVecIndexSqlNode &create_vec_index, Stmt *&stmt) {
  stmt = nullptr;
  const char *table_name = create_vec_index.relation_name.c_str();
  if (is_blank(table_name) || is_blank(create_vec_index.index_name.c_str()) || is_blank(create_vec_index.attribute_name.c_str()))
    return RC::INVALID_ARGUMENT;

  Table *table = db->find_table(table_name);
  if (nullptr == table) return RC::SCHEMA_TABLE_NOT_EXIST;

  const char *field_name = create_vec_index.attribute_name.c_str();
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) return RC::SCHEMA_FIELD_NOT_EXIST;
  vector<FieldMeta> field_metas;
  field_metas.push_back(*field_meta);

  // TODO 索引查重

  string distance_name = create_vec_index.distance_name;
  string type_name = create_vec_index.type_name;
  int lists = create_vec_index.lists_;
  int probes = create_vec_index.probes_;
  stmt = new CreateVecIndexStmt(table, field_metas, create_vec_index.index_name, distance_name, type_name, lists, probes);
  return RC::SUCCESS;
}
