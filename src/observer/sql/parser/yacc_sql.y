
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        GROUP
        INNER_JOIN
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        DATE_T
        STRING_T
        FLOAT_T
        VECTOR_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        MAX
        MIN
        AVG
        SUM
        COUNT
        NOT_LIKE
        LIKE
        NOT_IN
        IN
        NOT_EXISTS
        EXISTS
        LENGTH
        ROUND
        DATE_FORMAT
        NULLABLE
        UNNULLABLE
        IS_NULL
        IS_NOT_NULL
        EQ
        LT
        GT
        LE
        GE
        NE

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  UpdateTarget *                             update_target;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::vector<JoinSqlNode> *                 join_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  std::vector<UpdateTarget> *                update_target_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> DATE_STR //注意要在SSS之前定义，否则会被SSS匹配
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <string>              relation
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <string>              storage_format
%type <relation_list>       rel_list
%type <boolean>              null_def
%type <join_list>           join_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <update_target>       update_target
%type <update_target_list>  update_target_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            sub_select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%precedence HIGHER_THAN_EXPRESSION


%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      LOG_DEBUG("parse exit_stmt");
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      LOG_DEBUG("parse help_stmt");
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      LOG_DEBUG("parse sync_stmt");
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      LOG_DEBUG("parse begin_stmt");
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      LOG_DEBUG("parse commit_stmt");
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      LOG_DEBUG("parse rollback_stmt");
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      LOG_DEBUG("parse drop_table_stmt");
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      LOG_DEBUG("parse show_tables_stmt");
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      LOG_DEBUG("parse desc_table_stmt");
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID RBRACE
    {
      LOG_DEBUG("parse create_index_stmt");
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.attribute_name = $7;
      free($3);
      free($5);
      free($7);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      LOG_DEBUG("parse drop_index_stmt");
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      LOG_DEBUG("parse create_table_stmt");
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE null_def 
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->can_be_null = $6;
      free($1);
    }
    | ID type null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->can_be_null = $3;
      free($1);
    }
    ;
null_def:
    {
      $$ = false;
    }
    | NULLABLE {
      $$ = true;
    }
    | UNNULLABLE {
      $$ = false;
    }
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | DATE_T   { $$ = static_cast<int>(AttrType::DATE); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      LOG_DEBUG("parse insert_stmt");
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      LOG_DEBUG("parse value_list");
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      LOG_DEBUG("parse value_list");
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NULLABLE {
      $$ = new Value(string("ckk is stupid!"), 114514);
      @$ = @1;
    }
    | NUMBER {
      LOG_DEBUG("parse NUMBER: %d", $1);
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      LOG_DEBUG("parse FLOAT: %f", $1);
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |DATE_STR {
      LOG_DEBUG("parse DATE_STR: %s", $1);
      char *tmp = common::substr($1, 1, strlen($1)-2);  // 去掉首尾的引号
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);    //sscanf会自动转换字符串中的数字，不用显式stoi
      int date_num = year * 10000 + month * 100 + day;
      $$ = new Value(date_num, true);
      free(tmp);
      free($1);
    }
    |SSS {
      LOG_DEBUG("parse SSS: %s", $1);
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp, strlen(tmp));  
      free(tmp);
      free($1);
    }
    ;
storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      LOG_DEBUG("parse delete_stmt");
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_target update_target_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;

      if ($6 != nullptr) {
        $$->update.conditions.swap(*$6);
        delete $6;
      }

      if($5 != nullptr)
        $$->update.update_targets.swap(*$5);
      $$->update.update_targets.emplace_back(*$4);
      std::reverse($$->update.update_targets.begin(), $$->update.update_targets.end());
    }
    ;

update_target: 
    ID EQ value 
    {
      $$ = new UpdateTarget;
      $$->attribute_name = $1;
      $$->value = *$3;

      delete $3;
    }
    ;

update_target_list:
    /* nullptr */
    {
      $$ = nullptr;
    }
    | COMMA update_target update_target_list
    {
      if($3 == nullptr)
        $$ = new std::vector<UpdateTarget>;
      $$->emplace_back(*$2);
    }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      $$->selection.expressions.swap(*$2);
    }
    | SELECT expression_list FROM rel_list join_list where group_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.swap(*$4);
        delete $4;
      }

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }

      if ($5 != nullptr) {

        $$->selection.join.swap(*$5);
        delete $5;
      }

      if ($7 != nullptr) {
        $$->selection.group_by.swap(*$7);
        delete $7;
      }
    }
    ;
sub_select_stmt:
    LBRACE select_stmt RBRACE
    {
      LOG_DEBUG("parse sub_select_stmt");
      $$ = $2;
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace($$->begin(), $1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    | MAX LBRACE RBRACE {
      $$ = create_aggregate_expression("MAX", nullptr, sql_string, &@$);
    }
    | MIN LBRACE RBRACE {
      $$ = create_aggregate_expression("MIN", nullptr, sql_string, &@$);
    }
    | AVG LBRACE RBRACE {
      $$ = create_aggregate_expression("AVG", nullptr, sql_string, &@$);
    }
    | SUM LBRACE RBRACE {
      $$ = create_aggregate_expression("SUM", nullptr, sql_string, &@$);
    }
    | COUNT LBRACE RBRACE {
      $$ = create_aggregate_expression("COUNT", nullptr, sql_string, &@$);
    }
    | MAX LBRACE expression_list RBRACE {
      if($3->size() != 1) {
        $$ = create_aggregate_expression("MAX", nullptr, sql_string, &@$);
      } else {
        $$ = create_aggregate_expression("MAX", $3->at(0).get(), sql_string, &@$);
      }
    }
    | MIN LBRACE expression_list RBRACE {
      if($3->size() != 1) {
        $$ = create_aggregate_expression("MIN", nullptr, sql_string, &@$);
      } else {
        $$ = create_aggregate_expression("MIN", $3->at(0).get(), sql_string, &@$);
      }
    }
    | COUNT LBRACE expression_list RBRACE {
      if($3->size() != 1) {
        $$ = create_aggregate_expression("COUNT", nullptr, sql_string, &@$);
      } else {
        $$ = create_aggregate_expression("COUNT", $3->at(0).get(), sql_string, &@$);
      }
    }
    | AVG LBRACE expression_list RBRACE {
      if($3->size() != 1) {
        $$ = create_aggregate_expression("AVG", nullptr, sql_string, &@$);
      } else {
        $$ = create_aggregate_expression("AVG", $3->at(0).get(), sql_string, &@$);
      }
    }
    | SUM LBRACE expression_list RBRACE {
      if($3->size() != 1) {
        $$ = create_aggregate_expression("SUM", nullptr, sql_string, &@$);
      } else {
        $$ = create_aggregate_expression("SUM", $3->at(0).get(), sql_string, &@$);
      }
    }
    | LENGTH LBRACE expression RBRACE {
      $$ = new FuncExpr(FuncExpr::FuncType::LENGTH, nullptr, nullptr, $3);
      $$->set_name(token_name(sql_string, &@$));
    }
    | ROUND LBRACE expression COMMA expression RBRACE {
      $$ = new FuncExpr(FuncExpr::FuncType::ROUND, $5, nullptr, $3);
      $$->set_name(token_name(sql_string, &@$));
    }
    | DATE_FORMAT LBRACE expression COMMA expression RBRACE {
      $$ = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, nullptr, $5, $3);
      $$->set_name(token_name(sql_string, &@$));
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;
rel_list:
    relation {
      $$ = new std::vector<std::string>();
      $$->push_back($1);
      free($1);
    }
    | relation COMMA rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }

      $$->insert($$->begin(), $1);
      free($1);
    }
    ;

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
join_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | INNER_JOIN ID ON condition_list join_list {
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::vector<JoinSqlNode>;
      }

      JoinSqlNode join;
      join.relation = $2;
      // std::reverse($4->begin(), $4->end());
      if($4 != nullptr) {
        join.conditions.insert(join.conditions.end(), $4->begin(), $4->end());
        delete $4;
      }
      $$->emplace_back(join);
    }
    ;

condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    expression comp_op
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = false;
      $$->right_is_sub_query = false;
      $$->comp = $2;
      $$->left_expression = $1;
      $$->right_expression = new ValueExpr(Value(114514));
    }
    | expression comp_op sub_select_stmt
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = false;
      $$->right_is_sub_query = true;
      $$->comp = $2;
      $$->left_expression = $1;
      $$->right_sub_query = $3;
      $$->right_expression = nullptr;
    }
    |
    sub_select_stmt comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = true;
      $$->right_is_sub_query = false;
      $$->comp = $2;
      $$->left_sub_query = $1;
      $$->left_expression = nullptr;
      $$->right_expression = $3;
    }
    | 
    expression comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = false;
      $$->right_is_sub_query = false;
      $$->comp = $2;
      $$->left_expression = $1;
      $$->right_expression = $3;
    }
    | comp_op sub_select_stmt
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = false;
      $$->right_is_sub_query = true;
      $$->right_sub_query = $2;
      $$->comp = $1;
      $$->left_expression = new ValueExpr(Value(114514));
    }
    | expression comp_op LBRACE value value_list RBRACE %prec HIGHER_THAN_EXPRESSION
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = false;
      $$->right_is_sub_query = false;
      $$->comp = $2;
      $$->left_expression = $1;
      $5->push_back(*$4);
      $$->right_expression = new ValueListExpr(*$5);
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IS_NULL { $$ = XXX_IS_NULL; }
    | IS_NOT_NULL { $$ = XXX_IS_NOT_NULL; }
    | NOT_LIKE { $$ = NOT_LIKE_XXX; }
    | LIKE { $$ = LIKE_XXX; }
    | NOT_IN { $$ = NOT_IN_XXX; }
    | IN { $$ = IN_XXX; }
    | NOT_EXISTS { $$ = XXX_NOT_EXISTS; }
    | EXISTS { $$ = XXX_EXISTS; }
    ;

// your code here
group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    ;
load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      LOG_DEBUG("parse load_data_stmt");
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      LOG_DEBUG("parse explain_stmt");
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      LOG_DEBUG("parse set_variable_stmt");
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
