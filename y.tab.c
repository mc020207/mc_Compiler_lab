/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.yacc"

#include<stdio.h>
#include "fdmjast.h"
#include "printast.h"
extern A_prog root;

extern int yylex();
extern void yyerror(char*);
extern int  yywrap();

// extern int yydebug = 1;



#line 85 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OP_PLUS = 258,
    OP_MINUS = 259,
    OP_MULTIPLY = 260,
    OP_DIVTION = 261,
    PUTINT = 262,
    PUTCH = 263,
    PUTARRAY = 264,
    GETINT = 265,
    GETCH = 266,
    GETARRAY = 267,
    MAIN = 268,
    INT = 269,
    PUBLIC = 270,
    CLASS = 271,
    IF = 272,
    ELSE = 273,
    WHILE = 274,
    CONTINUE = 275,
    BREAK = 276,
    RETURN = 277,
    STARTTIME = 278,
    STOPTIME = 279,
    TTRUE = 280,
    FFALSE = 281,
    LENGTH = 282,
    THIS = 283,
    NEW = 284,
    EXTENDS = 285,
    ID = 286,
    NUMBER = 287,
    UMINUS = 288
  };
#endif
/* Tokens.  */
#define OP_PLUS 258
#define OP_MINUS 259
#define OP_MULTIPLY 260
#define OP_DIVTION 261
#define PUTINT 262
#define PUTCH 263
#define PUTARRAY 264
#define GETINT 265
#define GETCH 266
#define GETARRAY 267
#define MAIN 268
#define INT 269
#define PUBLIC 270
#define CLASS 271
#define IF 272
#define ELSE 273
#define WHILE 274
#define CONTINUE 275
#define BREAK 276
#define RETURN 277
#define STARTTIME 278
#define STOPTIME 279
#define TTRUE 280
#define FFALSE 281
#define LENGTH 282
#define THIS 283
#define NEW 284
#define EXTENDS 285
#define ID 286
#define NUMBER 287
#define UMINUS 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "parser.yacc"

    A_pos token; // 例：符号
    A_pos key; // 关键字
    A_type type;
    A_prog prog;
    A_mainMethod mainMethod;
    A_classDecl classDecl;
    A_classDeclList classDeclList;
    A_methodDecl methodDecl;
    A_methodDeclList methodDeclList;
    A_formal formal;
    A_formalList formalList;
    A_varDecl varDecl;
    A_varDeclList varDeclList;
    A_stmList stmList;
    A_stm stm;
    A_exp exp;
    A_exp numberRest
    A_expList expList;

#line 221 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   434

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  210

#define YYUNDEFTOK  2
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,     2,     2,     2,     2,     2,
      35,    36,     2,     2,    34,     2,    43,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
       2,    40,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    68,    68,    74,    79,    83,    88,    92,    97,   101,
     106,   110,   115,   119,   124,   129,   133,   138,   142,   147,
     151,   156,   161,   165,   170,   174,   179,   184,   189,   194,
     199,   204,   209,   214,   219,   224,   229,   234,   239,   244,
     249,   254,   259,   264,   269,   274,   279,   284,   289,   294,
     299,   304,   309,   314,   319,   324,   329,   334,   339,   344,
     349,   354,   360,   365,   370,   375,   380,   385,   390,   395,
     400,   405,   410,   415,   421,   426,   431
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OP_PLUS", "OP_MINUS", "OP_MULTIPLY",
  "OP_DIVTION", "PUTINT", "PUTCH", "PUTARRAY", "GETINT", "GETCH",
  "GETARRAY", "MAIN", "INT", "PUBLIC", "CLASS", "IF", "ELSE", "WHILE",
  "CONTINUE", "BREAK", "RETURN", "STARTTIME", "STOPTIME", "TTRUE",
  "FFALSE", "LENGTH", "THIS", "NEW", "EXTENDS", "ID", "NUMBER", "UMINUS",
  "','", "'('", "')'", "'{'", "'}'", "';'", "'='", "'['", "']'", "'.'",
  "'!'", "$accept", "PROG", "STMLIST", "CLASSDECLLIST", "METHODDECLLIST",
  "FORMALLIST", "FORMALRESTLIST", "FORMALREST", "VARDECLLIST", "EXPLIST",
  "EXPRESTLIST", "EXPREST", "NUMBERLIST", "NUMBERRESTLIST", "NUMBERREST",
  "MAINMETHOD", "CLASSDECL", "VARDECL", "METHODDECL", "TYPE", "STM", "EXP", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    44,    40,    41,   123,   125,    59,
      61,    91,    93,    46,    33
};
# endif

#define YYPACT_NINF (-151)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,     3,    38,    43,    30,  -151,    40,  -151,    43,    41,
      18,  -151,    37,    57,    12,    54,    66,    -8,    75,    92,
      12,   151,    12,    39,    67,    82,    33,    76,    92,  -151,
     238,    80,    81,    83,    84,    86,    87,    89,    90,    88,
      91,   238,    94,    96,  -151,  -151,    97,  -151,    -6,  -151,
    -151,   180,   151,   238,    95,   151,    10,    92,  -151,   102,
     104,    99,    85,   105,   108,  -151,  -151,    27,   238,   238,
     238,   106,   107,   238,   238,   238,  -151,  -151,    15,   109,
     110,   238,   100,   112,   151,   251,   111,   391,  -151,  -151,
     238,   238,   238,   238,   238,   238,   113,   114,   101,    47,
    -151,   115,  -151,   119,   238,   125,   255,   271,    26,  -151,
    -151,   275,   296,   300,  -151,   126,   127,   316,   238,   128,
     131,  -151,  -151,    31,    31,    27,    27,   321,   325,   146,
    -151,  -151,  -151,   148,  -151,    33,   341,   152,   150,   154,
     238,  -151,   151,    73,  -151,  -151,  -151,   345,  -151,   238,
    -151,   156,   238,   118,   158,   166,  -151,   238,  -151,  -151,
     366,   181,  -151,  -151,  -151,   370,   209,   162,   374,   167,
     164,   163,   169,   168,   171,   151,  -151,   238,   350,   175,
     238,  -151,   182,   186,  -151,   167,   183,    12,    33,  -151,
     169,  -151,  -151,  -151,   185,  -151,  -151,   391,  -151,  -151,
    -151,  -151,   151,   194,  -151,   187,   189,  -151,  -151,  -151
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     6,     0,     1,     0,     2,     6,     0,
       0,     5,     0,     0,    15,     0,     0,     0,     0,     8,
      15,     4,    15,     0,     0,     0,     0,     0,     8,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,    64,     0,    67,     0,    66,
      62,     0,     4,     0,     0,     4,     0,     8,    30,     0,
       0,     0,    36,     0,     0,    28,     7,    71,     0,     0,
       0,     0,     0,     0,     0,     0,    47,    48,     0,     0,
       0,     0,     0,     0,     4,     0,     0,    70,    26,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,     0,    35,     0,     0,     0,     0,     0,     0,    74,
      75,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,    72,    38,    55,    56,    57,    58,     0,     0,    61,
      27,    31,    32,     0,    37,    10,     0,    61,     0,     0,
       0,    76,     0,     0,    53,    54,    65,     0,    69,     0,
      43,    59,    17,    22,     0,     0,    59,    17,    50,    51,
       0,    40,    42,    41,    68,     0,     0,     0,    19,    24,
       0,     0,    12,     0,     0,     0,    73,    17,     0,    60,
       0,    16,    19,     0,    21,    24,     0,    15,     0,     9,
      12,    60,    52,    39,     0,    44,    46,    20,    18,    25,
      23,    33,     4,     0,    11,     0,     0,    13,    45,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,   -49,   220,   -23,  -151,    42,  -151,   -20,  -150,
      48,  -151,  -151,    44,  -151,  -151,  -151,  -151,  -151,  -131,
    -133,   -29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    54,     7,    27,   154,   189,   190,    19,   167,
     181,   182,   170,   184,   185,     3,     8,    20,    28,    64,
      55,    56
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      29,    67,    57,    86,   155,    66,    89,   173,    82,   161,
     163,     1,    78,    90,    91,    92,    93,     4,    90,    91,
      92,    93,    85,    23,    87,    83,    17,   194,    18,    90,
      91,    92,    93,    24,    97,   120,    92,    93,     5,   106,
     107,   108,   193,     9,   111,   112,   113,    62,    13,    63,
      94,    95,   117,    96,   114,    14,   104,   203,   105,     6,
     140,   123,   124,   125,   126,   127,   128,   104,   104,   105,
     105,    10,   104,    15,   105,   136,    12,    30,    58,    59,
      31,    32,    33,    34,    35,    36,   132,   133,    16,   147,
      37,    21,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    22,    49,    50,    25,    26,    51,    60,
      52,   160,   162,    61,    65,    68,    69,    53,    70,    71,
     165,    72,    73,   168,    74,    75,   101,    76,   168,    79,
      77,    80,    81,    88,    98,    99,   102,   178,   100,   103,
     131,   118,   109,   110,   129,   115,   116,   119,   168,   122,
     169,   197,   130,   206,   135,    30,   137,   134,    31,    32,
      33,    34,    35,    36,   148,   144,   145,   202,    37,   149,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,   152,    49,    50,    30,   153,    51,   157,    52,   158,
      34,    35,    36,   159,   171,    53,   166,   172,   179,   175,
     187,   183,   186,   188,   191,    44,    45,    46,    47,    48,
     192,    49,    50,    30,   196,    51,   180,    84,   199,    34,
      35,    36,   201,   205,    53,   207,   208,   209,    11,   200,
     198,     0,   204,     0,    44,    45,    46,    47,    48,     0,
      49,    50,    30,     0,    51,     0,   177,     0,    34,    35,
      36,     0,     0,    53,    90,    91,    92,    93,    90,    91,
      92,    93,     0,    44,    45,    46,    47,    48,     0,    49,
      50,     0,     0,    51,    90,    91,    92,    93,    90,    91,
      92,    93,    53,     0,     0,     0,     0,   121,     0,     0,
       0,   138,   104,     0,   105,     0,   104,     0,   105,    90,
      91,    92,    93,    90,    91,    92,    93,   139,     0,     0,
       0,   141,   104,     0,   105,     0,   104,     0,   105,    90,
      91,    92,    93,     0,    90,    91,    92,    93,    90,    91,
      92,    93,   142,     0,     0,     0,   143,   104,     0,   105,
       0,   104,     0,   105,    90,    91,    92,    93,    90,    91,
      92,    93,   146,    90,    91,    92,    93,   104,     0,   105,
     150,     0,   104,     0,   105,     0,   104,   151,   105,    90,
      91,    92,    93,    90,    91,    92,    93,    90,    91,    92,
      93,     0,   104,   156,   105,     0,   104,   164,   105,   195,
       0,   104,     0,   105,    90,    91,    92,    93,     0,     0,
       0,     0,   174,     0,     0,     0,   176,   104,   180,   105,
       0,   104,     0,   105,     0,   104,     0,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   104,     0,   105
};

static const yytype_int16 yycheck[] =
{
      20,    30,    22,    52,   135,    28,    55,   157,    14,   142,
     143,    15,    41,     3,     4,     5,     6,    14,     3,     4,
       5,     6,    51,    31,    53,    31,    14,   177,    16,     3,
       4,     5,     6,    41,    57,    84,     5,     6,     0,    68,
      69,    70,   175,    13,    73,    74,    75,    14,    30,    16,
      40,    41,    81,    43,    39,    37,    41,   188,    43,    16,
      34,    90,    91,    92,    93,    94,    95,    41,    41,    43,
      43,    31,    41,    36,    43,   104,    35,     4,    39,    40,
       7,     8,     9,    10,    11,    12,    39,    40,    31,   118,
      17,    37,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    37,    31,    32,    31,    15,    35,    42,
      37,   140,    39,    31,    38,    35,    35,    44,    35,    35,
     149,    35,    35,   152,    35,    35,    41,    39,   157,    35,
      39,    35,    35,    38,    32,    31,    31,   166,    39,    31,
      39,    41,    36,    36,    31,    36,    36,    35,   177,    38,
      32,   180,    38,   202,    35,     4,    31,    42,     7,     8,
       9,    10,    11,    12,    36,    39,    39,   187,    17,    38,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    35,    31,    32,     4,    37,    35,    35,    37,    39,
      10,    11,    12,    39,    36,    44,    40,    31,    36,    18,
      37,    34,    38,    34,    36,    25,    26,    27,    28,    29,
      39,    31,    32,     4,    39,    35,    34,    37,    32,    10,
      11,    12,    39,    38,    44,    31,    39,    38,     8,   185,
     182,    -1,   190,    -1,    25,    26,    27,    28,    29,    -1,
      31,    32,     4,    -1,    35,    -1,    37,    -1,    10,    11,
      12,    -1,    -1,    44,     3,     4,     5,     6,     3,     4,
       5,     6,    -1,    25,    26,    27,    28,    29,    -1,    31,
      32,    -1,    -1,    35,     3,     4,     5,     6,     3,     4,
       5,     6,    44,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    36,    41,    -1,    43,    -1,    41,    -1,    43,     3,
       4,     5,     6,     3,     4,     5,     6,    36,    -1,    -1,
      -1,    36,    41,    -1,    43,    -1,    41,    -1,    43,     3,
       4,     5,     6,    -1,     3,     4,     5,     6,     3,     4,
       5,     6,    36,    -1,    -1,    -1,    36,    41,    -1,    43,
      -1,    41,    -1,    43,     3,     4,     5,     6,     3,     4,
       5,     6,    36,     3,     4,     5,     6,    41,    -1,    43,
      39,    -1,    41,    -1,    43,    -1,    41,    42,    43,     3,
       4,     5,     6,     3,     4,     5,     6,     3,     4,     5,
       6,    -1,    41,    42,    43,    -1,    41,    42,    43,    39,
      -1,    41,    -1,    43,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    36,    41,    34,    43,
      -1,    41,    -1,    43,    -1,    41,    -1,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    15,    46,    60,    14,     0,    16,    48,    61,    13,
      31,    48,    35,    30,    37,    36,    31,    14,    16,    53,
      62,    37,    37,    31,    41,    31,    15,    49,    63,    53,
       4,     7,     8,     9,    10,    11,    12,    17,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    31,
      32,    35,    37,    44,    47,    65,    66,    53,    39,    40,
      42,    31,    14,    16,    64,    38,    49,    66,    35,    35,
      35,    35,    35,    35,    35,    35,    39,    39,    66,    35,
      35,    35,    14,    31,    37,    66,    47,    66,    38,    47,
       3,     4,     5,     6,    40,    41,    43,    49,    32,    31,
      39,    41,    31,    31,    41,    43,    66,    66,    66,    36,
      36,    66,    66,    66,    39,    36,    36,    66,    41,    35,
      47,    36,    38,    66,    66,    66,    66,    66,    66,    31,
      38,    39,    39,    40,    42,    35,    66,    31,    36,    36,
      34,    36,    36,    36,    39,    39,    36,    66,    36,    38,
      39,    42,    35,    37,    50,    64,    42,    35,    39,    39,
      66,    65,    39,    65,    42,    66,    40,    54,    66,    32,
      57,    36,    31,    54,    36,    18,    36,    37,    66,    36,
      34,    55,    56,    34,    58,    59,    38,    37,    34,    51,
      52,    36,    39,    65,    54,    39,    39,    66,    55,    32,
      58,    39,    53,    64,    51,    38,    47,    31,    39,    38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    53,    53,    54,    54,    55,    55,
      56,    57,    57,    58,    58,    59,    60,    61,    61,    62,
      62,    62,    62,    62,    63,    64,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     0,     2,     0,     3,
       0,     2,     0,     3,     2,     0,     2,     0,     2,     0,
       2,     2,     0,     2,     0,     2,     8,     8,     6,     4,
       3,     5,     5,     9,    10,     2,     1,     3,     3,     7,
       5,     5,     5,     4,     7,     9,     7,     2,     2,     3,
       5,     5,     7,     4,     4,     3,     3,     3,     3,     4,
       6,     3,     1,     1,     1,     4,     1,     1,     5,     4,
       2,     2,     3,     6,     3,     3,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 69 "parser.yacc"
    {
        root=A_Prog((yyvsp[-1].mainMethod)->pos,(yyvsp[-1].mainMethod),(yyvsp[0].classDeclList));
        (yyval.prog)=root;
    }
#line 1572 "y.tab.c"
    break;

  case 3:
#line 75 "parser.yacc"
    {
        (yyval.stmList)=A_StmList((yyvsp[-1].stm),(yyvsp[0].stmList));
    }
#line 1580 "y.tab.c"
    break;

  case 4:
#line 79 "parser.yacc"
    {
        (yyval.stmList)=NULL;
    }
#line 1588 "y.tab.c"
    break;

  case 5:
#line 84 "parser.yacc"
    {
        (yyval.classDeclList)=A_ClassDeclList((yyvsp[-1].classDecl),(yyvsp[0].classDeclList));
    }
#line 1596 "y.tab.c"
    break;

  case 6:
#line 88 "parser.yacc"
    {
        (yyval.classDeclList)=NULL:
    }
#line 1604 "y.tab.c"
    break;

  case 7:
#line 93 "parser.yacc"
    {
        (yyval.methodDeclList)=A_MethodDeclList((yyvsp[-1].methodDecl),(yyvsp[0].methodDeclList));
    }
#line 1612 "y.tab.c"
    break;

  case 8:
#line 97 "parser.yacc"
    {
        (yyval.methodDeclList)=NULL;
    }
#line 1620 "y.tab.c"
    break;

  case 9:
#line 102 "parser.yacc"
    {
        
    }
#line 1628 "y.tab.c"
    break;

  case 10:
#line 106 "parser.yacc"
    {
        (yyval.formalList)=NULL;
    }
#line 1636 "y.tab.c"
    break;

  case 11:
#line 111 "parser.yacc"
    {
        
    }
#line 1644 "y.tab.c"
    break;

  case 12:
#line 115 "parser.yacc"
    {
        (yyval.formalList)=NULL;
    }
#line 1652 "y.tab.c"
    break;

  case 13:
#line 120 "parser.yacc"
    {

    }
#line 1660 "y.tab.c"
    break;

  case 14:
#line 125 "parser.yacc"
    {
        (yyval.varDeclList)=A_VarDeclList((yyvsp[-1].varDecl),(yyvsp[0].varDeclList));
    }
#line 1668 "y.tab.c"
    break;

  case 15:
#line 129 "parser.yacc"
    {
        (yyval.varDeclList)=NULL;
    }
#line 1676 "y.tab.c"
    break;

  case 16:
#line 134 "parser.yacc"
    {
        
    }
#line 1684 "y.tab.c"
    break;

  case 17:
#line 138 "parser.yacc"
    {
        (yyval.expList)=NULL;
    }
#line 1692 "y.tab.c"
    break;

  case 18:
#line 143 "parser.yacc"
    {
        
    }
#line 1700 "y.tab.c"
    break;

  case 19:
#line 147 "parser.yacc"
    {
        (yyval.expList)=NULL;
    }
#line 1708 "y.tab.c"
    break;

  case 20:
#line 152 "parser.yacc"
    {

    }
#line 1716 "y.tab.c"
    break;

  case 21:
#line 157 "parser.yacc"
    {
        (yyval.expList)=A_ExpList((yyvsp[-1].exp),(yyvsp[0].expList));
    }
#line 1724 "y.tab.c"
    break;

  case 22:
#line 161 "parser.yacc"
    {
        (yyval.expList)=NULL;
    }
#line 1732 "y.tab.c"
    break;

  case 23:
#line 166 "parser.yacc"
    {
        (yyval.expList)=A_ExpList((yyvsp[-1].exp),(yyvsp[0].expList));
    }
#line 1740 "y.tab.c"
    break;

  case 24:
#line 170 "parser.yacc"
    {
        (yyval.expList)=NULL;
    }
#line 1748 "y.tab.c"
    break;

  case 25:
#line 175 "parser.yacc"
    {
        (yyval.exp)=(yyvsp[0].exp)
    }
#line 1756 "y.tab.c"
    break;

  case 26:
#line 180 "parser.yacc"
    {
        (yyval.mainMethod)=A_MainMethod((yyvsp[-7].key),NULL,(yyvsp[-1].stmList));
    }
#line 1764 "y.tab.c"
    break;

  case 27:
#line 185 "parser.yacc"
    {   
        
    }
#line 1772 "y.tab.c"
    break;

  case 28:
#line 190 "parser.yacc"
    {

    }
#line 1780 "y.tab.c"
    break;

  case 29:
#line 195 "parser.yacc"
    {

    }
#line 1788 "y.tab.c"
    break;

  case 30:
#line 200 "parser.yacc"
    {

    }
#line 1796 "y.tab.c"
    break;

  case 31:
#line 205 "parser.yacc"
    {

    }
#line 1804 "y.tab.c"
    break;

  case 32:
#line 210 "parser.yacc"
    {

    }
#line 1812 "y.tab.c"
    break;

  case 33:
#line 215 "parser.yacc"
    {
        
    }
#line 1820 "y.tab.c"
    break;

  case 34:
#line 220 "parser.yacc"
    {

    }
#line 1828 "y.tab.c"
    break;

  case 35:
#line 225 "parser.yacc"
    {

    }
#line 1836 "y.tab.c"
    break;

  case 36:
#line 230 "parser.yacc"
    {

    }
#line 1844 "y.tab.c"
    break;

  case 37:
#line 235 "parser.yacc"
    {
        
    }
#line 1852 "y.tab.c"
    break;

  case 38:
#line 240 "parser.yacc"
    {

    }
#line 1860 "y.tab.c"
    break;

  case 39:
#line 245 "parser.yacc"
    {

    }
#line 1868 "y.tab.c"
    break;

  case 40:
#line 250 "parser.yacc"
    {

    }
#line 1876 "y.tab.c"
    break;

  case 41:
#line 255 "parser.yacc"
    {

    }
#line 1884 "y.tab.c"
    break;

  case 42:
#line 260 "parser.yacc"
    {

    }
#line 1892 "y.tab.c"
    break;

  case 43:
#line 265 "parser.yacc"
    {
        (yyval.stm)=A_AssignStm((yyvsp[-3].exp)->pos,(yyvsp[-3].exp),NULL,(yyvsp[-1].exp));
    }
#line 1900 "y.tab.c"
    break;

  case 44:
#line 270 "parser.yacc"
    {

    }
#line 1908 "y.tab.c"
    break;

  case 45:
#line 275 "parser.yacc"
    {

    }
#line 1916 "y.tab.c"
    break;

  case 46:
#line 280 "parser.yacc"
    {

    }
#line 1924 "y.tab.c"
    break;

  case 47:
#line 285 "parser.yacc"
    {

    }
#line 1932 "y.tab.c"
    break;

  case 48:
#line 290 "parser.yacc"
    {

    }
#line 1940 "y.tab.c"
    break;

  case 49:
#line 295 "parser.yacc"
    {

    }
#line 1948 "y.tab.c"
    break;

  case 50:
#line 300 "parser.yacc"
    {
        (yyval.stm)=A_Putint((yyvsp[-4].key),(yyvsp[-2].exp));
    }
#line 1956 "y.tab.c"
    break;

  case 51:
#line 305 "parser.yacc"
    {
        (yyval.stm)=A_Putint((yyvsp[-4].key),(yyvsp[-2].exp));
    }
#line 1964 "y.tab.c"
    break;

  case 52:
#line 310 "parser.yacc"
    {

    }
#line 1972 "y.tab.c"
    break;

  case 53:
#line 315 "parser.yacc"
    {

    }
#line 1980 "y.tab.c"
    break;

  case 54:
#line 320 "parser.yacc"
    {

    }
#line 1988 "y.tab.c"
    break;

  case 55:
#line 325 "parser.yacc"
    {
        (yyval.exp)=A_OpExp((yyvsp[-2].exp)->pos,(yyvsp[-2].exp),A_plus,(yyvsp[0].exp));
    }
#line 1996 "y.tab.c"
    break;

  case 56:
#line 330 "parser.yacc"
    {
        (yyval.exp)=A_OpExp((yyvsp[-2].exp)->pos,(yyvsp[-2].exp),A_minus,(yyvsp[0].exp));
    }
#line 2004 "y.tab.c"
    break;

  case 57:
#line 335 "parser.yacc"
    {
        (yyval.exp)=A_OpExp((yyvsp[-2].exp)->pos,(yyvsp[-2].exp),A_times,(yyvsp[0].exp));
    }
#line 2012 "y.tab.c"
    break;

  case 58:
#line 340 "parser.yacc"
    {
        (yyval.exp)=A_OpExp((yyvsp[-2].exp)->pos,(yyvsp[-2].exp),A_div,(yyvsp[0].exp));
    }
#line 2020 "y.tab.c"
    break;

  case 59:
#line 345 "parser.yacc"
    {

    }
#line 2028 "y.tab.c"
    break;

  case 60:
#line 350 "parser.yacc"
    {

    }
#line 2036 "y.tab.c"
    break;

  case 61:
#line 356 "parser.yacc"
    {

    }
#line 2044 "y.tab.c"
    break;

  case 62:
#line 361 "parser.yacc"
    {
        (yyval.exp)=(yyvsp[0].exp);
    }
#line 2052 "y.tab.c"
    break;

  case 63:
#line 366 "parser.yacc"
    {

    }
#line 2060 "y.tab.c"
    break;

  case 64:
#line 371 "parser.yacc"
    {

    }
#line 2068 "y.tab.c"
    break;

  case 65:
#line 376 "parser.yacc"
    {

    }
#line 2076 "y.tab.c"
    break;

  case 66:
#line 381 "parser.yacc"
    {
        (yyval.exp)=(yyvsp[0].exp);
    }
#line 2084 "y.tab.c"
    break;

  case 67:
#line 386 "parser.yacc"
    {

    }
#line 2092 "y.tab.c"
    break;

  case 68:
#line 391 "parser.yacc"
    {

    }
#line 2100 "y.tab.c"
    break;

  case 69:
#line 396 "parser.yacc"
    {

    }
#line 2108 "y.tab.c"
    break;

  case 70:
#line 401 "parser.yacc"
    {

    }
#line 2116 "y.tab.c"
    break;

  case 71:
#line 406 "parser.yacc"
    {
        (yyval.exp)=A_MinusExp((yyvsp[-1].token),(yyvsp[0].exp));
    }
#line 2124 "y.tab.c"
    break;

  case 72:
#line 411 "parser.yacc"
    {
        (yyval.exp)=(yyvsp[-1].exp);
    }
#line 2132 "y.tab.c"
    break;

  case 73:
#line 416 "parser.yacc"
    {
        if ((yyvsp[-3].stmList)==NULL) (yyval.exp)=A_EscExp(NULL, (yyvsp[-3].stmList) , (yyvsp[-1].exp));
        else (yyval.exp)=A_EscExp((yyvsp[-3].stmList)->head->pos, (yyvsp[-3].stmList) , (yyvsp[-1].exp));
    }
#line 2141 "y.tab.c"
    break;

  case 74:
#line 422 "parser.yacc"
    {
        
    }
#line 2149 "y.tab.c"
    break;

  case 75:
#line 427 "parser.yacc"
    {
        
    }
#line 2157 "y.tab.c"
    break;

  case 76:
#line 432 "parser.yacc"
    {

    }
#line 2165 "y.tab.c"
    break;


#line 2169 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 435 "parser.yacc"


void yyerror(s)
char *s;
{
    fprintf(stderr, "%s\n",s);
}

int yywrap()
{
    return(1);
}
