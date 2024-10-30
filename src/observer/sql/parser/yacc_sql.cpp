/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 125 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_INNER_JOIN = 8,                 /* INNER_JOIN  */
<<<<<<< HEAD
  YYSYMBOL_HAVING = 9,                     /* HAVING  */
  YYSYMBOL_TABLE = 10,                     /* TABLE  */
  YYSYMBOL_TABLES = 11,                    /* TABLES  */
  YYSYMBOL_INDEX = 12,                     /* INDEX  */
  YYSYMBOL_CALC = 13,                      /* CALC  */
  YYSYMBOL_SELECT = 14,                    /* SELECT  */
  YYSYMBOL_ASC = 15,                       /* ASC  */
  YYSYMBOL_DESC = 16,                      /* DESC  */
  YYSYMBOL_SHOW = 17,                      /* SHOW  */
  YYSYMBOL_SYNC = 18,                      /* SYNC  */
  YYSYMBOL_INSERT = 19,                    /* INSERT  */
  YYSYMBOL_DELETE = 20,                    /* DELETE  */
  YYSYMBOL_UPDATE = 21,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 22,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 23,                    /* RBRACE  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 25,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 26,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 27,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 28,                     /* INT_T  */
  YYSYMBOL_DATE_T = 29,                    /* DATE_T  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 32,                  /* VECTOR_T  */
=======
  YYSYMBOL_TABLE = 9,                      /* TABLE  */
  YYSYMBOL_TABLES = 10,                    /* TABLES  */
  YYSYMBOL_INDEX = 11,                     /* INDEX  */
  YYSYMBOL_CALC = 12,                      /* CALC  */
  YYSYMBOL_SELECT = 13,                    /* SELECT  */
  YYSYMBOL_ASC = 14,                       /* ASC  */
  YYSYMBOL_DESC = 15,                      /* DESC  */
  YYSYMBOL_SHOW = 16,                      /* SHOW  */
  YYSYMBOL_SYNC = 17,                      /* SYNC  */
  YYSYMBOL_INSERT = 18,                    /* INSERT  */
  YYSYMBOL_DELETE = 19,                    /* DELETE  */
  YYSYMBOL_UPDATE = 20,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 21,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 22,                    /* RBRACE  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 24,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 25,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 26,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 27,                     /* INT_T  */
  YYSYMBOL_DATE_T = 28,                    /* DATE_T  */
  YYSYMBOL_STRING_T = 29,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 30,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 31,                  /* VECTOR_T  */
  YYSYMBOL_TEXT_T = 32,                    /* TEXT_T  */
>>>>>>> text
  YYSYMBOL_HELP = 33,                      /* HELP  */
  YYSYMBOL_EXIT = 34,                      /* EXIT  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_INTO = 36,                      /* INTO  */
  YYSYMBOL_VALUES = 37,                    /* VALUES  */
  YYSYMBOL_FROM = 38,                      /* FROM  */
  YYSYMBOL_WHERE = 39,                     /* WHERE  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_SET = 41,                       /* SET  */
  YYSYMBOL_ON = 42,                        /* ON  */
  YYSYMBOL_LOAD = 43,                      /* LOAD  */
  YYSYMBOL_DATA = 44,                      /* DATA  */
  YYSYMBOL_INFILE = 45,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 46,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 47,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 48,                    /* FORMAT  */
  YYSYMBOL_MAX = 49,                       /* MAX  */
  YYSYMBOL_MIN = 50,                       /* MIN  */
  YYSYMBOL_AVG = 51,                       /* AVG  */
  YYSYMBOL_SUM = 52,                       /* SUM  */
  YYSYMBOL_COUNT = 53,                     /* COUNT  */
  YYSYMBOL_NOT_LIKE = 54,                  /* NOT_LIKE  */
  YYSYMBOL_LIKE = 55,                      /* LIKE  */
  YYSYMBOL_NOT_IN = 56,                    /* NOT_IN  */
  YYSYMBOL_IN = 57,                        /* IN  */
  YYSYMBOL_NOT_EXISTS = 58,                /* NOT_EXISTS  */
  YYSYMBOL_EXISTS = 59,                    /* EXISTS  */
  YYSYMBOL_LENGTH = 60,                    /* LENGTH  */
  YYSYMBOL_ROUND = 61,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 62,               /* DATE_FORMAT  */
  YYSYMBOL_NULLABLE = 63,                  /* NULLABLE  */
  YYSYMBOL_UNNULLABLE = 64,                /* UNNULLABLE  */
  YYSYMBOL_IS_NULL = 65,                   /* IS_NULL  */
  YYSYMBOL_IS_NOT_NULL = 66,               /* IS_NOT_NULL  */
  YYSYMBOL_VEC_L2_DISTANCE = 67,           /* VEC_L2_DISTANCE  */
  YYSYMBOL_VEC_COSINE_DISTANCE_FUNC = 68,  /* VEC_COSINE_DISTANCE_FUNC  */
  YYSYMBOL_VEC_INNER_PRODUCT_FUNC = 69,    /* VEC_INNER_PRODUCT_FUNC  */
  YYSYMBOL_LBRACKET = 70,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 71,                  /* RBRACKET  */
  YYSYMBOL_UNIQUE = 72,                    /* UNIQUE  */
  YYSYMBOL_ORDER_BY = 73,                  /* ORDER_BY  */
  YYSYMBOL_AS = 74,                        /* AS  */
  YYSYMBOL_EQ = 75,                        /* EQ  */
  YYSYMBOL_LT = 76,                        /* LT  */
  YYSYMBOL_GT = 77,                        /* GT  */
  YYSYMBOL_LE = 78,                        /* LE  */
  YYSYMBOL_GE = 79,                        /* GE  */
  YYSYMBOL_NE = 80,                        /* NE  */
  YYSYMBOL_NUMBER = 81,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 82,                     /* FLOAT  */
  YYSYMBOL_ID = 83,                        /* ID  */
  YYSYMBOL_DATE_STR = 84,                  /* DATE_STR  */
<<<<<<< HEAD
  YYSYMBOL_SSS = 85,                       /* SSS  */
  YYSYMBOL_HIGHER_THAN_EXPRESSION = 86,    /* HIGHER_THAN_EXPRESSION  */
  YYSYMBOL_87_ = 87,                       /* '+'  */
  YYSYMBOL_88_ = 88,                       /* '-'  */
  YYSYMBOL_89_ = 89,                       /* '*'  */
  YYSYMBOL_90_ = 90,                       /* '/'  */
  YYSYMBOL_UMINUS = 91,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 92,                  /* $accept  */
  YYSYMBOL_commands = 93,                  /* commands  */
  YYSYMBOL_command_wrapper = 94,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 95,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 96,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 97,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 98,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 99,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 100,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 101,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 102,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 103,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 104,        /* create_index_stmt  */
  YYSYMBOL_id_list = 105,                  /* id_list  */
  YYSYMBOL_drop_index_stmt = 106,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 107,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 108,            /* attr_def_list  */
  YYSYMBOL_attr_def = 109,                 /* attr_def  */
  YYSYMBOL_null_def = 110,                 /* null_def  */
  YYSYMBOL_number = 111,                   /* number  */
  YYSYMBOL_type = 112,                     /* type  */
  YYSYMBOL_insert_stmt = 113,              /* insert_stmt  */
  YYSYMBOL_value_list = 114,               /* value_list  */
  YYSYMBOL_value = 115,                    /* value  */
  YYSYMBOL_storage_format = 116,           /* storage_format  */
  YYSYMBOL_delete_stmt = 117,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 118,              /* update_stmt  */
  YYSYMBOL_update_target = 119,            /* update_target  */
  YYSYMBOL_update_target_list = 120,       /* update_target_list  */
  YYSYMBOL_select_stmt = 121,              /* select_stmt  */
  YYSYMBOL_sub_select_stmt = 122,          /* sub_select_stmt  */
  YYSYMBOL_calc_stmt = 123,                /* calc_stmt  */
  YYSYMBOL_expression_list = 124,          /* expression_list  */
  YYSYMBOL_expression = 125,               /* expression  */
  YYSYMBOL_relation = 126,                 /* relation  */
  YYSYMBOL_rel_list = 127,                 /* rel_list  */
  YYSYMBOL_where = 128,                    /* where  */
  YYSYMBOL_having = 129,                   /* having  */
=======
  YYSYMBOL_TEXT_STR = 85,                  /* TEXT_STR  */
  YYSYMBOL_SSS = 86,                       /* SSS  */
  YYSYMBOL_HIGHER_THAN_EXPRESSION = 87,    /* HIGHER_THAN_EXPRESSION  */
  YYSYMBOL_88_ = 88,                       /* '+'  */
  YYSYMBOL_89_ = 89,                       /* '-'  */
  YYSYMBOL_90_ = 90,                       /* '*'  */
  YYSYMBOL_91_ = 91,                       /* '/'  */
  YYSYMBOL_UMINUS = 92,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 93,                  /* $accept  */
  YYSYMBOL_commands = 94,                  /* commands  */
  YYSYMBOL_command_wrapper = 95,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 96,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 97,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 98,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 99,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 100,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 101,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 102,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 103,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 104,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 105,        /* create_index_stmt  */
  YYSYMBOL_id_list = 106,                  /* id_list  */
  YYSYMBOL_drop_index_stmt = 107,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 108,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 109,            /* attr_def_list  */
  YYSYMBOL_attr_def = 110,                 /* attr_def  */
  YYSYMBOL_null_def = 111,                 /* null_def  */
  YYSYMBOL_number = 112,                   /* number  */
  YYSYMBOL_type = 113,                     /* type  */
  YYSYMBOL_insert_stmt = 114,              /* insert_stmt  */
  YYSYMBOL_value_list = 115,               /* value_list  */
  YYSYMBOL_value = 116,                    /* value  */
  YYSYMBOL_storage_format = 117,           /* storage_format  */
  YYSYMBOL_delete_stmt = 118,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 119,              /* update_stmt  */
  YYSYMBOL_update_target = 120,            /* update_target  */
  YYSYMBOL_update_target_list = 121,       /* update_target_list  */
  YYSYMBOL_select_stmt = 122,              /* select_stmt  */
  YYSYMBOL_sub_select_stmt = 123,          /* sub_select_stmt  */
  YYSYMBOL_calc_stmt = 124,                /* calc_stmt  */
  YYSYMBOL_expression_list = 125,          /* expression_list  */
  YYSYMBOL_expression = 126,               /* expression  */
  YYSYMBOL_relation = 127,                 /* relation  */
  YYSYMBOL_rel_list = 128,                 /* rel_list  */
  YYSYMBOL_where = 129,                    /* where  */
>>>>>>> text
  YYSYMBOL_join_list = 130,                /* join_list  */
  YYSYMBOL_order_by_list = 131,            /* order_by_list  */
  YYSYMBOL_order_by = 132,                 /* order_by  */
  YYSYMBOL_order_by_flag = 133,            /* order_by_flag  */
  YYSYMBOL_condition_list = 134,           /* condition_list  */
  YYSYMBOL_condition = 135,                /* condition  */
  YYSYMBOL_comp_op = 136,                  /* comp_op  */
  YYSYMBOL_group_by = 137,                 /* group_by  */
<<<<<<< HEAD
  YYSYMBOL_group_by_unit = 138,            /* group_by_unit  */
  YYSYMBOL_load_data_stmt = 139,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 140,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 141,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 142             /* opt_semicolon  */
=======
  YYSYMBOL_load_data_stmt = 138,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 139,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 140,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 141             /* opt_semicolon  */
>>>>>>> text
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  80
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< HEAD
#define YYLAST   789

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
=======
#define YYLAST   720

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
>>>>>>> text
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
<<<<<<< HEAD
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  321

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   342
=======
#define YYNRULES  152
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  305

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   343
>>>>>>> text


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
<<<<<<< HEAD
       2,     2,    89,    87,     2,    88,     2,    90,     2,     2,
=======
       2,     2,    90,    88,     2,    89,     2,    91,     2,     2,
>>>>>>> text
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
<<<<<<< HEAD
      85,    86,    91
=======
      85,    86,    87,    92
>>>>>>> text
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
<<<<<<< HEAD
       0,   235,   235,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   266,   273,   279,   286,   293,   300,   307,
     315,   322,   331,   348,   372,   376,   389,   400,   424,   448,
     472,   487,   505,   508,   521,   535,   546,   549,   552,   556,
     559,   560,   561,   562,   563,   566,   584,   588,   600,   604,
     609,   613,   618,   622,   631,   637,   651,   654,   661,   674,
     692,   701,   712,   715,   725,   730,   771,   777,   786,   791,
     802,   808,   813,   818,   823,   828,   833,   837,   841,   844,
     847,   851,   854,   859,   862,   865,   868,   871,   874,   877,
     884,   891,   898,   905,   912,   916,   920,   924,   928,   932,
     939,   944,   950,   959,   962,   975,   978,   985,   988,   994,
     997,  1009,  1012,  1025,  1028,  1041,  1044,  1048,  1056,  1059,
    1064,  1071,  1080,  1090,  1101,  1111,  1120,  1129,  1142,  1143,
    1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,  1153,
    1154,  1155,  1160,  1163,  1176,  1179,  1192,  1206,  1215,  1226,
    1227
=======
       0,   234,   234,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   265,   272,   278,   285,   292,   299,   306,
     314,   321,   330,   347,   371,   375,   388,   399,   424,   427,
     440,   458,   473,   476,   479,   483,   486,   487,   488,   489,
     490,   491,   494,   512,   516,   528,   532,   537,   541,   546,
     550,   559,   565,   571,   585,   588,   595,   608,   626,   635,
     646,   649,   659,   664,   700,   706,   715,   720,   731,   737,
     742,   747,   752,   757,   762,   766,   770,   773,   776,   780,
     783,   788,   791,   794,   797,   800,   803,   806,   813,   820,
     827,   834,   841,   845,   849,   853,   857,   861,   868,   873,
     879,   888,   891,   904,   907,   914,   917,   929,   932,   945,
     948,   961,   964,   968,   976,   979,   984,   991,  1000,  1011,
    1022,  1031,  1040,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1072,  1077,  1091,
    1100,  1111,  1112
>>>>>>> text
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
<<<<<<< HEAD
  "CREATE", "DROP", "GROUP", "INNER_JOIN", "HAVING", "TABLE", "TABLES",
  "INDEX", "CALC", "SELECT", "ASC", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "DATE_T", "STRING_T", "FLOAT_T",
  "VECTOR_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
=======
  "CREATE", "DROP", "GROUP", "INNER_JOIN", "TABLE", "TABLES", "INDEX",
  "CALC", "SELECT", "ASC", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "DATE_T", "STRING_T", "FLOAT_T", "VECTOR_T",
  "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
>>>>>>> text
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE",
  "FORMAT", "MAX", "MIN", "AVG", "SUM", "COUNT", "NOT_LIKE", "LIKE",
  "NOT_IN", "IN", "NOT_EXISTS", "EXISTS", "LENGTH", "ROUND", "DATE_FORMAT",
  "NULLABLE", "UNNULLABLE", "IS_NULL", "IS_NOT_NULL", "VEC_L2_DISTANCE",
  "VEC_COSINE_DISTANCE_FUNC", "VEC_INNER_PRODUCT_FUNC", "LBRACKET",
  "RBRACKET", "UNIQUE", "ORDER_BY", "AS", "EQ", "LT", "GT", "LE", "GE",
  "NE", "NUMBER", "FLOAT", "ID", "DATE_STR", "TEXT_STR", "SSS",
  "HIGHER_THAN_EXPRESSION", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "id_list", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "null_def", "number", "type", "insert_stmt",
  "value_list", "value", "storage_format", "delete_stmt", "update_stmt",
  "update_target", "update_target_list", "select_stmt", "sub_select_stmt",
  "calc_stmt", "expression_list", "expression", "relation", "rel_list",
  "where", "having", "join_list", "order_by_list", "order_by",
  "order_by_flag", "condition_list", "condition", "comp_op", "group_by",
  "group_by_unit", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

<<<<<<< HEAD
#define YYPACT_NINF (-258)
=======
#define YYPACT_NINF (-254)
>>>>>>> text

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

<<<<<<< HEAD
#define YYTABLE_NINF (-57)
=======
#define YYTABLE_NINF (-54)
>>>>>>> text

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
<<<<<<< HEAD
     706,    -3,    15,   499,   499,   -66,    11,  -258,    -2,    18,
     -23,  -258,  -258,  -258,  -258,  -258,   -21,    49,   706,   107,
     106,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,    32,    35,   105,    36,    53,   499,   116,   118,   119,
     120,   123,   124,   130,   131,  -258,   132,   140,   143,   -44,
    -258,  -258,   102,  -258,  -258,   541,  -258,  -258,  -258,    60,
     142,  -258,  -258,    78,    94,   145,   103,   147,  -258,  -258,
    -258,  -258,    -8,   159,   104,  -258,   166,   -17,   289,   331,
     373,   415,   457,   499,   499,   499,   499,   499,   499,   -39,
     187,   129,   148,  -258,  -258,  -258,  -258,   499,   499,   499,
     499,   499,   149,   176,   184,   150,   -44,   161,   153,   182,
      -6,   164,   206,   173,  -258,  -258,   234,  -258,   235,  -258,
     236,  -258,   238,  -258,   243,    -7,    68,    79,   127,   139,
     151,  -258,  -258,   -44,   196,   -53,  -258,  -258,   -61,   -61,
    -258,  -258,   -51,   244,   247,   240,  -258,   195,   248,  -258,
     237,   223,   250,   200,   262,  -258,   255,   197,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,   499,   499,   499,   499,   499,
     187,  -258,   198,  -258,   199,  -258,   149,   271,   -44,   121,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,   310,   699,  -258,   245,   261,   137,
     150,   184,   274,  -258,  -258,  -258,  -258,  -258,    -9,   153,
     263,   204,  -258,   221,   291,     8,    12,    24,    34,    38,
    -258,  -258,  -258,   244,   149,   184,   187,   303,   583,   625,
     240,   262,  -258,  -258,  -258,   248,  -258,   231,   246,  -258,
    -258,  -258,   250,   283,  -258,   307,   249,  -258,  -258,  -258,
    -258,  -258,  -258,   292,   326,   312,  -258,  -258,   109,   121,
    -258,   109,  -258,  -258,  -258,  -258,   313,  -258,     1,   254,
     320,   307,   240,   340,   336,  -258,    22,    41,   262,  -258,
     307,  -258,   323,   271,   499,   240,   275,   324,  -258,  -258,
    -258,  -258,  -258,   155,  -258,   499,  -258,  -258,   499,  -258,
     -11,   155,  -258,  -258,   337,  -258,   499,  -258,   -11,   337,
    -258
=======
     639,     4,    19,   471,   471,   -65,    14,  -254,    20,     7,
     -22,  -254,  -254,  -254,  -254,  -254,    24,    33,   639,   111,
      88,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,    34,    35,   108,    41,    47,   471,   110,   112,   114,
     116,   117,   136,   141,   142,  -254,   143,   144,   150,   121,
    -254,  -254,   -28,  -254,  -254,  -254,   514,  -254,  -254,  -254,
      78,    94,  -254,  -254,    99,   103,   149,   119,   148,  -254,
    -254,  -254,  -254,   171,   153,   125,  -254,   167,   -20,   256,
     299,   342,   385,   428,   471,   471,   471,   471,   471,   471,
     -42,   175,   128,   130,  -254,  -254,  -254,  -254,   471,   471,
     471,   471,   471,   131,   178,   179,   134,   121,   139,   137,
     145,   177,   146,  -254,  -254,   204,  -254,   211,  -254,   212,
    -254,   217,  -254,   219,   -16,   133,   147,   156,   160,   209,
    -254,  -254,   121,   172,   -60,  -254,  -254,   -58,   -58,  -254,
    -254,   -49,   208,   221,   206,  -254,   195,   229,  -254,   243,
     118,   230,   259,   210,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,   471,   471,   471,   471,   471,   175,  -254,   218,  -254,
     220,  -254,   131,   286,   121,    91,  -254,  -254,  -254,  -254,
    -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
     640,   612,  -254,   262,   283,   115,   134,   179,   301,  -254,
    -254,  -254,  -254,  -254,  -254,    -4,   137,   289,   231,   291,
      -6,     5,     9,    25,    32,  -254,  -254,  -254,   208,   131,
     179,   175,   293,   471,   557,   206,   300,  -254,  -254,  -254,
     229,  -254,   239,   246,  -254,  -254,  -254,   230,   281,   306,
     247,  -254,  -254,  -254,  -254,  -254,  -254,   290,  -254,   309,
    -254,   -53,    91,  -254,   -53,  -254,  -254,  -254,  -254,   311,
    -254,   287,  -254,   251,   314,   306,   206,   270,  -254,    21,
      39,   269,   306,  -254,   325,   286,   471,  -254,   331,  -254,
     271,  -254,  -254,  -254,   -10,  -254,  -254,  -254,  -254,   332,
     471,  -254,   -10,   332,  -254
>>>>>>> text
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
<<<<<<< HEAD
     159,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
      59,    60,    80,    63,    64,     0,    93,    92,    77,    78,
      74,    31,    30,     0,     0,     0,     0,     0,   157,     1,
     160,     2,    66,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,     0,     0,    82,    59,    60,    91,     0,     0,     0,
       0,     0,     0,     0,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    94,     0,    95,     0,    96,
       0,    97,     0,    98,     0,     0,     0,     0,     0,     0,
       0,    61,    62,     0,     0,    81,    83,    79,    86,    87,
      88,    89,   110,   113,     0,   128,    68,     0,    72,   158,
       0,     0,    42,     0,     0,    41,     0,     0,    36,    99,
     100,   102,   103,   101,   104,     0,     0,     0,     0,     0,
      56,    65,     0,    84,     0,   111,     0,   119,     0,     0,
     146,   147,   148,   149,   150,   151,   144,   145,   138,   139,
     140,   141,   142,   143,     0,     0,   116,   129,     0,     0,
       0,   115,     0,    50,    53,    51,    52,    54,    46,     0,
       0,     0,    40,     0,     0,     0,     0,     0,     0,     0,
      57,    85,   112,   113,     0,   115,    56,     0,     0,   131,
     128,     0,   136,    70,    71,    72,    69,     0,     0,    47,
      48,    45,    42,    66,    67,    34,     0,   105,   106,   109,
     108,   107,   114,     0,   152,     0,    76,   133,   134,     0,
     132,   135,   130,    73,   156,    49,     0,    43,    37,     0,
       0,    34,   128,     0,   117,    55,    92,    46,     0,    39,
      34,    32,     0,   119,     0,   128,   121,     0,    44,    38,
      35,    33,   120,   154,   118,     0,    75,   137,     0,   153,
     125,   154,   126,   127,   123,   155,     0,   122,   125,   123,
     124
=======
     151,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,     0,     0,     0,     0,
      56,    57,    78,    60,    61,    62,     0,    91,    90,    75,
      76,    72,    31,    30,     0,     0,     0,     0,     0,   149,
       1,   152,     2,     0,     0,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    53,     0,     0,    80,    56,    57,    89,     0,     0,
       0,     0,     0,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,    88,    92,     0,    93,     0,    94,     0,
      95,     0,    96,     0,     0,     0,     0,     0,     0,     0,
      58,    59,     0,     0,    79,    81,    77,    84,    85,    86,
      87,   108,   111,     0,   124,    66,     0,    70,   150,     0,
       0,    38,     0,     0,    36,    97,    98,   100,   101,    99,
     102,     0,     0,     0,     0,     0,    53,    63,     0,    82,
       0,   109,     0,   115,     0,     0,   141,   142,   143,   144,
     145,   146,   139,   140,   133,   134,   135,   136,   137,   138,
       0,     0,   114,   125,     0,     0,     0,   113,     0,    46,
      49,    47,    48,    50,    51,    42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    54,    83,   110,   111,     0,
     113,    53,     0,     0,   127,   124,     0,   131,    68,    69,
      70,    67,     0,     0,    43,    44,    41,    38,    64,    34,
       0,   103,   104,   107,   106,   105,   112,     0,   147,     0,
      74,   129,     0,   128,   130,   126,    71,   148,    45,     0,
      39,     0,    37,     0,     0,    34,   124,   117,    52,    90,
      42,     0,    34,    32,     0,   115,     0,    73,     0,    40,
       0,    35,    33,   116,   121,   132,    65,   122,   123,   119,
       0,   118,   121,   119,   120
>>>>>>> text
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
<<<<<<< HEAD
    -258,  -258,   342,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -257,  -258,  -258,   110,   136,    76,  -258,
    -258,  -258,  -178,   -49,   126,  -258,  -258,   192,   152,     0,
      26,  -258,    -1,   -45,  -175,   170,  -199,  -258,   111,  -258,
      86,    88,  -166,  -258,  -119,  -258,    96,  -258,  -258,  -258,
    -258
=======
    -254,  -254,   338,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,  -254,  -254,  -253,  -254,  -254,   123,   155,    77,  -254,
    -254,  -254,  -173,   -50,  -254,  -254,  -254,   152,   132,     8,
    -193,  -254,    -3,   -46,  -172,   151,  -188,    80,  -254,    70,
      72,  -214,  -254,   -91,  -254,  -254,  -254,  -254,  -254
>>>>>>> text
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
<<<<<<< HEAD
      28,    29,    30,   280,    31,    32,   220,   162,   251,   276,
     218,    33,   144,    67,   120,    34,    35,   158,   211,   237,
     204,    37,    68,    69,   153,   187,   156,   296,   235,   306,
     317,   314,   206,   207,   208,   284,   309,    38,    39,    40,
      81
=======
      28,    29,    30,   274,    31,    32,   217,   161,   246,   269,
     215,    33,   143,    68,   272,    34,    35,   157,   207,   232,
     200,    37,    69,    70,   152,   183,   155,   230,   287,   301,
     299,   202,   203,   204,   277,    38,    39,    40,    82
>>>>>>> text
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
<<<<<<< HEAD
      36,    87,   230,    70,   312,   313,   124,    41,     4,    42,
     100,   233,   246,   248,   118,     4,   174,    71,    36,    55,
     106,   182,    72,   184,   292,    44,    59,    45,   110,   111,
     183,   257,   185,   300,    73,   258,   264,    60,    61,   119,
      63,    64,   141,   142,    99,   -56,   143,   259,   135,   136,
     137,   138,   139,   140,   249,   250,    74,   260,   265,   263,
      75,   261,    76,   148,   149,   150,   151,   159,   164,    43,
     108,   109,   110,   111,   272,   288,   108,   109,   110,   111,
     108,   109,   110,   111,   107,   238,   239,   126,   128,   130,
     132,   134,   175,    77,   180,   108,   109,   110,   111,   108,
     109,   110,   111,   176,   249,   250,   147,    79,   297,    80,
     205,   108,   109,   110,   111,    82,   293,    84,    83,    85,
     165,   108,   109,   110,   111,   108,   109,   110,   111,   304,
     225,   226,   227,   228,   229,     4,    86,   101,    88,   236,
      89,    90,    91,    46,    87,    92,    93,   108,   109,   110,
     111,   177,    94,    95,    96,   108,   109,   110,   111,   241,
     243,   113,    97,   178,   222,    98,   108,   109,   110,   111,
      47,    48,    49,    50,    51,   179,   102,   114,   116,   308,
     112,    52,    53,    54,    55,   103,   115,   122,    56,    57,
      58,    59,   117,   268,   271,   205,   108,   109,   110,   111,
      55,   121,    60,    61,    62,    63,    64,    59,   123,    65,
      66,   143,   145,   154,   108,   109,   110,   111,    60,    61,
     286,    63,    64,   155,    87,    99,   108,   109,   110,   111,
     163,   146,   152,   157,   242,   244,   161,   205,   108,   109,
     110,   111,   108,   109,   110,   111,   160,   166,   167,   303,
     205,   213,   214,   215,   216,   217,   168,   169,   170,   171,
     310,   172,   189,   311,   267,   270,   173,   181,   186,   188,
     209,   318,   210,   212,   219,   221,     4,   223,   289,   234,
     224,   231,   232,   241,   247,   240,   253,   254,   299,    47,
      48,    49,    50,    51,   190,   191,   192,   193,   194,   195,
      52,    53,    54,    55,   255,   196,   197,    56,    57,    58,
      59,    46,   125,   256,   274,   198,   199,   200,   201,   202,
     203,    60,    61,    62,    63,    64,   266,   275,    65,    66,
     119,   279,   281,   283,   282,   285,   287,   290,    47,    48,
      49,    50,    51,   291,   294,   295,   301,   307,   305,    52,
      53,    54,    55,    46,   127,   252,    56,    57,    58,    59,
      78,   316,   277,   298,   190,   191,   192,   193,   194,   195,
      60,    61,    62,    63,    64,   196,   197,    65,    66,   278,
      47,    48,    49,    50,    51,   198,   199,   200,   201,   202,
     203,    52,    53,    54,    55,    46,   129,   273,    56,    57,
      58,    59,   245,   262,   302,   320,   319,   315,     0,     0,
       0,     0,    60,    61,    62,    63,    64,     0,     0,    65,
      66,     0,    47,    48,    49,    50,    51,     0,     0,     0,
       0,     0,     0,    52,    53,    54,    55,    46,   131,     0,
      56,    57,    58,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,    61,    62,    63,    64,     0,
       0,    65,    66,     0,    47,    48,    49,    50,    51,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    55,    46,
     133,     0,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    61,    62,    63,
      64,     0,     0,    65,    66,     0,    47,    48,    49,    50,
=======
      88,    71,   123,   225,   297,   298,   170,   102,    36,   101,
     228,   237,   239,    41,   178,    42,   251,   243,    72,   241,
     107,   265,   284,   179,    73,   180,    36,   252,    44,   291,
      45,   253,   111,   112,   181,   109,   110,   111,   112,   140,
     141,   263,   258,   -53,   142,    75,   103,   254,   134,   135,
     136,   137,   138,   139,   255,   104,    74,   257,   259,   244,
     245,    76,   285,   147,   148,   149,   150,   158,   109,   110,
     111,   112,   109,   110,   111,   112,    43,    78,   109,   110,
     111,   112,   109,   110,   111,   112,   125,   127,   129,   131,
     133,    81,   176,   109,   110,   111,   112,   109,   110,   111,
     112,   108,   244,   245,     4,   146,   288,    77,   201,   233,
     234,    80,    46,   109,   110,   111,   112,    83,    84,    85,
     109,   110,   111,   112,    86,   220,   221,   222,   223,   224,
      87,    89,   113,    90,   231,    91,   236,    92,    93,    88,
      47,    48,    49,    50,    51,   209,   210,   211,   212,   213,
     214,    52,    53,    54,    55,   238,   171,    94,    56,    57,
      58,    59,    95,    96,    97,    98,   109,   110,   111,   112,
     172,    99,    60,    61,    62,    63,    64,    65,    55,   173,
      66,    67,   114,   174,    55,    59,   115,   261,   264,   201,
     116,    59,   119,   118,   117,   120,    60,    61,   142,    63,
      64,    65,    60,    61,   100,    63,    64,    65,   121,   122,
     100,   144,   279,   145,   151,   153,    88,   156,   154,   163,
     160,   109,   110,   111,   112,   159,   165,   185,   162,   164,
     201,   182,   175,   166,   167,   109,   110,   111,   112,   168,
     294,   169,   184,   177,   109,   110,   111,   112,   109,   110,
     111,   112,   206,   216,   302,    47,    48,    49,    50,    51,
     186,   187,   188,   189,   190,   191,    52,    53,    54,    55,
     205,   192,   193,    56,    57,    58,    59,    46,   124,   208,
     218,   194,   195,   196,   197,   198,   199,    60,    61,    62,
      63,    64,    65,   219,   229,    66,    67,   109,   110,   111,
     112,   226,   235,   227,   236,    47,    48,    49,    50,    51,
     242,   248,   250,     4,   249,   260,    52,    53,    54,    55,
      46,   126,   267,    56,    57,    58,    59,   268,   271,   273,
     275,   278,   276,   280,   282,   281,   283,    60,    61,    62,
      63,    64,    65,   286,   290,    66,    67,   292,    47,    48,
      49,    50,    51,   295,   296,   300,    79,   289,   240,    52,
      53,    54,    55,    46,   128,   293,    56,    57,    58,    59,
     270,   247,   266,   304,   303,     0,     0,     0,     0,   256,
      60,    61,    62,    63,    64,    65,     0,     0,    66,    67,
       0,    47,    48,    49,    50,    51,     0,     0,     0,     0,
       0,     0,    52,    53,    54,    55,    46,   130,     0,    56,
      57,    58,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     0,
       0,    66,    67,     0,    47,    48,    49,    50,    51,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    55,    46,
     132,     0,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    61,    62,    63,
      64,    65,     0,     0,    66,    67,     0,    47,    48,    49,
      50,    51,     0,     0,     0,     0,     0,     0,    52,    53,
      54,    55,    46,     0,     0,    56,    57,    58,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      61,    62,    63,    64,    65,     0,     0,    66,    67,     0,
      47,    48,    49,    50,    51,     0,     0,     0,     0,     0,
       0,    52,    53,    54,    55,    46,     0,     0,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,    61,    62,    63,    64,    65,     0,     0,
      66,    67,     0,    47,    48,    49,    50,    51,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,   262,     0,
       0,    56,    57,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,    62,    63,    64,
      65,     0,     0,    66,    67,     0,    47,    48,    49,    50,
>>>>>>> text
      51,     0,     0,     0,     0,     0,     0,    52,    53,    54,
      55,    46,     0,     0,    56,    57,    58,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
<<<<<<< HEAD
      62,    63,    64,     0,     0,    65,    66,     0,    47,    48,
      49,    50,    51,     0,     0,     0,     0,     0,     0,    52,
      53,    54,    55,    46,     0,     0,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    63,    64,     0,     0,    65,    66,     0,
      47,    48,    49,    50,    51,     0,     0,     0,     0,     0,
       0,    52,    53,    54,    55,   189,     0,     0,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   104,   105,    62,    63,    64,     0,     0,    65,
      66,     0,    47,    48,    49,    50,    51,     0,     0,     0,
       0,     0,     0,    52,    53,    54,    55,   269,     0,     0,
      56,    57,    58,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,    61,    62,    63,    64,     0,
       0,    65,    66,     0,    47,    48,    49,    50,    51,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    55,     0,
       0,     0,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    61,    62,    63,
      64,     1,     2,    65,    66,     0,     0,     0,     0,     3,
       4,     0,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    11,    12,    13,     0,     0,     0,     0,     0,    14,
      15,     0,     0,     0,     0,     0,     0,    16,     0,    17,
       0,     0,    18,   190,   191,   192,   193,   194,   195,     0,
       0,     0,     0,     0,   196,   197,     0,     0,     0,     0,
       0,     0,     0,     0,   198,   199,   200,   201,   202,   203,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111
=======
      62,    63,    64,    65,     1,     2,    66,    67,     0,     0,
       0,     3,     4,     0,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,    12,    13,   186,   187,   188,   189,
     190,   191,    14,    15,     0,     0,     0,   192,   193,     0,
      16,     0,    17,     0,     0,    18,     0,   194,   195,   196,
     197,   198,   199,     0,   186,   187,   188,   189,   190,   191,
     109,   110,   111,   112,     0,   192,   193,     0,     0,     0,
       0,     0,     0,     0,     0,   194,   195,   196,   197,   198,
     199
>>>>>>> text
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
       0,    46,   180,     4,    15,    16,    23,    10,    14,    12,
      59,   186,   211,    22,    22,    14,    23,    83,    18,    63,
      65,    74,    11,    74,   281,    10,    70,    12,    89,    90,
      83,    23,    83,   290,    36,    23,   235,    81,    82,    47,
      84,    85,    81,    82,    88,    23,    24,    23,    93,    94,
      95,    96,    97,    98,    63,    64,    38,    23,   236,   234,
      83,    23,    83,   108,   109,   110,   111,   116,    74,    72,
      87,    88,    89,    90,   240,    74,    87,    88,    89,    90,
      87,    88,    89,    90,    24,   204,   205,    88,    89,    90,
      91,    92,    24,    44,   143,    87,    88,    89,    90,    87,
      88,    89,    90,    24,    63,    64,   107,     0,   286,     3,
     155,    87,    88,    89,    90,    83,   282,    12,    83,    83,
     120,    87,    88,    89,    90,    87,    88,    89,    90,   295,
     175,   176,   177,   178,   179,    14,    83,    35,    22,   188,
      22,    22,    22,    22,   189,    22,    22,    87,    88,    89,
      90,    24,    22,    22,    22,    87,    88,    89,    90,    22,
     209,    83,    22,    24,   164,    22,    87,    88,    89,    90,
      49,    50,    51,    52,    53,    24,    74,    83,    75,    24,
      38,    60,    61,    62,    63,    83,    41,    83,    67,    68,
      69,    70,    45,   238,   239,   240,    87,    88,    89,    90,
      63,    42,    81,    82,    83,    84,    85,    70,    42,    88,
      89,    24,    83,    37,    87,    88,    89,    90,    81,    82,
     269,    84,    85,    39,   269,    88,    87,    88,    89,    90,
      48,    83,    83,    83,   208,   209,    83,   282,    87,    88,
      89,    90,    87,    88,    89,    90,    85,    83,    42,   294,
     295,    28,    29,    30,    31,    32,    83,    23,    23,    23,
     305,    23,    22,   308,   238,   239,    23,    71,    24,    22,
      75,   316,    24,    36,    24,    75,    14,    22,   278,     8,
      83,    83,    83,    22,    10,    40,    23,    83,   288,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    83,    65,    66,    67,    68,    69,
      70,    22,    23,    22,    83,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    23,    81,    88,    89,
      47,    24,    83,     7,    42,    23,    23,    83,    49,    50,
      51,    52,    53,    23,     4,     9,    23,    23,    73,    60,
      61,    62,    63,    22,    23,   219,    67,    68,    69,    70,
      18,    24,   252,   287,    54,    55,    56,    57,    58,    59,
      81,    82,    83,    84,    85,    65,    66,    88,    89,   253,
      49,    50,    51,    52,    53,    75,    76,    77,    78,    79,
      80,    60,    61,    62,    63,    22,    23,   245,    67,    68,
      69,    70,   210,   233,   293,   319,   318,   311,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,    88,
      89,    -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    22,    23,    -1,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,
      -1,    88,    89,    -1,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    22,
      23,    -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    -1,    -1,    88,    89,    -1,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    22,    -1,    -1,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    -1,    88,    89,    -1,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    22,    -1,    -1,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    -1,    -1,    88,    89,    -1,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    22,    -1,    -1,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,    88,
      89,    -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    22,    -1,    -1,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,
      -1,    88,    89,    -1,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    -1,
      -1,    -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,     5,     6,    88,    89,    -1,    -1,    -1,    -1,    13,
      14,    -1,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    43,
      -1,    -1,    46,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90
=======
      46,     4,    22,   176,    14,    15,    22,    35,     0,    59,
     182,   204,   205,     9,    74,    11,    22,    21,    83,   207,
      66,   235,   275,    83,    10,    74,    18,    22,     9,   282,
      11,    22,    90,    91,    83,    88,    89,    90,    91,    81,
      82,   234,   230,    22,    23,    38,    74,    22,    94,    95,
      96,    97,    98,    99,    22,    83,    36,   229,   231,    63,
      64,    83,   276,   109,   110,   111,   112,   117,    88,    89,
      90,    91,    88,    89,    90,    91,    72,    44,    88,    89,
      90,    91,    88,    89,    90,    91,    89,    90,    91,    92,
      93,     3,   142,    88,    89,    90,    91,    88,    89,    90,
      91,    23,    63,    64,    13,   108,   279,    83,   154,   200,
     201,     0,    21,    88,    89,    90,    91,    83,    83,    11,
      88,    89,    90,    91,    83,   171,   172,   173,   174,   175,
      83,    21,    38,    21,   184,    21,    21,    21,    21,   185,
      49,    50,    51,    52,    53,    27,    28,    29,    30,    31,
      32,    60,    61,    62,    63,   205,    23,    21,    67,    68,
      69,    70,    21,    21,    21,    21,    88,    89,    90,    91,
      23,    21,    81,    82,    83,    84,    85,    86,    63,    23,
      89,    90,    83,    23,    63,    70,    83,   233,   234,   235,
      41,    70,    21,    45,    75,    42,    81,    82,    23,    84,
      85,    86,    81,    82,    89,    84,    85,    86,    83,    42,
      89,    83,   262,    83,    83,    37,   262,    83,    39,    42,
      83,    88,    89,    90,    91,    86,    22,    21,    83,    83,
     276,    23,    23,    22,    22,    88,    89,    90,    91,    22,
     286,    22,    21,    71,    88,    89,    90,    91,    88,    89,
      90,    91,    23,    23,   300,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      75,    65,    66,    67,    68,    69,    70,    21,    22,    36,
      21,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    83,     8,    89,    90,    88,    89,    90,
      91,    83,    40,    83,    21,    49,    50,    51,    52,    53,
       9,    22,    21,    13,    83,    22,    60,    61,    62,    63,
      21,    22,    83,    67,    68,    69,    70,    81,    47,    23,
      83,    22,    42,    22,    83,    48,    22,    81,    82,    83,
      84,    85,    86,    73,    75,    89,    90,    22,    49,    50,
      51,    52,    53,    22,    83,    23,    18,   280,   206,    60,
      61,    62,    63,    21,    22,   285,    67,    68,    69,    70,
     247,   216,   240,   303,   302,    -1,    -1,    -1,    -1,   228,
      81,    82,    83,    84,    85,    86,    -1,    -1,    89,    90,
      -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    21,    22,    -1,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    -1,
      -1,    89,    90,    -1,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    21,
      22,    -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    -1,    -1,    89,    90,    -1,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    21,    -1,    -1,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    -1,    -1,    89,    90,    -1,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    21,    -1,    -1,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    -1,    -1,
      89,    90,    -1,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    21,    -1,
      -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    -1,    -1,    89,    90,    -1,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    -1,    -1,    -1,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,     5,     6,    89,    90,    -1,    -1,
      -1,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    25,    26,    54,    55,    56,    57,
      58,    59,    33,    34,    -1,    -1,    -1,    65,    66,    -1,
      41,    -1,    43,    -1,    -1,    46,    -1,    75,    76,    77,
      78,    79,    80,    -1,    54,    55,    56,    57,    58,    59,
      88,    89,    90,    91,    -1,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80
>>>>>>> text
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
<<<<<<< HEAD
       0,     5,     6,    13,    14,    16,    17,    18,    19,    20,
      21,    25,    26,    27,    33,    34,    41,    43,    46,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   106,   107,   113,   117,   118,   121,   123,   139,   140,
     141,    10,    12,    72,    10,    12,    22,    49,    50,    51,
      52,    53,    60,    61,    62,    63,    67,    68,    69,    70,
      81,    82,    83,    84,    85,    88,    89,   115,   124,   125,
     124,    83,    11,    36,    38,    83,    83,    44,    94,     0,
       3,   142,    83,    83,    12,    83,    83,   125,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    88,
     115,    35,    74,    83,    81,    82,   125,    24,    87,    88,
      89,    90,    38,    83,    83,    41,    75,    45,    22,    47,
     116,    42,    83,    42,    23,    23,   124,    23,   124,    23,
     124,    23,   124,    23,   124,   125,   125,   125,   125,   125,
     125,    81,    82,    24,   114,    83,    83,   124,   125,   125,
     125,   125,    83,   126,    37,    39,   128,    83,   119,   115,
      85,    83,   109,    48,    74,   121,    83,    42,    83,    23,
      23,    23,    23,    23,    23,    24,    24,    24,    24,    24,
     115,    71,    74,    83,    74,    83,    24,   127,    22,    22,
      54,    55,    56,    57,    58,    59,    65,    66,    75,    76,
      77,    78,    79,    80,   122,   125,   134,   135,   136,    75,
      24,   120,    36,    28,    29,    30,    31,    32,   112,    24,
     108,    75,   121,    22,    83,   125,   125,   125,   125,   125,
     114,    83,    83,   126,     8,   130,   115,   121,   136,   136,
      40,    22,   122,   115,   122,   119,   128,    10,    22,    63,
      64,   110,   109,    23,    83,    83,    22,    23,    23,    23,
      23,    23,   127,   126,   128,   114,    23,   122,   125,    22,
     122,   125,   134,   120,    83,    81,   111,   108,   116,    24,
     105,    83,    42,     7,   137,    23,   115,    23,    74,   121,
      83,    23,   105,   134,     4,     9,   129,   114,   110,   121,
     105,    23,   130,   125,   134,    73,   131,    23,    24,   138,
     125,   125,    15,    16,   133,   138,    24,   132,   125,   133,
     132
=======
       0,     5,     6,    12,    13,    15,    16,    17,    18,    19,
      20,    24,    25,    26,    33,    34,    41,    43,    46,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   107,   108,   114,   118,   119,   122,   124,   138,   139,
     140,     9,    11,    72,     9,    11,    21,    49,    50,    51,
      52,    53,    60,    61,    62,    63,    67,    68,    69,    70,
      81,    82,    83,    84,    85,    86,    89,    90,   116,   125,
     126,   125,    83,    10,    36,    38,    83,    83,    44,    95,
       0,     3,   141,    83,    83,    11,    83,    83,   126,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      89,   116,    35,    74,    83,    81,    82,   126,    23,    88,
      89,    90,    91,    38,    83,    83,    41,    75,    45,    21,
      42,    83,    42,    22,    22,   125,    22,   125,    22,   125,
      22,   125,    22,   125,   126,   126,   126,   126,   126,   126,
      81,    82,    23,   115,    83,    83,   125,   126,   126,   126,
     126,    83,   127,    37,    39,   129,    83,   120,   116,    86,
      83,   110,    83,    42,    83,    22,    22,    22,    22,    22,
      22,    23,    23,    23,    23,    23,   116,    71,    74,    83,
      74,    83,    23,   128,    21,    21,    54,    55,    56,    57,
      58,    59,    65,    66,    75,    76,    77,    78,    79,    80,
     123,   126,   134,   135,   136,    75,    23,   121,    36,    27,
      28,    29,    30,    31,    32,   113,    23,   109,    21,    83,
     126,   126,   126,   126,   126,   115,    83,    83,   127,     8,
     130,   116,   122,   136,   136,    40,    21,   123,   116,   123,
     120,   129,     9,    21,    63,    64,   111,   110,    22,    83,
      21,    22,    22,    22,    22,    22,   128,   127,   129,   115,
      22,   126,    21,   123,   126,   134,   121,    83,    81,   112,
     109,    47,   117,    23,   106,    83,    42,   137,    22,   116,
      22,    48,    83,    22,   106,   134,    73,   131,   115,   111,
      75,   106,    22,   130,   126,    22,    83,    14,    15,   133,
      23,   132,   126,   133,   132
>>>>>>> text
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
<<<<<<< HEAD
       0,    92,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   104,   105,   105,   106,   107,   107,   107,
     107,   107,   108,   108,   109,   109,   110,   110,   110,   111,
     112,   112,   112,   112,   112,   113,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   116,   117,   118,
     119,   119,   120,   120,   121,   121,   122,   123,   124,   124,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     126,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   132,   132,   133,   133,   133,   134,   134,
     134,   135,   135,   135,   135,   135,   135,   135,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   137,   137,   138,   138,   139,   140,   141,   142,
     142
=======
       0,    93,    94,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   105,   106,   106,   107,   108,   109,   109,
     110,   110,   111,   111,   111,   112,   113,   113,   113,   113,
     113,   113,   114,   115,   115,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   118,   119,   120,   120,
     121,   121,   122,   122,   123,   124,   125,   125,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   127,   127,
     127,   128,   128,   129,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   133,   134,   134,   134,   135,   135,   135,
     135,   135,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   137,   138,   139,
     140,   141,   141
>>>>>>> text
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
<<<<<<< HEAD
       2,     2,     9,    10,     0,     3,     5,     8,    10,     9,
       6,     5,     0,     3,     6,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     8,     0,     3,     1,     1,
       1,     2,     2,     1,     1,     4,     0,     4,     4,     6,
       3,     3,     0,     3,     2,    10,     3,     2,     1,     3,
       1,     3,     2,     3,     4,     5,     3,     3,     3,     3,
       3,     2,     1,     1,     3,     3,     3,     3,     3,     4,
       4,     4,     4,     4,     4,     6,     6,     6,     6,     6,
       1,     2,     3,     0,     3,     0,     2,     0,     2,     0,
       5,     0,     4,     0,     4,     0,     1,     1,     0,     1,
       3,     2,     3,     3,     3,     3,     2,     6,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     3,     7,     2,     4,     0,
       1
=======
       2,     2,     9,    10,     0,     3,     5,     8,     0,     3,
       6,     3,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     1,     1,     2,     2,
       1,     1,     1,     4,     0,     4,     4,     6,     3,     3,
       0,     3,     2,     9,     3,     2,     1,     3,     1,     3,
       2,     3,     4,     5,     3,     3,     3,     3,     3,     2,
       1,     1,     3,     3,     3,     3,     3,     4,     4,     4,
       4,     4,     4,     6,     6,     6,     6,     6,     1,     2,
       3,     0,     3,     0,     2,     0,     5,     0,     4,     0,
       4,     0,     1,     1,     0,     1,     3,     2,     3,     3,
       3,     2,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     7,     2,
       4,     0,     1
>>>>>>> text
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
<<<<<<< HEAD
#line 236 "yacc_sql.y"
=======
#line 235 "yacc_sql.y"
>>>>>>> text
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
<<<<<<< HEAD
#line 1987 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 266 "yacc_sql.y"
=======
#line 1962 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 265 "yacc_sql.y"
>>>>>>> text
         {
      LOG_DEBUG("parse exit_stmt");
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
<<<<<<< HEAD
#line 1997 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 273 "yacc_sql.y"
=======
#line 1972 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 272 "yacc_sql.y"
>>>>>>> text
         {
      LOG_DEBUG("parse help_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
<<<<<<< HEAD
#line 2006 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 279 "yacc_sql.y"
=======
#line 1981 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 278 "yacc_sql.y"
>>>>>>> text
         {
      LOG_DEBUG("parse sync_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
<<<<<<< HEAD
#line 2015 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 286 "yacc_sql.y"
=======
#line 1990 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 285 "yacc_sql.y"
>>>>>>> text
               {
      LOG_DEBUG("parse begin_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
<<<<<<< HEAD
#line 2024 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 293 "yacc_sql.y"
=======
#line 1999 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 292 "yacc_sql.y"
>>>>>>> text
               {
      LOG_DEBUG("parse commit_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
<<<<<<< HEAD
#line 2033 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 300 "yacc_sql.y"
=======
#line 2008 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 299 "yacc_sql.y"
>>>>>>> text
                  {
      LOG_DEBUG("parse rollback_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
<<<<<<< HEAD
#line 2042 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 307 "yacc_sql.y"
=======
#line 2017 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 306 "yacc_sql.y"
>>>>>>> text
                  {
      LOG_DEBUG("parse drop_table_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 2053 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 315 "yacc_sql.y"
=======
#line 2028 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 314 "yacc_sql.y"
>>>>>>> text
                {
      LOG_DEBUG("parse show_tables_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
<<<<<<< HEAD
#line 2062 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 322 "yacc_sql.y"
=======
#line 2037 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 321 "yacc_sql.y"
>>>>>>> text
             {
      LOG_DEBUG("parse desc_table_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 2073 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 332 "yacc_sql.y"
=======
#line 2048 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 331 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse create_index_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      create_index.attribute_names.emplace_back((yyvsp[-2].string));
      create_index.is_unique = false;
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
<<<<<<< HEAD
#line 2094 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 349 "yacc_sql.y"
=======
#line 2069 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 348 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse create_index_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.is_unique = true;
      std::vector<std::string> attribute_names;
      attribute_names.emplace_back((yyvsp[-2].string));
      if ((yyvsp[-1].relation_list) != nullptr) {
        attribute_names.insert(attribute_names.end(), (yyvsp[-1].relation_list)->begin(), (yyvsp[-1].relation_list)->end());
        delete (yyvsp[-1].relation_list);
      }
      create_index.attribute_names = std::move(attribute_names);

      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
<<<<<<< HEAD
#line 2118 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 372 "yacc_sql.y"
=======
#line 2093 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 371 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse id_list");
      (yyval.relation_list) = nullptr;
    }
<<<<<<< HEAD
#line 2127 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA ID id_list  */
#line 376 "yacc_sql.y"
=======
#line 2102 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA ID id_list  */
#line 375 "yacc_sql.y"
>>>>>>> text
                        { 
      LOG_DEBUG("parse id_list");
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 2142 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 390 "yacc_sql.y"
=======
#line 2117 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 389 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse drop_index_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 2155 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 401 "yacc_sql.y"
=======
#line 2130 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 400 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }

      create_table.use_sub_select = false;
      create_table.sub_select = nullptr;
    }
<<<<<<< HEAD
#line 2183 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt  */
#line 425 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-7].string);
      free((yyvsp[-7].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-4].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-5].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-5].attr_info);
      if ((yyvsp[-2].string) != nullptr) {
        create_table.storage_format = (yyvsp[-2].string);
        free((yyvsp[-2].string));
      }

      create_table.use_sub_select = true;
      create_table.sub_select = (yyvsp[0].sql_node);
    }
#line 2211 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 449 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
      if ((yyvsp[-1].string) != nullptr) {
        create_table.storage_format = (yyvsp[-1].string);
        free((yyvsp[-1].string));
      }

      create_table.use_sub_select = true;
      create_table.sub_select = (yyvsp[0].sql_node);
    }
#line 2239 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID storage_format AS select_stmt  */
#line 473 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-3].string);
      free((yyvsp[-3].string));

      if ((yyvsp[-2].string) != nullptr) {
        create_table.storage_format = (yyvsp[-2].string);
        free((yyvsp[-2].string));
      }

      create_table.use_sub_select = true;
      create_table.sub_select = (yyvsp[0].sql_node);
    }
#line 2258 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID storage_format select_stmt  */
#line 488 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));

      if ((yyvsp[-1].string) != nullptr) {
        create_table.storage_format = (yyvsp[-1].string);
        free((yyvsp[-1].string));
      }

      create_table.use_sub_select = true;
      create_table.sub_select = (yyvsp[0].sql_node);
    }
#line 2277 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: %empty  */
#line 505 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 43: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 509 "yacc_sql.y"
=======
#line 2156 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 424 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2164 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 428 "yacc_sql.y"
>>>>>>> text
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
<<<<<<< HEAD
#line 2299 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 522 "yacc_sql.y"
=======
#line 2178 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 441 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->can_be_null = (yyvsp[0].boolean);

      if((yyval.attr_info)->type == AttrType::VECTORS){
        (yyval.attr_info)->length = (yyvsp[-2].number) * 4;
      }

      if((yyval.attr_info)->type == AttrType::TEXT){
        (yyval.attr_info)->length = 40; //  页号 + 长度
      }

      free((yyvsp[-5].string));
    }
<<<<<<< HEAD
#line 2317 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type null_def  */
#line 536 "yacc_sql.y"
=======
#line 2200 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type null_def  */
#line 459 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->can_be_null = (yyvsp[0].boolean);

      if((yyval.attr_info)->type == AttrType::TEXT){
        (yyval.attr_info)->length = 40; //  页号 + 长度
      }
      free((yyvsp[-2].string));
    }
<<<<<<< HEAD
#line 2330 "yacc_sql.cpp"
    break;

  case 46: /* null_def: %empty  */
#line 546 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2338 "yacc_sql.cpp"
    break;

  case 47: /* null_def: NULLABLE  */
#line 549 "yacc_sql.y"
               {
      (yyval.boolean) = true;
    }
#line 2346 "yacc_sql.cpp"
    break;

  case 48: /* null_def: UNNULLABLE  */
#line 552 "yacc_sql.y"
                 {
      (yyval.boolean) = false;
    }
#line 2354 "yacc_sql.cpp"
    break;

  case 49: /* number: NUMBER  */
#line 556 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2360 "yacc_sql.cpp"
    break;

  case 50: /* type: INT_T  */
#line 559 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2366 "yacc_sql.cpp"
    break;

  case 51: /* type: STRING_T  */
#line 560 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2372 "yacc_sql.cpp"
    break;

  case 52: /* type: FLOAT_T  */
#line 561 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2378 "yacc_sql.cpp"
    break;

  case 53: /* type: DATE_T  */
#line 562 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATE); }
#line 2384 "yacc_sql.cpp"
    break;

  case 54: /* type: VECTOR_T  */
#line 563 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2390 "yacc_sql.cpp"
    break;

  case 55: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 567 "yacc_sql.y"
=======
#line 2217 "yacc_sql.cpp"
    break;

  case 42: /* null_def: %empty  */
#line 473 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2225 "yacc_sql.cpp"
    break;

  case 43: /* null_def: NULLABLE  */
#line 476 "yacc_sql.y"
               {
      (yyval.boolean) = true;
    }
#line 2233 "yacc_sql.cpp"
    break;

  case 44: /* null_def: UNNULLABLE  */
#line 479 "yacc_sql.y"
                 {
      (yyval.boolean) = false;
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 483 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2247 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 486 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2253 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 487 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2259 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 488 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2265 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 489 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATE); }
#line 2271 "yacc_sql.cpp"
    break;

  case 50: /* type: VECTOR_T  */
#line 490 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2277 "yacc_sql.cpp"
    break;

  case 51: /* type: TEXT_T  */
#line 491 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXT); }
#line 2283 "yacc_sql.cpp"
    break;

  case 52: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 495 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse insert_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
<<<<<<< HEAD
#line 2408 "yacc_sql.cpp"
    break;

  case 56: /* value_list: %empty  */
#line 584 "yacc_sql.y"
=======
#line 2301 "yacc_sql.cpp"
    break;

  case 53: /* value_list: %empty  */
#line 512 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse value_list");
      (yyval.value_list) = nullptr;
    }
<<<<<<< HEAD
#line 2417 "yacc_sql.cpp"
    break;

  case 57: /* value_list: COMMA value value_list  */
#line 588 "yacc_sql.y"
=======
#line 2310 "yacc_sql.cpp"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 516 "yacc_sql.y"
>>>>>>> text
                              { 
      LOG_DEBUG("parse value_list");
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
<<<<<<< HEAD
#line 2432 "yacc_sql.cpp"
    break;

  case 58: /* value: NULLABLE  */
#line 600 "yacc_sql.y"
=======
#line 2325 "yacc_sql.cpp"
    break;

  case 55: /* value: NULLABLE  */
#line 528 "yacc_sql.y"
>>>>>>> text
             {
      (yyval.value) = new Value(string("ckk is stupid!"), 114514);
      (yyloc) = (yylsp[0]);
    }
<<<<<<< HEAD
#line 2441 "yacc_sql.cpp"
    break;

  case 59: /* value: NUMBER  */
#line 604 "yacc_sql.y"
=======
#line 2334 "yacc_sql.cpp"
    break;

  case 56: /* value: NUMBER  */
#line 532 "yacc_sql.y"
>>>>>>> text
            {
      LOG_DEBUG("NUMBER: ", (yyvsp[0].number));
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
<<<<<<< HEAD
#line 2451 "yacc_sql.cpp"
    break;

  case 60: /* value: FLOAT  */
#line 609 "yacc_sql.y"
=======
#line 2344 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 537 "yacc_sql.y"
>>>>>>> text
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
<<<<<<< HEAD
#line 2460 "yacc_sql.cpp"
    break;

  case 61: /* value: '-' NUMBER  */
#line 613 "yacc_sql.y"
=======
#line 2353 "yacc_sql.cpp"
    break;

  case 58: /* value: '-' NUMBER  */
#line 541 "yacc_sql.y"
>>>>>>> text
                {
      LOG_DEBUG("- %d", (yyvsp[0].number));
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
<<<<<<< HEAD
#line 2470 "yacc_sql.cpp"
    break;

  case 62: /* value: '-' FLOAT  */
#line 618 "yacc_sql.y"
=======
#line 2363 "yacc_sql.cpp"
    break;

  case 59: /* value: '-' FLOAT  */
#line 546 "yacc_sql.y"
>>>>>>> text
               {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
<<<<<<< HEAD
#line 2479 "yacc_sql.cpp"
    break;

  case 63: /* value: DATE_STR  */
#line 622 "yacc_sql.y"
=======
#line 2372 "yacc_sql.cpp"
    break;

  case 60: /* value: DATE_STR  */
#line 550 "yacc_sql.y"
>>>>>>> text
              {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);  // 去掉首尾的引号
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);    //sscanf会自动转换字符串中的数字，不用显式stoi
      int date_num = year * 10000 + month * 100 + day;
      (yyval.value) = new Value(date_num, true);
      free(tmp);
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 2493 "yacc_sql.cpp"
    break;

  case 64: /* value: SSS  */
#line 631 "yacc_sql.y"
=======
#line 2386 "yacc_sql.cpp"
    break;

  case 61: /* value: TEXT_STR  */
#line 559 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, strlen(tmp));
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 62: /* value: SSS  */
#line 565 "yacc_sql.y"
>>>>>>> text
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, strlen(tmp));  
      free(tmp);
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 2504 "yacc_sql.cpp"
    break;

  case 65: /* value: LBRACKET value value_list RBRACKET  */
#line 637 "yacc_sql.y"
=======
#line 2408 "yacc_sql.cpp"
    break;

  case 63: /* value: LBRACKET value value_list RBRACKET  */
#line 571 "yacc_sql.y"
>>>>>>> text
                                         {
      std::vector<float> nums;
      nums.emplace_back((yyvsp[-2].value)->get_float());
      if((yyvsp[-1].value_list) != nullptr) {
        std::reverse((yyvsp[-1].value_list)->begin(), (yyvsp[-1].value_list)->end());
        for (Value value : *(yyvsp[-1].value_list)) {
          nums.emplace_back(value.get_float());
        }
      }
      (yyval.value) = new Value(nums);
    }
<<<<<<< HEAD
#line 2520 "yacc_sql.cpp"
    break;

  case 66: /* storage_format: %empty  */
#line 651 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2528 "yacc_sql.cpp"
    break;

  case 67: /* storage_format: STORAGE FORMAT EQ ID  */
#line 655 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 68: /* delete_stmt: DELETE FROM ID where  */
#line 662 "yacc_sql.y"
=======
#line 2424 "yacc_sql.cpp"
    break;

  case 64: /* storage_format: %empty  */
#line 585 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2432 "yacc_sql.cpp"
    break;

  case 65: /* storage_format: STORAGE FORMAT EQ ID  */
#line 589 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2440 "yacc_sql.cpp"
    break;

  case 66: /* delete_stmt: DELETE FROM ID where  */
#line 596 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse delete_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 2551 "yacc_sql.cpp"
    break;

  case 69: /* update_stmt: UPDATE ID SET update_target update_target_list where  */
#line 675 "yacc_sql.y"
=======
#line 2455 "yacc_sql.cpp"
    break;

  case 67: /* update_stmt: UPDATE ID SET update_target update_target_list where  */
#line 609 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }

      if((yyvsp[-1].update_target_list) != nullptr)
        (yyval.sql_node)->update.update_targets.swap(*(yyvsp[-1].update_target_list));
      (yyval.sql_node)->update.update_targets.emplace_back(*(yyvsp[-2].update_target));
      std::reverse((yyval.sql_node)->update.update_targets.begin(), (yyval.sql_node)->update.update_targets.end());
    }
<<<<<<< HEAD
#line 2570 "yacc_sql.cpp"
    break;

  case 70: /* update_target: ID EQ value  */
#line 693 "yacc_sql.y"
=======
#line 2474 "yacc_sql.cpp"
    break;

  case 68: /* update_target: ID EQ value  */
#line 627 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->value = *(yyvsp[0].value);
      (yyval.update_target)->is_value = true;

      delete (yyvsp[0].value);
    }
<<<<<<< HEAD
#line 2583 "yacc_sql.cpp"
    break;

  case 71: /* update_target: ID EQ sub_select_stmt  */
#line 702 "yacc_sql.y"
=======
#line 2487 "yacc_sql.cpp"
    break;

  case 69: /* update_target: ID EQ sub_select_stmt  */
#line 636 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->sub_select = (yyvsp[0].sql_node);
      (yyval.update_target)->is_value = false;
    }
<<<<<<< HEAD
#line 2594 "yacc_sql.cpp"
    break;

  case 72: /* update_target_list: %empty  */
#line 712 "yacc_sql.y"
    {
      (yyval.update_target_list) = nullptr;
    }
#line 2602 "yacc_sql.cpp"
    break;

  case 73: /* update_target_list: COMMA update_target update_target_list  */
#line 716 "yacc_sql.y"
=======
#line 2498 "yacc_sql.cpp"
    break;

  case 70: /* update_target_list: %empty  */
#line 646 "yacc_sql.y"
    {
      (yyval.update_target_list) = nullptr;
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 71: /* update_target_list: COMMA update_target update_target_list  */
#line 650 "yacc_sql.y"
>>>>>>> text
    {
      if((yyvsp[0].update_target_list) == nullptr)
        (yyval.update_target_list) = new std::vector<UpdateTarget>;
      else (yyval.update_target_list) = (yyvsp[0].update_target_list);
      (yyval.update_target_list)->emplace_back(*(yyvsp[-1].update_target));
    }
<<<<<<< HEAD
#line 2613 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT expression_list  */
#line 726 "yacc_sql.y"
=======
#line 2517 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT expression_list  */
#line 660 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->selection.expressions.swap(*(yyvsp[0].expression_list));
    }
<<<<<<< HEAD
#line 2622 "yacc_sql.cpp"
    break;

  case 75: /* select_stmt: SELECT expression_list FROM relation rel_list join_list where group_by having order_by_list  */
#line 731 "yacc_sql.y"
=======
#line 2526 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT expression_list FROM relation rel_list join_list where group_by order_by_list  */
#line 665 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }

      if ((yyvsp[-5].expression_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].expression_list));
        delete (yyvsp[-5].expression_list);
      }
      (yyval.sql_node)->selection.relations.emplace_back((yyvsp[-6].expression));

      if ((yyvsp[-4].expression_list) != nullptr) {
        (yyval.sql_node)->selection.join.swap(*(yyvsp[-4].expression_list));
        delete (yyvsp[-4].expression_list);
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.having_conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
<<<<<<< HEAD
#line 2665 "yacc_sql.cpp"
    break;

  case 76: /* sub_select_stmt: LBRACE select_stmt RBRACE  */
#line 772 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 77: /* calc_stmt: CALC expression_list  */
#line 778 "yacc_sql.y"
=======
#line 2564 "yacc_sql.cpp"
    break;

  case 74: /* sub_select_stmt: LBRACE select_stmt RBRACE  */
#line 701 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 75: /* calc_stmt: CALC expression_list  */
#line 707 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
<<<<<<< HEAD
#line 2683 "yacc_sql.cpp"
    break;

  case 78: /* expression_list: expression  */
#line 787 "yacc_sql.y"
=======
#line 2582 "yacc_sql.cpp"
    break;

  case 76: /* expression_list: expression  */
#line 716 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
<<<<<<< HEAD
#line 2692 "yacc_sql.cpp"
    break;

  case 79: /* expression_list: expression COMMA expression_list  */
#line 792 "yacc_sql.y"
=======
#line 2591 "yacc_sql.cpp"
    break;

  case 77: /* expression_list: expression COMMA expression_list  */
#line 721 "yacc_sql.y"
>>>>>>> text
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
<<<<<<< HEAD
#line 2705 "yacc_sql.cpp"
    break;

  case 80: /* expression: ID  */
#line 802 "yacc_sql.y"
=======
#line 2604 "yacc_sql.cpp"
    break;

  case 78: /* expression: ID  */
#line 731 "yacc_sql.y"
>>>>>>> text
       {
      LOG_DEBUG("ID %s", (yyvsp[0].string));
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 2716 "yacc_sql.cpp"
    break;

  case 81: /* expression: ID DOT ID  */
#line 808 "yacc_sql.y"
=======
#line 2615 "yacc_sql.cpp"
    break;

  case 79: /* expression: ID DOT ID  */
#line 737 "yacc_sql.y"
>>>>>>> text
                {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
<<<<<<< HEAD
#line 2726 "yacc_sql.cpp"
    break;

  case 82: /* expression: ID ID  */
#line 813 "yacc_sql.y"
=======
#line 2625 "yacc_sql.cpp"
    break;

  case 80: /* expression: ID ID  */
#line 742 "yacc_sql.y"
>>>>>>> text
            {
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[-1].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 2736 "yacc_sql.cpp"
    break;

  case 83: /* expression: ID AS ID  */
#line 818 "yacc_sql.y"
=======
#line 2635 "yacc_sql.cpp"
    break;

  case 81: /* expression: ID AS ID  */
#line 747 "yacc_sql.y"
>>>>>>> text
               {
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
<<<<<<< HEAD
#line 2746 "yacc_sql.cpp"
    break;

  case 84: /* expression: ID DOT ID ID  */
#line 823 "yacc_sql.y"
=======
#line 2645 "yacc_sql.cpp"
    break;

  case 82: /* expression: ID DOT ID ID  */
#line 752 "yacc_sql.y"
>>>>>>> text
                   {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-3].string));
    }
<<<<<<< HEAD
#line 2756 "yacc_sql.cpp"
    break;

  case 85: /* expression: ID DOT ID AS ID  */
#line 828 "yacc_sql.y"
=======
#line 2655 "yacc_sql.cpp"
    break;

  case 83: /* expression: ID DOT ID AS ID  */
#line 757 "yacc_sql.y"
>>>>>>> text
                      {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-4].string));
    }
<<<<<<< HEAD
#line 2766 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '+' expression  */
#line 833 "yacc_sql.y"
=======
#line 2665 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '+' expression  */
#line 762 "yacc_sql.y"
>>>>>>> text
                                {
      LOG_DEBUG("add");
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
<<<<<<< HEAD
#line 2775 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '-' expression  */
#line 837 "yacc_sql.y"
=======
#line 2674 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '-' expression  */
#line 766 "yacc_sql.y"
>>>>>>> text
                                {
      LOG_DEBUG("sub");
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
<<<<<<< HEAD
#line 2784 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '*' expression  */
#line 841 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2792 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '/' expression  */
#line 844 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2800 "yacc_sql.cpp"
    break;

  case 90: /* expression: LBRACE expression RBRACE  */
#line 847 "yacc_sql.y"
=======
#line 2683 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '*' expression  */
#line 770 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2691 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '/' expression  */
#line 773 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2699 "yacc_sql.cpp"
    break;

  case 88: /* expression: LBRACE expression RBRACE  */
#line 776 "yacc_sql.y"
>>>>>>> text
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
<<<<<<< HEAD
#line 2809 "yacc_sql.cpp"
    break;

  case 91: /* expression: '-' expression  */
#line 851 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 92: /* expression: value  */
#line 854 "yacc_sql.y"
=======
#line 2708 "yacc_sql.cpp"
    break;

  case 89: /* expression: '-' expression  */
#line 780 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 90: /* expression: value  */
#line 783 "yacc_sql.y"
>>>>>>> text
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
<<<<<<< HEAD
#line 2827 "yacc_sql.cpp"
    break;

  case 93: /* expression: '*'  */
#line 859 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2835 "yacc_sql.cpp"
    break;

  case 94: /* expression: MAX LBRACE RBRACE  */
#line 862 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2843 "yacc_sql.cpp"
    break;

  case 95: /* expression: MIN LBRACE RBRACE  */
#line 865 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2851 "yacc_sql.cpp"
    break;

  case 96: /* expression: AVG LBRACE RBRACE  */
#line 868 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2859 "yacc_sql.cpp"
    break;

  case 97: /* expression: SUM LBRACE RBRACE  */
#line 871 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2867 "yacc_sql.cpp"
    break;

  case 98: /* expression: COUNT LBRACE RBRACE  */
#line 874 "yacc_sql.y"
                          {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2875 "yacc_sql.cpp"
    break;

  case 99: /* expression: MAX LBRACE expression_list RBRACE  */
#line 877 "yacc_sql.y"
=======
#line 2726 "yacc_sql.cpp"
    break;

  case 91: /* expression: '*'  */
#line 788 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 92: /* expression: MAX LBRACE RBRACE  */
#line 791 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 93: /* expression: MIN LBRACE RBRACE  */
#line 794 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2750 "yacc_sql.cpp"
    break;

  case 94: /* expression: AVG LBRACE RBRACE  */
#line 797 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 95: /* expression: SUM LBRACE RBRACE  */
#line 800 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 96: /* expression: COUNT LBRACE RBRACE  */
#line 803 "yacc_sql.y"
                          {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 97: /* expression: MAX LBRACE expression_list RBRACE  */
#line 806 "yacc_sql.y"
>>>>>>> text
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("MAX", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
<<<<<<< HEAD
#line 2887 "yacc_sql.cpp"
    break;

  case 100: /* expression: MIN LBRACE expression_list RBRACE  */
#line 884 "yacc_sql.y"
=======
#line 2786 "yacc_sql.cpp"
    break;

  case 98: /* expression: MIN LBRACE expression_list RBRACE  */
#line 813 "yacc_sql.y"
>>>>>>> text
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("MIN", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
<<<<<<< HEAD
#line 2899 "yacc_sql.cpp"
    break;

  case 101: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 891 "yacc_sql.y"
=======
#line 2798 "yacc_sql.cpp"
    break;

  case 99: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 820 "yacc_sql.y"
>>>>>>> text
                                          {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("COUNT", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
<<<<<<< HEAD
#line 2911 "yacc_sql.cpp"
    break;

  case 102: /* expression: AVG LBRACE expression_list RBRACE  */
#line 898 "yacc_sql.y"
=======
#line 2810 "yacc_sql.cpp"
    break;

  case 100: /* expression: AVG LBRACE expression_list RBRACE  */
#line 827 "yacc_sql.y"
>>>>>>> text
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("AVG", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
<<<<<<< HEAD
#line 2923 "yacc_sql.cpp"
    break;

  case 103: /* expression: SUM LBRACE expression_list RBRACE  */
#line 905 "yacc_sql.y"
=======
#line 2822 "yacc_sql.cpp"
    break;

  case 101: /* expression: SUM LBRACE expression_list RBRACE  */
#line 834 "yacc_sql.y"
>>>>>>> text
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("SUM", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
<<<<<<< HEAD
#line 2935 "yacc_sql.cpp"
    break;

  case 104: /* expression: LENGTH LBRACE expression RBRACE  */
#line 912 "yacc_sql.y"
=======
#line 2834 "yacc_sql.cpp"
    break;

  case 102: /* expression: LENGTH LBRACE expression RBRACE  */
#line 841 "yacc_sql.y"
>>>>>>> text
                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, nullptr, nullptr, (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
<<<<<<< HEAD
#line 2944 "yacc_sql.cpp"
    break;

  case 105: /* expression: ROUND LBRACE expression COMMA expression RBRACE  */
#line 916 "yacc_sql.y"
=======
#line 2843 "yacc_sql.cpp"
    break;

  case 103: /* expression: ROUND LBRACE expression COMMA expression RBRACE  */
#line 845 "yacc_sql.y"
>>>>>>> text
                                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, (yyvsp[-1].expression), nullptr, (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
<<<<<<< HEAD
#line 2953 "yacc_sql.cpp"
    break;

  case 106: /* expression: DATE_FORMAT LBRACE expression COMMA expression RBRACE  */
#line 920 "yacc_sql.y"
=======
#line 2852 "yacc_sql.cpp"
    break;

  case 104: /* expression: DATE_FORMAT LBRACE expression COMMA expression RBRACE  */
#line 849 "yacc_sql.y"
>>>>>>> text
                                                            {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, nullptr, (yyvsp[-1].expression), (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
<<<<<<< HEAD
#line 2962 "yacc_sql.cpp"
    break;

  case 107: /* expression: VEC_INNER_PRODUCT_FUNC LBRACE expression COMMA expression RBRACE  */
#line 924 "yacc_sql.y"
=======
#line 2861 "yacc_sql.cpp"
    break;

  case 105: /* expression: VEC_INNER_PRODUCT_FUNC LBRACE expression COMMA expression RBRACE  */
#line 853 "yacc_sql.y"
>>>>>>> text
                                                                       {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
<<<<<<< HEAD
#line 2971 "yacc_sql.cpp"
    break;

  case 108: /* expression: VEC_COSINE_DISTANCE_FUNC LBRACE expression COMMA expression RBRACE  */
#line 928 "yacc_sql.y"
=======
#line 2870 "yacc_sql.cpp"
    break;

  case 106: /* expression: VEC_COSINE_DISTANCE_FUNC LBRACE expression COMMA expression RBRACE  */
#line 857 "yacc_sql.y"
>>>>>>> text
                                                                         {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
<<<<<<< HEAD
#line 2980 "yacc_sql.cpp"
    break;

  case 109: /* expression: VEC_L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 932 "yacc_sql.y"
=======
#line 2879 "yacc_sql.cpp"
    break;

  case 107: /* expression: VEC_L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 861 "yacc_sql.y"
>>>>>>> text
                                                                {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
<<<<<<< HEAD
#line 2989 "yacc_sql.cpp"
    break;

  case 110: /* relation: ID  */
#line 939 "yacc_sql.y"
=======
#line 2888 "yacc_sql.cpp"
    break;

  case 108: /* relation: ID  */
#line 868 "yacc_sql.y"
>>>>>>> text
       {
      (yyval.expression) = new UnboundTableExpr((yyvsp[0].string), string());
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 2999 "yacc_sql.cpp"
    break;

  case 111: /* relation: ID ID  */
#line 944 "yacc_sql.y"
=======
#line 2898 "yacc_sql.cpp"
    break;

  case 109: /* relation: ID ID  */
#line 873 "yacc_sql.y"
>>>>>>> text
            {
      (yyval.expression) = new UnboundTableExpr((yyvsp[-1].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 3010 "yacc_sql.cpp"
    break;

  case 112: /* relation: ID AS ID  */
#line 950 "yacc_sql.y"
=======
#line 2909 "yacc_sql.cpp"
    break;

  case 110: /* relation: ID AS ID  */
#line 879 "yacc_sql.y"
>>>>>>> text
               {
      (yyval.expression) = new UnboundTableExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
<<<<<<< HEAD
#line 3021 "yacc_sql.cpp"
    break;

  case 113: /* rel_list: %empty  */
#line 959 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 114: /* rel_list: COMMA relation rel_list  */
#line 962 "yacc_sql.y"
=======
#line 2920 "yacc_sql.cpp"
    break;

  case 111: /* rel_list: %empty  */
#line 888 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 112: /* rel_list: COMMA relation rel_list  */
#line 891 "yacc_sql.y"
>>>>>>> text
                              {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
<<<<<<< HEAD
#line 3043 "yacc_sql.cpp"
    break;

  case 115: /* where: %empty  */
#line 975 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 116: /* where: WHERE condition_list  */
#line 978 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 117: /* having: %empty  */
#line 985 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3067 "yacc_sql.cpp"
    break;

  case 118: /* having: HAVING condition_list  */
#line 988 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 119: /* join_list: %empty  */
#line 994 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3083 "yacc_sql.cpp"
    break;

  case 120: /* join_list: INNER_JOIN relation ON condition_list join_list  */
#line 997 "yacc_sql.y"
=======
#line 2942 "yacc_sql.cpp"
    break;

  case 113: /* where: %empty  */
#line 904 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 114: /* where: WHERE condition_list  */
#line 907 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 115: /* join_list: %empty  */
#line 914 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 116: /* join_list: INNER_JOIN relation ON condition_list join_list  */
#line 917 "yacc_sql.y"
>>>>>>> text
                                                      {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(new JoinTableExpr(*(yyvsp[-1].condition_list), (yyvsp[-3].expression)));
    }
<<<<<<< HEAD
#line 3096 "yacc_sql.cpp"
    break;

  case 121: /* order_by_list: %empty  */
#line 1009 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3104 "yacc_sql.cpp"
    break;

  case 122: /* order_by_list: ORDER_BY expression order_by_flag order_by  */
#line 1013 "yacc_sql.y"
=======
#line 2979 "yacc_sql.cpp"
    break;

  case 117: /* order_by_list: %empty  */
#line 929 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2987 "yacc_sql.cpp"
    break;

  case 118: /* order_by_list: ORDER_BY expression order_by_flag order_by  */
#line 933 "yacc_sql.y"
>>>>>>> text
    {
       if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
<<<<<<< HEAD
#line 3117 "yacc_sql.cpp"
    break;

  case 123: /* order_by: %empty  */
#line 1025 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3125 "yacc_sql.cpp"
    break;

  case 124: /* order_by: COMMA expression order_by_flag order_by  */
#line 1029 "yacc_sql.y"
=======
#line 3000 "yacc_sql.cpp"
    break;

  case 119: /* order_by: %empty  */
#line 945 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3008 "yacc_sql.cpp"
    break;

  case 120: /* order_by: COMMA expression order_by_flag order_by  */
#line 949 "yacc_sql.y"
>>>>>>> text
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
<<<<<<< HEAD
#line 3138 "yacc_sql.cpp"
    break;

  case 125: /* order_by_flag: %empty  */
#line 1041 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3146 "yacc_sql.cpp"
    break;

  case 126: /* order_by_flag: ASC  */
#line 1045 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3154 "yacc_sql.cpp"
    break;

  case 127: /* order_by_flag: DESC  */
#line 1049 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 3162 "yacc_sql.cpp"
    break;

  case 128: /* condition_list: %empty  */
#line 1056 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3170 "yacc_sql.cpp"
    break;

  case 129: /* condition_list: condition  */
#line 1059 "yacc_sql.y"
=======
#line 3021 "yacc_sql.cpp"
    break;

  case 121: /* order_by_flag: %empty  */
#line 961 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 122: /* order_by_flag: ASC  */
#line 965 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3037 "yacc_sql.cpp"
    break;

  case 123: /* order_by_flag: DESC  */
#line 969 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 3045 "yacc_sql.cpp"
    break;

  case 124: /* condition_list: %empty  */
#line 976 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3053 "yacc_sql.cpp"
    break;

  case 125: /* condition_list: condition  */
#line 979 "yacc_sql.y"
>>>>>>> text
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
<<<<<<< HEAD
#line 3180 "yacc_sql.cpp"
    break;

  case 130: /* condition_list: condition AND condition_list  */
#line 1064 "yacc_sql.y"
=======
#line 3063 "yacc_sql.cpp"
    break;

  case 126: /* condition_list: condition AND condition_list  */
#line 984 "yacc_sql.y"
>>>>>>> text
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
<<<<<<< HEAD
#line 3190 "yacc_sql.cpp"
    break;

  case 131: /* condition: expression comp_op  */
#line 1072 "yacc_sql.y"
=======
#line 3073 "yacc_sql.cpp"
    break;

  case 127: /* condition: expression comp_op  */
#line 992 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[0].comp);
      (yyval.condition)->left_expression = (yyvsp[-1].expression);
      (yyval.condition)->right_expression = new ValueExpr(Value(114514));
    }
<<<<<<< HEAD
#line 3203 "yacc_sql.cpp"
    break;

  case 132: /* condition: expression comp_op sub_select_stmt  */
#line 1081 "yacc_sql.y"
=======
#line 3086 "yacc_sql.cpp"
    break;

  case 128: /* condition: expression comp_op sub_select_stmt  */
#line 1001 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->right_expression = nullptr;
    }
<<<<<<< HEAD
#line 3217 "yacc_sql.cpp"
    break;

  case 133: /* condition: sub_select_stmt comp_op sub_select_stmt  */
#line 1091 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = true;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_sub_query = (yyvsp[-2].sql_node);
      (yyval.condition)->left_expression = nullptr;
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->right_expression = nullptr;
    }
#line 3232 "yacc_sql.cpp"
    break;

  case 134: /* condition: sub_select_stmt comp_op expression  */
#line 1102 "yacc_sql.y"
=======
#line 3100 "yacc_sql.cpp"
    break;

  case 129: /* condition: sub_select_stmt comp_op expression  */
#line 1012 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = true;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_sub_query = (yyvsp[-2].sql_node);
      (yyval.condition)->left_expression = nullptr;
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
<<<<<<< HEAD
#line 3246 "yacc_sql.cpp"
    break;

  case 135: /* condition: expression comp_op expression  */
#line 1112 "yacc_sql.y"
=======
#line 3114 "yacc_sql.cpp"
    break;

  case 130: /* condition: expression comp_op expression  */
#line 1023 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
<<<<<<< HEAD
#line 3259 "yacc_sql.cpp"
    break;

  case 136: /* condition: comp_op sub_select_stmt  */
#line 1121 "yacc_sql.y"
=======
#line 3127 "yacc_sql.cpp"
    break;

  case 131: /* condition: comp_op sub_select_stmt  */
#line 1032 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = new ValueExpr(Value(114514));
    }
<<<<<<< HEAD
#line 3272 "yacc_sql.cpp"
    break;

  case 137: /* condition: expression comp_op LBRACE value value_list RBRACE  */
#line 1130 "yacc_sql.y"
=======
#line 3140 "yacc_sql.cpp"
    break;

  case 132: /* condition: expression comp_op LBRACE value value_list RBRACE  */
#line 1041 "yacc_sql.y"
>>>>>>> text
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-4].comp);
      (yyval.condition)->left_expression = (yyvsp[-5].expression);
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.condition)->right_expression = new ValueListExpr(*(yyvsp[-1].value_list));
    }
<<<<<<< HEAD
#line 3286 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: EQ  */
#line 1142 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3292 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: LT  */
#line 1143 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3298 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: GT  */
#line 1144 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3304 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: LE  */
#line 1145 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3310 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: GE  */
#line 1146 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3316 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: NE  */
#line 1147 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3322 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: IS_NULL  */
#line 1148 "yacc_sql.y"
              { (yyval.comp) = XXX_IS_NULL; }
#line 3328 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: IS_NOT_NULL  */
#line 1149 "yacc_sql.y"
                  { (yyval.comp) = XXX_IS_NOT_NULL; }
#line 3334 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: NOT_LIKE  */
#line 1150 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_XXX; }
#line 3340 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: LIKE  */
#line 1151 "yacc_sql.y"
           { (yyval.comp) = LIKE_XXX; }
#line 3346 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: NOT_IN  */
#line 1152 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_XXX; }
#line 3352 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: IN  */
#line 1153 "yacc_sql.y"
         { (yyval.comp) = IN_XXX; }
#line 3358 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: NOT_EXISTS  */
#line 1154 "yacc_sql.y"
                 { (yyval.comp) = XXX_NOT_EXISTS; }
#line 3364 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: EXISTS  */
#line 1155 "yacc_sql.y"
             { (yyval.comp) = XXX_EXISTS; }
#line 3370 "yacc_sql.cpp"
    break;

  case 152: /* group_by: %empty  */
#line 1160 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3378 "yacc_sql.cpp"
    break;

  case 153: /* group_by: GROUP BY expression group_by_unit  */
#line 1163 "yacc_sql.y"
                                        {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3392 "yacc_sql.cpp"
    break;

  case 154: /* group_by_unit: %empty  */
#line 1176 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3400 "yacc_sql.cpp"
    break;

  case 155: /* group_by_unit: COMMA expression group_by_unit  */
#line 1180 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3414 "yacc_sql.cpp"
    break;

  case 156: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1193 "yacc_sql.y"
=======
#line 3154 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: EQ  */
#line 1053 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3160 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: LT  */
#line 1054 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3166 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: GT  */
#line 1055 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3172 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: LE  */
#line 1056 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3178 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: GE  */
#line 1057 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3184 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: NE  */
#line 1058 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3190 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: IS_NULL  */
#line 1059 "yacc_sql.y"
              { (yyval.comp) = XXX_IS_NULL; }
#line 3196 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: IS_NOT_NULL  */
#line 1060 "yacc_sql.y"
                  { (yyval.comp) = XXX_IS_NOT_NULL; }
#line 3202 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: NOT_LIKE  */
#line 1061 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_XXX; }
#line 3208 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: LIKE  */
#line 1062 "yacc_sql.y"
           { (yyval.comp) = LIKE_XXX; }
#line 3214 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: NOT_IN  */
#line 1063 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_XXX; }
#line 3220 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: IN  */
#line 1064 "yacc_sql.y"
         { (yyval.comp) = IN_XXX; }
#line 3226 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: NOT_EXISTS  */
#line 1065 "yacc_sql.y"
                 { (yyval.comp) = XXX_NOT_EXISTS; }
#line 3232 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: EXISTS  */
#line 1066 "yacc_sql.y"
             { (yyval.comp) = XXX_EXISTS; }
#line 3238 "yacc_sql.cpp"
    break;

  case 147: /* group_by: %empty  */
#line 1072 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3246 "yacc_sql.cpp"
    break;

  case 148: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1078 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse load_data_stmt");
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
<<<<<<< HEAD
#line 3429 "yacc_sql.cpp"
    break;

  case 157: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1207 "yacc_sql.y"
=======
#line 3261 "yacc_sql.cpp"
    break;

  case 149: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1092 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse explain_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
<<<<<<< HEAD
#line 3439 "yacc_sql.cpp"
    break;

  case 158: /* set_variable_stmt: SET ID EQ value  */
#line 1216 "yacc_sql.y"
=======
#line 3271 "yacc_sql.cpp"
    break;

  case 150: /* set_variable_stmt: SET ID EQ value  */
#line 1101 "yacc_sql.y"
>>>>>>> text
    {
      LOG_DEBUG("parse set_variable_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
<<<<<<< HEAD
#line 3452 "yacc_sql.cpp"
    break;


#line 3456 "yacc_sql.cpp"
=======
#line 3284 "yacc_sql.cpp"
    break;


#line 3288 "yacc_sql.cpp"
>>>>>>> text

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

<<<<<<< HEAD
#line 1229 "yacc_sql.y"
=======
#line 1114 "yacc_sql.y"
>>>>>>> text

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
