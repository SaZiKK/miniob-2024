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
    HAVING = 264,                  /* HAVING  */
    TABLE = 265,                   /* TABLE  */
    TABLES = 266,                  /* TABLES  */
    INDEX = 267,                   /* INDEX  */
    CALC = 268,                    /* CALC  */
    SELECT = 269,                  /* SELECT  */
    ASC = 270,                     /* ASC  */
    DESC = 271,                    /* DESC  */
    SHOW = 272,                    /* SHOW  */
    SYNC = 273,                    /* SYNC  */
    INSERT = 274,                  /* INSERT  */
    DELETE = 275,                  /* DELETE  */
    UPDATE = 276,                  /* UPDATE  */
    LBRACE = 277,                  /* LBRACE  */
    RBRACE = 278,                  /* RBRACE  */
    COMMA = 279,                   /* COMMA  */
    TRX_BEGIN = 280,               /* TRX_BEGIN  */
    TRX_COMMIT = 281,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 282,            /* TRX_ROLLBACK  */
    INT_T = 283,                   /* INT_T  */
    DATE_T = 284,                  /* DATE_T  */
    STRING_T = 285,                /* STRING_T  */
    FLOAT_T = 286,                 /* FLOAT_T  */
    VECTOR_T = 287,                /* VECTOR_T  */
    HELP = 288,                    /* HELP  */
    EXIT = 289,                    /* EXIT  */
    DOT = 290,                     /* DOT  */
    INTO = 291,                    /* INTO  */
    VALUES = 292,                  /* VALUES  */
    FROM = 293,                    /* FROM  */
    WHERE = 294,                   /* WHERE  */
    AND = 295,                     /* AND  */
    SET = 296,                     /* SET  */
    ON = 297,                      /* ON  */
    LOAD = 298,                    /* LOAD  */
    DATA = 299,                    /* DATA  */
    INFILE = 300,                  /* INFILE  */
    EXPLAIN = 301,                 /* EXPLAIN  */
    STORAGE = 302,                 /* STORAGE  */
    FORMAT = 303,                  /* FORMAT  */
    MAX = 304,                     /* MAX  */
    MIN = 305,                     /* MIN  */
    AVG = 306,                     /* AVG  */
    SUM = 307,                     /* SUM  */
    COUNT = 308,                   /* COUNT  */
    NOT_LIKE = 309,                /* NOT_LIKE  */
    LIKE = 310,                    /* LIKE  */
    NOT_IN = 311,                  /* NOT_IN  */
    IN = 312,                      /* IN  */
    NOT_EXISTS = 313,              /* NOT_EXISTS  */
    EXISTS = 314,                  /* EXISTS  */
    LENGTH = 315,                  /* LENGTH  */
    ROUND = 316,                   /* ROUND  */
    DATE_FORMAT = 317,             /* DATE_FORMAT  */
    NULLABLE = 318,                /* NULLABLE  */
    UNNULLABLE = 319,              /* UNNULLABLE  */
    IS_NULL = 320,                 /* IS_NULL  */
    IS_NOT_NULL = 321,             /* IS_NOT_NULL  */
    VEC_L2_DISTANCE = 322,         /* VEC_L2_DISTANCE  */
    VEC_COSINE_DISTANCE_FUNC = 323, /* VEC_COSINE_DISTANCE_FUNC  */
    VEC_INNER_PRODUCT_FUNC = 324,  /* VEC_INNER_PRODUCT_FUNC  */
    LBRACKET = 325,                /* LBRACKET  */
    RBRACKET = 326,                /* RBRACKET  */
    UNIQUE = 327,                  /* UNIQUE  */
    ORDER_BY = 328,                /* ORDER_BY  */
    AS = 329,                      /* AS  */
    EQ = 330,                      /* EQ  */
    LT = 331,                      /* LT  */
    GT = 332,                      /* GT  */
    LE = 333,                      /* LE  */
    GE = 334,                      /* GE  */
    NE = 335,                      /* NE  */
    NUMBER = 336,                  /* NUMBER  */
    FLOAT = 337,                   /* FLOAT  */
    ID = 338,                      /* ID  */
    DATE_STR = 339,                /* DATE_STR  */
    SSS = 340,                     /* SSS  */
    HIGHER_THAN_EXPRESSION = 341,  /* HIGHER_THAN_EXPRESSION  */
    UMINUS = 342                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 147 "yacc_sql.y"

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

#line 172 "yacc_sql.hpp"

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
