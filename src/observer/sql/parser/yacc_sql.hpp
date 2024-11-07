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
    TEXT_T = 288,                  /* TEXT_T  */
    HELP = 289,                    /* HELP  */
    EXIT = 290,                    /* EXIT  */
    DOT = 291,                     /* DOT  */
    INTO = 292,                    /* INTO  */
    VALUES = 293,                  /* VALUES  */
    FROM = 294,                    /* FROM  */
    WHERE = 295,                   /* WHERE  */
    AND = 296,                     /* AND  */
    OR = 297,                      /* OR  */
    SET = 298,                     /* SET  */
    ON = 299,                      /* ON  */
    LOAD = 300,                    /* LOAD  */
    DATA = 301,                    /* DATA  */
    INFILE = 302,                  /* INFILE  */
    EXPLAIN = 303,                 /* EXPLAIN  */
    STORAGE = 304,                 /* STORAGE  */
    FORMAT = 305,                  /* FORMAT  */
    MAX = 306,                     /* MAX  */
    MIN = 307,                     /* MIN  */
    AVG = 308,                     /* AVG  */
    SUM = 309,                     /* SUM  */
    COUNT = 310,                   /* COUNT  */
    NOT_LIKE = 311,                /* NOT_LIKE  */
    LIKE = 312,                    /* LIKE  */
    NOT_IN = 313,                  /* NOT_IN  */
    IN = 314,                      /* IN  */
    NOT_EXISTS = 315,              /* NOT_EXISTS  */
    EXISTS = 316,                  /* EXISTS  */
    LENGTH = 317,                  /* LENGTH  */
    ROUND = 318,                   /* ROUND  */
    DATE_FORMAT = 319,             /* DATE_FORMAT  */
    NULLABLE = 320,                /* NULLABLE  */
    UNNULLABLE = 321,              /* UNNULLABLE  */
    IS_NULL = 322,                 /* IS_NULL  */
    IS_NOT_NULL = 323,             /* IS_NOT_NULL  */
    VEC_L2_DISTANCE = 324,         /* VEC_L2_DISTANCE  */
    VEC_COSINE_DISTANCE = 325,     /* VEC_COSINE_DISTANCE  */
    VEC_INNER_PRODUCT = 326,       /* VEC_INNER_PRODUCT  */
    IVFFLAT = 327,                 /* IVFFLAT  */
    LBRACKET = 328,                /* LBRACKET  */
    RBRACKET = 329,                /* RBRACKET  */
    UNIQUE = 330,                  /* UNIQUE  */
    ORDER_BY = 331,                /* ORDER_BY  */
    VIEW = 332,                    /* VIEW  */
    WITH = 333,                    /* WITH  */
    DISTANCE = 334,                /* DISTANCE  */
    TYPE = 335,                    /* TYPE  */
    LISTS = 336,                   /* LISTS  */
    PROBES = 337,                  /* PROBES  */
    LIMIT = 338,                   /* LIMIT  */
    AS = 339,                      /* AS  */
    EQ = 340,                      /* EQ  */
    LT = 341,                      /* LT  */
    GT = 342,                      /* GT  */
    LE = 343,                      /* LE  */
    GE = 344,                      /* GE  */
    NE = 345,                      /* NE  */
    NUMBER = 346,                  /* NUMBER  */
    FLOAT = 347,                   /* FLOAT  */
    ID = 348,                      /* ID  */
    DATE_STR = 349,                /* DATE_STR  */
    TEXT_STR = 350,                /* TEXT_STR  */
    SSS = 351,                     /* SSS  */
    HIGHER_THAN_EXPRESSION = 352,  /* HIGHER_THAN_EXPRESSION  */
    UMINUS = 353                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 157 "yacc_sql.y"

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

#line 184 "yacc_sql.hpp"

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
