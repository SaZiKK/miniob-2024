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
// Created by Meiyi
//

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "common/value.h"
#include <algorithm>  // std::transform
#include <cctype>     // std::toupper

class Expression;
class SelectStmt;

/**
 * @defgroup SQLParser SQL Parser
 */

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
enum CompOp {
  EQUAL_TO,         ///< "="
  LESS_EQUAL,       ///< "<="
  NOT_EQUAL,        ///< "<>"
  LESS_THAN,        ///< "<"
  GREAT_EQUAL,      ///< ">="
  GREAT_THAN,       ///< ">"
  LIKE_XXX,         ///< "LIKE"通过正则表达式匹配
  NOT_LIKE_XXX,     ///< "NOT LIKE"通过正则表达式匹配
  IN_XXX,           ///< "IN"是否在某个集合中
  NOT_IN_XXX,       ///< "NOT IN"是否不在某个集合中
  XXX_NOT_EXISTS,   ///< "NOT EXISTS"是否不存在
  XXX_EXISTS,       ///< "EXISTS"是否存在
  XXX_IS_NULL,      ///< "IS NULL"是否为NULL
  XXX_IS_NOT_NULL,  ///< "IS NOT NULL"是否不为NULL
  NO_OP
};

typedef class ParsedSqlNode SubSelectSqlNode;

/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
struct ConditionSqlNode {
  bool left_is_sub_query;
  Expression *left_expression;

  CompOp comp;

  bool right_is_sub_query;
  Expression *right_expression;

  // SELECT 子句
  SubSelectSqlNode *left_sub_query;
  SubSelectSqlNode *right_sub_query;
  SelectStmt *left_sub_query_stmt;
  SelectStmt *right_sub_query_stmt;

  // 关联问题
  bool left_use_father = false;
  bool right_use_father = false;

  // 1 - AND  2 - OR   0 - DEFAULT
  int conjuction_type = 0;
};

/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是
 * relations。 where 条件
 * conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */

struct SelectSqlNode {
  std::vector<std::unique_ptr<Expression>> expressions;  ///< 查询的表达式
  std::vector<std::unique_ptr<Expression>> relations;    ///< 查询的表
  std::vector<ConditionSqlNode> conditions;              ///< where conditions
  std::vector<ConditionSqlNode> having_conditions;       ///< having conditions
  std::vector<std::unique_ptr<Expression>> join;         ///< join clause
  std::vector<std::unique_ptr<Expression>> group_by;     ///< group by clause
  std::vector<std::unique_ptr<Expression>> order_by;     ///< order by clause

  int vec_order_limit_ = -1;
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode {
  std::vector<std::unique_ptr<Expression>> expressions;  ///< calc clause
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode {
  std::string relation_name;  ///< Relation to insert into
  std::vector<Value> values;  ///< 要插入的值
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode {
  std::string relation_name;  ///< Relation to delete from
  std::vector<ConditionSqlNode> conditions;
};

struct UpdateTarget {
  bool is_value;
  Value value;
  std::string attribute_name;
  SubSelectSqlNode *sub_select;
};

/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode {
  std::string relation_name;  ///< Relation to update
  std::vector<UpdateTarget> update_targets;
  std::vector<ConditionSqlNode> conditions;
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 */
struct AttrInfoSqlNode {
  AttrType type;     ///< Type of attribute
  std::string name;  ///< Attribute name
  size_t length;     ///< Length of attribute
  bool can_be_null;  ///< if can be null
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode {
  std::string relation_name;                ///< Relation name
  std::vector<AttrInfoSqlNode> attr_infos;  ///< attributes
  std::string storage_format;               ///< storage format
  bool use_sub_select;                      ///< if use select stmt
  SubSelectSqlNode *sub_select;             ///< select sql node
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode {
  std::string relation_name;  ///< 要删除的表名
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode {
  std::string index_name;                    ///< Index name
  std::string relation_name;                 ///< Relation name
  std::vector<std::string> attribute_names;  ///< Attribute name
  bool is_unique;                            ///< 是否是唯一索引
};

struct CreateVecIndexSqlNode {
  std::string index_name;
  std::string relation_name;
  std::string attribute_name;

  std::string distance_name;
  std::string type_name;
  int lists_;
  int probes_;
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode {
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode {
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details
 * 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode {
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode {
  std::string name;
  Value value;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode {
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode {
  std::string error_msg;
  int line;
  int column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_SELECT_AGGRE,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,  ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE,  ///< 设置变量
  SCF_CREATE_VEC_INDEX,
};
/**
 * @brief 表示一个SQL语句
 * @ingroup SQLParser
 */
class ParsedSqlNode {
 public:
  enum SqlCommandFlag flag;
  ErrorSqlNode error;
  CalcSqlNode calc;
  SelectSqlNode selection;
  InsertSqlNode insertion;
  DeleteSqlNode deletion;
  UpdateSqlNode update;
  CreateTableSqlNode create_table;
  DropTableSqlNode drop_table;
  CreateIndexSqlNode create_index;
  DropIndexSqlNode drop_index;
  DescTableSqlNode desc_table;
  LoadDataSqlNode load_data;
  ExplainSqlNode explain;
  SetVariableSqlNode set_variable;
  CreateVecIndexSqlNode create_vec_index;

 public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief 表示语法解析后的数据
 * @ingroup SQLParser
 */
class ParsedSqlResult {
 public:
  void add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);

  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes() { return sql_nodes_; }

 private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_;  ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};
