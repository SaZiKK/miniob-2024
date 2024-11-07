#include "common/log/log.h"
#include "common/lang/string.h"
#include "common/types.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/create_view_stmt.h"
#include "sql/stmt/select_stmt.h"

RC CreateViewStmt::create(Db *db, CreateViewSqlNode &create_view, Stmt *&stmt) {
  SelectSqlNode *select_sql_node = &create_view.sub_select->selection;
  Stmt *_select_stmt = nullptr;
  bool use_father_table_flags = false;
  bool is_allow_insert = true;
  SelectStmt::create(db, *select_sql_node, _select_stmt, use_father_table_flags);

  SelectStmt *select_stmt = nullptr;
  select_stmt = dynamic_cast<SelectStmt *>(_select_stmt);

  string view_name = create_view.view_name;
  std::vector<Table *> tables = select_stmt->tables();
  if (tables.size() > 1) {
    is_allow_insert = false;
  }
  // FilterStmt *filter_stmt = select_stmt->filter_stmt();
  std::vector<std::unique_ptr<Expression>> query_expressions = move(select_stmt->query_expressions());
  std::vector<ViewAttrInfoSqlNode> attr_infos;
  FilterStmt *filter_stmt = select_stmt->filter_stmt();

  for (auto &it : query_expressions) {
    ViewAttrInfoSqlNode *attr_info = new ViewAttrInfoSqlNode();
    attr_info->type = it->value_type();
    attr_info->name = it->name();
    attr_info->length = it->value_length();
    attr_info->expr = move(it);
    attr_infos.push_back(move(*attr_info));
    if (it->type() != ExprType::FIELD) {
      is_allow_insert = false;
    }
  }

  CreateViewStmt *create_view_stmt = new CreateViewStmt(view_name, tables, filter_stmt, move(attr_infos));

  create_view_stmt->set_is_allow_insert(is_allow_insert);

  stmt = create_view_stmt;

  return RC::SUCCESS;
}