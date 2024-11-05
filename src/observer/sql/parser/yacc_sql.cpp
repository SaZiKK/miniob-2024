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
  YYSYMBOL_WITH = 77,                      /* WITH  */
  YYSYMBOL_DISTANCE = 78,                  /* DISTANCE  */
  YYSYMBOL_TYPE = 79,                      /* TYPE  */
  YYSYMBOL_LISTS = 80,                     /* LISTS  */
  YYSYMBOL_PROBES = 81,                    /* PROBES  */
  YYSYMBOL_LIMIT = 82,                     /* LIMIT  */
  YYSYMBOL_AS = 83,                        /* AS  */
  YYSYMBOL_EQ = 84,                        /* EQ  */
  YYSYMBOL_LT = 85,                        /* LT  */
  YYSYMBOL_GT = 86,                        /* GT  */
  YYSYMBOL_LE = 87,                        /* LE  */
  YYSYMBOL_GE = 88,                        /* GE  */
  YYSYMBOL_NE = 89,                        /* NE  */
  YYSYMBOL_NUMBER = 90,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 91,                     /* FLOAT  */
  YYSYMBOL_ID = 92,                        /* ID  */
  YYSYMBOL_DATE_STR = 93,                  /* DATE_STR  */
  YYSYMBOL_TEXT_STR = 94,                  /* TEXT_STR  */
  YYSYMBOL_SSS = 95,                       /* SSS  */
  YYSYMBOL_HIGHER_THAN_EXPRESSION = 96,    /* HIGHER_THAN_EXPRESSION  */
  YYSYMBOL_97_ = 97,                       /* '+'  */
  YYSYMBOL_98_ = 98,                       /* '-'  */
  YYSYMBOL_99_ = 99,                       /* '*'  */
  YYSYMBOL_100_ = 100,                     /* '/'  */
  YYSYMBOL_UMINUS = 101,                   /* UMINUS  */
  YYSYMBOL_YYACCEPT = 102,                 /* $accept  */
  YYSYMBOL_commands = 103,                 /* commands  */
  YYSYMBOL_command_wrapper = 104,          /* command_wrapper  */
  YYSYMBOL_exit_stmt = 105,                /* exit_stmt  */
  YYSYMBOL_help_stmt = 106,                /* help_stmt  */
  YYSYMBOL_sync_stmt = 107,                /* sync_stmt  */
  YYSYMBOL_begin_stmt = 108,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 109,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 110,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 111,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 112,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 113,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 114,        /* create_index_stmt  */
  YYSYMBOL_create_vec_index_stmt = 115,    /* create_vec_index_stmt  */
  YYSYMBOL_id_list = 116,                  /* id_list  */
  YYSYMBOL_drop_index_stmt = 117,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 118,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 119,            /* attr_def_list  */
  YYSYMBOL_attr_def = 120,                 /* attr_def  */
  YYSYMBOL_null_def = 121,                 /* null_def  */
  YYSYMBOL_type = 122,                     /* type  */
  YYSYMBOL_insert_stmt = 123,              /* insert_stmt  */
  YYSYMBOL_value_list = 124,               /* value_list  */
  YYSYMBOL_number = 125,                   /* number  */
  YYSYMBOL_float = 126,                    /* float  */
  YYSYMBOL_value = 127,                    /* value  */
  YYSYMBOL_storage_format = 128,           /* storage_format  */
  YYSYMBOL_delete_stmt = 129,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 130,              /* update_stmt  */
  YYSYMBOL_update_target = 131,            /* update_target  */
  YYSYMBOL_update_target_list = 132,       /* update_target_list  */
  YYSYMBOL_select_stmt = 133,              /* select_stmt  */
  YYSYMBOL_sub_select_stmt = 134,          /* sub_select_stmt  */
  YYSYMBOL_calc_stmt = 135,                /* calc_stmt  */
  YYSYMBOL_expression_list = 136,          /* expression_list  */
  YYSYMBOL_limited = 137,                  /* limited  */
  YYSYMBOL_aggre_type = 138,               /* aggre_type  */
  YYSYMBOL_vec_func_type = 139,            /* vec_func_type  */
  YYSYMBOL_expression = 140,               /* expression  */
  YYSYMBOL_query_unit = 141,               /* query_unit  */
  YYSYMBOL_query_list = 142,               /* query_list  */
  YYSYMBOL_relation = 143,                 /* relation  */
  YYSYMBOL_rel_list = 144,                 /* rel_list  */
  YYSYMBOL_where = 145,                    /* where  */
  YYSYMBOL_having = 146,                   /* having  */
  YYSYMBOL_join_list = 147,                /* join_list  */
  YYSYMBOL_order_by_list = 148,            /* order_by_list  */
  YYSYMBOL_order_by = 149,                 /* order_by  */
  YYSYMBOL_order_by_flag = 150,            /* order_by_flag  */
  YYSYMBOL_condition_list = 151,           /* condition_list  */
  YYSYMBOL_condition = 152,                /* condition  */
  YYSYMBOL_comp_op = 153,                  /* comp_op  */
  YYSYMBOL_group_by = 154,                 /* group_by  */
  YYSYMBOL_group_by_unit = 155,            /* group_by_unit  */
  YYSYMBOL_load_data_stmt = 156,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 157,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 158,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 159             /* opt_semicolon  */
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
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   698

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  174
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  366

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   352


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
       2,     2,    99,    97,     2,    98,     2,   100,     2,     2,
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
      95,    96,   101
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   253,   253,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   285,   291,   296,   302,   308,   314,
     320,   327,   333,   341,   357,   379,   395,   398,   410,   420,
     444,   468,   492,   507,   525,   528,   541,   565,   580,   583,
     586,   591,   592,   593,   594,   595,   596,   599,   616,   619,
     631,   634,   640,   643,   649,   653,   657,   661,   670,   676,
     682,   696,   699,   706,   718,   736,   745,   756,   759,   769,
     817,   823,   832,   837,   850,   853,   858,   862,   866,   870,
     874,   881,   885,   889,   896,   900,   904,   915,   919,   925,
     937,   942,   947,   952,   955,   958,   961,   964,   968,   971,
     974,   977,   984,   988,   992,   996,  1000,  1004,  1011,  1014,
    1019,  1026,  1029,  1040,  1045,  1051,  1060,  1063,  1076,  1079,
    1086,  1089,  1095,  1098,  1110,  1113,  1126,  1129,  1142,  1145,
    1149,  1157,  1160,  1166,  1172,  1180,  1189,  1199,  1210,  1220,
    1229,  1238,  1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,
    1259,  1260,  1261,  1262,  1263,  1264,  1269,  1272,  1285,  1288,
    1301,  1314,  1322,  1332,  1333
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
  "LBRACKET", "RBRACKET", "UNIQUE", "ORDER_BY", "WITH", "DISTANCE", "TYPE",
  "LISTS", "PROBES", "LIMIT", "AS", "EQ", "LT", "GT", "LE", "GE", "NE",
  "NUMBER", "FLOAT", "ID", "DATE_STR", "TEXT_STR", "SSS",
  "HIGHER_THAN_EXPRESSION", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "create_vec_index_stmt", "id_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "null_def", "type", "insert_stmt", "value_list", "number", "float",
  "value", "storage_format", "delete_stmt", "update_stmt", "update_target",
  "update_target_list", "select_stmt", "sub_select_stmt", "calc_stmt",
  "expression_list", "limited", "aggre_type", "vec_func_type",
  "expression", "query_unit", "query_list", "relation", "rel_list",
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

#define YYPACT_NINF (-274)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     650,    27,    26,   394,   394,   -64,    10,  -274,    -2,     9,
     -52,  -274,  -274,  -274,  -274,  -274,   -46,     5,   650,    58,
      57,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,   -26,   -23,    64,   112,    28,    47,   394,  -274,
    -274,  -274,  -274,  -274,   125,   142,   161,  -274,   165,   178,
     181,   328,  -274,  -274,   132,  -274,  -274,   394,  -274,  -274,
     191,    56,   -27,   199,  -274,  -274,   123,   136,   188,   163,
     201,  -274,  -274,  -274,  -274,    -8,   209,   167,   169,  -274,
     210,     1,   394,   394,   394,   394,   394,   394,  -274,   328,
    -274,  -274,  -274,  -274,  -274,   -48,  -274,  -274,   231,   -74,
    -274,   344,   394,   394,   394,   394,   394,   171,  -274,   394,
     223,   226,   230,   183,   328,   186,   184,   233,    -9,   200,
     247,   249,   207,  -274,     7,    60,   146,   168,   174,   190,
     231,  -274,  -274,   328,   227,  -274,  -274,  -274,   277,  -274,
     -37,   -37,  -274,  -274,  -274,   199,   211,   282,   292,  -274,
     221,   288,  -274,   276,   291,   302,   243,   301,  -274,   306,
     238,   239,  -274,  -274,   394,   394,   394,   394,   394,   258,
     231,  -274,  -274,  -274,   -66,   309,   328,   187,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,   250,   562,  -274,    37,   318,   139,   183,   230,
     331,  -274,  -274,  -274,  -274,  -274,  -274,   -16,   184,   335,
     272,  -274,   278,   346,   347,    29,    34,    38,    44,    52,
    -274,  -274,   279,  -274,   211,   364,   231,   350,   444,   494,
     292,   292,   301,  -274,  -274,  -274,   288,  -274,   283,   -71,
    -274,  -274,  -274,   302,   325,  -274,   362,   296,   297,  -274,
    -274,  -274,  -274,  -274,  -274,   309,   211,   230,   369,  -274,
    -274,   108,   126,  -274,   108,  -274,  -274,  -274,  -274,   304,
     377,  -274,    -6,   310,   380,   381,   362,  -274,   361,   403,
    -274,    59,   328,    91,    95,    99,   122,   544,   231,    97,
     301,  -274,   362,  -274,   334,   389,   292,   416,   415,   231,
     143,   162,   402,  -274,  -274,  -274,   405,  -274,   364,   394,
     292,   352,   355,  -274,   351,  -274,   198,  -274,   394,   349,
     170,   348,   394,  -274,   -12,   -71,  -274,   366,   198,  -274,
    -274,   409,  -274,   417,  -274,   394,  -274,   372,   -12,   356,
     409,   -38,  -274,  -274,  -274,  -274,   420,   371,   368,   -71,
     429,   373,   376,   -71,   432,  -274
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     173,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,    86,
      87,    89,    90,    88,     0,     0,     0,    97,     0,     0,
       0,     0,    94,    95,   100,    96,    98,     0,   109,    81,
       0,    82,   118,   121,    32,    31,     0,     0,     0,     0,
       0,   171,     1,   174,     2,    71,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
      60,    62,    67,    68,    69,     0,    65,    66,    58,     0,
     108,     0,     0,     0,     0,     0,     0,     0,   120,     0,
       0,     0,   128,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
      58,    61,    63,     0,     0,   101,   102,   110,     0,    83,
     103,   104,   105,   106,   119,   121,     0,     0,   141,    73,
       0,    77,   172,     0,     0,    44,     0,     0,    43,     0,
       0,     0,    38,   112,     0,     0,     0,     0,     0,     0,
      58,    99,   111,   122,   123,   126,     0,     0,   160,   161,
     162,   163,   164,   165,   158,   159,   152,   153,   154,   155,
     156,   157,     0,     0,   129,   142,     0,     0,     0,   128,
       0,    51,    54,    52,    53,    55,    56,    48,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
      70,    59,     0,   124,     0,   132,    58,     0,     0,   145,
     141,   141,     0,   150,    75,    76,    77,    74,     0,     0,
      49,    50,    47,    44,    71,    72,    36,     0,     0,   113,
     114,   117,   116,   115,   125,   126,     0,   128,     0,    80,
     147,   148,     0,   146,   149,   143,   144,    78,   170,     0,
       0,    45,    39,     0,     0,     0,    36,   127,     0,   166,
      57,    97,     0,    94,    95,    96,    98,     0,    58,    48,
       0,    41,    36,    33,     0,     0,   141,     0,   130,    58,
      94,    95,     0,    46,    40,    37,     0,    34,   132,     0,
     141,   134,     0,   151,     0,   133,   168,   131,     0,    84,
      99,     0,     0,   167,   138,     0,    79,     0,   168,   139,
     140,   136,    85,     0,   169,     0,   135,     0,   138,     0,
     136,     0,   137,    93,    92,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -274,  -274,   443,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -273,  -274,  -274,   215,   244,   172,
    -274,  -274,  -133,  -238,  -274,   -90,   216,  -274,  -274,   261,
     228,     2,  -184,  -274,   115,  -274,  -274,  -274,    -3,   353,
     320,  -222,   208,  -199,  -274,   158,  -274,   127,   130,  -225,
    -274,     8,  -274,   141,  -274,  -274,  -274,  -274
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   284,    32,    33,   219,   165,   252,
     217,    34,   144,   106,   107,   108,   128,    35,    36,   161,
     209,   237,   202,    38,    69,   336,    70,   356,   203,    73,
     120,   185,   235,   159,   321,   267,   329,   346,   341,   204,
     205,   206,   308,   333,    39,    40,    41,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,    72,    37,   339,   340,     4,   249,   179,     4,   140,
     247,   280,   265,   305,   126,   275,   276,   232,   145,   100,
      37,    75,   243,   245,   133,   146,   233,   279,    74,   315,
     173,   353,   354,   355,   162,    76,    46,    42,    47,    43,
      78,   127,   141,   142,   288,    91,    79,   231,    77,   250,
     251,    80,   259,   180,   270,   273,   117,   260,    82,    44,
      83,   261,   115,   116,   110,   118,    85,   262,   289,    86,
     113,   114,   115,   116,   167,   263,    87,   300,   240,   241,
     112,   318,   -64,   -64,   174,   113,   114,   115,   116,   134,
     135,   136,   137,   138,   139,   327,   236,   342,   113,   114,
     115,   116,    45,   268,   113,   114,   115,   116,    71,    71,
     150,   151,   152,   153,   -60,   -60,    72,   244,   -62,   -62,
      89,   360,   -67,   -67,    88,   364,   113,   114,   115,   116,
     168,   113,   114,   115,   116,   113,   114,   115,   116,    90,
       4,   113,   114,   115,   116,   -69,   -69,    92,    48,   113,
     114,   115,   116,   113,   114,   115,   116,   113,   114,   115,
     116,   242,   250,   251,    93,   312,   -61,   -61,   109,   221,
     175,   225,   226,   227,   228,   229,   322,    49,    50,    51,
      52,    53,   298,    94,    91,   -63,   -63,    95,    54,    55,
      56,   291,   176,   -70,   -70,    58,    59,    60,   177,   292,
      96,     4,   309,    97,    98,   113,   114,   115,   116,    48,
     238,   239,    99,   111,   178,   121,   293,   294,    64,   295,
     103,   296,   332,   119,   297,    68,   148,   149,   122,   100,
     101,   123,   102,   103,   104,   271,   274,   105,    49,    50,
      51,    52,    53,   113,   114,   115,   116,   124,   125,    54,
      55,    56,    57,   129,   132,   143,    58,    59,    60,   130,
      61,   131,   156,   154,   157,   113,   114,   115,   116,    91,
     158,   113,   114,   115,   116,   160,   164,    62,    63,    64,
      65,   163,    66,   166,   301,    67,    68,   113,   114,   115,
     116,   170,   169,   171,   110,   113,   114,   115,   116,   172,
     182,   181,   314,   184,   186,   207,   188,   189,   190,   191,
     192,   193,   208,   210,   187,     4,   326,   194,   195,   211,
     212,   213,   214,   215,   216,   334,   218,   220,   222,   338,
     223,   224,   230,   234,   196,   197,   198,   199,   200,   201,
     242,   248,   348,    49,    50,    51,    52,    53,   188,   189,
     190,   191,   192,   193,    54,    55,    56,    57,   254,   194,
     195,    58,    59,    60,   255,    61,    48,   147,   257,   258,
     256,   264,   266,   269,   127,   278,   196,   197,   198,   199,
     200,   201,    62,    63,    64,    65,   283,    66,   285,   286,
      67,    68,   290,    98,   141,    49,    50,    51,    52,    53,
     299,    99,   302,   303,   304,   306,    54,    55,    56,    57,
     307,   316,   317,    58,    59,    60,    48,    61,   100,   101,
     319,   102,   103,   104,   320,   323,   105,   324,   328,   330,
     331,   335,   337,   345,    62,    63,    64,    65,   343,    66,
     351,   347,    67,    68,   357,    49,    50,    51,    52,    53,
     349,   358,   359,   361,   362,   365,    54,    55,    56,    57,
     363,    81,   253,    58,    59,    60,   187,    61,   281,   246,
     282,   313,   155,   287,   277,   183,   325,   352,   350,   344,
       0,     0,     0,     0,    62,    63,    64,    65,     0,    66,
       0,     0,    67,    68,     0,    49,    50,    51,    52,    53,
       0,     0,     0,     0,     0,     0,    54,    55,    56,    57,
       0,     0,     0,    58,    59,    60,   272,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,    63,    64,    65,     0,    66,
       0,     0,    67,    68,     0,    49,    50,    51,    52,    53,
       0,     0,     0,     0,     0,     0,    54,    55,    56,    57,
       0,     0,     0,    58,    59,    60,    48,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,    63,    64,    65,     0,    66,
       0,     0,    67,    68,     0,    49,    50,    51,    52,    53,
       0,     0,     0,     0,     0,     0,    54,    55,    56,    57,
       0,     0,     0,    58,    59,    60,     0,    61,   188,   189,
     190,   191,   192,   193,     0,     0,     0,     0,     0,   194,
     195,     0,     0,     0,   310,   311,    64,    65,     0,    66,
       0,     0,    67,    68,     0,     0,   196,   197,   198,   199,
     200,   201,     0,     0,     0,     1,     2,     0,     0,   113,
     114,   115,   116,     3,     4,     0,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,    12,    13,     0,     0,
       0,     0,     0,     0,    14,    15,     0,     0,     0,     0,
       0,     0,     0,    16,     0,    17,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       3,     4,     0,    15,    16,    14,    22,   140,    14,    99,
     209,   249,   234,   286,    22,   240,   241,    83,    92,    90,
      18,    11,   206,   207,    23,    99,    92,    98,    92,   302,
      23,    69,    70,    71,   124,    37,    10,    10,    12,    12,
      92,    49,    90,    91,   266,    48,    92,   180,    39,    65,
      66,    46,    23,   143,   238,   239,    83,    23,     0,    32,
       3,    23,    99,   100,    67,    92,    92,    23,   267,    92,
      97,    98,    99,   100,    83,    23,    12,    83,    41,    42,
      24,   306,    23,    24,    24,    97,    98,    99,   100,    92,
      93,    94,    95,    96,    97,   320,   186,   335,    97,    98,
      99,   100,    75,   236,    97,    98,    99,   100,   111,   112,
     113,   114,   115,   116,    23,    24,   119,   207,    23,    24,
      92,   359,    23,    24,    12,   363,    97,    98,    99,   100,
     128,    97,    98,    99,   100,    97,    98,    99,   100,    92,
      14,    97,    98,    99,   100,    23,    24,    22,    22,    97,
      98,    99,   100,    97,    98,    99,   100,    97,    98,    99,
     100,    22,    65,    66,    22,   298,    23,    24,    36,   167,
      24,   174,   175,   176,   177,   178,   309,    51,    52,    53,
      54,    55,   272,    22,   187,    23,    24,    22,    62,    63,
      64,    65,    24,    23,    24,    69,    70,    71,    24,    73,
      22,    14,   292,    22,    65,    97,    98,    99,   100,    22,
     202,   203,    73,    22,    24,    92,    90,    91,    92,    93,
      94,    95,    24,    24,    98,    99,   111,   112,    92,    90,
      91,    43,    93,    94,    95,   238,   239,    98,    51,    52,
      53,    54,    55,    97,    98,    99,   100,    84,    47,    62,
      63,    64,    65,    44,    44,    24,    69,    70,    71,    92,
      73,    92,    39,    92,    38,    97,    98,    99,   100,   272,
      40,    97,    98,    99,   100,    92,    92,    90,    91,    92,
      93,    95,    95,    50,   282,    98,    99,    97,    98,    99,
     100,    44,    92,    44,   297,    97,    98,    99,   100,    92,
      23,    74,   300,    92,    22,    84,    56,    57,    58,    59,
      60,    61,    24,    37,    22,    14,   319,    67,    68,    28,
      29,    30,    31,    32,    33,   328,    24,    84,    22,   332,
      92,    92,    74,    24,    84,    85,    86,    87,    88,    89,
      22,    10,   345,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    23,    67,
      68,    69,    70,    71,    92,    73,    22,    23,    22,    22,
      92,    92,     8,    23,    49,    92,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    24,    95,    92,    92,
      98,    99,    23,    65,    90,    51,    52,    53,    54,    55,
      23,    73,    92,    23,    23,    44,    62,    63,    64,    65,
       7,    77,    23,    69,    70,    71,    22,    73,    90,    91,
       4,    93,    94,    95,     9,    23,    98,    22,    76,    74,
      79,    82,    84,    24,    90,    91,    92,    93,    72,    95,
      84,    24,    98,    99,    24,    51,    52,    53,    54,    55,
      78,    80,    84,    24,    81,    23,    62,    63,    64,    65,
      84,    18,   218,    69,    70,    71,    22,    73,   253,   208,
     254,   299,   119,   265,   246,   155,   318,   350,   348,   338,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,    -1,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      -1,    -1,    -1,    69,    70,    71,    22,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,    -1,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      -1,    -1,    -1,    69,    70,    71,    22,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,    -1,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      -1,    -1,    -1,    69,    70,    71,    -1,    73,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      68,    -1,    -1,    -1,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,    -1,    -1,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,     5,     6,    -1,    -1,    97,
      98,    99,   100,    13,    14,    -1,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    13,    14,    16,    17,    18,    19,    20,
      21,    25,    26,    27,    34,    35,    43,    45,    48,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   117,   118,   123,   129,   130,   133,   135,   156,
     157,   158,    10,    12,    32,    75,    10,    12,    22,    51,
      52,    53,    54,    55,    62,    63,    64,    65,    69,    70,
      71,    73,    90,    91,    92,    93,    95,    98,    99,   136,
     138,   140,   140,   141,    92,    11,    37,    39,    92,    92,
      46,   104,     0,     3,   159,    92,    92,    12,    12,    92,
      92,   140,    22,    22,    22,    22,    22,    22,    65,    73,
      90,    91,    93,    94,    95,    98,   125,   126,   127,    36,
     140,    22,    24,    97,    98,    99,   100,    83,    92,    24,
     142,    92,    92,    43,    84,    47,    22,    49,   128,    44,
      92,    92,    44,    23,   140,   140,   140,   140,   140,   140,
     127,    90,    91,    24,   124,    92,    99,    23,   136,   136,
     140,   140,   140,   140,    92,   141,    39,    38,    40,   145,
      92,   131,   127,    95,    92,   120,    50,    83,   133,    92,
      44,    44,    92,    23,    24,    24,    24,    24,    24,   124,
     127,    74,    23,   142,    92,   143,    22,    22,    56,    57,
      58,    59,    60,    61,    67,    68,    84,    85,    86,    87,
      88,    89,   134,   140,   151,   152,   153,    84,    24,   132,
      37,    28,    29,    30,    31,    32,    33,   122,    24,   119,
      84,   133,    22,    92,    92,   140,   140,   140,   140,   140,
      74,   124,    83,    92,    24,   144,   127,   133,   153,   153,
      41,    42,    22,   134,   127,   134,   131,   145,    10,    22,
      65,    66,   121,   120,    23,    92,    92,    22,    22,    23,
      23,    23,    23,    23,    92,   143,     8,   147,   124,    23,
     134,   140,    22,   134,   140,   151,   151,   132,    92,    98,
     125,   119,   128,    24,   116,    92,    92,   144,   143,   145,
      23,    65,    73,    90,    91,    93,    95,    98,   127,    23,
      83,   133,    92,    23,    23,   116,    44,     7,   154,   127,
      90,    91,   124,   121,   133,   116,    77,    23,   151,     4,
       9,   146,   124,    23,    22,   147,   140,   151,    76,   148,
      74,    79,    24,   155,   140,    82,   137,    84,   140,    15,
      16,   150,   125,    72,   155,    24,   149,    24,   140,    78,
     150,    84,   149,    69,    70,    71,   139,    24,    80,    84,
     125,    24,    81,    84,   125,    23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   114,   115,   116,   116,   117,   118,
     118,   118,   118,   118,   119,   119,   120,   120,   121,   121,
     121,   122,   122,   122,   122,   122,   122,   123,   124,   124,
     125,   125,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   129,   130,   131,   131,   132,   132,   133,
     134,   135,   136,   136,   137,   137,   138,   138,   138,   138,
     138,   139,   139,   139,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   141,   141,
     141,   142,   142,   143,   143,   143,   144,   144,   145,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   150,   150,
     150,   151,   151,   151,   151,   152,   152,   152,   152,   152,
     152,   152,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   154,   154,   155,   155,
     156,   157,   158,   159,   159
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,    27,     0,     3,     5,     8,
      10,     9,     6,     5,     0,     3,     6,     3,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     8,     0,     3,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       4,     0,     4,     4,     6,     3,     3,     0,     3,    12,
       3,     2,     1,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       3,     4,     4,     6,     6,     6,     6,     6,     1,     3,
       2,     0,     3,     1,     2,     3,     0,     3,     0,     2,
       0,     2,     0,     5,     0,     4,     0,     4,     0,     1,
       1,     0,     1,     3,     3,     2,     3,     3,     3,     3,
       2,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     3,
       7,     2,     4,     0,     1
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
#line 254 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2005 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 285 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 291 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2022 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 296 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 302 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2038 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 308 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2046 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 314 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 320 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 327 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 333 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2082 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 342 "yacc_sql.y"
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
#line 2102 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 358 "yacc_sql.y"
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
#line 2125 "yacc_sql.cpp"
    break;

  case 35: /* create_vec_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE ID RBRACE WITH LBRACE TYPE EQ IVFFLAT COMMA DISTANCE EQ vec_func_type COMMA LISTS EQ number COMMA PROBES EQ number RBRACE  */
#line 379 "yacc_sql.y"
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
#line 2143 "yacc_sql.cpp"
    break;

  case 36: /* id_list: %empty  */
#line 395 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2151 "yacc_sql.cpp"
    break;

  case 37: /* id_list: COMMA ID id_list  */
#line 398 "yacc_sql.y"
                        { 
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2165 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 411 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2177 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 421 "yacc_sql.y"
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
#line 2205 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format AS select_stmt  */
#line 445 "yacc_sql.y"
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
#line 2233 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 469 "yacc_sql.y"
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
#line 2261 "yacc_sql.cpp"
    break;

  case 42: /* create_table_stmt: CREATE TABLE ID storage_format AS select_stmt  */
#line 493 "yacc_sql.y"
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
#line 2280 "yacc_sql.cpp"
    break;

  case 43: /* create_table_stmt: CREATE TABLE ID storage_format select_stmt  */
#line 508 "yacc_sql.y"
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
#line 2299 "yacc_sql.cpp"
    break;

  case 44: /* attr_def_list: %empty  */
#line 525 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2307 "yacc_sql.cpp"
    break;

  case 45: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 529 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2321 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 542 "yacc_sql.y"
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
#line 2349 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID type null_def  */
#line 566 "yacc_sql.y"
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
#line 2366 "yacc_sql.cpp"
    break;

  case 48: /* null_def: %empty  */
#line 580 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2374 "yacc_sql.cpp"
    break;

  case 49: /* null_def: NULLABLE  */
#line 583 "yacc_sql.y"
               {
      (yyval.boolean) = true;
    }
#line 2382 "yacc_sql.cpp"
    break;

  case 50: /* null_def: UNNULLABLE  */
#line 586 "yacc_sql.y"
                 {
      (yyval.boolean) = false;
    }
#line 2390 "yacc_sql.cpp"
    break;

  case 51: /* type: INT_T  */
#line 591 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2396 "yacc_sql.cpp"
    break;

  case 52: /* type: STRING_T  */
#line 592 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2402 "yacc_sql.cpp"
    break;

  case 53: /* type: FLOAT_T  */
#line 593 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2408 "yacc_sql.cpp"
    break;

  case 54: /* type: DATE_T  */
#line 594 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATE); }
#line 2414 "yacc_sql.cpp"
    break;

  case 55: /* type: VECTOR_T  */
#line 595 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2420 "yacc_sql.cpp"
    break;

  case 56: /* type: TEXT_T  */
#line 596 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXT); }
#line 2426 "yacc_sql.cpp"
    break;

  case 57: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 600 "yacc_sql.y"
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
#line 2443 "yacc_sql.cpp"
    break;

  case 58: /* value_list: %empty  */
#line 616 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 619 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2465 "yacc_sql.cpp"
    break;

  case 60: /* number: NUMBER  */
#line 631 "yacc_sql.y"
           {
      (yyval.number) = (yyvsp[0].number);
    }
#line 2473 "yacc_sql.cpp"
    break;

  case 61: /* number: '-' NUMBER  */
#line 634 "yacc_sql.y"
                 {
      (yyval.number) = -(yyvsp[0].number);
    }
#line 2481 "yacc_sql.cpp"
    break;

  case 62: /* float: FLOAT  */
#line 640 "yacc_sql.y"
          {
      (yyval.floats) = (yyvsp[0].floats);
    }
#line 2489 "yacc_sql.cpp"
    break;

  case 63: /* float: '-' FLOAT  */
#line 643 "yacc_sql.y"
                {
      (yyval.floats) = -(yyvsp[0].floats);
    }
#line 2497 "yacc_sql.cpp"
    break;

  case 64: /* value: NULLABLE  */
#line 649 "yacc_sql.y"
             {
      (yyval.value) = new Value(string("ckk is stupid!"), 114514);
      (yyloc) = (yylsp[0]);
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 65: /* value: number  */
#line 653 "yacc_sql.y"
            {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 66: /* value: float  */
#line 657 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 67: /* value: DATE_STR  */
#line 661 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);  // 去掉首尾的引号
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);    //sscanf会自动转换字符串中的数字，不用显式stoi
      int date_num = year * 10000 + month * 100 + day;
      (yyval.value) = new Value(date_num, true);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 68: /* value: TEXT_STR  */
#line 670 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, strlen(tmp));
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2549 "yacc_sql.cpp"
    break;

  case 69: /* value: SSS  */
#line 676 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, strlen(tmp));  
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2560 "yacc_sql.cpp"
    break;

  case 70: /* value: LBRACKET value value_list RBRACKET  */
#line 682 "yacc_sql.y"
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
#line 2576 "yacc_sql.cpp"
    break;

  case 71: /* storage_format: %empty  */
#line 696 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2584 "yacc_sql.cpp"
    break;

  case 72: /* storage_format: STORAGE FORMAT EQ ID  */
#line 700 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2592 "yacc_sql.cpp"
    break;

  case 73: /* delete_stmt: DELETE FROM ID where  */
#line 707 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2606 "yacc_sql.cpp"
    break;

  case 74: /* update_stmt: UPDATE ID SET update_target update_target_list where  */
#line 719 "yacc_sql.y"
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
#line 2625 "yacc_sql.cpp"
    break;

  case 75: /* update_target: ID EQ value  */
#line 737 "yacc_sql.y"
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->value = *(yyvsp[0].value);
      (yyval.update_target)->is_value = true;

      delete (yyvsp[0].value);
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 76: /* update_target: ID EQ sub_select_stmt  */
#line 746 "yacc_sql.y"
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->sub_select = (yyvsp[0].sql_node);
      (yyval.update_target)->is_value = false;
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 77: /* update_target_list: %empty  */
#line 756 "yacc_sql.y"
    {
      (yyval.update_target_list) = nullptr;
    }
#line 2657 "yacc_sql.cpp"
    break;

  case 78: /* update_target_list: COMMA update_target update_target_list  */
#line 760 "yacc_sql.y"
    {
      if((yyvsp[0].update_target_list) == nullptr)
        (yyval.update_target_list) = new std::vector<UpdateTarget>;
      else (yyval.update_target_list) = (yyvsp[0].update_target_list);
      (yyval.update_target_list)->emplace_back(*(yyvsp[-1].update_target));
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 79: /* select_stmt: SELECT query_unit query_list FROM relation rel_list join_list where group_by having order_by_list limited  */
#line 770 "yacc_sql.y"
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
#line 2718 "yacc_sql.cpp"
    break;

  case 80: /* sub_select_stmt: LBRACE select_stmt RBRACE  */
#line 818 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 81: /* calc_stmt: CALC expression_list  */
#line 824 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2736 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression  */
#line 833 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 83: /* expression_list: expression COMMA expression_list  */
#line 838 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 84: /* limited: %empty  */
#line 850 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 85: /* limited: LIMIT number  */
#line 853 "yacc_sql.y"
                   {
      (yyval.number) = (yyvsp[0].number);
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 86: /* aggre_type: MAX  */
#line 858 "yacc_sql.y"
        { 
      const char * result = "MAX";
      (yyval.aggre_type) = result; 
    }
#line 2783 "yacc_sql.cpp"
    break;

  case 87: /* aggre_type: MIN  */
#line 862 "yacc_sql.y"
          { 
      const char * result = "MIN";
      (yyval.aggre_type) = result; 
    }
#line 2792 "yacc_sql.cpp"
    break;

  case 88: /* aggre_type: COUNT  */
#line 866 "yacc_sql.y"
            { 
      const char * result = "COUNT";
      (yyval.aggre_type) = result; 
    }
#line 2801 "yacc_sql.cpp"
    break;

  case 89: /* aggre_type: AVG  */
#line 870 "yacc_sql.y"
          { 
      const char * result = "AVG";
      (yyval.aggre_type) = result; 
    }
#line 2810 "yacc_sql.cpp"
    break;

  case 90: /* aggre_type: SUM  */
#line 874 "yacc_sql.y"
          { 
      const char * result = "SUM";
      (yyval.aggre_type) = result; 
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 91: /* vec_func_type: VEC_INNER_PRODUCT  */
#line 881 "yacc_sql.y"
                      { 
      const char * result = "INNER_PRODUCT";
      (yyval.vec_func_type) = result; 
    }
#line 2828 "yacc_sql.cpp"
    break;

  case 92: /* vec_func_type: VEC_COSINE_DISTANCE  */
#line 885 "yacc_sql.y"
                          { 
      const char * result = "COSINE_DISTANCE";
      (yyval.vec_func_type) = result; 
    }
#line 2837 "yacc_sql.cpp"
    break;

  case 93: /* vec_func_type: VEC_L2_DISTANCE  */
#line 889 "yacc_sql.y"
                      { 
      const char * result = "L2_DISTANCE";
      (yyval.vec_func_type) = result; 
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 94: /* expression: NUMBER  */
#line 896 "yacc_sql.y"
           {
      (yyval.expression) = new ValueExpr(Value((yyvsp[0].number)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 95: /* expression: FLOAT  */
#line 900 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(Value((yyvsp[0].floats)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 96: /* expression: DATE_STR  */
#line 904 "yacc_sql.y"
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
#line 2880 "yacc_sql.cpp"
    break;

  case 97: /* expression: NULLABLE  */
#line 915 "yacc_sql.y"
               {
      (yyval.expression) = new ValueExpr(Value(string("dmx is handsome"), 114514));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2889 "yacc_sql.cpp"
    break;

  case 98: /* expression: SSS  */
#line 919 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.expression) = new ValueExpr(Value(tmp));
      free(tmp);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 99: /* expression: LBRACKET value value_list RBRACKET  */
#line 925 "yacc_sql.y"
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
#line 2917 "yacc_sql.cpp"
    break;

  case 100: /* expression: ID  */
#line 937 "yacc_sql.y"
         {
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 2927 "yacc_sql.cpp"
    break;

  case 101: /* expression: ID DOT ID  */
#line 942 "yacc_sql.y"
                {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
#line 2937 "yacc_sql.cpp"
    break;

  case 102: /* expression: ID DOT '*'  */
#line 947 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 103: /* expression: expression '+' expression  */
#line 952 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2955 "yacc_sql.cpp"
    break;

  case 104: /* expression: expression '-' expression  */
#line 955 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2963 "yacc_sql.cpp"
    break;

  case 105: /* expression: expression '*' expression  */
#line 958 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 106: /* expression: expression '/' expression  */
#line 961 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2979 "yacc_sql.cpp"
    break;

  case 107: /* expression: LBRACE expression RBRACE  */
#line 964 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2988 "yacc_sql.cpp"
    break;

  case 108: /* expression: '-' expression  */
#line 968 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2996 "yacc_sql.cpp"
    break;

  case 109: /* expression: '*'  */
#line 971 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 3004 "yacc_sql.cpp"
    break;

  case 110: /* expression: aggre_type LBRACE RBRACE  */
#line 974 "yacc_sql.y"
                               {
      (yyval.expression) = create_aggregate_expression((yyvsp[-2].aggre_type), nullptr, sql_string, &(yyloc));
    }
#line 3012 "yacc_sql.cpp"
    break;

  case 111: /* expression: aggre_type LBRACE expression_list RBRACE  */
#line 977 "yacc_sql.y"
                                               {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression((yyvsp[-3].aggre_type), nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression((yyvsp[-3].aggre_type), (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 3024 "yacc_sql.cpp"
    break;

  case 112: /* expression: LENGTH LBRACE expression RBRACE  */
#line 984 "yacc_sql.y"
                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, nullptr, nullptr, (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3033 "yacc_sql.cpp"
    break;

  case 113: /* expression: ROUND LBRACE expression COMMA expression RBRACE  */
#line 988 "yacc_sql.y"
                                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, (yyvsp[-1].expression), nullptr, (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3042 "yacc_sql.cpp"
    break;

  case 114: /* expression: DATE_FORMAT LBRACE expression COMMA expression RBRACE  */
#line 992 "yacc_sql.y"
                                                            {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, nullptr, (yyvsp[-1].expression), (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 115: /* expression: VEC_INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 996 "yacc_sql.y"
                                                                  {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 116: /* expression: VEC_COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1000 "yacc_sql.y"
                                                                    {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3069 "yacc_sql.cpp"
    break;

  case 117: /* expression: VEC_L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 1004 "yacc_sql.y"
                                                                {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3078 "yacc_sql.cpp"
    break;

  case 118: /* query_unit: expression  */
#line 1011 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3086 "yacc_sql.cpp"
    break;

  case 119: /* query_unit: expression AS ID  */
#line 1014 "yacc_sql.y"
                       {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), (yyvsp[-2].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 3096 "yacc_sql.cpp"
    break;

  case 120: /* query_unit: expression ID  */
#line 1019 "yacc_sql.y"
                    {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 3106 "yacc_sql.cpp"
    break;

  case 121: /* query_list: %empty  */
#line 1026 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3114 "yacc_sql.cpp"
    break;

  case 122: /* query_list: COMMA query_unit query_list  */
#line 1029 "yacc_sql.y"
                                  {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 123: /* relation: ID  */
#line 1040 "yacc_sql.y"
       {
      (yyval.expression) = new UnboundTableExpr((yyvsp[0].string), string());
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 3138 "yacc_sql.cpp"
    break;

  case 124: /* relation: ID ID  */
#line 1045 "yacc_sql.y"
            {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), new UnboundTableExpr((yyvsp[-1].string), (yyvsp[0].string)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3149 "yacc_sql.cpp"
    break;

  case 125: /* relation: ID AS ID  */
#line 1051 "yacc_sql.y"
               {
      (yyval.expression) = new AliasExpr((yyvsp[0].string), new UnboundTableExpr((yyvsp[-2].string), (yyvsp[0].string)));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3160 "yacc_sql.cpp"
    break;

  case 126: /* rel_list: %empty  */
#line 1060 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3168 "yacc_sql.cpp"
    break;

  case 127: /* rel_list: COMMA relation rel_list  */
#line 1063 "yacc_sql.y"
                              {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3182 "yacc_sql.cpp"
    break;

  case 128: /* where: %empty  */
#line 1076 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3190 "yacc_sql.cpp"
    break;

  case 129: /* where: WHERE condition_list  */
#line 1079 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3198 "yacc_sql.cpp"
    break;

  case 130: /* having: %empty  */
#line 1086 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3206 "yacc_sql.cpp"
    break;

  case 131: /* having: HAVING condition_list  */
#line 1089 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3214 "yacc_sql.cpp"
    break;

  case 132: /* join_list: %empty  */
#line 1095 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3222 "yacc_sql.cpp"
    break;

  case 133: /* join_list: INNER_JOIN relation ON condition_list join_list  */
#line 1098 "yacc_sql.y"
                                                      {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(new JoinTableExpr(*(yyvsp[-1].condition_list), (yyvsp[-3].expression)));
    }
#line 3235 "yacc_sql.cpp"
    break;

  case 134: /* order_by_list: %empty  */
#line 1110 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3243 "yacc_sql.cpp"
    break;

  case 135: /* order_by_list: ORDER_BY expression order_by_flag order_by  */
#line 1114 "yacc_sql.y"
    {
       if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
#line 3256 "yacc_sql.cpp"
    break;

  case 136: /* order_by: %empty  */
#line 1126 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3264 "yacc_sql.cpp"
    break;

  case 137: /* order_by: COMMA expression order_by_flag order_by  */
#line 1130 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
#line 3277 "yacc_sql.cpp"
    break;

  case 138: /* order_by_flag: %empty  */
#line 1142 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3285 "yacc_sql.cpp"
    break;

  case 139: /* order_by_flag: ASC  */
#line 1146 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3293 "yacc_sql.cpp"
    break;

  case 140: /* order_by_flag: DESC  */
#line 1150 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 3301 "yacc_sql.cpp"
    break;

  case 141: /* condition_list: %empty  */
#line 1157 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3309 "yacc_sql.cpp"
    break;

  case 142: /* condition_list: condition  */
#line 1160 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyvsp[0].condition)->conjuction_type = 0;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3320 "yacc_sql.cpp"
    break;

  case 143: /* condition_list: condition AND condition_list  */
#line 1166 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjuction_type = 1;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3331 "yacc_sql.cpp"
    break;

  case 144: /* condition_list: condition OR condition_list  */
#line 1172 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjuction_type = 2;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3342 "yacc_sql.cpp"
    break;

  case 145: /* condition: expression comp_op  */
#line 1181 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[0].comp);
      (yyval.condition)->left_expression = (yyvsp[-1].expression);
      (yyval.condition)->right_expression = new ValueExpr(Value(114514));
    }
#line 3355 "yacc_sql.cpp"
    break;

  case 146: /* condition: expression comp_op sub_select_stmt  */
#line 1190 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->right_expression = nullptr;
    }
#line 3369 "yacc_sql.cpp"
    break;

  case 147: /* condition: sub_select_stmt comp_op sub_select_stmt  */
#line 1200 "yacc_sql.y"
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
#line 3384 "yacc_sql.cpp"
    break;

  case 148: /* condition: sub_select_stmt comp_op expression  */
#line 1211 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = true;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_sub_query = (yyvsp[-2].sql_node);
      (yyval.condition)->left_expression = nullptr;
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
#line 3398 "yacc_sql.cpp"
    break;

  case 149: /* condition: expression comp_op expression  */
#line 1221 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
#line 3411 "yacc_sql.cpp"
    break;

  case 150: /* condition: comp_op sub_select_stmt  */
#line 1230 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = new ValueExpr(Value(114514));
    }
#line 3424 "yacc_sql.cpp"
    break;

  case 151: /* condition: expression comp_op LBRACE value value_list RBRACE  */
#line 1239 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-4].comp);
      (yyval.condition)->left_expression = (yyvsp[-5].expression);
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.condition)->right_expression = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 3438 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: EQ  */
#line 1251 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3444 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: LT  */
#line 1252 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3450 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: GT  */
#line 1253 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3456 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: LE  */
#line 1254 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3462 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: GE  */
#line 1255 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3468 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: NE  */
#line 1256 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3474 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: IS_NULL  */
#line 1257 "yacc_sql.y"
              { (yyval.comp) = XXX_IS_NULL; }
#line 3480 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: IS_NOT_NULL  */
#line 1258 "yacc_sql.y"
                  { (yyval.comp) = XXX_IS_NOT_NULL; }
#line 3486 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: NOT_LIKE  */
#line 1259 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_XXX; }
#line 3492 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: LIKE  */
#line 1260 "yacc_sql.y"
           { (yyval.comp) = LIKE_XXX; }
#line 3498 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: NOT_IN  */
#line 1261 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_XXX; }
#line 3504 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: IN  */
#line 1262 "yacc_sql.y"
         { (yyval.comp) = IN_XXX; }
#line 3510 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: NOT_EXISTS  */
#line 1263 "yacc_sql.y"
                 { (yyval.comp) = XXX_NOT_EXISTS; }
#line 3516 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: EXISTS  */
#line 1264 "yacc_sql.y"
             { (yyval.comp) = XXX_EXISTS; }
#line 3522 "yacc_sql.cpp"
    break;

  case 166: /* group_by: %empty  */
#line 1269 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3530 "yacc_sql.cpp"
    break;

  case 167: /* group_by: GROUP BY expression group_by_unit  */
#line 1272 "yacc_sql.y"
                                        {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3544 "yacc_sql.cpp"
    break;

  case 168: /* group_by_unit: %empty  */
#line 1285 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3552 "yacc_sql.cpp"
    break;

  case 169: /* group_by_unit: COMMA expression group_by_unit  */
#line 1289 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3566 "yacc_sql.cpp"
    break;

  case 170: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1302 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3580 "yacc_sql.cpp"
    break;

  case 171: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1315 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3589 "yacc_sql.cpp"
    break;

  case 172: /* set_variable_stmt: SET ID EQ value  */
#line 1323 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3601 "yacc_sql.cpp"
    break;


#line 3605 "yacc_sql.cpp"

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

#line 1335 "yacc_sql.y"

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
