/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    INNER_JOIN = 263,              /* INNER_JOIN  */
    TABLE = 264,                   /* TABLE  */
    TABLES = 265,                  /* TABLES  */
    INDEX = 266,                   /* INDEX  */
    CALC = 267,                    /* CALC  */
    SELECT = 268,                  /* SELECT  */
    ASC = 269,                     /* ASC  */
    DESC = 270,                    /* DESC  */
    SHOW = 271,                    /* SHOW  */
    SYNC = 272,                    /* SYNC  */
    INSERT = 273,                  /* INSERT  */
    DELETE = 274,                  /* DELETE  */
    UPDATE = 275,                  /* UPDATE  */
    LBRACE = 276,                  /* LBRACE  */
    RBRACE = 277,                  /* RBRACE  */
    COMMA = 278,                   /* COMMA  */
    TRX_BEGIN = 279,               /* TRX_BEGIN  */
    TRX_COMMIT = 280,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 281,            /* TRX_ROLLBACK  */
    INT_T = 282,                   /* INT_T  */
    DATE_T = 283,                  /* DATE_T  */
    STRING_T = 284,                /* STRING_T  */
    FLOAT_T = 285,                 /* FLOAT_T  */
    VECTOR_T = 286,                /* VECTOR_T  */
    HELP = 287,                    /* HELP  */
    EXIT = 288,                    /* EXIT  */
    DOT = 289,                     /* DOT  */
    INTO = 290,                    /* INTO  */
    VALUES = 291,                  /* VALUES  */
    FROM = 292,                    /* FROM  */
    WHERE = 293,                   /* WHERE  */
    AND = 294,                     /* AND  */
    SET = 295,                     /* SET  */
    ON = 296,                      /* ON  */
    LOAD = 297,                    /* LOAD  */
    DATA = 298,                    /* DATA  */
    INFILE = 299,                  /* INFILE  */
    EXPLAIN = 300,                 /* EXPLAIN  */
    STORAGE = 301,                 /* STORAGE  */
    FORMAT = 302,                  /* FORMAT  */
    MAX = 303,                     /* MAX  */
    MIN = 304,                     /* MIN  */
    AVG = 305,                     /* AVG  */
    SUM = 306,                     /* SUM  */
    COUNT = 307,                   /* COUNT  */
    NOT_LIKE = 308,                /* NOT_LIKE  */
    LIKE = 309,                    /* LIKE  */
    NOT_IN = 310,                  /* NOT_IN  */
    IN = 311,                      /* IN  */
    NOT_EXISTS = 312,              /* NOT_EXISTS  */
    EXISTS = 313,                  /* EXISTS  */
    LENGTH = 314,                  /* LENGTH  */
    ROUND = 315,                   /* ROUND  */
    DATE_FORMAT = 316,             /* DATE_FORMAT  */
    NULLABLE = 317,                /* NULLABLE  */
    UNNULLABLE = 318,              /* UNNULLABLE  */
    IS_NULL = 319,                 /* IS_NULL  */
    IS_NOT_NULL = 320,             /* IS_NOT_NULL  */
    VEC_L2_DISTANCE = 321,         /* VEC_L2_DISTANCE  */
    VEC_COSINE_DISTANCE_FUNC = 322, /* VEC_COSINE_DISTANCE_FUNC  */
    VEC_INNER_PRODUCT_FUNC = 323,  /* VEC_INNER_PRODUCT_FUNC  */
    LBRACKET = 324,                /* LBRACKET  */
    RBRACKET = 325,                /* RBRACKET  */
    UNIQUE = 326,                  /* UNIQUE  */
    ORDER_BY = 327,                /* ORDER_BY  */
    AS = 328,                      /* AS  */
    EQ = 329,                      /* EQ  */
    LT = 330,                      /* LT  */
    GT = 331,                      /* GT  */
    LE = 332,                      /* LE  */
    GE = 333,                      /* GE  */
    NE = 334,                      /* NE  */
    NUMBER = 335,                  /* NUMBER  */
    FLOAT = 336,                   /* FLOAT  */
    ID = 337,                      /* ID  */
    DATE_STR = 338,                /* DATE_STR  */
    SSS = 339,                     /* SSS  */
    HIGHER_THAN_EXPRESSION = 340,  /* HIGHER_THAN_EXPRESSION  */
    UMINUS = 341                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 146 "yacc_sql.y"

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
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  std::vector<UpdateTarget> *                update_target_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;

#line 171 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
