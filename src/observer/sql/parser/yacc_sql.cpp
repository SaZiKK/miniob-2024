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
  YYSYMBOL_TEXT_T = 33,                    /* TEXT_T  */
  YYSYMBOL_HELP = 34,                      /* HELP  */
  YYSYMBOL_EXIT = 35,                      /* EXIT  */
  YYSYMBOL_DOT = 36,                       /* DOT  */
  YYSYMBOL_INTO = 37,                      /* INTO  */
  YYSYMBOL_VALUES = 38,                    /* VALUES  */
  YYSYMBOL_FROM = 39,                      /* FROM  */
  YYSYMBOL_WHERE = 40,                     /* WHERE  */
  YYSYMBOL_AND = 41,                       /* AND  */
  YYSYMBOL_OR = 42,                        /* OR  */
  YYSYMBOL_SET = 43,                       /* SET  */
  YYSYMBOL_ON = 44,                        /* ON  */
  YYSYMBOL_LOAD = 45,                      /* LOAD  */
  YYSYMBOL_DATA = 46,                      /* DATA  */
  YYSYMBOL_INFILE = 47,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 48,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 49,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 50,                    /* FORMAT  */
  YYSYMBOL_MAX = 51,                       /* MAX  */
  YYSYMBOL_MIN = 52,                       /* MIN  */
  YYSYMBOL_AVG = 53,                       /* AVG  */
  YYSYMBOL_SUM = 54,                       /* SUM  */
  YYSYMBOL_COUNT = 55,                     /* COUNT  */
  YYSYMBOL_NOT_LIKE = 56,                  /* NOT_LIKE  */
  YYSYMBOL_LIKE = 57,                      /* LIKE  */
  YYSYMBOL_NOT_IN = 58,                    /* NOT_IN  */
  YYSYMBOL_IN = 59,                        /* IN  */
  YYSYMBOL_NOT_EXISTS = 60,                /* NOT_EXISTS  */
  YYSYMBOL_EXISTS = 61,                    /* EXISTS  */
  YYSYMBOL_LENGTH = 62,                    /* LENGTH  */
  YYSYMBOL_ROUND = 63,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 64,               /* DATE_FORMAT  */
  YYSYMBOL_NULLABLE = 65,                  /* NULLABLE  */
  YYSYMBOL_UNNULLABLE = 66,                /* UNNULLABLE  */
  YYSYMBOL_IS_NULL = 67,                   /* IS_NULL  */
  YYSYMBOL_IS_NOT_NULL = 68,               /* IS_NOT_NULL  */
  YYSYMBOL_VEC_L2_DISTANCE = 69,           /* VEC_L2_DISTANCE  */
  YYSYMBOL_VEC_COSINE_DISTANCE = 70,       /* VEC_COSINE_DISTANCE  */
  YYSYMBOL_VEC_INNER_PRODUCT = 71,         /* VEC_INNER_PRODUCT  */
  YYSYMBOL_IVFFLAT = 72,                   /* IVFFLAT  */
  YYSYMBOL_LBRACKET = 73,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 74,                  /* RBRACKET  */
  YYSYMBOL_UNIQUE = 75,                    /* UNIQUE  */
  YYSYMBOL_ORDER_BY = 76,                  /* ORDER_BY  */
  YYSYMBOL_VIEW = 77,                      /* VIEW  */
  YYSYMBOL_WITH = 78,                      /* WITH  */
  YYSYMBOL_DISTANCE = 79,                  /* DISTANCE  */
  YYSYMBOL_TYPE = 80,                      /* TYPE  */
  YYSYMBOL_LISTS = 81,                     /* LISTS  */
  YYSYMBOL_PROBES = 82,                    /* PROBES  */
  YYSYMBOL_LIMIT = 83,                     /* LIMIT  */
  YYSYMBOL_AS = 84,                        /* AS  */
  YYSYMBOL_EQ = 85,                        /* EQ  */
  YYSYMBOL_LT = 86,                        /* LT  */
  YYSYMBOL_GT = 87,                        /* GT  */
  YYSYMBOL_LE = 88,                        /* LE  */
  YYSYMBOL_GE = 89,                        /* GE  */
  YYSYMBOL_NE = 90,                        /* NE  */
  YYSYMBOL_NUMBER = 91,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 92,                     /* FLOAT  */
  YYSYMBOL_ID = 93,                        /* ID  */
  YYSYMBOL_DATE_STR = 94,                  /* DATE_STR  */
  YYSYMBOL_TEXT_STR = 95,                  /* TEXT_STR  */
  YYSYMBOL_SSS = 96,                       /* SSS  */
  YYSYMBOL_HIGHER_THAN_EXPRESSION = 97,    /* HIGHER_THAN_EXPRESSION  */
  YYSYMBOL_98_ = 98,                       /* '+'  */
  YYSYMBOL_99_ = 99,                       /* '-'  */
  YYSYMBOL_100_ = 100,                     /* '*'  */
  YYSYMBOL_101_ = 101,                     /* '/'  */
  YYSYMBOL_UMINUS = 102,                   /* UMINUS  */
  YYSYMBOL_YYACCEPT = 103,                 /* $accept  */
  YYSYMBOL_commands = 104,                 /* commands  */
  YYSYMBOL_command_wrapper = 105,          /* command_wrapper  */
  YYSYMBOL_exit_stmt = 106,                /* exit_stmt  */
  YYSYMBOL_help_stmt = 107,                /* help_stmt  */
  YYSYMBOL_sync_stmt = 108,                /* sync_stmt  */
  YYSYMBOL_begin_stmt = 109,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 110,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 111,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 112,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 113,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 114,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 115,        /* create_index_stmt  */
  YYSYMBOL_create_vec_index_stmt = 116,    /* create_vec_index_stmt  */
  YYSYMBOL_id_list = 117,                  /* id_list  */
  YYSYMBOL_drop_index_stmt = 118,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 119,        /* create_table_stmt  */
  YYSYMBOL_create_view_stmt = 120,         /* create_view_stmt  */
  YYSYMBOL_attr_def_list = 121,            /* attr_def_list  */
  YYSYMBOL_attr_def = 122,                 /* attr_def  */
  YYSYMBOL_null_def = 123,                 /* null_def  */
  YYSYMBOL_type = 124,                     /* type  */
  YYSYMBOL_insert_stmt = 125,              /* insert_stmt  */
  YYSYMBOL_value_list = 126,               /* value_list  */
  YYSYMBOL_number = 127,                   /* number  */
  YYSYMBOL_float = 128,                    /* float  */
  YYSYMBOL_value = 129,                    /* value  */
  YYSYMBOL_storage_format = 130,           /* storage_format  */
  YYSYMBOL_delete_stmt = 131,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 132,              /* update_stmt  */
  YYSYMBOL_update_target = 133,            /* update_target  */
  YYSYMBOL_update_target_list = 134,       /* update_target_list  */
  YYSYMBOL_select_stmt = 135,              /* select_stmt  */
  YYSYMBOL_sub_select_stmt = 136,          /* sub_select_stmt  */
  YYSYMBOL_calc_stmt = 137,                /* calc_stmt  */
  YYSYMBOL_expression_list = 138,          /* expression_list  */
  YYSYMBOL_limited = 139,                  /* limited  */
  YYSYMBOL_aggre_type = 140,               /* aggre_type  */
  YYSYMBOL_vec_func_type = 141,            /* vec_func_type  */
  YYSYMBOL_expression = 142,               /* expression  */
  YYSYMBOL_query_unit = 143,               /* query_unit  */
  YYSYMBOL_query_list = 144,               /* query_list  */
  YYSYMBOL_relation = 145,                 /* relation  */
  YYSYMBOL_rel_list = 146,                 /* rel_list  */
  YYSYMBOL_where = 147,                    /* where  */
  YYSYMBOL_having = 148,                   /* having  */
  YYSYMBOL_join_list = 149,                /* join_list  */
  YYSYMBOL_order_by_list = 150,            /* order_by_list  */
  YYSYMBOL_order_by = 151,                 /* order_by  */
  YYSYMBOL_order_by_flag = 152,            /* order_by_flag  */
  YYSYMBOL_condition_list = 153,           /* condition_list  */
  YYSYMBOL_condition = 154,                /* condition  */
  YYSYMBOL_comp_op = 155,                  /* comp_op  */
  YYSYMBOL_group_by = 156,                 /* group_by  */
  YYSYMBOL_group_by_unit = 157,            /* group_by_unit  */
  YYSYMBOL_load_data_stmt = 158,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 159,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 160,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 161             /* opt_semicolon  */
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
#define YYFINAL  84
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   618

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  371

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   353


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
       2,     2,   100,    98,     2,    99,     2,   101,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   102
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   256,   256,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   289,   295,   300,   306,   312,
     318,   324,   338,   344,   352,   368,   390,   406,   409,   421,
     431,   455,   479,   503,   518,   535,   546,   549,   562,   586,
     601,   604,   607,   612,   613,   614,   615,   616,   617,   620,
     637,   640,   652,   655,   661,   664,   670,   674,   678,   682,
     691,   697,   703,   717,   720,   727,   739,   757,   766,   777,
     780,   790,   838,   844,   853,   858,   871,   874,   879,   883,
     887,   891,   895,   902,   906,   910,   917,   921,   925,   936,
     940,   946,   958,   963,   968,   973,   976,   979,   982,   985,
     989,   992,   995,   998,  1005,  1009,  1013,  1017,  1021,  1025,
    1032,  1035,  1040,  1047,  1050,  1061,  1066,  1072,  1081,  1084,
    1097,  1100,  1107,  1110,  1116,  1119,  1131,  1134,  1147,  1150,
    1163,  1166,  1170,  1178,  1181,  1187,  1193,  1201,  1210,  1220,
    1231,  1241,  1250,  1259,  1272,  1273,  1274,  1275,  1276,  1277,
    1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1290,  1293,
    1306,  1309,  1322,  1335,  1343,  1353,  1354
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
  "CREATE", "DROP", "GROUP", "INNER_JOIN", "HAVING", "TABLE", "TABLES",
  "INDEX", "CALC", "SELECT", "ASC", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "DATE_T", "STRING_T", "FLOAT_T",
  "VECTOR_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "STORAGE", "FORMAT", "MAX", "MIN", "AVG", "SUM", "COUNT", "NOT_LIKE",
  "LIKE", "NOT_IN", "IN", "NOT_EXISTS", "EXISTS", "LENGTH", "ROUND",
  "DATE_FORMAT", "NULLABLE", "UNNULLABLE", "IS_NULL", "IS_NOT_NULL",
  "VEC_L2_DISTANCE", "VEC_COSINE_DISTANCE", "VEC_INNER_PRODUCT", "IVFFLAT",
  "LBRACKET", "RBRACKET", "UNIQUE", "ORDER_BY", "VIEW", "WITH", "DISTANCE",
  "TYPE", "LISTS", "PROBES", "LIMIT", "AS", "EQ", "LT", "GT", "LE", "GE",
  "NE", "NUMBER", "FLOAT", "ID", "DATE_STR", "TEXT_STR", "SSS",
  "HIGHER_THAN_EXPRESSION", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "create_vec_index_stmt", "id_list",
  "drop_index_stmt", "create_table_stmt", "create_view_stmt",
  "attr_def_list", "attr_def", "null_def", "type", "insert_stmt",
  "value_list", "number", "float", "value", "storage_format",
  "delete_stmt", "update_stmt", "update_target", "update_target_list",
  "select_stmt", "sub_select_stmt", "calc_stmt", "expression_list",
  "limited", "aggre_type", "vec_func_type", "expression", "query_unit",
  "query_list", "relation", "rel_list", "where", "having", "join_list",
  "order_by_list", "order_by", "order_by_flag", "condition_list",
  "condition", "comp_op", "group_by", "group_by_unit", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-279)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-73)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     561,   314,    18,   301,   301,   -69,    28,  -279,    13,    22,
     -23,  -279,  -279,  -279,  -279,  -279,   -19,    41,   561,    91,
      97,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,    17,    32,   124,   148,    82,    95,   102,
     301,  -279,  -279,  -279,  -279,  -279,   140,   142,   178,  -279,
     185,   189,   192,   519,  -279,  -279,   180,  -279,  -279,   301,
    -279,  -279,   195,   194,   122,   200,  -279,  -279,   126,   136,
     193,   149,   190,  -279,  -279,  -279,  -279,   -13,   213,   170,
     172,   182,  -279,   223,    40,   301,   301,   301,   301,   301,
     301,  -279,   519,  -279,  -279,  -279,  -279,  -279,   -54,  -279,
    -279,   244,   -74,  -279,   249,   301,   301,   301,   301,   301,
     176,  -279,   301,   231,   235,   246,   203,   519,   179,   204,
     238,    -9,   205,   261,   262,   295,   217,  -279,    44,   309,
     333,   337,   359,   387,   244,  -279,  -279,   519,   241,  -279,
    -279,  -279,   293,  -279,   -44,   -44,  -279,  -279,  -279,   200,
     224,   303,   191,  -279,   242,   304,  -279,   292,    99,   307,
     247,   295,  -279,   313,   243,   245,  -279,  -279,  -279,   301,
     301,   301,   301,   301,   263,   244,  -279,  -279,  -279,   -66,
     315,   519,   139,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,   422,   472,  -279,
      23,   322,   286,   203,   246,   340,  -279,  -279,  -279,  -279,
    -279,  -279,     3,   204,   335,   267,  -279,   269,   345,   346,
      48,    56,    67,    98,   127,  -279,  -279,   276,  -279,   224,
     367,   244,   353,   351,   401,   191,   191,   295,  -279,  -279,
    -279,   304,  -279,   291,   -68,  -279,  -279,  -279,   307,   330,
    -279,   362,   294,   297,  -279,  -279,  -279,  -279,  -279,  -279,
     315,   224,   246,   365,  -279,  -279,    71,   -11,  -279,    71,
    -279,  -279,  -279,  -279,   305,   375,  -279,    -6,   306,   389,
     394,   362,  -279,   374,   412,  -279,    53,   519,    79,    85,
      94,   100,   451,   244,    69,   295,  -279,   362,  -279,   347,
     403,   191,   423,   419,   244,   128,   135,   406,  -279,  -279,
    -279,   408,  -279,   367,   301,   191,   363,   366,  -279,   361,
    -279,   437,  -279,   301,   379,   158,   364,   301,  -279,     6,
     -68,  -279,   376,   437,  -279,  -279,   443,  -279,   444,  -279,
     301,  -279,   390,     6,   391,   443,   -37,  -279,  -279,  -279,
    -279,   453,   410,   399,   -68,   474,   393,   411,   -68,   476,
    -279
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     175,    24,    23,    16,    17,    18,    19,    10,    11,    12,
      13,    14,    15,     8,     9,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    89,    91,    92,    90,     0,     0,     0,    99,
       0,     0,     0,     0,    96,    97,   102,    98,   100,     0,
     111,    83,     0,    84,   120,   123,    33,    32,     0,     0,
       0,     0,     0,   173,     1,   176,     2,    73,     0,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,    66,     0,    62,    64,    69,    70,    71,     0,    67,
      68,    60,     0,   110,     0,     0,     0,     0,     0,     0,
       0,   122,     0,     0,     0,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   109,     0,     0,
       0,     0,     0,     0,    60,    63,    65,     0,     0,   103,
     104,   112,     0,    85,   105,   106,   107,   108,   121,   123,
       0,     0,   143,    75,     0,    79,   174,     0,     0,    46,
       0,     0,    44,     0,     0,     0,    45,    39,   114,     0,
       0,     0,     0,     0,     0,    60,   101,   113,   124,   125,
     128,     0,     0,   162,   163,   164,   165,   166,   167,   160,
     161,   154,   155,   156,   157,   158,   159,     0,     0,   131,
     144,     0,     0,     0,   130,     0,    53,    56,    54,    55,
      57,    58,    50,     0,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,     0,    72,    61,     0,   126,     0,
     134,    60,     0,     0,   147,   143,   143,     0,   152,    77,
      78,    79,    76,     0,     0,    51,    52,    49,    46,    73,
      74,    37,     0,     0,   115,   116,   119,   118,   117,   127,
     128,     0,   130,     0,    82,   149,   150,     0,   148,   151,
     145,   146,    80,   172,     0,     0,    47,    40,     0,     0,
       0,    37,   129,     0,   168,    59,    99,     0,    96,    97,
      98,   100,     0,    60,    50,     0,    42,    37,    34,     0,
       0,   143,     0,   132,    60,    96,    97,     0,    48,    41,
      38,     0,    35,   134,     0,   143,   136,     0,   153,     0,
     135,   170,   133,     0,    86,   101,     0,     0,   169,   140,
       0,    81,     0,   170,   141,   142,   138,    87,     0,   171,
       0,   137,     0,   140,     0,   138,     0,   139,    95,    94,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -279,  -279,   428,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -278,  -279,  -279,  -279,   259,   296,
     214,  -279,  -279,  -140,  -242,  -279,   -92,   264,  -279,  -279,
     312,   275,     2,  -195,  -279,    72,  -279,  -279,  -279,    -3,
     405,   382,  -225,   278,  -199,  -279,   211,  -279,   197,   196,
    -239,  -279,   -24,  -279,   210,  -279,  -279,  -279,  -279
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   289,    32,    33,    34,   224,   169,
     257,   222,    35,   148,   109,   110,   111,   131,    36,    37,
     165,   214,   242,   207,    39,    71,   341,    72,   361,   208,
      75,   123,   190,   240,   163,   326,   272,   334,   351,   346,
     209,   210,   211,   313,   338,    40,    41,    42,    86
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,    74,    38,     4,   184,     4,   280,   281,     4,   129,
     144,    50,   285,   310,   270,   252,   248,   250,   237,   149,
      38,   344,   345,   103,    76,   254,   150,   238,    48,   320,
      49,   284,   358,   359,   360,   166,   130,   145,   146,    77,
      51,    52,    53,    54,    55,   236,   293,    94,   275,   278,
      78,    56,    57,    58,   296,   185,   118,   119,    60,    61,
      62,    79,   297,   137,   245,   246,   113,   178,   255,   256,
      80,   264,   323,   294,    81,   171,   -66,   -66,   305,   265,
     298,   299,    66,   300,   106,   301,   332,    82,   302,    70,
     266,    84,   138,   139,   140,   141,   142,   143,   347,   241,
      85,   273,   -62,   -62,   116,   117,   118,   119,   -64,   -64,
      87,    73,    73,   154,   155,   156,   157,   -69,   -69,    74,
     249,   267,   365,   -71,   -71,    88,   369,   216,   217,   218,
     219,   220,   221,   172,   255,   256,    89,   176,   116,   117,
     118,   119,   116,   117,   118,   119,   116,   117,   118,   119,
     268,   -63,   -63,     4,   116,   117,   118,   119,   -65,   -65,
      90,    50,    95,   317,    96,   116,   117,   118,   119,   116,
     117,   118,   119,   226,   327,    91,   230,   231,   232,   233,
     234,   -72,   -72,   243,   244,   303,   152,   153,    92,    94,
      51,    52,    53,    54,    55,    93,   116,   117,   118,   119,
      97,    56,    57,    58,    59,   314,   120,    98,    60,    61,
      62,    99,    63,   192,   100,   121,   112,   114,   115,   124,
     116,   117,   118,   119,   122,   116,   117,   118,   119,   125,
      64,    65,    66,    67,   127,    68,   126,   128,    69,    70,
     276,   279,    51,    52,    53,    54,    55,   193,   194,   195,
     196,   197,   198,    56,    57,    58,    59,   132,   199,   200,
      60,    61,    62,   133,    63,   134,   135,   136,   147,   158,
     160,    50,   151,   161,    94,   167,   201,   202,   203,   204,
     205,   206,    64,    65,    66,    67,   162,    68,   170,   306,
      69,    70,   116,   117,   118,   119,   164,   168,   173,   113,
      51,    52,    53,    54,    55,   174,   175,   319,   247,     4,
     177,    56,    57,    58,    59,   186,   187,   189,    60,    61,
      62,   331,    63,    50,    43,   191,    44,   212,   213,   215,
     339,   223,   225,   179,   343,   227,   228,   235,   229,   239,
      64,    65,    66,    67,   247,    68,    45,   353,    69,    70,
     253,   101,    51,    52,    53,    54,    55,   180,   259,   102,
     260,   181,   261,    56,    57,    58,    59,   262,   263,   269,
      60,    61,    62,   192,    63,   271,   274,   103,   104,   130,
     105,   106,   107,   182,   283,   108,   288,   290,   295,    46,
     291,    47,    64,    65,    66,    67,   145,    68,   304,   307,
      69,    70,    51,    52,    53,    54,    55,   116,   117,   118,
     119,   183,   308,    56,    57,    58,    59,   309,   311,   312,
      60,    61,    62,   277,    63,   321,   322,   324,   325,   328,
     329,   116,   117,   118,   119,   116,   117,   118,   119,   333,
     335,   336,    64,    65,    66,    67,    83,    68,   348,   342,
      69,    70,    51,    52,    53,    54,    55,   116,   117,   118,
     119,   337,   340,    56,    57,    58,    59,   350,   352,   354,
      60,    61,    62,    50,    63,   367,   356,   362,   193,   194,
     195,   196,   197,   198,   364,   116,   117,   118,   119,   199,
     200,   363,    64,    65,    66,    67,   368,    68,   366,   370,
      69,    70,    51,    52,    53,    54,    55,   201,   202,   203,
     204,   205,   206,    56,    57,    58,    59,   286,   318,   258,
      60,    61,    62,   287,    63,   251,   282,   159,   193,   194,
     195,   196,   197,   198,   330,   116,   117,   118,   119,   199,
     200,   188,   315,   316,    66,    67,     0,    68,   292,   355,
      69,    70,   357,   349,     0,     0,     0,   201,   202,   203,
     204,   205,   206,     0,     0,     0,     1,     2,     0,     0,
     116,   117,   118,   119,     3,     4,     0,     5,     6,     7,
       8,     9,    10,     0,   101,     0,    11,    12,    13,     0,
       0,     0,   102,     0,     0,    14,    15,     0,     0,     0,
       0,     0,     0,     0,    16,     0,    17,     0,     0,    18,
     103,   104,     0,   105,   106,   107,     0,     0,   108
};

static const yytype_int16 yycheck[] =
{
       3,     4,     0,    14,   144,    14,   245,   246,    14,    22,
     102,    22,   254,   291,   239,   214,   211,   212,    84,    93,
      18,    15,    16,    91,    93,    22,   100,    93,    10,   307,
      12,    99,    69,    70,    71,   127,    49,    91,    92,    11,
      51,    52,    53,    54,    55,   185,   271,    50,   243,   244,
      37,    62,    63,    64,    65,   147,   100,   101,    69,    70,
      71,    39,    73,    23,    41,    42,    69,    23,    65,    66,
      93,    23,   311,   272,    93,    84,    23,    24,    84,    23,
      91,    92,    93,    94,    95,    96,   325,    46,    99,   100,
      23,     0,    95,    96,    97,    98,    99,   100,   340,   191,
       3,   241,    23,    24,    98,    99,   100,   101,    23,    24,
      93,   114,   115,   116,   117,   118,   119,    23,    24,   122,
     212,    23,   364,    23,    24,    93,   368,    28,    29,    30,
      31,    32,    33,   131,    65,    66,    12,   135,    98,    99,
     100,   101,    98,    99,   100,   101,    98,    99,   100,   101,
      23,    23,    24,    14,    98,    99,   100,   101,    23,    24,
      12,    22,    22,   303,    22,    98,    99,   100,   101,    98,
      99,   100,   101,   171,   314,    93,   179,   180,   181,   182,
     183,    23,    24,   207,   208,   277,   114,   115,    93,   192,
      51,    52,    53,    54,    55,    93,    98,    99,   100,   101,
      22,    62,    63,    64,    65,   297,    84,    22,    69,    70,
      71,    22,    73,    22,    22,    93,    36,    22,    24,    93,
      98,    99,   100,   101,    24,    98,    99,   100,   101,    93,
      91,    92,    93,    94,    85,    96,    43,    47,    99,   100,
     243,   244,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    44,    67,    68,
      69,    70,    71,    93,    73,    93,    84,    44,    24,    93,
      39,    22,    23,    38,   277,    96,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    40,    96,    50,   287,
      99,   100,    98,    99,   100,   101,    93,    93,    93,   302,
      51,    52,    53,    54,    55,    44,    44,   305,    22,    14,
      93,    62,    63,    64,    65,    74,    23,    93,    69,    70,
      71,   324,    73,    22,    10,    22,    12,    85,    24,    37,
     333,    24,    85,    24,   337,    22,    93,    74,    93,    24,
      91,    92,    93,    94,    22,    96,    32,   350,    99,   100,
      10,    65,    51,    52,    53,    54,    55,    24,    23,    73,
      93,    24,    93,    62,    63,    64,    65,    22,    22,    93,
      69,    70,    71,    22,    73,     8,    23,    91,    92,    49,
      94,    95,    96,    24,    93,    99,    24,    93,    23,    75,
      93,    77,    91,    92,    93,    94,    91,    96,    23,    93,
      99,   100,    51,    52,    53,    54,    55,    98,    99,   100,
     101,    24,    23,    62,    63,    64,    65,    23,    44,     7,
      69,    70,    71,    22,    73,    78,    23,     4,     9,    23,
      22,    98,    99,   100,   101,    98,    99,   100,   101,    76,
      74,    80,    91,    92,    93,    94,    18,    96,    72,    85,
      99,   100,    51,    52,    53,    54,    55,    98,    99,   100,
     101,    24,    83,    62,    63,    64,    65,    24,    24,    79,
      69,    70,    71,    22,    73,    82,    85,    24,    56,    57,
      58,    59,    60,    61,    85,    98,    99,   100,   101,    67,
      68,    81,    91,    92,    93,    94,    85,    96,    24,    23,
      99,   100,    51,    52,    53,    54,    55,    85,    86,    87,
      88,    89,    90,    62,    63,    64,    65,   258,   304,   223,
      69,    70,    71,   259,    73,   213,   251,   122,    56,    57,
      58,    59,    60,    61,   323,    98,    99,   100,   101,    67,
      68,   159,    91,    92,    93,    94,    -1,    96,   270,   353,
      99,   100,   355,   343,    -1,    -1,    -1,    85,    86,    87,
      88,    89,    90,    -1,    -1,    -1,     5,     6,    -1,    -1,
      98,    99,   100,   101,    13,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    65,    -1,    25,    26,    27,    -1,
      -1,    -1,    73,    -1,    -1,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    -1,    -1,    48,
      91,    92,    -1,    94,    95,    96,    -1,    -1,    99
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    13,    14,    16,    17,    18,    19,    20,
      21,    25,    26,    27,    34,    35,    43,    45,    48,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   118,   119,   120,   125,   131,   132,   135,   137,
     158,   159,   160,    10,    12,    32,    75,    77,    10,    12,
      22,    51,    52,    53,    54,    55,    62,    63,    64,    65,
      69,    70,    71,    73,    91,    92,    93,    94,    96,    99,
     100,   138,   140,   142,   142,   143,    93,    11,    37,    39,
      93,    93,    46,   105,     0,     3,   161,    93,    93,    12,
      12,    93,    93,    93,   142,    22,    22,    22,    22,    22,
      22,    65,    73,    91,    92,    94,    95,    96,    99,   127,
     128,   129,    36,   142,    22,    24,    98,    99,   100,   101,
      84,    93,    24,   144,    93,    93,    43,    85,    47,    22,
      49,   130,    44,    93,    93,    84,    44,    23,   142,   142,
     142,   142,   142,   142,   129,    91,    92,    24,   126,    93,
     100,    23,   138,   138,   142,   142,   142,   142,    93,   143,
      39,    38,    40,   147,    93,   133,   129,    96,    93,   122,
      50,    84,   135,    93,    44,    44,   135,    93,    23,    24,
      24,    24,    24,    24,   126,   129,    74,    23,   144,    93,
     145,    22,    22,    56,    57,    58,    59,    60,    61,    67,
      68,    85,    86,    87,    88,    89,    90,   136,   142,   153,
     154,   155,    85,    24,   134,    37,    28,    29,    30,    31,
      32,    33,   124,    24,   121,    85,   135,    22,    93,    93,
     142,   142,   142,   142,   142,    74,   126,    84,    93,    24,
     146,   129,   135,   155,   155,    41,    42,    22,   136,   129,
     136,   133,   147,    10,    22,    65,    66,   123,   122,    23,
      93,    93,    22,    22,    23,    23,    23,    23,    23,    93,
     145,     8,   149,   126,    23,   136,   142,    22,   136,   142,
     153,   153,   134,    93,    99,   127,   121,   130,    24,   117,
      93,    93,   146,   145,   147,    23,    65,    73,    91,    92,
      94,    96,    99,   129,    23,    84,   135,    93,    23,    23,
     117,    44,     7,   156,   129,    91,    92,   126,   123,   135,
     117,    78,    23,   153,     4,     9,   148,   126,    23,    22,
     149,   142,   153,    76,   150,    74,    80,    24,   157,   142,
      83,   139,    85,   142,    15,    16,   152,   127,    72,   157,
      24,   151,    24,   142,    79,   152,    85,   151,    69,    70,
      71,   141,    24,    81,    85,   127,    24,    82,    85,   127,
      23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   103,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   115,   116,   117,   117,   118,
     119,   119,   119,   119,   119,   120,   121,   121,   122,   122,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   125,
     126,   126,   127,   127,   128,   128,   129,   129,   129,   129,
     129,   129,   129,   130,   130,   131,   132,   133,   133,   134,
     134,   135,   136,   137,   138,   138,   139,   139,   140,   140,
     140,   140,   140,   141,   141,   141,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     143,   143,   143,   144,   144,   145,   145,   145,   146,   146,
     147,   147,   148,   148,   149,   149,   150,   150,   151,   151,
     152,   152,   152,   153,   153,   153,   153,   154,   154,   154,
     154,   154,   154,   154,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   156,   156,
     157,   157,   158,   159,   160,   161,   161
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     9,    10,    27,     0,     3,     5,
       8,    10,     9,     6,     5,     5,     0,     3,     6,     3,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     8,
       0,     3,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     4,     0,     4,     4,     6,     3,     3,     0,
       3,    12,     3,     2,     1,     3,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     3,     4,     4,     6,     6,     6,     6,     6,
       1,     3,     2,     0,     3,     1,     2,     3,     0,     3,
       0,     2,     0,     2,     0,     5,     0,     4,     0,     4,
       0,     1,     1,     0,     1,     3,     3,     2,     3,     3,
       3,     3,     2,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     3,     7,     2,     4,     0,     1
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
#line 257 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1994 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 289 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 295 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2011 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 300 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2019 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 306 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2027 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 312 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2035 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 318 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2043 "yacc_sql.cpp"
    break;

  case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 324 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2053 "yacc_sql.cpp"
    break;

  case 32: /* show_tables_stmt: SHOW TABLES  */
#line 338 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2061 "yacc_sql.cpp"
    break;

  case 33: /* desc_table_stmt: DESC ID  */
#line 344 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2071 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 353 "yacc_sql.y"
    {
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
#line 2091 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 369 "yacc_sql.y"
    {
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
#line 2114 "yacc_sql.cpp"
    break;

  case 36: /* create_vec_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE ID RBRACE WITH LBRACE TYPE EQ IVFFLAT COMMA DISTANCE EQ vec_func_type COMMA LISTS EQ number COMMA PROBES EQ number RBRACE  */
#line 390 "yacc_sql.y"
                                                                                                                                                                    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VEC_INDEX);
      CreateVecIndexSqlNode &create_vec_index = (yyval.sql_node)->create_vec_index;
      create_vec_index.index_name = (yyvsp[-23].string);
      create_vec_index.relation_name = (yyvsp[-21].string);
      create_vec_index.attribute_name = (yyvsp[-19].string);

      // para
      create_vec_index.type_name = "IVFFLAT";
      create_vec_index.distance_name = (yyvsp[-9].vec_func_type);
      create_vec_index.lists_ = (yyvsp[-5].number);
      create_vec_index.probes_ = (yyvsp[-1].number);
    }
#line 2132 "yacc_sql.cpp"
    break;

  case 37: /* id_list: %empty  */
#line 406 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2140 "yacc_sql.cpp"
    break;

  case 38: /* id_list: COMMA ID id_list  */
#line 409 "yacc_sql.y"
                        { 
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2154 "yacc_sql.cpp"
    break;

  case 39: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 422 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2166 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 432 "yacc_sql.y"
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
#line 2194 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt  */
#line 456 "yacc_sql.y"
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
#line 2222 "yacc_sql.cpp"
    break;

  case 42: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 480 "yacc_sql.y"
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
#line 2250 "yacc_sql.cpp"
    break;

  case 43: /* create_table_stmt: CREATE TABLE ID storage_format AS select_stmt  */
#line 504 "yacc_sql.y"
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
#line 2269 "yacc_sql.cpp"
    break;

  case 44: /* create_table_stmt: CREATE TABLE ID storage_format select_stmt  */
#line 519 "yacc_sql.y"
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
#line 2288 "yacc_sql.cpp"
    break;

  case 45: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 536 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.view_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
      create_view.sub_select = (yyvsp[0].sql_node);
    }
#line 2300 "yacc_sql.cpp"
    break;

  case 46: /* attr_def_list: %empty  */
#line 546 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2308 "yacc_sql.cpp"
    break;

  case 47: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 550 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2322 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 563 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->can_be_null = (yyvsp[0].boolean);

      if((yyval.attr_info)->type == AttrType::VECTORS){
        if ((yyvsp[-2].number) <= 1000) {
          (yyval.attr_info)->length = (yyvsp[-2].number) * 4;
        } else if ((yyvsp[-2].number) > 1000 && (yyvsp[-2].number) <= 16000) {
          (yyval.attr_info)->length = 40; // 页号 + 长度 + 标志位 高维向量数据最多占8页
        } else {
          (yyval.attr_info)->length = 16000 * 4 + 114514; // 超长就给一个非法长度，后面检查
        }
      }

      if((yyval.attr_info)->type == AttrType::TEXT){
        (yyval.attr_info)->length = 40; //  页号 + 长度
      }

      free((yyvsp[-5].string));
    }
#line 2350 "yacc_sql.cpp"
    break;

  case 49: /* attr_def: ID type null_def  */
#line 587 "yacc_sql.y"
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
#line 2367 "yacc_sql.cpp"
    break;

  case 50: /* null_def: %empty  */
#line 601 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 51: /* null_def: NULLABLE  */
#line 604 "yacc_sql.y"
               {
      (yyval.boolean) = true;
    }
#line 2383 "yacc_sql.cpp"
    break;

  case 52: /* null_def: UNNULLABLE  */
#line 607 "yacc_sql.y"
                 {
      (yyval.boolean) = false;
    }
#line 2391 "yacc_sql.cpp"
    break;

  case 53: /* type: INT_T  */
#line 612 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2397 "yacc_sql.cpp"
    break;

  case 54: /* type: STRING_T  */
#line 613 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2403 "yacc_sql.cpp"
    break;

  case 55: /* type: FLOAT_T  */
#line 614 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2409 "yacc_sql.cpp"
    break;

  case 56: /* type: DATE_T  */
#line 615 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATE); }
#line 2415 "yacc_sql.cpp"
    break;

  case 57: /* type: VECTOR_T  */
#line 616 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2421 "yacc_sql.cpp"
    break;

  case 58: /* type: TEXT_T  */
#line 617 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXT); }
#line 2427 "yacc_sql.cpp"
    break;

  case 59: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 621 "yacc_sql.y"
    {
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
#line 2444 "yacc_sql.cpp"
    break;

  case 60: /* value_list: %empty  */
#line 637 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2452 "yacc_sql.cpp"
    break;

  case 61: /* value_list: COMMA value value_list  */
#line 640 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2466 "yacc_sql.cpp"
    break;

  case 62: /* number: NUMBER  */
#line 652 "yacc_sql.y"
           {
      (yyval.number) = (yyvsp[0].number);
    }
#line 2474 "yacc_sql.cpp"
    break;

  case 63: /* number: '-' NUMBER  */
#line 655 "yacc_sql.y"
                 {
      (yyval.number) = -(yyvsp[0].number);
    }
#line 2482 "yacc_sql.cpp"
    break;

  case 64: /* float: FLOAT  */
#line 661 "yacc_sql.y"
          {
      (yyval.floats) = (yyvsp[0].floats);
    }
#line 2490 "yacc_sql.cpp"
    break;

  case 65: /* float: '-' FLOAT  */
#line 664 "yacc_sql.y"
                {
      (yyval.floats) = -(yyvsp[0].floats);
    }
#line 2498 "yacc_sql.cpp"
    break;

  case 66: /* value: NULLABLE  */
#line 670 "yacc_sql.y"
             {
      (yyval.value) = new Value(string("ckk is stupid!"), 114514);
      (yyloc) = (yylsp[0]);
    }
#line 2507 "yacc_sql.cpp"
    break;

  case 67: /* value: number  */
#line 674 "yacc_sql.y"
            {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2516 "yacc_sql.cpp"
    break;

  case 68: /* value: float  */
#line 678 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2525 "yacc_sql.cpp"
    break;

  case 69: /* value: DATE_STR  */
#line 682 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);  // 去掉首尾的引号
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);    //sscanf会自动转换字符串中的数字，不用显式stoi
      int date_num = year * 10000 + month * 100 + day;
      (yyval.value) = new Value(date_num, true);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 70: /* value: TEXT_STR  */
#line 691 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, strlen(tmp));
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2550 "yacc_sql.cpp"
    break;

  case 71: /* value: SSS  */
#line 697 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, strlen(tmp));  
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 72: /* value: LBRACKET value value_list RBRACKET  */
#line 703 "yacc_sql.y"
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
#line 2577 "yacc_sql.cpp"
    break;

  case 73: /* storage_format: %empty  */
#line 717 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2585 "yacc_sql.cpp"
    break;

  case 74: /* storage_format: STORAGE FORMAT EQ ID  */
#line 721 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 75: /* delete_stmt: DELETE FROM ID where  */
#line 728 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 76: /* update_stmt: UPDATE ID SET update_target update_target_list where  */
#line 740 "yacc_sql.y"
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
#line 2626 "yacc_sql.cpp"
    break;

  case 77: /* update_target: ID EQ value  */
#line 758 "yacc_sql.y"
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->value = *(yyvsp[0].value);
      (yyval.update_target)->is_value = true;

      delete (yyvsp[0].value);
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 78: /* update_target: ID EQ sub_select_stmt  */
#line 767 "yacc_sql.y"
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->sub_select = (yyvsp[0].sql_node);
      (yyval.update_target)->is_value = false;
    }
#line 2650 "yacc_sql.cpp"
    break;

  case 79: /* update_target_list: %empty  */
#line 777 "yacc_sql.y"
    {
      (yyval.update_target_list) = nullptr;
    }
#line 2658 "yacc_sql.cpp"
    break;

  case 80: /* update_target_list: COMMA update_target update_target_list  */
#line 781 "yacc_sql.y"
    {
      if((yyvsp[0].update_target_list) == nullptr)
        (yyval.update_target_list) = new std::vector<UpdateTarget>;
      else (yyval.update_target_list) = (yyvsp[0].update_target_list);
      (yyval.update_target_list)->emplace_back(*(yyvsp[-1].update_target));
    }
#line 2669 "yacc_sql.cpp"
    break;

  case 81: /* select_stmt: SELECT query_unit query_list FROM relation rel_list join_list where group_by having order_by_list limited  */
#line 791 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-9].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-9].expression_list));
        delete (yyvsp[-9].expression_list);
      }
      (yyval.sql_node)->selection.expressions.emplace_back((yyvsp[-10].expression));
      std::reverse((yyval.sql_node)->selection.expressions.begin(), (yyval.sql_node)->selection.expressions.end());

      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }
      (yyval.sql_node)->selection.relations.emplace_back((yyvsp[-7].expression));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-5].expression_list) != nullptr) {
        (yyval.sql_node)->selection.join.swap(*(yyvsp[-5].expression_list));
        delete (yyvsp[-5].expression_list);
      }
      std::reverse((yyval.sql_node)->selection.join.begin(), (yyval.sql_node)->selection.join.end());

      if ((yyvsp[-4].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-4].condition_list));
        delete (yyvsp[-4].condition_list);
      }

      if ((yyvsp[-3].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].expression_list));
        delete (yyvsp[-3].expression_list);
      }

      if((yyvsp[-2].condition_list) != nullptr) {
        (yyval.sql_node)->selection.having_conditions.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
      }

      if((yyvsp[-1].expression_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }
      std::reverse((yyval.sql_node)->selection.order_by.begin(), (yyval.sql_node)->selection.order_by.end());

      (yyval.sql_node)->selection.vec_order_limit_ = (yyvsp[0].number);
    }
#line 2719 "yacc_sql.cpp"
    break;

  case 82: /* sub_select_stmt: LBRACE select_stmt RBRACE  */
#line 839 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
    }
#line 2727 "yacc_sql.cpp"
    break;

  case 83: /* calc_stmt: CALC expression_list  */
#line 845 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2737 "yacc_sql.cpp"
    break;

  case 84: /* expression_list: expression  */
#line 854 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2746 "yacc_sql.cpp"
    break;

  case 85: /* expression_list: expression COMMA expression_list  */
#line 859 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2759 "yacc_sql.cpp"
    break;

  case 86: /* limited: %empty  */
#line 871 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 2767 "yacc_sql.cpp"
    break;

  case 87: /* limited: LIMIT number  */
#line 874 "yacc_sql.y"
                   {
      (yyval.number) = (yyvsp[0].number);
    }
#line 2775 "yacc_sql.cpp"
    break;

  case 88: /* aggre_type: MAX  */
#line 879 "yacc_sql.y"
        { 
      const char * result = "MAX";
      (yyval.aggre_type) = result; 
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 89: /* aggre_type: MIN  */
#line 883 "yacc_sql.y"
          { 
      const char * result = "MIN";
      (yyval.aggre_type) = result; 
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 90: /* aggre_type: COUNT  */
#line 887 "yacc_sql.y"
            { 
      const char * result = "COUNT";
      (yyval.aggre_type) = result; 
    }
#line 2802 "yacc_sql.cpp"
    break;

  case 91: /* aggre_type: AVG  */
#line 891 "yacc_sql.y"
          { 
      const char * result = "AVG";
      (yyval.aggre_type) = result; 
    }
#line 2811 "yacc_sql.cpp"
    break;

  case 92: /* aggre_type: SUM  */
#line 895 "yacc_sql.y"
          { 
      const char * result = "SUM";
      (yyval.aggre_type) = result; 
    }
#line 2820 "yacc_sql.cpp"
    break;

  case 93: /* vec_func_type: VEC_INNER_PRODUCT  */
#line 902 "yacc_sql.y"
                      { 
      const char * result = "INNER_PRODUCT";
      (yyval.vec_func_type) = result; 
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 94: /* vec_func_type: VEC_COSINE_DISTANCE  */
#line 906 "yacc_sql.y"
                          { 
      const char * result = "COSINE_DISTANCE";
      (yyval.vec_func_type) = result; 
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 95: /* vec_func_type: VEC_L2_DISTANCE  */
#line 910 "yacc_sql.y"
                      { 
      const char * result = "L2_DISTANCE";
      (yyval.vec_func_type) = result; 
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 96: /* expression: NUMBER  */
#line 917 "yacc_sql.y"
           {
      (yyval.expression) = new ValueExpr(Value((yyvsp[0].number)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 97: /* expression: FLOAT  */
#line 921 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(Value((yyvsp[0].floats)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2865 "yacc_sql.cpp"
    break;

  case 98: /* expression: DATE_STR  */
#line 925 "yacc_sql.y"
               {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);
      int date_num = year * 10000 + month * 100 + day;
      free(tmp);
      free((yyvsp[0].string));

      (yyval.expression) = new ValueExpr(Value(date_num, true));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 99: /* expression: NULLABLE  */
#line 936 "yacc_sql.y"
               {
      (yyval.expression) = new ValueExpr(Value(string("dmx is handsome"), 114514));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 100: /* expression: SSS  */
#line 940 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.expression) = new ValueExpr(Value(tmp));
      free(tmp);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 101: /* expression: LBRACKET value value_list RBRACKET  */
#line 946 "yacc_sql.y"
                                         {
      std::vector<float> nums;
      nums.emplace_back((yyvsp[-2].value)->get_float());
      if((yyvsp[-1].value_list) != nullptr) {
        std::reverse((yyvsp[-1].value_list)->begin(), (yyvsp[-1].value_list)->end());
        for (Value value : *(yyvsp[-1].value_list)) {
          nums.emplace_back(value.get_float());
        }
      }
      (yyval.expression) = new ValueExpr(Value(nums));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 102: /* expression: ID  */
#line 958 "yacc_sql.y"
         {
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 103: /* expression: ID DOT ID  */
#line 963 "yacc_sql.y"
                {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
#line 2938 "yacc_sql.cpp"
    break;

  case 104: /* expression: ID DOT '*'  */
#line 968 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
#line 2948 "yacc_sql.cpp"
    break;

  case 105: /* expression: expression '+' expression  */
#line 973 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 106: /* expression: expression '-' expression  */
#line 976 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2964 "yacc_sql.cpp"
    break;

  case 107: /* expression: expression '*' expression  */
#line 979 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2972 "yacc_sql.cpp"
    break;

  case 108: /* expression: expression '/' expression  */
#line 982 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2980 "yacc_sql.cpp"
    break;

  case 109: /* expression: LBRACE expression RBRACE  */
#line 985 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2989 "yacc_sql.cpp"
    break;

  case 110: /* expression: '-' expression  */
#line 989 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2997 "yacc_sql.cpp"
    break;

  case 111: /* expression: '*'  */
#line 992 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3005 "yacc_sql.cpp"
    break;

  case 112: /* expression: aggre_type LBRACE RBRACE  */
#line 995 "yacc_sql.y"
                               {
      (yyval.expression) = create_aggregate_expression((yyvsp[-2].aggre_type), nullptr, sql_string, &(yyloc));
    }
#line 3013 "yacc_sql.cpp"
    break;

  case 113: /* expression: aggre_type LBRACE expression_list RBRACE  */
#line 998 "yacc_sql.y"
                                               {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression((yyvsp[-3].aggre_type), nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression((yyvsp[-3].aggre_type), (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 114: /* expression: LENGTH LBRACE expression RBRACE  */
#line 1005 "yacc_sql.y"
                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, nullptr, nullptr, (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3034 "yacc_sql.cpp"
    break;

  case 115: /* expression: ROUND LBRACE expression COMMA expression RBRACE  */
#line 1009 "yacc_sql.y"
                                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, (yyvsp[-1].expression), nullptr, (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3043 "yacc_sql.cpp"
    break;

  case 116: /* expression: DATE_FORMAT LBRACE expression COMMA expression RBRACE  */
#line 1013 "yacc_sql.y"
                                                            {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, nullptr, (yyvsp[-1].expression), (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3052 "yacc_sql.cpp"
    break;

  case 117: /* expression: VEC_INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 1017 "yacc_sql.y"
                                                                  {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3061 "yacc_sql.cpp"
    break;

  case 118: /* expression: VEC_COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1021 "yacc_sql.y"
                                                                    {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 119: /* expression: VEC_L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1025 "yacc_sql.y"
                                                                {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 120: /* query_unit: expression  */
#line 1032 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 121: /* query_unit: expression AS ID  */
#line 1035 "yacc_sql.y"
                       {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), (yyvsp[-2].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 3097 "yacc_sql.cpp"
    break;

  case 122: /* query_unit: expression ID  */
#line 1040 "yacc_sql.y"
                    {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 3107 "yacc_sql.cpp"
    break;

  case 123: /* query_list: %empty  */
#line 1047 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3115 "yacc_sql.cpp"
    break;

  case 124: /* query_list: COMMA query_unit query_list  */
#line 1050 "yacc_sql.y"
                                  {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3129 "yacc_sql.cpp"
    break;

  case 125: /* relation: ID  */
#line 1061 "yacc_sql.y"
       {
      (yyval.expression) = new UnboundTableExpr((yyvsp[0].string), string());
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 3139 "yacc_sql.cpp"
    break;

  case 126: /* relation: ID ID  */
#line 1066 "yacc_sql.y"
            {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), new UnboundTableExpr((yyvsp[-1].string), (yyvsp[0].string)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3150 "yacc_sql.cpp"
    break;

  case 127: /* relation: ID AS ID  */
#line 1072 "yacc_sql.y"
               {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), new UnboundTableExpr((yyvsp[-2].string), (yyvsp[0].string)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3161 "yacc_sql.cpp"
    break;

  case 128: /* rel_list: %empty  */
#line 1081 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3169 "yacc_sql.cpp"
    break;

  case 129: /* rel_list: COMMA relation rel_list  */
#line 1084 "yacc_sql.y"
                              {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3183 "yacc_sql.cpp"
    break;

  case 130: /* where: %empty  */
#line 1097 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3191 "yacc_sql.cpp"
    break;

  case 131: /* where: WHERE condition_list  */
#line 1100 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3199 "yacc_sql.cpp"
    break;

  case 132: /* having: %empty  */
#line 1107 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3207 "yacc_sql.cpp"
    break;

  case 133: /* having: HAVING condition_list  */
#line 1110 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3215 "yacc_sql.cpp"
    break;

  case 134: /* join_list: %empty  */
#line 1116 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3223 "yacc_sql.cpp"
    break;

  case 135: /* join_list: INNER_JOIN relation ON condition_list join_list  */
#line 1119 "yacc_sql.y"
                                                      {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(new JoinTableExpr(*(yyvsp[-1].condition_list), (yyvsp[-3].expression)));
    }
#line 3236 "yacc_sql.cpp"
    break;

  case 136: /* order_by_list: %empty  */
#line 1131 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3244 "yacc_sql.cpp"
    break;

  case 137: /* order_by_list: ORDER_BY expression order_by_flag order_by  */
#line 1135 "yacc_sql.y"
    {
       if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
#line 3257 "yacc_sql.cpp"
    break;

  case 138: /* order_by: %empty  */
#line 1147 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3265 "yacc_sql.cpp"
    break;

  case 139: /* order_by: COMMA expression order_by_flag order_by  */
#line 1151 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
#line 3278 "yacc_sql.cpp"
    break;

  case 140: /* order_by_flag: %empty  */
#line 1163 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3286 "yacc_sql.cpp"
    break;

  case 141: /* order_by_flag: ASC  */
#line 1167 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3294 "yacc_sql.cpp"
    break;

  case 142: /* order_by_flag: DESC  */
#line 1171 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 3302 "yacc_sql.cpp"
    break;

  case 143: /* condition_list: %empty  */
#line 1178 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3310 "yacc_sql.cpp"
    break;

  case 144: /* condition_list: condition  */
#line 1181 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyvsp[0].condition)->conjuction_type = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3321 "yacc_sql.cpp"
    break;

  case 145: /* condition_list: condition AND condition_list  */
#line 1187 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjuction_type = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3332 "yacc_sql.cpp"
    break;

  case 146: /* condition_list: condition OR condition_list  */
#line 1193 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjuction_type = 2;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3343 "yacc_sql.cpp"
    break;

  case 147: /* condition: expression comp_op  */
#line 1202 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[0].comp);
      (yyval.condition)->left_expression = (yyvsp[-1].expression);
      (yyval.condition)->right_expression = new ValueExpr(Value(114514));
    }
#line 3356 "yacc_sql.cpp"
    break;

  case 148: /* condition: expression comp_op sub_select_stmt  */
#line 1211 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->right_expression = nullptr;
    }
#line 3370 "yacc_sql.cpp"
    break;

  case 149: /* condition: sub_select_stmt comp_op sub_select_stmt  */
#line 1221 "yacc_sql.y"
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
#line 3385 "yacc_sql.cpp"
    break;

  case 150: /* condition: sub_select_stmt comp_op expression  */
#line 1232 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = true;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_sub_query = (yyvsp[-2].sql_node);
      (yyval.condition)->left_expression = nullptr;
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
#line 3399 "yacc_sql.cpp"
    break;

  case 151: /* condition: expression comp_op expression  */
#line 1242 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
#line 3412 "yacc_sql.cpp"
    break;

  case 152: /* condition: comp_op sub_select_stmt  */
#line 1251 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = new ValueExpr(Value(114514));
    }
#line 3425 "yacc_sql.cpp"
    break;

  case 153: /* condition: expression comp_op LBRACE value value_list RBRACE  */
#line 1260 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-4].comp);
      (yyval.condition)->left_expression = (yyvsp[-5].expression);
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.condition)->right_expression = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 3439 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: EQ  */
#line 1272 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3445 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: LT  */
#line 1273 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3451 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: GT  */
#line 1274 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3457 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: LE  */
#line 1275 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3463 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: GE  */
#line 1276 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3469 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: NE  */
#line 1277 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3475 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: IS_NULL  */
#line 1278 "yacc_sql.y"
              { (yyval.comp) = XXX_IS_NULL; }
#line 3481 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: IS_NOT_NULL  */
#line 1279 "yacc_sql.y"
                  { (yyval.comp) = XXX_IS_NOT_NULL; }
#line 3487 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: NOT_LIKE  */
#line 1280 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_XXX; }
#line 3493 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: LIKE  */
#line 1281 "yacc_sql.y"
           { (yyval.comp) = LIKE_XXX; }
#line 3499 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: NOT_IN  */
#line 1282 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_XXX; }
#line 3505 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: IN  */
#line 1283 "yacc_sql.y"
         { (yyval.comp) = IN_XXX; }
#line 3511 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: NOT_EXISTS  */
#line 1284 "yacc_sql.y"
                 { (yyval.comp) = XXX_NOT_EXISTS; }
#line 3517 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: EXISTS  */
#line 1285 "yacc_sql.y"
             { (yyval.comp) = XXX_EXISTS; }
#line 3523 "yacc_sql.cpp"
    break;

  case 168: /* group_by: %empty  */
#line 1290 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3531 "yacc_sql.cpp"
    break;

  case 169: /* group_by: GROUP BY expression group_by_unit  */
#line 1293 "yacc_sql.y"
                                        {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3545 "yacc_sql.cpp"
    break;

  case 170: /* group_by_unit: %empty  */
#line 1306 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3553 "yacc_sql.cpp"
    break;

  case 171: /* group_by_unit: COMMA expression group_by_unit  */
#line 1310 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3567 "yacc_sql.cpp"
    break;

  case 172: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1323 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3581 "yacc_sql.cpp"
    break;

  case 173: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1336 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3590 "yacc_sql.cpp"
    break;

  case 174: /* set_variable_stmt: SET ID EQ value  */
#line 1344 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3602 "yacc_sql.cpp"
    break;


#line 3606 "yacc_sql.cpp"

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

#line 1356 "yacc_sql.y"

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
