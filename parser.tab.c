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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y"

#include "ast.h" // Parse/AST Tree Management
#include "symboltable.h" /*Symbol Table Management*/
#include "semantic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int yylineno; // Declared in lexer
extern char* yytext;
extern int lexerrorno;
int semerrorno = 0; 
int syntaxerrorno = 0;
extern int yylex();
extern int yyparse();
extern void yyerror(); 
extern FILE* yyin;
extern int lnolastid; // Symbol table util
struct Node* root = NULL; // AST Root Node
struct SymbolTable* symbolTable = NULL;

struct FactorNode* head = NULL;


#line 95 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PLUS = 3,                       /* PLUS  */
  YYSYMBOL_MINUS = 4,                      /* MINUS  */
  YYSYMBOL_MUL = 5,                        /* MUL  */
  YYSYMBOL_DIV = 6,                        /* DIV  */
  YYSYMBOL_LPAREN = 7,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 8,                     /* RPAREN  */
  YYSYMBOL_LCURLY = 9,                     /* LCURLY  */
  YYSYMBOL_RCURLY = 10,                    /* RCURLY  */
  YYSYMBOL_SEMICOLON = 11,                 /* SEMICOLON  */
  YYSYMBOL_COMA = 12,                      /* COMA  */
  YYSYMBOL_LBRACKET = 13,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 14,                  /* RBRACKET  */
  YYSYMBOL_IDENTIFIER = 15,                /* IDENTIFIER  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_INT = 17,                       /* INT  */
  YYSYMBOL_FLOAT = 18,                     /* FLOAT  */
  YYSYMBOL_PRINTKW = 19,                   /* PRINTKW  */
  YYSYMBOL_INTKW = 20,                     /* INTKW  */
  YYSYMBOL_FLOATKW = 21,                   /* FLOATKW  */
  YYSYMBOL_RETURNKW = 22,                  /* RETURNKW  */
  YYSYMBOL_YYACCEPT = 23,                  /* $accept  */
  YYSYMBOL_program = 24,                   /* program  */
  YYSYMBOL_stmt_list = 25,                 /* stmt_list  */
  YYSYMBOL_stmt = 26,                      /* stmt  */
  YYSYMBOL_array_decl = 27,                /* array_decl  */
  YYSYMBOL_declaration = 28,               /* declaration  */
  YYSYMBOL_var_decl = 29,                  /* var_decl  */
  YYSYMBOL_func_def = 30,                  /* func_def  */
  YYSYMBOL_func_decl = 31,                 /* func_decl  */
  YYSYMBOL_func_params = 32,               /* func_params  */
  YYSYMBOL_param_list = 33,                /* param_list  */
  YYSYMBOL_param = 34,                     /* param  */
  YYSYMBOL_func_call = 35,                 /* func_call  */
  YYSYMBOL_func_args = 36,                 /* func_args  */
  YYSYMBOL_arg_list = 37,                  /* arg_list  */
  YYSYMBOL_arg = 38,                       /* arg  */
  YYSYMBOL_type = 39,                      /* type  */
  YYSYMBOL_assignment = 40,                /* assignment  */
  YYSYMBOL_print_stmt = 41,                /* print_stmt  */
  YYSYMBOL_return_stmt = 42,               /* return_stmt  */
  YYSYMBOL_expr = 43,                      /* expr  */
  YYSYMBOL_array_index = 44,               /* array_index  */
  YYSYMBOL_term = 45,                      /* term  */
  YYSYMBOL_factor = 46,                    /* factor  */
  YYSYMBOL_number = 47                     /* number  */
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
typedef yytype_int8 yy_state_t;

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  23
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    48,    48,    58,    67,    72,    78,    84,    90,    96,
     102,   108,   114,   120,   126,   129,   139,   149,   152,   162,
     171,   179,   185,   193,   202,   211,   220,   228,   234,   243,
     252,   260,   266,   273,   281,   289,   290,   291,   300,   307,
     314,   315,   317,   326,   332,   341,   350,   351,   352,   353,
     354,   363,   372,   382,   391,   398,   399,   400,   401,   403,
     410,   417,   424,   432
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
  "\"end of file\"", "error", "\"invalid token\"", "PLUS", "MINUS", "MUL",
  "DIV", "LPAREN", "RPAREN", "LCURLY", "RCURLY", "SEMICOLON", "COMA",
  "LBRACKET", "RBRACKET", "IDENTIFIER", "ASSIGN", "INT", "FLOAT",
  "PRINTKW", "INTKW", "FLOATKW", "RETURNKW", "$accept", "program",
  "stmt_list", "stmt", "array_decl", "declaration", "var_decl", "func_def",
  "func_decl", "func_params", "param_list", "param", "func_call",
  "func_args", "arg_list", "arg", "type", "assignment", "print_stmt",
  "return_stmt", "expr", "array_index", "term", "factor", "number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      64,   185,   113,    19,   -42,   -42,   117,   -42,   -42,   113,
       6,   -42,    41,   -42,    33,     2,   -42,   -42,   -42,     5,
     -42,   -42,   -42,    65,    36,    72,   -42,   -42,   122,   122,
       4,     4,     3,   118,   -42,    16,   113,   126,   113,    92,
      46,   -42,   -42,    95,   113,   -42,   113,   -42,   -42,   135,
     144,   -42,   113,   148,   153,   141,   -42,    72,    72,   -42,
     -42,   -42,    59,    76,   -42,   154,    11,   169,    96,   179,
     -42,   -42,   -42,    83,    90,   -42,    89,    40,   173,   141,
      72,   141,    72,   175,   -42,   -42,   -42,   -42,   106,   113,
     -42,   -42,   -42,   -42,    69,    78,    95,   -42,   108,   -42,
     -42,   -42,   -42,   -42,   -42,    91,   -42,   -42,   -42,   115,
     -42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    60,    63,    62,     0,    32,    31,     0,
       0,     2,     0,     9,    17,     0,     6,     7,     8,     0,
      10,    11,    13,     0,    50,    43,    54,    61,     0,     0,
       0,     0,    60,     0,    50,     0,     0,     0,     0,     0,
       0,     1,     3,    21,     0,     5,     0,    16,    14,     0,
       0,    12,     0,     0,     0,     0,    60,    49,    47,    56,
      55,    59,     0,    26,    29,    30,     0,     0,     0,     0,
      41,    39,    42,     0,    20,    23,     0,     0,     0,    48,
      45,    46,    44,     0,    58,    53,    57,    52,     0,     0,
      51,    36,    35,    34,     0,     0,     0,    24,     0,    33,
      37,    25,    28,    40,    38,     0,    19,    22,    15,     0,
      18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -11,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,    42,   -42,   -42,   -42,    67,   -41,   -42,   -42,   -42,
       1,     0,   -20,   -26,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    17,    73,
      74,    75,    18,    62,    63,    64,    19,    20,    21,    22,
      23,    34,    25,    26,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      24,    42,    76,    33,    59,    60,    41,    39,    57,    58,
      40,     2,    24,    45,    49,    50,    36,     1,    46,    56,
      47,     4,     5,     2,   -27,    90,    35,    85,    87,    80,
      82,    32,    36,     4,     5,    37,    65,    66,    68,    69,
      43,    -4,     1,    49,    50,    77,    44,    78,     2,    49,
      50,    -4,    52,    83,    98,    76,     3,    72,     4,     5,
       6,     7,     8,     9,    -4,     1,    48,    88,    49,    50,
     103,     2,   -59,   -59,   -59,   -59,    51,    53,    54,     3,
     104,     4,     5,     6,     7,     8,     9,   105,    89,   106,
      65,    95,     1,    70,   109,    49,    50,    92,     2,    49,
      50,    -4,    96,    71,    97,    24,     3,    93,     4,     5,
       6,     7,     8,     9,     1,     7,     8,   101,     1,   108,
       2,    49,    50,    55,    38,   110,    61,    67,    32,     2,
       4,     5,    32,     2,     4,     5,    79,    56,   107,     4,
       5,    32,     2,     4,     5,    81,    30,    31,     0,    84,
      56,     2,     4,     5,    86,     2,   102,    49,    50,    56,
       2,     4,     5,    56,     0,     4,     5,     0,    56,     0,
       4,     5,    28,    29,    30,    31,    49,    50,    49,    50,
      91,     0,    49,    50,    99,     0,   100,    94,    28,    29,
      30,    31
};

static const yytype_int8 yycheck[] =
{
       0,    12,    43,     2,    30,    31,     0,     6,    28,    29,
       9,     7,    12,    11,     3,     4,    13,     1,    16,    15,
      15,    17,    18,     7,     8,    14,     7,    53,    54,    49,
      50,    15,    13,    17,    18,    16,    35,    36,    37,    38,
       7,     0,     1,     3,     4,    44,    13,    46,     7,     3,
       4,    10,    16,    52,    14,    96,    15,    11,    17,    18,
      19,    20,    21,    22,     0,     1,     1,     8,     3,     4,
       1,     7,     3,     4,     5,     6,    11,     5,     6,    15,
      11,    17,    18,    19,    20,    21,    22,     9,    12,    11,
      89,     8,     1,     1,   105,     3,     4,     1,     7,     3,
       4,    10,    12,    11,    15,   105,    15,    11,    17,    18,
      19,    20,    21,    22,     1,    20,    21,    11,     1,    11,
       7,     3,     4,     1,     7,    10,     8,     1,    15,     7,
      17,    18,    15,     7,    17,    18,     1,    15,    96,    17,
      18,    15,     7,    17,    18,     1,     5,     6,    -1,     1,
      15,     7,    17,    18,     1,     7,    89,     3,     4,    15,
       7,    17,    18,    15,    -1,    17,    18,    -1,    15,    -1,
      17,    18,     3,     4,     5,     6,     3,     4,     3,     4,
      11,    -1,     3,     4,    11,    -1,    11,     8,     3,     4,
       5,     6
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     7,    15,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    27,    28,    29,    30,    31,    35,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     3,     4,
       5,     6,    15,    43,    44,     7,    13,    16,     7,    43,
      43,     0,    25,     7,    13,    11,    16,    15,     1,     3,
       4,    11,    16,     5,     6,     1,    15,    45,    45,    46,
      46,     8,    36,    37,    38,    43,    43,     1,    43,    43,
       1,    11,    11,    32,    33,    34,    39,    43,    43,     1,
      45,     1,    45,    43,     1,    46,     1,    46,     8,    12,
      14,    11,     1,    11,     8,     8,    12,    15,    14,    11,
      11,    11,    38,     1,    11,     9,    11,    34,    11,    25,
      10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    23,    24,    25,    25,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    27,    28,    29,    30,    31,
      32,    32,    33,    33,    34,    35,    36,    36,    37,    37,
      38,    39,    39,    40,    40,    40,    40,    40,    41,    41,
      41,    41,    42,    43,    43,    43,    43,    43,    43,    43,
      43,    44,    45,    45,    45,    45,    45,    45,    45,    46,
      46,    46,    47,    47
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     5,     2,     1,     7,     5,
       1,     0,     3,     1,     2,     5,     1,     0,     3,     1,
       1,     1,     1,     4,     4,     4,     4,     4,     5,     3,
       5,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     4,     3,     3,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmt_list  */
#line 49 "parser.y"
{
	(yyval.ast) = createNode(node_program); // Begin forming Parse tree/AST 
	(yyval.ast)->program.stmt_list = (yyvsp[0].ast);
	(yyval.ast)->lineno = yylineno;
	root = (yyval.ast);
	printf("PARSER : Program successfully parsed\n");
}
#line 1492 "parser.tab.c"
    break;

  case 3: /* stmt_list: stmt stmt_list  */
#line 59 "parser.y"
{
	(yyval.ast) = createNode(node_stmt_list);
	(yyval.ast)->stmt_list.stmt = (yyvsp[-1].ast);
	(yyval.ast)->stmt_list.stmt_list = (yyvsp[0].ast);	
	(yyval.ast)->lineno = yylineno;
	printf("PARSER : Processed statement list\n");
}
#line 1504 "parser.tab.c"
    break;

  case 4: /* stmt_list: %empty  */
#line 67 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt_list); // If statement list is empty 
		(yyval.ast)->lineno = yylineno; 
	}
#line 1513 "parser.tab.c"
    break;

  case 5: /* stmt: var_decl SEMICOLON  */
#line 73 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1523 "parser.tab.c"
    break;

  case 6: /* stmt: func_def  */
#line 79 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1533 "parser.tab.c"
    break;

  case 7: /* stmt: func_decl  */
#line 85 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1543 "parser.tab.c"
    break;

  case 8: /* stmt: func_call  */
#line 91 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1553 "parser.tab.c"
    break;

  case 9: /* stmt: array_decl  */
#line 97 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1563 "parser.tab.c"
    break;

  case 10: /* stmt: assignment  */
#line 103 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1573 "parser.tab.c"
    break;

  case 11: /* stmt: print_stmt  */
#line 109 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1583 "parser.tab.c"
    break;

  case 12: /* stmt: expr SEMICOLON  */
#line 115 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1593 "parser.tab.c"
    break;

  case 13: /* stmt: return_stmt  */
#line 121 "parser.y"
        {
		(yyval.ast) = createNode(node_stmt);
		(yyval.ast)->stmt.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1603 "parser.tab.c"
    break;

  case 14: /* stmt: expr error  */
#line 126 "parser.y"
                     {syntaxerrorno++; printf("Ln.%d : SYNTAX ERROR : MISSING SEMICOLON\n", lnolastid);}
#line 1609 "parser.tab.c"
    break;

  case 15: /* array_decl: declaration LBRACKET expr RBRACKET SEMICOLON  */
#line 130 "parser.y"
{
	printf("Found array decl\n");
	(yyval.ast) = createNode(node_array_decl);
	(yyval.ast)->array_decl.decl = (yyvsp[-4].ast);
	(yyval.ast)->array_decl.size = (yyvsp[-2].ast);
	(yyval.ast)->lineno = yylineno;
}
#line 1621 "parser.tab.c"
    break;

  case 16: /* declaration: type IDENTIFIER  */
#line 140 "parser.y"
        {
		printf("PARSER : Found  declaration\n");
		(yyval.ast) = createNode(node_declaration);
		(yyval.ast)->declaration.type = (yyvsp[-1].ast);
		(yyval.ast)->declaration.identifier = (yyvsp[0].string);
		(yyval.ast)->lineno = lnolastid;
	}
#line 1633 "parser.tab.c"
    break;

  case 18: /* func_def: declaration LPAREN func_params RPAREN LCURLY stmt_list RCURLY  */
#line 153 "parser.y"
        {
		printf("Found function definition\n");
		(yyval.ast) = createNode(node_func_def);
		(yyval.ast)->func_def.decl = (yyvsp[-6].ast);
		(yyval.ast)->func_def.params = (yyvsp[-4].ast); 
		(yyval.ast)->func_def.stmt_list = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1646 "parser.tab.c"
    break;

  case 19: /* func_decl: declaration LPAREN func_params RPAREN SEMICOLON  */
#line 163 "parser.y"
        {
		printf("PARSER : Found function declaration\n");
		(yyval.ast) = createNode(node_func_decl);
		(yyval.ast)->func_decl.decl = (yyvsp[-4].ast);
		(yyval.ast)->func_decl.params = (yyvsp[-2].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1658 "parser.tab.c"
    break;

  case 20: /* func_params: param_list  */
#line 172 "parser.y"
        {
		printf("Found func_params\n");
		(yyval.ast) = createNode(node_func_params);
		(yyval.ast)->func_params.param_list = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1669 "parser.tab.c"
    break;

  case 21: /* func_params: %empty  */
#line 179 "parser.y"
        {
		printf("Found func_params\n");
		(yyval.ast) = createNode(node_func_params);
		(yyval.ast)->lineno = yylineno;
	}
#line 1679 "parser.tab.c"
    break;

  case 22: /* param_list: param_list COMA param  */
#line 186 "parser.y"
        {	// Multiple parameters
		printf("Found param_list\n");
		(yyval.ast) = createNode(node_param_list);
		(yyval.ast)->param_list.param_list = (yyvsp[-2].ast);
		(yyval.ast)->param_list.param = (yyvsp[0].ast); 
		(yyval.ast)->lineno = yylineno;
	}
#line 1691 "parser.tab.c"
    break;

  case 23: /* param_list: param  */
#line 194 "parser.y"
        {
		// Single parameter
		printf("Found param_list\n");
		(yyval.ast) = createNode(node_param_list);
		(yyval.ast)->param_list.param_list = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1703 "parser.tab.c"
    break;

  case 24: /* param: type IDENTIFIER  */
#line 203 "parser.y"
        {
		printf("Found param\n");
		(yyval.ast) = createNode(node_param);
		(yyval.ast)->param.type = (yyvsp[-1].ast);
		(yyval.ast)->param.identifier = (yyvsp[0].string);
		(yyval.ast)->lineno = yylineno;
	}
#line 1715 "parser.tab.c"
    break;

  case 25: /* func_call: IDENTIFIER LPAREN func_args RPAREN SEMICOLON  */
#line 212 "parser.y"
        {
		printf("Found function call\n");
		(yyval.ast) = createNode(node_func_call);
		(yyval.ast)->func_call.identifier = (yyvsp[-4].string);
		(yyval.ast)->func_call.args = (yyvsp[-2].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1727 "parser.tab.c"
    break;

  case 26: /* func_args: arg_list  */
#line 221 "parser.y"
        {
		printf("Found function args\n");
		(yyval.ast) = createNode(node_func_args);
		(yyval.ast)->func_args.arg_list = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1738 "parser.tab.c"
    break;

  case 27: /* func_args: %empty  */
#line 228 "parser.y"
        {
		printf("Found function args\n");
		(yyval.ast) = createNode(node_func_args);
		(yyval.ast)->lineno = yylineno;
	}
#line 1748 "parser.tab.c"
    break;

  case 28: /* arg_list: arg_list COMA arg  */
#line 235 "parser.y"
        {
		// Multiple args
		printf("Found arg list\n");
		(yyval.ast) = createNode(node_arg_list);
		(yyval.ast)->arg_list.arg_list = (yyvsp[-2].ast);
		(yyval.ast)->arg_list.arg = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1761 "parser.tab.c"
    break;

  case 29: /* arg_list: arg  */
#line 244 "parser.y"
        {
		// Single arg
		printf("Found arg list\n");
		(yyval.ast) = createNode(node_arg_list);
		(yyval.ast)->arg_list.arg = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1773 "parser.tab.c"
    break;

  case 30: /* arg: expr  */
#line 253 "parser.y"
        {
		printf("Found arg\n");
		(yyval.ast) = createNode(node_arg);
		(yyval.ast)->arg.expr = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1784 "parser.tab.c"
    break;

  case 31: /* type: FLOATKW  */
#line 261 "parser.y"
        {
		(yyval.ast) = createNode(node_typekw);
		(yyval.ast)->typekw.type = (yyvsp[0].string);
		(yyval.ast)->lineno = yylineno;
	}
#line 1794 "parser.tab.c"
    break;

  case 32: /* type: INTKW  */
#line 267 "parser.y"
        {
		(yyval.ast) = createNode(node_typekw);
		(yyval.ast)->typekw.type = (yyvsp[0].string);
		(yyval.ast)->lineno = yylineno;
	}
#line 1804 "parser.tab.c"
    break;

  case 33: /* assignment: var_decl ASSIGN expr SEMICOLON  */
#line 274 "parser.y"
        {	
		(yyval.ast) = createNode(node_assignment);
		(yyval.ast)->assignment.assignee = (yyvsp[-3].ast);
		(yyval.ast)->assignment.assign = (yyvsp[-2].operator);
		(yyval.ast)->assignment.expr = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1816 "parser.tab.c"
    break;

  case 34: /* assignment: IDENTIFIER ASSIGN expr SEMICOLON  */
#line 282 "parser.y"
        {
		(yyval.ast) = createNode(node_assignment);
		(yyval.ast)->assignment.identifier = (yyvsp[-3].string);
		(yyval.ast)->assignment.assign = (yyvsp[-2].operator);
		(yyval.ast)->assignment.expr = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1828 "parser.tab.c"
    break;

  case 35: /* assignment: IDENTIFIER ASSIGN expr error  */
#line 289 "parser.y"
                                       {syntaxerrorno++; printf("Ln.%d : PARSER : SYNTAX ERROR : MISSING SEMICOLON\n", yylineno);}
#line 1834 "parser.tab.c"
    break;

  case 36: /* assignment: IDENTIFIER ASSIGN error SEMICOLON  */
#line 290 "parser.y"
                                            {syntaxerrorno++; printf("SYNTAX ERROR : Missing assignment arg.");}
#line 1840 "parser.tab.c"
    break;

  case 37: /* assignment: array_index ASSIGN expr SEMICOLON  */
#line 292 "parser.y"
        {
		(yyval.ast) = createNode(node_assignment);
		(yyval.ast)->assignment.assignee = (yyvsp[-3].ast);
		(yyval.ast)->assignment.assign = (yyvsp[-2].operator);
		(yyval.ast)->assignment.expr = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1852 "parser.tab.c"
    break;

  case 38: /* print_stmt: PRINTKW LPAREN expr RPAREN SEMICOLON  */
#line 301 "parser.y"
        {
		printf("PARSER : Found  a print statement\n");
		(yyval.ast) = createNode(node_print_stmt);
		(yyval.ast)->print_stmt.expr = (yyvsp[-2].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1863 "parser.tab.c"
    break;

  case 39: /* print_stmt: PRINTKW expr SEMICOLON  */
#line 308 "parser.y"
        {
		printf("PARSER : Found  a print statement\n");
		(yyval.ast) = createNode(node_print_stmt);
		(yyval.ast)->print_stmt.expr = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1874 "parser.tab.c"
    break;

  case 40: /* print_stmt: PRINTKW LPAREN expr RPAREN error  */
#line 314 "parser.y"
                                           {syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
#line 1880 "parser.tab.c"
    break;

  case 41: /* print_stmt: PRINTKW expr error  */
#line 315 "parser.y"
                             { syntaxerrorno++; printf("SYNTAX ERROR : MISSING SEMICOLON\n");}
#line 1886 "parser.tab.c"
    break;

  case 42: /* return_stmt: RETURNKW expr SEMICOLON  */
#line 318 "parser.y"
        {
		printf("Found return statement");
		(yyval.ast) = createNode(node_return_stmt);
		(yyval.ast)->return_stmt.expr = (yyvsp[-1].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1897 "parser.tab.c"
    break;

  case 43: /* expr: term  */
#line 327 "parser.y"
        {
		(yyval.ast) = createNode(node_expr);
		(yyval.ast)->expr.left = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1907 "parser.tab.c"
    break;

  case 44: /* expr: expr MINUS term  */
#line 333 "parser.y"
        {
		printf("PARSER : Found  subtraction expression\n");
		(yyval.ast) = createNode(node_expr);
		(yyval.ast)->expr.operator = (yyvsp[-1].operator);
		(yyval.ast)->expr.left = (yyvsp[-2].ast);
		(yyval.ast)->expr.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1920 "parser.tab.c"
    break;

  case 45: /* expr: expr PLUS term  */
#line 342 "parser.y"
        {
		printf("PARSER : Found  addition expression\n");
		(yyval.ast) = createNode(node_expr);
		(yyval.ast)->expr.operator = (yyvsp[-1].operator);
		(yyval.ast)->expr.left = (yyvsp[-2].ast);
		(yyval.ast)->expr.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1933 "parser.tab.c"
    break;

  case 46: /* expr: expr MINUS error  */
#line 350 "parser.y"
                           {syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
#line 1939 "parser.tab.c"
    break;

  case 47: /* expr: error MINUS term  */
#line 351 "parser.y"
                                {syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
#line 1945 "parser.tab.c"
    break;

  case 48: /* expr: expr PLUS error  */
#line 352 "parser.y"
                          {syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
#line 1951 "parser.tab.c"
    break;

  case 49: /* expr: error PLUS term  */
#line 353 "parser.y"
                                {syntaxerrorno++; printf("Ln.%d: SYNTAX ERROR : Illegal statement\n", yylineno);}
#line 1957 "parser.tab.c"
    break;

  case 50: /* expr: array_index  */
#line 355 "parser.y"
        {
		printf("PARSER : Found  array_index expression\n");
		(yyval.ast) = createNode(node_expr);
		(yyval.ast)->expr.right = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 1968 "parser.tab.c"
    break;

  case 51: /* array_index: IDENTIFIER LBRACKET expr RBRACKET  */
#line 364 "parser.y"
{
	printf("PARSER: Found array_index\n");
	(yyval.ast) = createNode(node_array_index);
	(yyval.ast)->array_index.identifier = (yyvsp[-3].string);
	(yyval.ast)->array_index.index = (yyvsp[-1].ast);
	(yyval.ast)->lineno = yylineno;
}
#line 1980 "parser.tab.c"
    break;

  case 52: /* term: term DIV factor  */
#line 373 "parser.y"
        {
		printf("PARSER : Found  division expression\n");
		(yyval.ast) = createNode(node_term);
		(yyval.ast)->term.term = (yyvsp[-2].ast);
		(yyval.ast)->term.operator = (yyvsp[-1].operator);
		(yyval.ast)->term.factor = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
		
	}
#line 1994 "parser.tab.c"
    break;

  case 53: /* term: term MUL factor  */
#line 383 "parser.y"
        {
		printf("PARSER : Found  multiplication expression\n");
		(yyval.ast) = createNode(node_term);
		(yyval.ast)->term.term = (yyvsp[-2].ast);
		(yyval.ast)->term.operator = (yyvsp[-1].operator);
		(yyval.ast)->term.factor = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 2007 "parser.tab.c"
    break;

  case 54: /* term: factor  */
#line 392 "parser.y"
        {
		printf("PARSER : Found  factor\n"); 
		(yyval.ast) = createNode(node_term); 
		(yyval.ast)->term.factor = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 2018 "parser.tab.c"
    break;

  case 55: /* term: error DIV factor  */
#line 398 "parser.y"
                           {syntaxerrorno++; printf("Ln.%d : SYNTAX ERROR : Missing term in expression\n", yylineno);}
#line 2024 "parser.tab.c"
    break;

  case 56: /* term: error MUL factor  */
#line 399 "parser.y"
                           {syntaxerrorno++; printf("Ln.%d :SYNTAX ERROR : Missing term in expression\n", yylineno);}
#line 2030 "parser.tab.c"
    break;

  case 57: /* term: term DIV error  */
#line 400 "parser.y"
                         {syntaxerrorno++; printf("Ln.%d :SYNTAX ERROR : Missing factor in expression\n", yylineno);}
#line 2036 "parser.tab.c"
    break;

  case 58: /* term: term MUL error  */
#line 401 "parser.y"
                         {syntaxerrorno++; printf("Ln.%d :SYNTAX ERROR : Missing factor in expression\n", yylineno);}
#line 2042 "parser.tab.c"
    break;

  case 59: /* factor: LPAREN expr RPAREN  */
#line 404 "parser.y"
        {
	printf("PARSER : Found  parenthesis-enclosed expression\n");
	(yyval.ast) = createNode(node_factor);
	(yyval.ast)->lineno = yylineno;
	(yyval.ast)->factor.expr = (yyvsp[-1].ast);
	}
#line 2053 "parser.tab.c"
    break;

  case 60: /* factor: IDENTIFIER  */
#line 411 "parser.y"
        {
		printf("PARSER : Found  identifier\n");
		(yyval.ast) = createNode(node_factor);
		(yyval.ast)->factor.identifier = (yyvsp[0].string);
		(yyval.ast)->lineno = yylineno;
	}
#line 2064 "parser.tab.c"
    break;

  case 61: /* factor: number  */
#line 418 "parser.y"
        {	
		(yyval.ast) = createNode(node_factor);
		(yyval.ast)->factor.number = (yyvsp[0].ast);
		(yyval.ast)->lineno = yylineno;
	}
#line 2074 "parser.tab.c"
    break;

  case 62: /* number: FLOAT  */
#line 425 "parser.y"
        {
		printf("PARSER : Found  number - float\n");
		(yyval.ast) = createNode(node_number);
		(yyval.ast)->number.value = (yyvsp[0].string);
		(yyval.ast)->number.type = "float";
		(yyval.ast)->lineno = yylineno;
	}
#line 2086 "parser.tab.c"
    break;

  case 63: /* number: INT  */
#line 433 "parser.y"
        {
		printf("PARSER : Found  number - int\n");
		(yyval.ast) = createNode(node_number);
		(yyval.ast)->number.value = (yyvsp[0].string);
		(yyval.ast)->number.type = "int";
		(yyval.ast)->lineno = yylineno;
	}
#line 2098 "parser.tab.c"
    break;


#line 2102 "parser.tab.c"

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
          = {yyssp, yytoken};
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
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
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

#line 441 "parser.y"


int main(int argc, char** argv) {
	symbolTable = createSymbolTable(100); 
    yyin = fopen(argv[1], "r");  // Allow for dynamic file input 
    if (!yyin) {
        perror("fopen");
        return 1;
    }
    yyparse();  // Parse the entire input
    fclose(yyin);
	traverseAST(root, 0, ""); // Print out parse tree
	
	semanticAnalysis(root, symbolTable);
	printSymbolTable(symbolTable);

	printf("\n\nCOMPILATION REPORT\nLEXER : Lexical Errors: %d\nPARSER: Syntax Errors: %d\nSEM. ANALYZER: Semantic Errors: %d\n", lexerrorno, syntaxerrorno, semerrorno);
	if(lexerrorno != 0 | syntaxerrorno != 0 | semerrorno != 0)
	{
		printf("\nACTION : Please resolve noted errors before proceeding to code generation ! \n");
	} else 
	{
		printf("Source code is error-free! Continuing to intermediate representation & code generation\n");
	}

	// Release dynamic memory allocation
	
	deleteAST(root);
	deleteSymbolTable(symbolTable);
	return 0;
}
