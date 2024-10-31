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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "common/log/log.h"
#include "common/value.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/expr/aggregator.h"
#include "storage/common/chunk.h"

class Trx;
class PhysicalOperator;
class LogicalOperator;
class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType {
  NONE,
  STAR,                 ///< 星号，表示所有字段
  UNBOUND_FIELD,        ///< 未绑定的字段，需要在resolver阶段解析为FieldExpr
  UNBOUND_TABLE,        ///< 未绑定的表明，需要在resolver阶段提取别名和原名
  UNBOUND_AGGREGATION,  ///< 未绑定的聚合函数，需要在resolver阶段解析为AggregateExpr

  ALIAS,        ///< 别名
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  JOINTABLE,    ///< join 字段
  ORDERBY,      ///< order 字段
  VALUE,        ///< 常量值
  VALUELIST,    ///< 常量值列表
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  AGGREGATION,  ///< 聚合运算
  SUBQUERY,     ///< 子查询
  FUNC,         ///< 函数运算
  VECFUNC,      ///< 向量函数运算
};

class Expression {
 public:
  Expression() = default;
  virtual ~Expression() = default;

  /**
   * @brief 判断两个表达式是否相等
   */
  virtual bool equal(const Expression &other) const { return false; }
  /**
   * @brief
   * 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  // 针对valuelist
  virtual RC get_value_list(std::vector<Value> &value) { return RC::UNIMPLEMENTED; }

  // 针对子查询
  virtual RC try_get_tuple_list(std::vector<std::vector<Value>> &tuple) { return RC::UNIMPLEMENTED; }

  /**
   * @brief
   * 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLEMENTED; }

  /**
   * @brief 从 `chunk` 中获取表达式的计算结果 `column`
   */
  virtual RC get_column(Chunk &chunk, Column &column) { return RC::UNIMPLEMENTED; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式值的长度
   */
  virtual int value_length() const { return -1; }

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual const char *name() const { return name_.c_str(); }
  virtual void set_name(std::string name) { name_ = name; }

  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   */
  virtual int pos() const { return pos_; }
  virtual void set_pos(int pos) { pos_ = pos; }

  /**
   * @brief 用于 ComparisonExpr 获得比较结果 `select`。
   */
  virtual RC eval(Chunk &chunk, std::vector<uint8_t> &select) { return RC::UNIMPLEMENTED; }

  virtual RC get_alias(string &alias) const { return RC::UNIMPLEMENTED; }

  static RC copy_expr(const std::unique_ptr<Expression> &expr_src, std::unique_ptr<Expression> &expr_dst);

 protected:
  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   * @details 当 pos_ = -1 时表示下层算子没有在返回的 chunk
   * 中计算出该表达式的计算结果， 当 pos_ >=
   * 0时表示在下层算子中已经计算出该表达式的值（比如聚合表达式），且该表达式对应的结果位于
   * chunk 中 下标为 pos_ 的列中。
   */
  int pos_ = -1;

 private:
  std::string name_;
};

// *********************************************************
// * 别名表达式
// * 需要绑定：将别名导入子表达式并销毁自身
class AliasExpr : public Expression {
 public:
  AliasExpr(string alias_name, std::unique_ptr<Expression> child) : alias_name_(alias_name), child_(std::move(child)) {}
  AliasExpr(string alias_name, Expression *child) : alias_name_(alias_name), child_(child) {}
  virtual ~AliasExpr() = default;

  ExprType type() const override { return ExprType::ALIAS; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::UNIMPLEMENTED; }

  const char *alias_name() const { return alias_name_.c_str(); }
  std::unique_ptr<Expression> &child() { return child_; }

 private:
  std::string alias_name_;
  std::unique_ptr<Expression> child_;
};

// *********************************************************
// * 星号 "*" 表达式
// * 需要绑定：将 "*" 转换成某个表格的全部属性集合
// * 需要别名
class StarExpr : public Expression {
 public:
  StarExpr() : table_name_() {}
  StarExpr(const char *table_name) : table_name_(table_name) {}
  virtual ~StarExpr() = default;

  ExprType type() const override { return ExprType::STAR; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::UNIMPLEMENTED; }  // 不需要实现

  const char *table_name() const { return table_name_.c_str(); }
  const char *star_alias() const { return star_alias_.c_str(); }

  void set_star_alias(string star_alias) { star_alias_ = star_alias; }
  RC get_alias(string &alias) const override {
    if (star_alias_.empty()) return RC::INVALID_ARGUMENT;
    alias = star_alias_;
    return RC::SUCCESS;
  }

 private:
  std::string table_name_;

  std::string star_alias_;
};

// *********************************************************
// * 未绑定域表达式
// * 需要绑定：通过表格名和域名找到真正的 Field
// * 需要别名
class UnboundFieldExpr : public Expression {
 public:
  UnboundFieldExpr(const std::string &table_name, const std::string &field_name, const std::string field_alias = "")
      : table_name_(table_name), field_name_(field_name), field_alias_(field_alias) {
    table_alias_ = "";
  }

  virtual ~UnboundFieldExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_FIELD; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }
  void set_table_alias(string table_alias) { table_alias_ = table_alias; }
  void set_table_name(string table_name) { table_name_ = table_name; }
  void set_field_alias(string field_alias) { field_alias_ = field_alias; }
  void set_field_name(string field_name) { field_name_ = field_name; }

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }
  const char *field_alias() const { return field_alias_.c_str(); }
  const char *table_alias() const { return table_alias_.c_str(); }

  bool has_table_alias() const { return !string(table_alias_).empty(); }
  bool has_field_alias() const { return !string(field_alias_).empty(); }

  RC get_alias(string &alias) const override {
    if (field_alias_.empty()) return RC::INVALID_ARGUMENT;
    alias = field_alias_;
    return RC::SUCCESS;
  }

  int is_asc() const { return is_asc_; }
  void set_asc_or_desc(int flag) { is_asc_ = flag ? (flag > 0 ? 1 : -1) : 0; }

 private:
  std::string table_name_;
  std::string field_name_;

  // alias part
  std::string field_alias_;
  std::string table_alias_;

  // order by part
  // {-1, 0, 1} <=> {desc, not need order, asc}
  int is_asc_ = 0;
};

// *********************************************************
// * 未绑定表格表达式
// * 需要绑定：通过表格名找到真正的 Table
// * 需要别名
class UnboundTableExpr : public Expression {
 public:
  UnboundTableExpr(const std::string &table_name, const std::string table_alias = "") : table_name_(table_name), table_alias_(table_alias) {}

  virtual ~UnboundTableExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_TABLE; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  void set_table_alias(string table_alias) { table_alias_ = table_alias; }

  const char *table_name() const { return table_name_.c_str(); }
  const char *table_alias() const { return table_alias_.c_str(); }

  RC get_alias(string &alias) const override {
    if (table_alias_.empty()) return RC::INVALID_ARGUMENT;
    alias = table_alias_;
    return RC::SUCCESS;
  }

  bool has_table_alias() const { return !string(table_alias_).empty(); }

 private:
  std::string table_name_;

  // alias part
  std::string table_alias_;
};

// *********************************************************
// * 排序表达式
// *
class OrderByExpr : public Expression {
 public:
  OrderByExpr(std::unique_ptr<Expression> child, int flag) : child_(std::move(child)), flag_(flag) {}
  OrderByExpr(Expression *child, int flag) : child_(child), flag_(flag) {}

  virtual ~OrderByExpr() = default;

  ExprType type() const override { return ExprType::ORDERBY; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  const std::unique_ptr<Expression> &child() const { return child_; }
  const int flag() const { return flag_; }

 private:
  std::unique_ptr<Expression> child_;
  int flag_;
};

// *********************************************************
// * 表格连接表达式
// *
class JoinTableExpr : public Expression {
 public:
  JoinTableExpr(std::vector<ConditionSqlNode> conditions, unique_ptr<Expression> child) : conditions_(conditions), child_(std::move(child)) {}
  JoinTableExpr(std::vector<ConditionSqlNode> conditions, Expression *child) : conditions_(conditions), child_(child) {}

  virtual ~JoinTableExpr() = default;

  ExprType type() const override { return ExprType::JOINTABLE; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  const std::vector<ConditionSqlNode> conditions() const { return conditions_; }
  const std::unique_ptr<Expression> &child() const { return child_; }

 private:
  std::vector<ConditionSqlNode> conditions_;
  std::unique_ptr<Expression> child_;
};

// *********************************************************
// * 绑定表格表达式
// *
// * 需要别名
class FieldExpr : public Expression {
 public:
  FieldExpr() = default;
  FieldExpr(Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Field &field) : field_(field) {}

  virtual ~FieldExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }
  int value_length() const override { return field_.meta()->len(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }
  const char *field_name() const { return field_.field_name(); }

  RC get_alias(string &alias) const override {
    if (!field_.has_field_alias()) return RC::INVALID_ARGUMENT;
    alias = field_.field_alias();
    return RC::SUCCESS;
  }

  RC get_column(Chunk &chunk, Column &column) override;

  RC get_value(const Tuple &tuple, Value &value) const override;

 private:
  Field field_;
};

// *********************************************************
// * Value 表达式
// *
class ValueExpr : public Expression {
 public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  bool equal(const Expression &other) const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_column(Chunk &chunk, Column &column) override;
  RC try_get_value(Value &value) const override {
    value = value_;
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }
  AttrType value_type() const override { return value_.attr_type(); }
  int value_length() const override { return value_.length(); }

  void get_value(Value &value) const { value = value_; }
  const Value &get_value() const { return value_; }
  Value value() { return value_; }

 private:
  Value value_;
};

// *********************************************************
// * 子查询表达式
// *
// TODO 重写子查询逻辑
class SubQueryExpr : public Expression {
 public:
  SubQueryExpr() = default;
  explicit SubQueryExpr(SelectStmt *sub_query, bool father_sub_mode = false) : sub_query_(sub_query), father_sub_mode_(father_sub_mode) { init(); };

  virtual ~SubQueryExpr() = default;

  ExprType type() const override { return ExprType::SUBQUERY; }
  AttrType value_type() const override { return AttrType::TUPLES; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_tuple_list(std::vector<std::vector<Value>> &tuple) override;
  // RC get_tuple_schema(TupleSchema tuple_schema);

  RC init();

  SelectStmt *sub_query() { return sub_query_; }
  bool father_sub_mode() { return father_sub_mode_; }
  void set_father_sub_mode(bool flag) { father_sub_mode_ = flag; }

 private:
  SelectStmt *sub_query_;
  bool has_calculated = false;
  bool father_sub_mode_ = false;
  std::vector<std::vector<Value>> tuple_list_;
};

// *********************************************************
// * ValueList 表达式
// *
class ValueListExpr : public Expression {
 public:
  ValueListExpr() = default;
  explicit ValueListExpr(const std::vector<Value> &values) : values_(values) {}
  explicit ValueListExpr(std::vector<Value> &values) : values_(values) {}

  virtual ~ValueListExpr() = default;

  ExprType type() const override { return ExprType::VALUELIST; }
  AttrType value_type() const override { return AttrType::VALUE_LIST; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  RC get_value_list(std::vector<Value> &value) override {
    value = values_;
    return RC::SUCCESS;
  }

  const std::vector<Value> &values() const { return values_; }

 private:
  std::vector<Value> values_;
};

// *********************************************************
// * 类型强制转换表达式
// *
class CastExpr : public Expression {
 public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

 private:
  RC cast(const Value &value, Value &cast_value) const;

 private:
  std::unique_ptr<Expression> child_;  ///< 从这个表达式转换
  AttrType cast_type_;                 ///< 想要转换成这个类型
};

enum CompType {
  VAL_VAL,        ///< 值-值
  VAL_LIST,       ///< 值-列表
  LIST_VAL,       ///< 列表-值
  LIST_LIST,      ///< 列表-列表
  VAL_TUPLES,     ///< 值-元组列
  TUPLES_VAL,     ///< 元组列-值
  TUPLES_TUPLES,  ///< 元组列-元组列
  TUPLES_LIST,    ///< 元组列-列表
  LIST_TUPLES,    ///< 列表-元组列
  VAL_TUPLE,      ///< 值-元组
  LIST_TUPLE,     ///< 列表-元组
  TUPLE_TUPLE,    ///< 元组-元组
  TUPLES_TUPLE,   ///< 元组列-元组
  TUPLE_VAL,      ///< 元组-值
  TUPLE_LIST,     ///< 元组-列表
  TUPLE_TUPLES,   ///< 元组-元组列
};

// *********************************************************
// * 比较表达式
// *
class ComparisonExpr : public Expression {
 public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }
  RC get_value(const Tuple &tuple, Value &value) const override;
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  CompOp comp() const { return comp_; }

  /**
   * @brief 根据 ComparisonExpr 获得 `select` 结果。
   * select 的长度与chunk 的行数相同，表示每一行在ComparisonExpr
   * 计算后是否会被输出。
   */
  RC eval(Chunk &chunk, std::vector<uint8_t> &select) override;

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, const std::vector<Value> left_list, const std::vector<Value> right_list, bool &value,
                   const std::vector<std::vector<Value>> left_tuple_list, const std::vector<std::vector<Value>> right_tuple_list) const;

  /// compare two string with pattern
  static bool likeMatch(const std::string &str, const std::string &pattern);

  template <typename T>
  RC compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const;

  // 设置表达式的比较类型
  void set_comp_type(CompType type) const { type_ = type; }
  RC set_comp_type_by_verilog() const;

  // 获取表达式的比较类型
  CompType comp_type() const { return type_; }

  RC check_value(bool father_sub_mode = false) const;

 private:
  mutable CompType type_;
  CompOp comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

// *********************************************************
// * 比较连接表达式
// *
class ConjunctionExpr : public Expression {
 public:
  enum class Type {
    AND,
    OR,
  };

 public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  RC get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

 private:
  Type conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

// *********************************************************
// * 算术表达式
// *
// * 需要别名
class ArithmeticExpr : public Expression {
 public:
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

 public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  bool equal(const Expression &other) const override;
  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;
  int value_length() const override {
    if (!right_) {
      return left_->value_length();
    }
    return 4;  // sizeof(float) or sizeof(int)
  };

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }
  string type_to_string() const;

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  string arith_alias() const { return arith_alias_; }
  void set_alias(string alias) { arith_alias_ = alias; }

  RC get_alias(string &alias) const override {
    if (arith_alias_.empty()) return RC::INVALID_ARGUMENT;
    alias = arith_alias_;
    return RC::SUCCESS;
  }

 private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

  RC calc_column(const Column &left_column, const Column &right_column, Column &column) const;

  template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
  RC execute_calc(const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const;

 private:
  Type arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;

  string arith_alias_;
};

// *********************************************************
// * 未绑定的聚合表达式
// * 需要绑定：绑定子表达式并且将字符串转化成枚举类型
// * 需要别名
class UnboundAggregateExpr : public Expression {
 public:
  UnboundAggregateExpr(const char *aggregate_name, Expression *child);
  virtual ~UnboundAggregateExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_AGGREGATION; }

  const char *aggregate_name() const { return aggregate_name_.c_str(); }

  std::unique_ptr<Expression> &child() { return child_; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }
  AttrType value_type() const override { return child_->value_type(); }

 public:
  void set_aggre_alias(string aggre_alias) { aggre_alias_ = aggre_alias; }

  const char *aggre_alias() const { return aggre_alias_.c_str(); }
  bool has_aggre_alias() const { return !aggre_alias_.empty(); }

  RC get_alias(string &alias) const override {
    if (aggre_alias_.empty()) return RC::INVALID_ARGUMENT;
    alias = aggre_alias_;
    return RC::SUCCESS;
  }

 private:
  std::string aggregate_name_;
  std::unique_ptr<Expression> child_;

  std::string aggre_alias_;
};

// *********************************************************
// * 绑定的聚合表达式
// *
// * 需要别名
class AggregateExpr : public Expression {
 public:
  enum class Type {
    COUNT,
    SUM,
    AVG,
    MAX,
    MIN,
  };

 public:
  AggregateExpr(Type type, Expression *child);
  AggregateExpr(Type type, std::unique_ptr<Expression> child);
  virtual ~AggregateExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::AGGREGATION; }

  AttrType value_type() const override { return child_->value_type(); }
  int value_length() const override { return child_->value_length(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  Type aggregate_type() const { return aggregate_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

  const std::unique_ptr<Expression> &child() const { return child_; }

  std::unique_ptr<Aggregator> create_aggregator() const;

  RC get_alias(string &alias) const override {
    if (aggre_alias_.empty()) return RC::INVALID_ARGUMENT;
    alias = aggre_alias_;
    return RC::SUCCESS;
  }

 public:
  static RC type_from_string(const char *type_str, Type &type);

 public:
  void set_aggre_alias(string aggre_alias) { aggre_alias_ = aggre_alias; }

  const char *aggre_alias() const { return aggre_alias_.c_str(); }
  bool has_aggre_alias() const { return !aggre_alias_.empty(); }

 private:
  Type aggregate_type_;
  std::unique_ptr<Expression> child_;

  std::string aggre_alias_;
};

// *********************************************************
// * 普通函数表达式
// *
class FuncExpr : public Expression {
 public:
  enum class FuncType { LENGTH, ROUND, DATE_FORMAT, UNDEFINED };

  FuncExpr(FuncType type, std::unique_ptr<Expression> target_num, std::unique_ptr<Expression> target_format, std::unique_ptr<Expression> child);
  FuncExpr(FuncType type, Expression *target_num, Expression *target_format, Expression *child);
  virtual ~FuncExpr() = default;

  ExprType type() const override { return ExprType::FUNC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  RC static func_length(const Value value, Value &result);
  RC static func_round(const Value value, int target_num, Value &result);
  RC static func_date_format(const Value value, string target_format, Value &result);

  FuncType func_type() const { return type_; }

  std::unique_ptr<Expression> &child() { return child_; }

 private:
  FuncType type_;
  int target_num_;
  string target_format_;
  std::unique_ptr<Expression> child_;
};

// *********************************************************
// * 向量函数表达式
// *
class VecFuncExpr : public Expression {
 public:
  enum class VecFuncType {
    L2_DISTANCE,
    COSINE_DISTANCE,
    INNER_PRODUCT,
  };

  VecFuncExpr(VecFuncType type, unique_ptr<Expression> child_left, unique_ptr<Expression> child_right);
  VecFuncExpr(VecFuncType type, Expression *left, Expression *right);
  virtual ~VecFuncExpr() = default;

  ExprType type() const override { return ExprType::VECFUNC; }

  AttrType value_type() const override { return AttrType::FLOATS; };

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  VecFuncType func_type() const { return type_; }

  std::unique_ptr<Expression> &child_left() { return child_left_; }
  std::unique_ptr<Expression> &child_right() { return child_right_; }

  static RC L2_DISTANCE_FUNC(const Value left, const Value right, Value &result);
  static RC COSINE_DISTANCE_FUNC(const Value left, const Value right, Value &result);
  static RC INNER_PRODUCT_FUNC(const Value left, const Value right, Value &result);

 private:
  VecFuncType type_;
  std::unique_ptr<Expression> child_left_;
  std::unique_ptr<Expression> child_right_;
};