#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示删除表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class DropTableStmt : public Stmt {
 public:
  // 构造析构
  DropTableStmt(const std::string &table_name) : table_name_(table_name) {}
  virtual ~DropTableStmt() = default;

  // 获取 STMT 语句类型
  StmtType type() const override { return StmtType::DROP_TABLE; }

  // 获取成员变量接口
  const std::string &table_name() const { return table_name_; }

  // 创建 STMT 对象
  static RC create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt);

 private:
  // 删除表格只需要表格的名称
  std::string table_name_;
};