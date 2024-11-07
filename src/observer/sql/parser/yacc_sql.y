
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
        HAVING
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        ASC
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
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        OR
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
        VEC_L2_DISTANCE
        VEC_COSINE_DISTANCE
        VEC_INNER_PRODUCT
        IVFFLAT
        LBRACKET
        RBRACKET
        UNIQUE
        ORDER_BY
        WITH
        DISTANCE
        TYPE    
        LISTS   
        PROBES  
        LIMIT
        AS
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
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::vector<std::string> *                 relation_list;
  std::vector<UpdateTarget> *                update_target_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;
  const char *                               aggre_type;
  const char *                               vec_func_type;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> DATE_STR //注意要在SSS之前定义，否则会被SSS匹配
%token <string> TEXT_STR
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <number>              limited
%type <floats>              float
%type <comp>                comp_op
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      having
%type <condition_list>      condition_list
%type <string>              storage_format
%type <expression>          relation
%type <expression_list>     rel_list
%type <boolean>             null_def
%type <expression_list>     query_list
%type <expression>          query_unit
%type <expression_list>     join_list
%type <expression_list>     order_by
%type <expression_list>     order_by_list
%type <number>              order_by_flag
%type <expression_list>     group_by_unit
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <update_target>       update_target
%type <update_target_list>  update_target_list
%type <relation_list>       id_list
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
%type <sql_node>            create_vec_index_stmt
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
%type <aggre_type>          aggre_type
%type <vec_func_type>       vec_func_type
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
  | create_vec_index_stmt
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
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      if ($8 != nullptr) {
        create_index.attribute_names.swap(*$8);
        delete $8;
      }
      create_index.attribute_names.emplace_back($7);
      create_index.is_unique = false;
      free($3);
      free($5);
      free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.is_unique = true;
      std::vector<std::string> attribute_names;
      attribute_names.emplace_back($8);
      if ($9 != nullptr) {
        attribute_names.insert(attribute_names.end(), $9->begin(), $9->end());
        delete $9;
      }
      create_index.attribute_names = std::move(attribute_names);

      free($4);
      free($6);
      free($8);
    }
    ;

create_vec_index_stmt:
    CREATE VECTOR_T INDEX ID ON ID LBRACE ID RBRACE WITH LBRACE TYPE EQ IVFFLAT COMMA DISTANCE EQ vec_func_type COMMA LISTS EQ number COMMA PROBES EQ number RBRACE {
      $$ = new ParsedSqlNode(SCF_CREATE_VEC_INDEX);
      CreateVecIndexSqlNode &create_vec_index = $$->create_vec_index;
      create_vec_index.index_name = $4;
      create_vec_index.relation_name = $6;
      create_vec_index.attribute_name = $8;

      // para
      create_vec_index.type_name = "IVFFLAT";
      create_vec_index.distance_name = $18;
      create_vec_index.lists_ = $22;
      create_vec_index.probes_ = $26;
    }

id_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID id_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->emplace_back($2);
      free($2);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
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

      create_table.use_sub_select = false;
      create_table.sub_select = nullptr;
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt
    {
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

      create_table.use_sub_select = true;
      create_table.sub_select = $10;
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt
    {
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

      create_table.use_sub_select = true;
      create_table.sub_select = $9;
    }
    | CREATE TABLE ID storage_format AS select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      if ($4 != nullptr) {
        create_table.storage_format = $4;
        free($4);
      }

      create_table.use_sub_select = true;
      create_table.sub_select = $6;
    }
    | CREATE TABLE ID storage_format select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      if ($4 != nullptr) {
        create_table.storage_format = $4;
        free($4);
      }

      create_table.use_sub_select = true;
      create_table.sub_select = $5;
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

      if($$->type == AttrType::VECTORS){
        if ($4 <= 1000) {
          $$->length = $4 * 4;
        } else if ($4 > 1000 && $4 <= 16000) {
          $$->real_length = $4 * 4;
          $$->length = 40; // 页号 + 长度 + 标志位 高维向量数据最多占8页
        } else {
          $$->length = 16000 * 4 + 114514; // 超长就给一个非法长度，后面检查
        }
      }

      if($$->type == AttrType::TEXT){
        $$->length = 40; //  页号 + 长度
      }

      free($1);
    }
    | ID type null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->can_be_null = $3;

      if($$->type == AttrType::TEXT){
        $$->length = 40; //  页号 + 长度
      }
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

type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | DATE_T   { $$ = static_cast<int>(AttrType::DATE); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    | TEXT_T   { $$ = static_cast<int>(AttrType::TEXT); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
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
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

number:
    NUMBER {
      $$ = $1;
    }
    | '-' NUMBER {
      $$ = -$2;
    }
    ;

float:
    FLOAT {
      $$ = $1;
    }
    | '-' FLOAT {
      $$ = -$2;
    }
    ;

value:
    NULLABLE {
      $$ = new Value(string("ckk is stupid!"), 114514);
      @$ = @1;
    }
    |number {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |float {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |DATE_STR {
      char *tmp = common::substr($1, 1, strlen($1)-2);  // 去掉首尾的引号
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);    //sscanf会自动转换字符串中的数字，不用显式stoi
      int date_num = year * 10000 + month * 100 + day;
      $$ = new Value(date_num, true);
      free(tmp);
      free($1);
    }
    |TEXT_STR {
      char *tmp = common::substr($1, 1, strlen($1)-2);
      $$ = new Value(tmp, strlen(tmp));
      free(tmp);
      free($1);
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp, strlen(tmp));  
      free(tmp);
      free($1);
    }
    | LBRACKET value value_list RBRACKET {
      std::vector<float> nums;
      nums.emplace_back($2->get_float());
      if($3 != nullptr) {
        std::reverse($3->begin(), $3->end());
        for (Value value : *$3) {
          nums.emplace_back(value.get_float());
        }
      }
      $$ = new Value(nums);
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
      $$->is_value = true;

      delete $3;
    }
    | ID EQ sub_select_stmt
    {
      $$ = new UpdateTarget;
      $$->attribute_name = $1;
      $$->sub_select = $3;
      $$->is_value = false;
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
      else $$ = $3;
      $$->emplace_back(*$2);
    }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT query_unit query_list FROM relation rel_list join_list where group_by having order_by_list limited
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($3 != nullptr) {
        $$->selection.expressions.swap(*$3);
        delete $3;
      }
      $$->selection.expressions.emplace_back($2);
      std::reverse($$->selection.expressions.begin(), $$->selection.expressions.end());

      if ($6 != nullptr) {
        $$->selection.relations.swap(*$6);
        delete $6;
      }
      $$->selection.relations.emplace_back($5);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if ($7 != nullptr) {
        $$->selection.join.swap(*$7);
        delete $7;
      }
      std::reverse($$->selection.join.begin(), $$->selection.join.end());

      if ($8 != nullptr) {
        $$->selection.conditions.swap(*$8);
        delete $8;
      }

      if ($9 != nullptr) {
        $$->selection.group_by.swap(*$9);
        delete $9;
      }

      if($10 != nullptr) {
        $$->selection.having_conditions.swap(*$10);
        delete $10;
      }

      if($11 != nullptr) {
        $$->selection.order_by.swap(*$11);
        delete $11;
      }
      std::reverse($$->selection.order_by.begin(), $$->selection.order_by.end());

      $$->selection.vec_order_limit_ = $12;
    }
    ;
sub_select_stmt:
    LBRACE select_stmt RBRACE
    {
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

limited:
    /* empty */
    {
      $$ = -1;
    }
    | LIMIT number {
      $$ = $2;
    }

aggre_type:
    MAX { 
      const char * result = "MAX";
      $$ = result; 
    }
    | MIN { 
      const char * result = "MIN";
      $$ = result; 
    }
    | COUNT { 
      const char * result = "COUNT";
      $$ = result; 
    }
    | AVG { 
      const char * result = "AVG";
      $$ = result; 
    }
    | SUM { 
      const char * result = "SUM";
      $$ = result; 
    }
    ;

vec_func_type:
    VEC_INNER_PRODUCT { 
      const char * result = "INNER_PRODUCT";
      $$ = result; 
    }
    | VEC_COSINE_DISTANCE { 
      const char * result = "COSINE_DISTANCE";
      $$ = result; 
    }
    | VEC_L2_DISTANCE { 
      const char * result = "L2_DISTANCE";
      $$ = result; 
    }
    ;

expression:
    NUMBER {
      $$ = new ValueExpr(Value($1));
      $$->set_name(token_name(sql_string, &@$));
    }
    | FLOAT {
      $$ = new ValueExpr(Value($1));
      $$->set_name(token_name(sql_string, &@$));
    }
    | DATE_STR {
      char *tmp = common::substr($1, 1, strlen($1)-2);
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);
      int date_num = year * 10000 + month * 100 + day;
      free(tmp);
      free($1);

      $$ = new ValueExpr(Value(date_num, true));
      $$->set_name(token_name(sql_string, &@$));
    }
    | NULLABLE {
      $$ = new ValueExpr(Value(string("dmx is handsome"), 114514));
      $$->set_name(token_name(sql_string, &@$));
    }
    | SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new ValueExpr(Value(tmp));
      free(tmp);
      $$->set_name(token_name(sql_string, &@$));
    }
    | LBRACKET value value_list RBRACKET {
      std::vector<float> nums;
      nums.emplace_back($2->get_float());
      if($3 != nullptr) {
        std::reverse($3->begin(), $3->end());
        for (Value value : *$3) {
          nums.emplace_back(value.get_float());
        }
      }
      $$ = new ValueExpr(Value(nums));
      $$->set_name(token_name(sql_string, &@$));
    }
    | ID {
      $$ = new UnboundFieldExpr(string(), $1);
      $$->set_name(token_name(sql_string, &@$));
      free($1);
    }
    | ID DOT ID {
      $$ = new UnboundFieldExpr($1, $3);
      $$->set_name(token_name(sql_string, &@$));
      free($1);
    }
    | ID DOT '*' {
      $$ = new StarExpr($1);
      $$->set_name(token_name(sql_string, &@$));
      free($1);
    }
    | expression '+' expression {
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
    | '*' {
      $$ = new StarExpr();
    }
    | aggre_type LBRACE RBRACE {
      $$ = create_aggregate_expression($1, nullptr, sql_string, &@$);
    }
    | aggre_type LBRACE expression_list RBRACE {
      if($3->size() != 1) {
        $$ = create_aggregate_expression($1, nullptr, sql_string, &@$);
      } else {
        $$ = create_aggregate_expression($1, $3->at(0).get(), sql_string, &@$);
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
    | VEC_INNER_PRODUCT LBRACE expression COMMA expression RBRACE {
      $$ = new VecFuncExpr(VecFuncExpr::VecFuncType::INNER_PRODUCT, $3, $5);
      $$->set_name(token_name(sql_string, &@$));
    }
    | VEC_COSINE_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = new VecFuncExpr(VecFuncExpr::VecFuncType::COSINE_DISTANCE, $3, $5);
      $$->set_name(token_name(sql_string, &@$));
    }
    | VEC_L2_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = new VecFuncExpr(VecFuncExpr::VecFuncType::L2_DISTANCE, $3, $5);
      $$->set_name(token_name(sql_string, &@$));
    }
    ;

query_unit:
    expression {
      $$ = $1;
    }
    | expression AS ID {
      $$ = new AliasExpr($3, $1);
      $$->set_name(token_name(sql_string, &@$));
      free($3);
    }
    | expression ID {
      $$ = new AliasExpr($2, $1);
      $$->set_name(token_name(sql_string, &@$));
      free($2);
    }

query_list:
    {
      $$ = nullptr;
    }
    | COMMA query_unit query_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }

      $$->emplace_back($2);
    }

relation:
    ID {
      $$ = new UnboundTableExpr($1, string());
      $$->set_name(token_name(sql_string, &@$));
      free($1);
    }
    | ID ID {
      $$ = new AliasExpr($2, new UnboundTableExpr($1, $2));
      $$->set_name(token_name(sql_string, &@$));
      free($1);
      free($2);
    }
    | ID AS ID {
      $$ = new AliasExpr($3, new UnboundTableExpr($1, $3));
      $$->set_name(token_name(sql_string, &@$));
      free($1);
      free($3);
    }


rel_list:
    {
      $$ = nullptr;
    }
    | COMMA relation rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }

      $$->emplace_back($2);
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

having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING condition_list {
      $$ = $2;
    }

join_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | INNER_JOIN relation ON condition_list join_list {
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace_back(new JoinTableExpr(*$4, $2));
    }
    ;

order_by_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER_BY expression order_by_flag order_by
    {
       if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace_back(make_unique<OrderByExpr>($2, $3));
    }
    ;

order_by:
    /* nullptr */
    {
      $$ = nullptr;
    }
    | COMMA expression order_by_flag order_by
    {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace_back(make_unique<OrderByExpr>($2, $3));
    }
    ;

order_by_flag:
    /* nullptr */
    {
      $$ = 1;
    }
    | ASC 
    {
      $$ = 1;
    }
    | DESC
    {
      $$ = -1;
    }
    ;

condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $1->conjuction_type = 0;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $1->conjuction_type = 1;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $1->conjuction_type = 2;
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
    | sub_select_stmt comp_op sub_select_stmt
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = true;
      $$->right_is_sub_query = true;
      $$->comp = $2;
      $$->left_sub_query = $1;
      $$->left_expression = nullptr;
      $$->right_sub_query = $3;
      $$->right_expression = nullptr;
    }
    | sub_select_stmt comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_sub_query = true;
      $$->right_is_sub_query = false;
      $$->comp = $2;
      $$->left_sub_query = $1;
      $$->left_expression = nullptr;
      $$->right_expression = $3;
    }
    | expression comp_op expression
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

group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression group_by_unit {
      if($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }

      $$->emplace_back($3);
    }
    ;

group_by_unit:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA expression group_by_unit
    {
      if($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }

      $$->emplace_back($2);
    }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
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
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
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
