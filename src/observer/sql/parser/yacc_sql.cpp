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
  YYSYMBOL_join_list = 130,                /* join_list  */
  YYSYMBOL_order_by_list = 131,            /* order_by_list  */
  YYSYMBOL_order_by = 132,                 /* order_by  */
  YYSYMBOL_order_by_flag = 133,            /* order_by_flag  */
  YYSYMBOL_condition_list = 134,           /* condition_list  */
  YYSYMBOL_condition = 135,                /* condition  */
  YYSYMBOL_comp_op = 136,                  /* comp_op  */
  YYSYMBOL_group_by = 137,                 /* group_by  */
  YYSYMBOL_group_by_unit = 138,            /* group_by_unit  */
  YYSYMBOL_load_data_stmt = 139,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 140,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 141,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 142             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   790

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  322

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   342


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
       2,     2,    89,    87,     2,    88,     2,    90,     2,     2,
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
      85,    86,    91
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   235,   235,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   266,   273,   279,   286,   293,   300,   307,
     315,   322,   331,   348,   372,   376,   389,   400,   424,   448,
     472,   487,   505,   508,   521,   535,   546,   549,   552,   556,
     559,   560,   561,   562,   563,   566,   584,   588,   600,   604,
     609,   613,   618,   622,   631,   637,   651,   654,   661,   674,
     692,   701,   712,   715,   725,   730,   771,   777,   786,   791,
     802,   808,   813,   818,   823,   828,   833,   838,   842,   846,
     849,   852,   856,   859,   864,   867,   870,   873,   876,   879,
     882,   889,   896,   903,   910,   917,   921,   925,   929,   933,
     937,   944,   949,   955,   964,   967,   980,   983,   990,   993,
     999,  1002,  1014,  1017,  1030,  1033,  1046,  1049,  1053,  1061,
    1064,  1069,  1076,  1085,  1095,  1106,  1116,  1125,  1134,  1147,
    1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,
    1158,  1159,  1160,  1165,  1168,  1181,  1184,  1197,  1211,  1220,
    1231,  1232
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
  "VECTOR_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE",
  "FORMAT", "MAX", "MIN", "AVG", "SUM", "COUNT", "NOT_LIKE", "LIKE",
  "NOT_IN", "IN", "NOT_EXISTS", "EXISTS", "LENGTH", "ROUND", "DATE_FORMAT",
  "NULLABLE", "UNNULLABLE", "IS_NULL", "IS_NOT_NULL", "VEC_L2_DISTANCE",
  "VEC_COSINE_DISTANCE_FUNC", "VEC_INNER_PRODUCT_FUNC", "LBRACKET",
  "RBRACKET", "UNIQUE", "ORDER_BY", "AS", "EQ", "LT", "GT", "LE", "GE",
  "NE", "NUMBER", "FLOAT", "ID", "DATE_STR", "SSS",
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

#define YYPACT_NINF (-253)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-57)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     707,    -3,    95,   500,   500,   -66,    18,  -253,    -2,    22,
      10,  -253,  -253,  -253,  -253,  -253,    21,    70,   707,   112,
     116,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,    47,    56,   129,    59,    60,   500,   124,   125,   131,
     137,   159,   164,   165,   166,  -253,   171,   180,   187,   192,
    -253,  -253,    80,  -253,  -253,   542,  -253,  -253,  -253,    68,
     174,  -253,  -253,   130,   141,   121,   139,   186,  -253,  -253,
    -253,  -253,   -10,   190,   154,  -253,   199,   -17,   290,   332,
     374,   416,   458,   500,   500,   500,   500,   500,   500,   -41,
     218,   -27,   169,  -253,  -253,  -253,  -253,   500,   500,   500,
     500,   500,   170,   210,   209,   182,   192,   181,   184,   201,
      -6,   185,   212,   188,  -253,  -253,   252,  -253,   255,  -253,
     258,  -253,   259,  -253,   260,    -7,    79,    89,   128,   140,
     146,  -253,  -253,   192,   213,   -55,  -253,  -253,  -253,    -4,
      -4,  -253,  -253,   -47,   261,   264,   241,  -253,   230,   263,
    -253,   278,   228,   291,   253,   274,  -253,   305,   248,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,   500,   500,   500,   500,
     500,   218,  -253,   249,  -253,   250,  -253,   170,   326,   192,
     122,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,   -33,   700,  -253,   295,   314,
     138,   182,   209,   327,  -253,  -253,  -253,  -253,  -253,    -9,
     184,   315,   262,  -253,   265,   322,     8,    12,    34,    38,
      61,  -253,  -253,  -253,   261,   170,   209,   218,   323,   584,
     626,   241,   274,  -253,  -253,  -253,   263,  -253,   266,   275,
    -253,  -253,  -253,   291,   300,  -253,   337,   279,  -253,  -253,
    -253,  -253,  -253,  -253,   321,   357,   342,  -253,  -253,   110,
     122,  -253,   110,  -253,  -253,  -253,  -253,   343,  -253,     1,
     284,   345,   337,   241,   365,   361,  -253,    86,    54,   274,
    -253,   337,  -253,   353,   326,   500,   241,   304,   363,  -253,
    -253,  -253,  -253,  -253,   156,  -253,   500,  -253,  -253,   500,
    -253,   -11,   156,  -253,  -253,   356,  -253,   500,  -253,   -11,
     356,  -253
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     160,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
      59,    60,    80,    63,    64,     0,    94,    93,    77,    78,
      74,    31,    30,     0,     0,     0,     0,     0,   158,     1,
     161,     2,    66,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,     0,     0,    83,    59,    60,    92,     0,     0,     0,
       0,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    95,     0,    96,     0,    97,
       0,    98,     0,    99,     0,     0,     0,     0,     0,     0,
       0,    61,    62,     0,     0,    81,    82,    84,    79,    87,
      88,    89,    90,   111,   114,     0,   129,    68,     0,    72,
     159,     0,     0,    42,     0,     0,    41,     0,     0,    36,
     100,   101,   103,   104,   102,   105,     0,     0,     0,     0,
       0,    56,    65,     0,    85,     0,   112,     0,   120,     0,
       0,   147,   148,   149,   150,   151,   152,   145,   146,   139,
     140,   141,   142,   143,   144,     0,     0,   117,   130,     0,
       0,     0,   116,     0,    50,    53,    51,    52,    54,    46,
       0,     0,     0,    40,     0,     0,     0,     0,     0,     0,
       0,    57,    86,   113,   114,     0,   116,    56,     0,     0,
     132,   129,     0,   137,    70,    71,    72,    69,     0,     0,
      47,    48,    45,    42,    66,    67,    34,     0,   106,   107,
     110,   109,   108,   115,     0,   153,     0,    76,   134,   135,
       0,   133,   136,   131,    73,   157,    49,     0,    43,    37,
       0,     0,    34,   129,     0,   118,    55,    93,    46,     0,
      39,    34,    32,     0,   120,     0,   129,   122,     0,    44,
      38,    35,    33,   121,   155,   119,     0,    75,   138,     0,
     154,   126,   155,   127,   128,   124,   156,     0,   123,   126,
     124,   125
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -253,  -253,   369,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -252,  -253,  -253,   135,   178,   101,  -253,
    -253,  -253,  -179,   -49,   136,  -253,  -253,   193,   145,     0,
      30,  -253,    -1,   -45,  -176,   172,  -198,  -253,   109,  -253,
      85,    88,  -167,  -253,   -68,  -253,    96,  -253,  -253,  -253,
    -253
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   281,    31,    32,   221,   163,   252,   277,
     219,    33,   144,    67,   120,    34,    35,   159,   212,   238,
     205,    37,    68,    69,   154,   188,   157,   297,   236,   307,
     318,   315,   207,   208,   209,   285,   310,    38,    39,    40,
      81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    87,   231,    70,   313,   314,   124,    41,     4,    42,
     100,   234,   118,   249,   247,     4,   175,    71,    36,   183,
     106,   191,   192,   193,   194,   195,   196,   185,   184,    72,
     293,   258,   197,   198,    73,   259,   186,   119,   265,   301,
     141,   142,   199,   200,   201,   202,   203,   204,   135,   136,
     137,   138,   139,   140,   250,   251,   145,   260,   266,   264,
      74,   261,   146,   149,   150,   151,   152,   160,   165,    43,
     108,   109,   110,   111,   273,   289,   108,   109,   110,   111,
     108,   109,   110,   111,   262,   110,   111,   126,   128,   130,
     132,   134,   107,    75,   181,   108,   109,   110,   111,   108,
     109,   110,   111,   176,    76,    44,   148,    45,   298,   -56,
     143,   206,    79,   177,    77,   101,   294,   250,   251,    80,
     166,   108,   109,   110,   111,   108,   109,   110,   111,   305,
      82,   226,   227,   228,   229,   230,     4,   239,   240,    83,
     237,    84,    85,    86,    46,    87,    88,    89,   108,   109,
     110,   111,   178,    90,   102,   108,   109,   110,   111,    91,
     242,   244,   115,   103,   179,   223,   108,   109,   110,   111,
     180,    47,    48,    49,    50,    51,   108,   109,   110,   111,
     309,    92,    52,    53,    54,    55,    93,    94,    95,    56,
      57,    58,    59,    96,   269,   272,   206,   108,   109,   110,
     111,    55,    97,    60,    61,    62,    63,    64,    59,    98,
      65,    66,   112,   113,   116,   108,   109,   110,   111,    60,
      61,   287,    63,    64,   114,    87,    99,   108,   109,   110,
     111,   117,   121,   108,   109,   110,   111,   122,   206,   243,
     245,   123,   143,   108,   109,   110,   111,   155,   156,   164,
     304,   206,   147,   153,   168,    55,   214,   215,   216,   217,
     218,   311,    59,   190,   312,   158,   161,   162,   167,   268,
     271,   169,   319,    60,    61,   170,    63,    64,   171,   290,
      99,   172,   173,   174,   182,   187,   189,   211,     4,   300,
      47,    48,    49,    50,    51,   191,   192,   193,   194,   195,
     196,    52,    53,    54,    55,   210,   197,   198,    56,    57,
      58,    59,    46,   125,   213,   220,   199,   200,   201,   202,
     203,   204,    60,    61,    62,    63,    64,   224,   222,    65,
      66,   225,   232,   233,   235,   241,   242,   248,   254,    47,
      48,    49,    50,    51,   257,   255,   267,   119,   256,   275,
      52,    53,    54,    55,    46,   127,   276,    56,    57,    58,
      59,   280,   282,   283,   284,   286,   288,   291,   292,   295,
     296,    60,    61,    62,    63,    64,   302,   306,    65,    66,
     317,    47,    48,    49,    50,    51,   308,    78,   278,   299,
     279,   274,    52,    53,    54,    55,    46,   129,   253,    56,
      57,    58,    59,   303,   246,   321,   263,   320,   316,     0,
       0,     0,     0,    60,    61,    62,    63,    64,     0,     0,
      65,    66,     0,    47,    48,    49,    50,    51,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,    46,   131,
       0,    56,    57,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    61,    62,    63,    64,
       0,     0,    65,    66,     0,    47,    48,    49,    50,    51,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
      46,   133,     0,    56,    57,    58,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,    61,    62,
      63,    64,     0,     0,    65,    66,     0,    47,    48,    49,
      50,    51,     0,     0,     0,     0,     0,     0,    52,    53,
      54,    55,    46,     0,     0,    56,    57,    58,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      61,    62,    63,    64,     0,     0,    65,    66,     0,    47,
      48,    49,    50,    51,     0,     0,     0,     0,     0,     0,
      52,    53,    54,    55,    46,     0,     0,    56,    57,    58,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,    61,    62,    63,    64,     0,     0,    65,    66,
       0,    47,    48,    49,    50,    51,     0,     0,     0,     0,
       0,     0,    52,    53,    54,    55,   190,     0,     0,    56,
      57,    58,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,   105,    62,    63,    64,     0,     0,
      65,    66,     0,    47,    48,    49,    50,    51,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,   270,     0,
       0,    56,    57,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    61,    62,    63,    64,
       0,     0,    65,    66,     0,    47,    48,    49,    50,    51,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
       0,     0,     0,    56,    57,    58,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,    61,    62,
      63,    64,     1,     2,    65,    66,     0,     0,     0,     0,
       3,     4,     0,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,    12,    13,     0,     0,     0,     0,     0,
      14,    15,     0,     0,     0,     0,     0,     0,    16,     0,
      17,     0,     0,    18,   191,   192,   193,   194,   195,   196,
       0,     0,     0,     0,     0,   197,   198,     0,     0,     0,
       0,     0,     0,     0,     0,   199,   200,   201,   202,   203,
     204,     0,     0,     0,     0,     0,     0,   108,   109,   110,
     111
};

static const yytype_int16 yycheck[] =
{
       0,    46,   181,     4,    15,    16,    23,    10,    14,    12,
      59,   187,    22,    22,   212,    14,    23,    83,    18,    74,
      65,    54,    55,    56,    57,    58,    59,    74,    83,    11,
     282,    23,    65,    66,    36,    23,    83,    47,   236,   291,
      81,    82,    75,    76,    77,    78,    79,    80,    93,    94,
      95,    96,    97,    98,    63,    64,    83,    23,   237,   235,
      38,    23,    89,   108,   109,   110,   111,   116,    74,    72,
      87,    88,    89,    90,   241,    74,    87,    88,    89,    90,
      87,    88,    89,    90,    23,    89,    90,    88,    89,    90,
      91,    92,    24,    83,   143,    87,    88,    89,    90,    87,
      88,    89,    90,    24,    83,    10,   107,    12,   287,    23,
      24,   156,     0,    24,    44,    35,   283,    63,    64,     3,
     120,    87,    88,    89,    90,    87,    88,    89,    90,   296,
      83,   176,   177,   178,   179,   180,    14,   205,   206,    83,
     189,    12,    83,    83,    22,   190,    22,    22,    87,    88,
      89,    90,    24,    22,    74,    87,    88,    89,    90,    22,
      22,   210,    41,    83,    24,   165,    87,    88,    89,    90,
      24,    49,    50,    51,    52,    53,    87,    88,    89,    90,
      24,    22,    60,    61,    62,    63,    22,    22,    22,    67,
      68,    69,    70,    22,   239,   240,   241,    87,    88,    89,
      90,    63,    22,    81,    82,    83,    84,    85,    70,    22,
      88,    89,    38,    83,    75,    87,    88,    89,    90,    81,
      82,   270,    84,    85,    83,   270,    88,    87,    88,    89,
      90,    45,    42,    87,    88,    89,    90,    83,   283,   209,
     210,    42,    24,    87,    88,    89,    90,    37,    39,    48,
     295,   296,    83,    83,    42,    63,    28,    29,    30,    31,
      32,   306,    70,    22,   309,    83,    85,    83,    83,   239,
     240,    83,   317,    81,    82,    23,    84,    85,    23,   279,
      88,    23,    23,    23,    71,    24,    22,    24,    14,   289,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    75,    65,    66,    67,    68,
      69,    70,    22,    23,    36,    24,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    22,    75,    88,
      89,    83,    83,    83,     8,    40,    22,    10,    23,    49,
      50,    51,    52,    53,    22,    83,    23,    47,    83,    83,
      60,    61,    62,    63,    22,    23,    81,    67,    68,    69,
      70,    24,    83,    42,     7,    23,    23,    83,    23,     4,
       9,    81,    82,    83,    84,    85,    23,    73,    88,    89,
      24,    49,    50,    51,    52,    53,    23,    18,   253,   288,
     254,   246,    60,    61,    62,    63,    22,    23,   220,    67,
      68,    69,    70,   294,   211,   320,   234,   319,   312,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,
      88,    89,    -1,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    22,    23,
      -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      -1,    -1,    88,    89,    -1,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      22,    23,    -1,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    -1,    -1,    88,    89,    -1,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    22,    -1,    -1,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    -1,    -1,    88,    89,    -1,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    22,    -1,    -1,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    -1,    -1,    88,    89,
      -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    22,    -1,    -1,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,    -1,
      88,    89,    -1,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    22,    -1,
      -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      -1,    -1,    88,    89,    -1,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      -1,    -1,    -1,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,     5,     6,    88,    89,    -1,    -1,    -1,    -1,
      13,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      43,    -1,    -1,    46,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,
      90
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
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
     125,    81,    82,    24,   114,    83,    89,    83,   124,   125,
     125,   125,   125,    83,   126,    37,    39,   128,    83,   119,
     115,    85,    83,   109,    48,    74,   121,    83,    42,    83,
      23,    23,    23,    23,    23,    23,    24,    24,    24,    24,
      24,   115,    71,    74,    83,    74,    83,    24,   127,    22,
      22,    54,    55,    56,    57,    58,    59,    65,    66,    75,
      76,    77,    78,    79,    80,   122,   125,   134,   135,   136,
      75,    24,   120,    36,    28,    29,    30,    31,    32,   112,
      24,   108,    75,   121,    22,    83,   125,   125,   125,   125,
     125,   114,    83,    83,   126,     8,   130,   115,   121,   136,
     136,    40,    22,   122,   115,   122,   119,   128,    10,    22,
      63,    64,   110,   109,    23,    83,    83,    22,    23,    23,
      23,    23,    23,   127,   126,   128,   114,    23,   122,   125,
      22,   122,   125,   134,   120,    83,    81,   111,   108,   116,
      24,   105,    83,    42,     7,   137,    23,   115,    23,    74,
     121,    83,    23,   105,   134,     4,     9,   129,   114,   110,
     121,   105,    23,   130,   125,   134,    73,   131,    23,    24,
     138,   125,   125,    15,    16,   133,   138,    24,   132,   125,
     133,   132
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
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
     125,   126,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   133,   134,
     134,   134,   135,   135,   135,   135,   135,   135,   135,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   137,   138,   138,   139,   140,   141,
     142,   142
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     8,    10,     9,
       6,     5,     0,     3,     6,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     8,     0,     3,     1,     1,
       1,     2,     2,     1,     1,     4,     0,     4,     4,     6,
       3,     3,     0,     3,     2,    10,     3,     2,     1,     3,
       1,     3,     3,     2,     3,     4,     5,     3,     3,     3,
       3,     3,     2,     1,     1,     3,     3,     3,     3,     3,
       4,     4,     4,     4,     4,     4,     6,     6,     6,     6,
       6,     1,     2,     3,     0,     3,     0,     2,     0,     2,
       0,     5,     0,     4,     0,     4,     0,     1,     1,     0,
       1,     3,     2,     3,     3,     3,     3,     2,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     3,     7,     2,     4,
       0,     1
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
#line 236 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1989 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 266 "yacc_sql.y"
         {
      LOG_DEBUG("parse exit_stmt");
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1999 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 273 "yacc_sql.y"
         {
      LOG_DEBUG("parse help_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2008 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 279 "yacc_sql.y"
         {
      LOG_DEBUG("parse sync_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2017 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 286 "yacc_sql.y"
               {
      LOG_DEBUG("parse begin_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2026 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 293 "yacc_sql.y"
               {
      LOG_DEBUG("parse commit_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2035 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 300 "yacc_sql.y"
                  {
      LOG_DEBUG("parse rollback_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2044 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 307 "yacc_sql.y"
                  {
      LOG_DEBUG("parse drop_table_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2055 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 315 "yacc_sql.y"
                {
      LOG_DEBUG("parse show_tables_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 322 "yacc_sql.y"
             {
      LOG_DEBUG("parse desc_table_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2075 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 332 "yacc_sql.y"
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
#line 2096 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 349 "yacc_sql.y"
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
#line 2120 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 372 "yacc_sql.y"
    {
      LOG_DEBUG("parse id_list");
      (yyval.relation_list) = nullptr;
    }
#line 2129 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA ID id_list  */
#line 376 "yacc_sql.y"
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
#line 2144 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 390 "yacc_sql.y"
    {
      LOG_DEBUG("parse drop_index_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 401 "yacc_sql.y"
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
#line 2185 "yacc_sql.cpp"
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
#line 2213 "yacc_sql.cpp"
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
#line 2241 "yacc_sql.cpp"
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
#line 2260 "yacc_sql.cpp"
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
#line 2279 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: %empty  */
#line 505 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 43: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 509 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2301 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 522 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->can_be_null = (yyvsp[0].boolean);

      if((yyval.attr_info)->type == AttrType::VECTORS){
        (yyval.attr_info)->length = (yyvsp[-2].number) * 4;
      }

      free((yyvsp[-5].string));
    }
#line 2319 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type null_def  */
#line 536 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->can_be_null = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2332 "yacc_sql.cpp"
    break;

  case 46: /* null_def: %empty  */
#line 546 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 47: /* null_def: NULLABLE  */
#line 549 "yacc_sql.y"
               {
      (yyval.boolean) = true;
    }
#line 2348 "yacc_sql.cpp"
    break;

  case 48: /* null_def: UNNULLABLE  */
#line 552 "yacc_sql.y"
                 {
      (yyval.boolean) = false;
    }
#line 2356 "yacc_sql.cpp"
    break;

  case 49: /* number: NUMBER  */
#line 556 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2362 "yacc_sql.cpp"
    break;

  case 50: /* type: INT_T  */
#line 559 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2368 "yacc_sql.cpp"
    break;

  case 51: /* type: STRING_T  */
#line 560 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2374 "yacc_sql.cpp"
    break;

  case 52: /* type: FLOAT_T  */
#line 561 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2380 "yacc_sql.cpp"
    break;

  case 53: /* type: DATE_T  */
#line 562 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATE); }
#line 2386 "yacc_sql.cpp"
    break;

  case 54: /* type: VECTOR_T  */
#line 563 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2392 "yacc_sql.cpp"
    break;

  case 55: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 567 "yacc_sql.y"
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
#line 2410 "yacc_sql.cpp"
    break;

  case 56: /* value_list: %empty  */
#line 584 "yacc_sql.y"
    {
      LOG_DEBUG("parse value_list");
      (yyval.value_list) = nullptr;
    }
#line 2419 "yacc_sql.cpp"
    break;

  case 57: /* value_list: COMMA value value_list  */
#line 588 "yacc_sql.y"
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
#line 2434 "yacc_sql.cpp"
    break;

  case 58: /* value: NULLABLE  */
#line 600 "yacc_sql.y"
             {
      (yyval.value) = new Value(string("ckk is stupid!"), 114514);
      (yyloc) = (yylsp[0]);
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 59: /* value: NUMBER  */
#line 604 "yacc_sql.y"
            {
      LOG_DEBUG("NUMBER: ", (yyvsp[0].number));
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 60: /* value: FLOAT  */
#line 609 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2462 "yacc_sql.cpp"
    break;

  case 61: /* value: '-' NUMBER  */
#line 613 "yacc_sql.y"
                {
      LOG_DEBUG("- %d", (yyvsp[0].number));
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[-1]);
    }
#line 2472 "yacc_sql.cpp"
    break;

  case 62: /* value: '-' FLOAT  */
#line 618 "yacc_sql.y"
               {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[-1]);
    }
#line 2481 "yacc_sql.cpp"
    break;

  case 63: /* value: DATE_STR  */
#line 622 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);  // 去掉首尾的引号
      int year, month, day;
      sscanf(tmp, "%d-%d-%d", &year, &month, &day);    //sscanf会自动转换字符串中的数字，不用显式stoi
      int date_num = year * 10000 + month * 100 + day;
      (yyval.value) = new Value(date_num, true);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2495 "yacc_sql.cpp"
    break;

  case 64: /* value: SSS  */
#line 631 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, strlen(tmp));  
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 65: /* value: LBRACKET value value_list RBRACKET  */
#line 637 "yacc_sql.y"
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
#line 2522 "yacc_sql.cpp"
    break;

  case 66: /* storage_format: %empty  */
#line 651 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2530 "yacc_sql.cpp"
    break;

  case 67: /* storage_format: STORAGE FORMAT EQ ID  */
#line 655 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 68: /* delete_stmt: DELETE FROM ID where  */
#line 662 "yacc_sql.y"
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
#line 2553 "yacc_sql.cpp"
    break;

  case 69: /* update_stmt: UPDATE ID SET update_target update_target_list where  */
#line 675 "yacc_sql.y"
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
#line 2572 "yacc_sql.cpp"
    break;

  case 70: /* update_target: ID EQ value  */
#line 693 "yacc_sql.y"
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->value = *(yyvsp[0].value);
      (yyval.update_target)->is_value = true;

      delete (yyvsp[0].value);
    }
#line 2585 "yacc_sql.cpp"
    break;

  case 71: /* update_target: ID EQ sub_select_stmt  */
#line 702 "yacc_sql.y"
    {
      (yyval.update_target) = new UpdateTarget;
      (yyval.update_target)->attribute_name = (yyvsp[-2].string);
      (yyval.update_target)->sub_select = (yyvsp[0].sql_node);
      (yyval.update_target)->is_value = false;
    }
#line 2596 "yacc_sql.cpp"
    break;

  case 72: /* update_target_list: %empty  */
#line 712 "yacc_sql.y"
    {
      (yyval.update_target_list) = nullptr;
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 73: /* update_target_list: COMMA update_target update_target_list  */
#line 716 "yacc_sql.y"
    {
      if((yyvsp[0].update_target_list) == nullptr)
        (yyval.update_target_list) = new std::vector<UpdateTarget>;
      else (yyval.update_target_list) = (yyvsp[0].update_target_list);
      (yyval.update_target_list)->emplace_back(*(yyvsp[-1].update_target));
    }
#line 2615 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT expression_list  */
#line 726 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->selection.expressions.swap(*(yyvsp[0].expression_list));
    }
#line 2624 "yacc_sql.cpp"
    break;

  case 75: /* select_stmt: SELECT expression_list FROM relation rel_list join_list where group_by having order_by_list  */
#line 731 "yacc_sql.y"
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
#line 2667 "yacc_sql.cpp"
    break;

  case 76: /* sub_select_stmt: LBRACE select_stmt RBRACE  */
#line 772 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
    }
#line 2675 "yacc_sql.cpp"
    break;

  case 77: /* calc_stmt: CALC expression_list  */
#line 778 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2685 "yacc_sql.cpp"
    break;

  case 78: /* expression_list: expression  */
#line 787 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 79: /* expression_list: expression COMMA expression_list  */
#line 792 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2707 "yacc_sql.cpp"
    break;

  case 80: /* expression: ID  */
#line 802 "yacc_sql.y"
       {
      LOG_DEBUG("ID %s", (yyvsp[0].string));
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 2718 "yacc_sql.cpp"
    break;

  case 81: /* expression: ID DOT ID  */
#line 808 "yacc_sql.y"
                {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
#line 2728 "yacc_sql.cpp"
    break;

  case 82: /* expression: ID DOT '*'  */
#line 813 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
#line 2738 "yacc_sql.cpp"
    break;

  case 83: /* expression: ID ID  */
#line 818 "yacc_sql.y"
            {
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[-1].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-1].string));
    }
#line 2748 "yacc_sql.cpp"
    break;

  case 84: /* expression: ID AS ID  */
#line 823 "yacc_sql.y"
               {
      (yyval.expression) = new UnboundFieldExpr(string(), (yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 85: /* expression: ID DOT ID ID  */
#line 828 "yacc_sql.y"
                   {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-3].string));
    }
#line 2768 "yacc_sql.cpp"
    break;

  case 86: /* expression: ID DOT ID AS ID  */
#line 833 "yacc_sql.y"
                      {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-4].string));
    }
#line 2778 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '+' expression  */
#line 838 "yacc_sql.y"
                                {
      LOG_DEBUG("add");
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2787 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '-' expression  */
#line 842 "yacc_sql.y"
                                {
      LOG_DEBUG("sub");
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2796 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '*' expression  */
#line 846 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2804 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '/' expression  */
#line 849 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2812 "yacc_sql.cpp"
    break;

  case 91: /* expression: LBRACE expression RBRACE  */
#line 852 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 92: /* expression: '-' expression  */
#line 856 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 93: /* expression: value  */
#line 859 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 94: /* expression: '*'  */
#line 864 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 95: /* expression: MAX LBRACE RBRACE  */
#line 867 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 96: /* expression: MIN LBRACE RBRACE  */
#line 870 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2863 "yacc_sql.cpp"
    break;

  case 97: /* expression: AVG LBRACE RBRACE  */
#line 873 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2871 "yacc_sql.cpp"
    break;

  case 98: /* expression: SUM LBRACE RBRACE  */
#line 876 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 99: /* expression: COUNT LBRACE RBRACE  */
#line 879 "yacc_sql.y"
                          {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2887 "yacc_sql.cpp"
    break;

  case 100: /* expression: MAX LBRACE expression_list RBRACE  */
#line 882 "yacc_sql.y"
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("MAX", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 2899 "yacc_sql.cpp"
    break;

  case 101: /* expression: MIN LBRACE expression_list RBRACE  */
#line 889 "yacc_sql.y"
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("MIN", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 2911 "yacc_sql.cpp"
    break;

  case 102: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 896 "yacc_sql.y"
                                          {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("COUNT", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 2923 "yacc_sql.cpp"
    break;

  case 103: /* expression: AVG LBRACE expression_list RBRACE  */
#line 903 "yacc_sql.y"
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("AVG", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 2935 "yacc_sql.cpp"
    break;

  case 104: /* expression: SUM LBRACE expression_list RBRACE  */
#line 910 "yacc_sql.y"
                                        {
      if((yyvsp[-1].expression_list)->size() != 1) {
        (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
      } else {
        (yyval.expression) = create_aggregate_expression("SUM", (yyvsp[-1].expression_list)->at(0).get(), sql_string, &(yyloc));
      }
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 105: /* expression: LENGTH LBRACE expression RBRACE  */
#line 917 "yacc_sql.y"
                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, nullptr, nullptr, (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 106: /* expression: ROUND LBRACE expression COMMA expression RBRACE  */
#line 921 "yacc_sql.y"
                                                      {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, (yyvsp[-1].expression), nullptr, (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2965 "yacc_sql.cpp"
    break;

  case 107: /* expression: DATE_FORMAT LBRACE expression COMMA expression RBRACE  */
#line 925 "yacc_sql.y"
                                                            {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, nullptr, (yyvsp[-1].expression), (yyvsp[-3].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 108: /* expression: VEC_INNER_PRODUCT_FUNC LBRACE expression COMMA expression RBRACE  */
#line 929 "yacc_sql.y"
                                                                       {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2983 "yacc_sql.cpp"
    break;

  case 109: /* expression: VEC_COSINE_DISTANCE_FUNC LBRACE expression COMMA expression RBRACE  */
#line 933 "yacc_sql.y"
                                                                         {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 110: /* expression: VEC_L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 937 "yacc_sql.y"
                                                                {
      (yyval.expression) = new VecFuncExpr(VecFuncExpr::VecFuncType::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 3001 "yacc_sql.cpp"
    break;

  case 111: /* relation: ID  */
#line 944 "yacc_sql.y"
       {
      (yyval.expression) = new UnboundTableExpr((yyvsp[0].string), string());
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 3011 "yacc_sql.cpp"
    break;

  case 112: /* relation: ID ID  */
#line 949 "yacc_sql.y"
            {
      (yyval.expression) = new UnboundTableExpr((yyvsp[-1].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3022 "yacc_sql.cpp"
    break;

  case 113: /* relation: ID AS ID  */
#line 955 "yacc_sql.y"
               {
      (yyval.expression) = new UnboundTableExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3033 "yacc_sql.cpp"
    break;

  case 114: /* rel_list: %empty  */
#line 964 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3041 "yacc_sql.cpp"
    break;

  case 115: /* rel_list: COMMA relation rel_list  */
#line 967 "yacc_sql.y"
                              {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3055 "yacc_sql.cpp"
    break;

  case 116: /* where: %empty  */
#line 980 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3063 "yacc_sql.cpp"
    break;

  case 117: /* where: WHERE condition_list  */
#line 983 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3071 "yacc_sql.cpp"
    break;

  case 118: /* having: %empty  */
#line 990 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 119: /* having: HAVING condition_list  */
#line 993 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 120: /* join_list: %empty  */
#line 999 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3095 "yacc_sql.cpp"
    break;

  case 121: /* join_list: INNER_JOIN relation ON condition_list join_list  */
#line 1002 "yacc_sql.y"
                                                      {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(new JoinTableExpr(*(yyvsp[-1].condition_list), (yyvsp[-3].expression)));
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 122: /* order_by_list: %empty  */
#line 1014 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3116 "yacc_sql.cpp"
    break;

  case 123: /* order_by_list: ORDER_BY expression order_by_flag order_by  */
#line 1018 "yacc_sql.y"
    {
       if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
#line 3129 "yacc_sql.cpp"
    break;

  case 124: /* order_by: %empty  */
#line 1030 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3137 "yacc_sql.cpp"
    break;

  case 125: /* order_by: COMMA expression order_by_flag order_by  */
#line 1034 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace_back(make_unique<OrderByExpr>((yyvsp[-2].expression), (yyvsp[-1].number)));
    }
#line 3150 "yacc_sql.cpp"
    break;

  case 126: /* order_by_flag: %empty  */
#line 1046 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3158 "yacc_sql.cpp"
    break;

  case 127: /* order_by_flag: ASC  */
#line 1050 "yacc_sql.y"
    {
      (yyval.number) = 1;
    }
#line 3166 "yacc_sql.cpp"
    break;

  case 128: /* order_by_flag: DESC  */
#line 1054 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 3174 "yacc_sql.cpp"
    break;

  case 129: /* condition_list: %empty  */
#line 1061 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3182 "yacc_sql.cpp"
    break;

  case 130: /* condition_list: condition  */
#line 1064 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3192 "yacc_sql.cpp"
    break;

  case 131: /* condition_list: condition AND condition_list  */
#line 1069 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3202 "yacc_sql.cpp"
    break;

  case 132: /* condition: expression comp_op  */
#line 1077 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[0].comp);
      (yyval.condition)->left_expression = (yyvsp[-1].expression);
      (yyval.condition)->right_expression = new ValueExpr(Value(114514));
    }
#line 3215 "yacc_sql.cpp"
    break;

  case 133: /* condition: expression comp_op sub_select_stmt  */
#line 1086 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->right_expression = nullptr;
    }
#line 3229 "yacc_sql.cpp"
    break;

  case 134: /* condition: sub_select_stmt comp_op sub_select_stmt  */
#line 1096 "yacc_sql.y"
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
#line 3244 "yacc_sql.cpp"
    break;

  case 135: /* condition: sub_select_stmt comp_op expression  */
#line 1107 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = true;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_sub_query = (yyvsp[-2].sql_node);
      (yyval.condition)->left_expression = nullptr;
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
#line 3258 "yacc_sql.cpp"
    break;

  case 136: /* condition: expression comp_op expression  */
#line 1117 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = (yyvsp[-2].expression);
      (yyval.condition)->right_expression = (yyvsp[0].expression);
    }
#line 3271 "yacc_sql.cpp"
    break;

  case 137: /* condition: comp_op sub_select_stmt  */
#line 1126 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = true;
      (yyval.condition)->right_sub_query = (yyvsp[0].sql_node);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->left_expression = new ValueExpr(Value(114514));
    }
#line 3284 "yacc_sql.cpp"
    break;

  case 138: /* condition: expression comp_op LBRACE value value_list RBRACE  */
#line 1135 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_sub_query = false;
      (yyval.condition)->right_is_sub_query = false;
      (yyval.condition)->comp = (yyvsp[-4].comp);
      (yyval.condition)->left_expression = (yyvsp[-5].expression);
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.condition)->right_expression = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 3298 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: EQ  */
#line 1147 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3304 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: LT  */
#line 1148 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3310 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: GT  */
#line 1149 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3316 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: LE  */
#line 1150 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3322 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: GE  */
#line 1151 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3328 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: NE  */
#line 1152 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3334 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: IS_NULL  */
#line 1153 "yacc_sql.y"
              { (yyval.comp) = XXX_IS_NULL; }
#line 3340 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: IS_NOT_NULL  */
#line 1154 "yacc_sql.y"
                  { (yyval.comp) = XXX_IS_NOT_NULL; }
#line 3346 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: NOT_LIKE  */
#line 1155 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_XXX; }
#line 3352 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: LIKE  */
#line 1156 "yacc_sql.y"
           { (yyval.comp) = LIKE_XXX; }
#line 3358 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: NOT_IN  */
#line 1157 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_XXX; }
#line 3364 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: IN  */
#line 1158 "yacc_sql.y"
         { (yyval.comp) = IN_XXX; }
#line 3370 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: NOT_EXISTS  */
#line 1159 "yacc_sql.y"
                 { (yyval.comp) = XXX_NOT_EXISTS; }
#line 3376 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: EXISTS  */
#line 1160 "yacc_sql.y"
             { (yyval.comp) = XXX_EXISTS; }
#line 3382 "yacc_sql.cpp"
    break;

  case 153: /* group_by: %empty  */
#line 1165 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3390 "yacc_sql.cpp"
    break;

  case 154: /* group_by: GROUP BY expression group_by_unit  */
#line 1168 "yacc_sql.y"
                                        {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3404 "yacc_sql.cpp"
    break;

  case 155: /* group_by_unit: %empty  */
#line 1181 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3412 "yacc_sql.cpp"
    break;

  case 156: /* group_by_unit: COMMA expression group_by_unit  */
#line 1185 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }

      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 3426 "yacc_sql.cpp"
    break;

  case 157: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1198 "yacc_sql.y"
    {
      LOG_DEBUG("parse load_data_stmt");
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3441 "yacc_sql.cpp"
    break;

  case 158: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1212 "yacc_sql.y"
    {
      LOG_DEBUG("parse explain_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3451 "yacc_sql.cpp"
    break;

  case 159: /* set_variable_stmt: SET ID EQ value  */
#line 1221 "yacc_sql.y"
    {
      LOG_DEBUG("parse set_variable_stmt");
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3464 "yacc_sql.cpp"
    break;


#line 3468 "yacc_sql.cpp"

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

#line 1234 "yacc_sql.y"

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
