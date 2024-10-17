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
<<<<<<< HEAD
    INNER_JOIN = 263,              /* INNER_JOIN  */
    TABLE = 264,                   /* TABLE  */
    TABLES = 265,                  /* TABLES  */
    INDEX = 266,                   /* INDEX  */
    CALC = 267,                    /* CALC  */
    SELECT = 268,                  /* SELECT  */
    DESC = 269,                    /* DESC  */
    SHOW = 270,                    /* SHOW  */
    SYNC = 271,                    /* SYNC  */
    INSERT = 272,                  /* INSERT  */
    DELETE = 273,                  /* DELETE  */
    UPDATE = 274,                  /* UPDATE  */
    LBRACE = 275,                  /* LBRACE  */
    RBRACE = 276,                  /* RBRACE  */
    COMMA = 277,                   /* COMMA  */
    TRX_BEGIN = 278,               /* TRX_BEGIN  */
    TRX_COMMIT = 279,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 280,            /* TRX_ROLLBACK  */
    INT_T = 281,                   /* INT_T  */
    DATE_T = 282,                  /* DATE_T  */
    STRING_T = 283,                /* STRING_T  */
    FLOAT_T = 284,                 /* FLOAT_T  */
    HELP = 285,                    /* HELP  */
    EXIT = 286,                    /* EXIT  */
    DOT = 287,                     /* DOT  */
    INTO = 288,                    /* INTO  */
    VALUES = 289,                  /* VALUES  */
    FROM = 290,                    /* FROM  */
    WHERE = 291,                   /* WHERE  */
    AND = 292,                     /* AND  */
    SET = 293,                     /* SET  */
    ON = 294,                      /* ON  */
    LOAD = 295,                    /* LOAD  */
    DATA = 296,                    /* DATA  */
    INFILE = 297,                  /* INFILE  */
    EXPLAIN = 298,                 /* EXPLAIN  */
    STORAGE = 299,                 /* STORAGE  */
    FORMAT = 300,                  /* FORMAT  */
    MAX = 301,                     /* MAX  */
    MIN = 302,                     /* MIN  */
    AVG = 303,                     /* AVG  */
    SUM = 304,                     /* SUM  */
    COUNT = 305,                   /* COUNT  */
    NOT_LIKE = 306,                /* NOT_LIKE  */
    LIKE = 307,                    /* LIKE  */
    NOT_IN = 308,                  /* NOT_IN  */
    IN = 309,                      /* IN  */
    NOT_EXISTS = 310,              /* NOT_EXISTS  */
    EXISTS = 311,                  /* EXISTS  */
    LENGTH = 312,                  /* LENGTH  */
    ROUND = 313,                   /* ROUND  */
    DATE_FORMAT = 314,             /* DATE_FORMAT  */
    NULLABLE = 315,                /* NULLABLE  */
    UNNULLABLE = 316,              /* UNNULLABLE  */
    IS_NULL = 317,                 /* IS_NULL  */
    IS_NOT_NULL = 318,             /* IS_NOT_NULL  */
    EQ = 319,                      /* EQ  */
    LT = 320,                      /* LT  */
    GT = 321,                      /* GT  */
    LE = 322,                      /* LE  */
    GE = 323,                      /* GE  */
    NE = 324,                      /* NE  */
    NUMBER = 325,                  /* NUMBER  */
    FLOAT = 326,                   /* FLOAT  */
    ID = 327,                      /* ID  */
    DATE_STR = 328,                /* DATE_STR  */
    SSS = 329,                     /* SSS  */
    HIGHER_THAN_EXPRESSION = 330,  /* HIGHER_THAN_EXPRESSION  */
    UMINUS = 331                   /* UMINUS  */
=======
    TABLE = 263,                   /* TABLE  */
    TABLES = 264,                  /* TABLES  */
    INDEX = 265,                   /* INDEX  */
    CALC = 266,                    /* CALC  */
    SELECT = 267,                  /* SELECT  */
    DESC = 268,                    /* DESC  */
    SHOW = 269,                    /* SHOW  */
    SYNC = 270,                    /* SYNC  */
    INSERT = 271,                  /* INSERT  */
    DELETE = 272,                  /* DELETE  */
    UPDATE = 273,                  /* UPDATE  */
    LBRACE = 274,                  /* LBRACE  */
    RBRACE = 275,                  /* RBRACE  */
    COMMA = 276,                   /* COMMA  */
    TRX_BEGIN = 277,               /* TRX_BEGIN  */
    TRX_COMMIT = 278,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 279,            /* TRX_ROLLBACK  */
    INT_T = 280,                   /* INT_T  */
    STRING_T = 281,                /* STRING_T  */
    FLOAT_T = 282,                 /* FLOAT_T  */
    VECTOR_T = 283,                /* VECTOR_T  */
    HELP = 284,                    /* HELP  */
    EXIT = 285,                    /* EXIT  */
    DOT = 286,                     /* DOT  */
    INTO = 287,                    /* INTO  */
    VALUES = 288,                  /* VALUES  */
    FROM = 289,                    /* FROM  */
    WHERE = 290,                   /* WHERE  */
    AND = 291,                     /* AND  */
    SET = 292,                     /* SET  */
    ON = 293,                      /* ON  */
    LOAD = 294,                    /* LOAD  */
    DATA = 295,                    /* DATA  */
    INFILE = 296,                  /* INFILE  */
    EXPLAIN = 297,                 /* EXPLAIN  */
    STORAGE = 298,                 /* STORAGE  */
    FORMAT = 299,                  /* FORMAT  */
    EQ = 300,                      /* EQ  */
    LT = 301,                      /* LT  */
    GT = 302,                      /* GT  */
    LE = 303,                      /* LE  */
    GE = 304,                      /* GE  */
    NE = 305,                      /* NE  */
    NUMBER = 306,                  /* NUMBER  */
    FLOAT = 307,                   /* FLOAT  */
    ID = 308,                      /* ID  */
    SSS = 309,                     /* SSS  */
    UMINUS = 310                   /* UMINUS  */
>>>>>>> 4d420c7 (add vectordb docs and unimplement vectordb (#460))
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
<<<<<<< HEAD
#line 136 "yacc_sql.y"
=======
#line 117 "yacc_sql.y"
>>>>>>> 4d420c7 (add vectordb docs and unimplement vectordb (#460))

  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
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
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;

<<<<<<< HEAD
#line 161 "yacc_sql.hpp"
=======
#line 138 "yacc_sql.hpp"
>>>>>>> 4d420c7 (add vectordb docs and unimplement vectordb (#460))

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
