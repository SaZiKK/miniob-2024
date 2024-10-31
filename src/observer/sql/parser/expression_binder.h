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
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include <vector>

#include "sql/expr/expression.h"

class BinderContext {
 public:
  BinderContext() = default;
  virtual ~BinderContext() = default;

  void add_table(Table *table) { query_tables_.push_back(table); }
  void add_t_alias(pair<std::string, std::string> pair_) { T_AliasMap.insert(pair_); }
  void add_fa_t_alias(pair<std::string, std::string> pair_) { FA_T_AliasMap.insert(pair_); }
  void add_f_alias(pair<std::string, std::string> pair_) { F_AliasMap.insert(pair_); }

  Table *find_table(const char *table_name) const;

  const std::vector<Table *> &query_tables() const { return query_tables_; }
  const std::unordered_map<std::string, std::string> t_alias() const { return T_AliasMap; }
  const std::unordered_map<std::string, std::string> fa_t_alias() const { return FA_T_AliasMap; }
  const std::unordered_map<std::string, std::string> f_alias() const { return F_AliasMap; }

  // ? 试图将表格别名还原
  const RC try_revert_t(string &table_name) {
    if (T_AliasMap.count(table_name)) {
      table_name = T_AliasMap[table_name];
      return RC::SUCCESS;
    }
    if (FA_T_AliasMap.count(table_name)) {
      table_name = FA_T_AliasMap[table_name];
      return RC::SUCCESS;
    }
    return RC::INVALID_ARGUMENT;
  }
  const RC try_revert_f(string &field_name) {
    if (F_AliasMap.count(field_name)) {
      field_name = F_AliasMap[field_name];
      return RC::SUCCESS;
    }
    return RC::INVALID_ARGUMENT;
  }

 private:
  std::vector<Table *> query_tables_;

  // 当层别名起了就不能用原名
  // 上层起的别名下层用不用均可
  std::unordered_map<std::string, std::string> T_AliasMap;
  std::unordered_map<std::string, std::string> FA_T_AliasMap;

  // 传出的属性别名
  std::unordered_map<std::string, std::string> F_AliasMap;
};

/**
 * @brief 绑定表达式
 * @details
 * 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder {
 public:
  ExpressionBinder(BinderContext &context) : context_(context) {}
  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  BinderContext context() const { return context_; }

 private:
  RC bind_star_expression(std::unique_ptr<Expression> &star_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_unbound_field_expression(std::unique_ptr<Expression> &unbound_field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_field_expression(std::unique_ptr<Expression> &field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_value_expression(std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_cast_expression(std::unique_ptr<Expression> &cast_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_comparison_expression(std::unique_ptr<Expression> &comparison_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_conjunction_expression(std::unique_ptr<Expression> &conjunction_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_arithmetic_expression(std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_aggregate_expression(std::unique_ptr<Expression> &aggregate_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_func_expression(unique_ptr<Expression> &func_expr, vector<unique_ptr<Expression>> &bound_expressions);
  RC bind_vec_func_expression(unique_ptr<Expression> &vec_func_expr, vector<unique_ptr<Expression>> &bound_expressions);
  RC bind_alias_expression(unique_ptr<Expression> &alias_expr, vector<unique_ptr<Expression>> &bound_expressions);

 private:
  BinderContext &context_;
};