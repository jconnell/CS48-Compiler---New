/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     READ = 260,
     WRITE = 261,
     BANG = 262,
     EQUALS = 263,
     NOTEQUALS = 264,
     GREATER = 265,
     GREATEREQ = 266,
     LESS = 267,
     LESSEQ = 268,
     DO = 269,
     WHILE = 270,
     FOR = 271,
     LPAREN = 272,
     RPAREN = 273,
     LBRACKET = 274,
     RBRACKET = 275,
     AND = 276,
     OR = 277,
     SEMI = 278,
     INT = 279,
     DOUBLE = 280,
     CHAR = 281,
     SWITCH = 282,
     CASE = 283,
     CONST = 284,
     CONTINUE = 285,
     DEFAULT = 286,
     RETURN = 287,
     SIZEOF = 288,
     STATIC = 289,
     VOID = 290,
     BREAK = 291,
     INCR = 292,
     DECR = 293,
     COMMENT = 294,
     INUM = 295,
     ID = 296,
     DIVIDE = 297,
     ASSIGN = 298,
     MULTIPLY = 299,
     ADD = 300,
     SUBTRACT = 301,
     FNUM = 302,
     STRING = 303
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define READ 260
#define WRITE 261
#define BANG 262
#define EQUALS 263
#define NOTEQUALS 264
#define GREATER 265
#define GREATEREQ 266
#define LESS 267
#define LESSEQ 268
#define DO 269
#define WHILE 270
#define FOR 271
#define LPAREN 272
#define RPAREN 273
#define LBRACKET 274
#define RBRACKET 275
#define AND 276
#define OR 277
#define SEMI 278
#define INT 279
#define DOUBLE 280
#define CHAR 281
#define SWITCH 282
#define CASE 283
#define CONST 284
#define CONTINUE 285
#define DEFAULT 286
#define RETURN 287
#define SIZEOF 288
#define STATIC 289
#define VOID 290
#define BREAK 291
#define INCR 292
#define DECR 293
#define COMMENT 294
#define INUM 295
#define ID 296
#define DIVIDE 297
#define ASSIGN 298
#define MULTIPLY 299
#define ADD 300
#define SUBTRACT 301
#define FNUM 302
#define STRING 303




/* Copy the first part of user declarations.  */
#line 9 "cs48.y"

#define YYPARSER /* distinguishes Yacc output from other code files */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokens.h"	/* from the lexer */
#include "ast.h"	/* for the node definitions and functions */

/*for verbose errors*/
#define YYERROR_VERBOSE 1

#define YYSTYPE ast_node
static ast_node savedTree; /* stores syntax tree for later return */
extern char *yytext;		/*the token's text from the lexxer*/


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 219 "cs48.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   608

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNRULES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      53,    54,     2,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,    49,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    56,     2,     2,     2,     2,
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
      45,    46,    47,    48,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    22,
      26,    28,    30,    32,    34,    38,    43,    50,    57,    64,
      66,    68,    69,    73,    75,    78,    81,    86,    91,    96,
      99,   100,   103,   104,   106,   108,   110,   112,   114,   116,
     118,   120,   122,   124,   132,   135,   137,   139,   141,   143,
     148,   152,   155,   157,   163,   171,   177,   185,   195,   197,
     198,   201,   205,   209,   211,   215,   219,   223,   225,   227,
     232,   236,   240,   244,   248,   252,   256,   260,   264,   268,
     272,   276,   280,   283,   286,   288,   291,   294,   297,   300,
     304,   309,   311,   313,   315,   317,   319,   324,   326,   327,
     331
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      59,     0,    -1,    60,    -1,    60,    61,    -1,    61,    -1,
      62,    -1,    67,    -1,    24,    63,    49,    -1,    25,    63,
      49,    -1,    63,    50,    66,    -1,    66,    -1,    41,    -1,
      40,    -1,    64,    -1,    64,    43,    89,    -1,    64,    51,
      65,    52,    -1,    24,    64,    53,    68,    54,    71,    -1,
      25,    64,    53,    68,    54,    71,    -1,    35,    64,    53,
      68,    54,    71,    -1,    69,    -1,    35,    -1,    -1,    69,
      50,    70,    -1,    70,    -1,    24,    64,    -1,    25,    64,
      -1,    24,    64,    51,    52,    -1,    25,    64,    51,    52,
      -1,    55,    72,    73,    56,    -1,    72,    62,    -1,    -1,
      73,    74,    -1,    -1,    79,    -1,    71,    -1,    80,    -1,
      81,    -1,    82,    -1,    83,    -1,    85,    -1,    86,    -1,
      88,    -1,    75,    -1,    27,    53,    90,    54,    55,    76,
      56,    -1,    76,    78,    -1,    78,    -1,    90,    -1,    40,
      -1,    47,    -1,    28,    77,    57,    73,    -1,    31,    57,
      73,    -1,    89,    49,    -1,    49,    -1,     3,    53,    89,
      54,    74,    -1,     3,    53,    89,    54,    74,     4,    74,
      -1,    15,    53,    89,    54,    74,    -1,    14,    74,    15,
      53,    89,    54,    49,    -1,    16,    53,    84,    49,    84,
      49,    84,    54,    74,    -1,    89,    -1,    -1,    32,    49,
      -1,    32,    89,    49,    -1,     5,    90,    49,    -1,    48,
      -1,     6,    89,    49,    -1,     6,    87,    49,    -1,    90,
      43,    89,    -1,    91,    -1,    64,    -1,    64,    51,    89,
      52,    -1,    89,    45,    89,    -1,    89,    46,    89,    -1,
      89,    44,    89,    -1,    89,    42,    89,    -1,    89,    12,
      89,    -1,    89,    13,    89,    -1,    89,    10,    89,    -1,
      89,    11,    89,    -1,    89,     8,    89,    -1,    89,     9,
      89,    -1,    89,    21,    89,    -1,    89,    22,    89,    -1,
       7,    89,    -1,    46,    89,    -1,    90,    -1,    37,    89,
      -1,    38,    89,    -1,    89,    37,    -1,    89,    38,    -1,
      53,    89,    54,    -1,    33,    53,    90,    54,    -1,    92,
      -1,    40,    -1,    47,    -1,    30,    -1,    36,    -1,    64,
      53,    93,    54,    -1,    94,    -1,    -1,    94,    50,    89,
      -1,    89,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    89,    89,   102,   112,   118,   120,   127,   158,   192,
     202,   208,   217,   226,   233,   238,   251,   258,   265,   275,
     277,   278,   282,   292,   299,   301,   303,   305,   311,   326,
     337,   342,   353,   359,   361,   363,   365,   367,   369,   371,
     373,   375,   377,   383,   393,   404,   409,   411,   414,   421,
     429,   437,   439,   448,   453,   463,   473,   482,   494,   497,
     505,   507,   513,   521,   530,   535,   543,   550,   555,   558,
     568,   574,   580,   586,   592,   598,   604,   610,   616,   622,
     628,   634,   640,   645,   650,   652,   657,   662,   667,   672,
     674,   679,   681,   686,   691,   693,   700,   728,   731,   736,
     746
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "READ", "WRITE", "BANG",
  "EQUALS", "NOTEQUALS", "GREATER", "GREATEREQ", "LESS", "LESSEQ", "DO",
  "WHILE", "FOR", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "AND", "OR",
  "SEMI", "INT", "DOUBLE", "CHAR", "SWITCH", "CASE", "CONST", "CONTINUE",
  "DEFAULT", "RETURN", "SIZEOF", "STATIC", "VOID", "BREAK", "INCR", "DECR",
  "COMMENT", "INUM", "ID", "DIVIDE", "ASSIGN", "MULTIPLY", "ADD",
  "SUBTRACT", "FNUM", "STRING", "';'", "','", "'['", "']'", "'('", "')'",
  "'{'", "'}'", "':'", "$accept", "program", "declaration_list",
  "declaration", "var_declaration", "var_decl_list", "idifier", "arraylen",
  "var_decl", "func_declaration", "formal_params", "formal_list",
  "formal_param", "compound_statement", "local_declarations",
  "statement_list", "statement", "switch_statement", "cases",
  "casecompare", "acase", "expression_statement", "if_statement",
  "while_statement", "do_while_statement", "for_statement",
  "for_header_expression", "return_statement", "read_statement", "strl",
  "write_statement", "expression", "var", "r_value", "call", "args",
  "arg_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   304,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,    59,
      44,    91,    93,    40,    41,   123,   125,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    65,    66,    66,    66,    67,    67,    67,    68,
      68,    68,    69,    69,    70,    70,    70,    70,    71,    72,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    75,    76,    76,    77,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    82,    83,    84,    84,
      85,    85,    86,    87,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    93,    93,    94,
      94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     3,     3,
       1,     1,     1,     1,     3,     4,     6,     6,     6,     1,
       1,     0,     3,     1,     2,     2,     4,     4,     4,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     2,     1,     1,     1,     1,     4,
       3,     2,     1,     5,     7,     5,     7,     9,     1,     0,
       2,     3,     3,     1,     3,     3,     3,     1,     1,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     1,     2,     2,     2,     2,     3,
       4,     1,     1,     1,     1,     1,     4,     1,     0,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     4,     5,     6,    11,
       0,    13,    10,     0,    13,     0,     1,     3,     7,     0,
       0,     0,    21,     8,    21,    21,    13,     9,     0,    94,
       0,    95,     0,     0,    92,     0,    93,     0,    68,    14,
      84,    67,    91,    12,     0,     0,     0,    20,     0,    19,
      23,     0,     0,    82,     0,    85,    86,    83,     0,     0,
      98,     0,     0,     0,     0,     0,     0,     0,     0,    87,
      88,     0,     0,     0,     0,     0,    15,    24,    25,     0,
       0,     0,     0,    68,     0,    89,     0,   100,     0,    97,
      78,    79,    76,    77,    74,    75,    80,    81,    73,    72,
      70,    71,    66,     0,     0,    30,    16,    22,    17,    18,
      90,    69,    96,     0,    26,    27,    32,    99,     0,     0,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    28,    34,    31,    42,    33,    35,    36,    37,    38,
      39,    40,    41,     0,     0,     0,    63,     0,     0,     0,
       0,    59,     0,    60,     0,    51,     0,    62,    65,    64,
       0,     0,     0,    58,     0,    61,     0,     0,     0,    59,
       0,    53,     0,    55,     0,     0,     0,     0,    59,     0,
       0,     0,    45,    54,    56,     0,    47,    48,     0,    46,
      32,    43,    44,     0,    32,    50,    57,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    10,    38,    44,    12,     8,
      48,    49,    50,   132,   116,   121,   133,   134,   181,   188,
     182,   135,   136,   137,   138,   139,   162,   140,   141,   147,
     142,   143,    40,    41,    42,    88,    89
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -154
static const yytype_int16 yypact[] =
{
     -18,   -10,   -10,   -10,    26,   -18,  -154,  -154,  -154,  -154,
     -37,   -32,  -154,    44,   -29,    -6,  -154,  -154,  -154,   -10,
      96,    34,   -15,  -154,   -15,   -15,   -14,  -154,    96,  -154,
      25,  -154,    96,    96,  -154,    96,  -154,    96,    35,   508,
      39,  -154,  -154,  -154,    40,   -10,   -10,  -154,    33,    45,
    -154,    56,    60,    14,   -10,    14,    14,    -2,   245,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,  -154,
    -154,    96,    96,    96,    96,    96,  -154,    64,    65,    68,
      73,    68,    68,    69,    71,  -154,   388,   508,    76,    77,
     545,   545,    67,    67,    67,    67,   562,   523,    14,    14,
      -2,    -2,   508,    79,    83,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,    96,  -154,  -154,    75,   508,   -10,   -10,
    -154,   152,    85,   -10,    43,   197,    87,    88,    91,   342,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,   406,    96,    98,  -154,    99,   448,   135,
      96,    96,   -10,  -154,   466,  -154,   263,  -154,  -154,  -154,
     100,   302,   103,   508,   102,  -154,   197,    96,   197,    96,
     105,   150,   320,  -154,   112,    10,   197,   114,    96,    24,
     108,   -23,  -154,  -154,  -154,   115,  -154,  -154,   113,  -154,
    -154,  -154,  -154,   197,  -154,   197,  -154,   197
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,  -154,   166,    58,     2,    -1,  -154,   153,  -154,
      82,  -154,    95,   -33,  -154,  -151,   -91,  -154,  -154,  -154,
      -4,  -154,  -154,  -154,  -154,  -154,  -153,  -154,  -154,  -154,
    -154,    -5,   -51,  -154,  -154,  -154,  -154
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      11,    14,    15,    84,    13,   179,     1,     2,   180,    45,
      46,    20,    18,    19,    20,    39,   174,     3,    26,    21,
      47,    22,    21,    53,    24,   185,    16,    55,    56,    20,
      57,     9,    58,   191,   149,    69,    70,    21,   179,   195,
      71,   180,    72,   197,    77,    78,   106,    25,   108,   109,
      28,    69,    70,    83,    86,    87,    90,    91,    92,    93,
      94,    95,    96,    97,   186,     9,    98,    99,   100,   101,
     102,   187,   145,    29,    43,   171,    30,   173,    54,    31,
      32,    33,    75,    34,     9,   183,    59,    79,    60,    35,
      36,   146,    76,    23,    19,    80,    37,    45,    46,   118,
     119,   164,   196,    28,    69,    70,    51,    52,   117,    71,
      81,    72,    73,    74,    82,   103,   104,    26,    26,   148,
      59,    13,    83,   105,   154,   110,    29,   113,   189,    30,
     112,   114,    31,    32,    33,   115,    34,     9,   144,   156,
     150,   151,    35,    36,   152,   161,   163,   157,   158,    37,
     160,    83,   169,   167,   176,   122,   170,   123,   124,    28,
     175,   178,   172,   184,   163,   190,   125,   126,   127,   193,
     194,    17,    27,   163,   120,   107,     0,   192,    83,   128,
       0,     0,    29,     0,   129,    30,     0,     0,    31,    32,
      33,     0,    34,     9,     0,     0,     0,     0,    35,    36,
     122,   130,   123,   124,    28,    37,     0,   105,   131,     0,
       0,   125,   126,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   128,     0,     0,    29,     0,   129,
      30,     0,     0,    31,    32,    33,     0,    34,     9,     0,
       0,     0,     0,    35,    36,     0,   130,     0,     0,     0,
      37,     0,   105,    61,    62,    63,    64,    65,    66,     0,
       0,     0,     0,     0,     0,     0,    67,    68,     0,     0,
       0,    61,    62,    63,    64,    65,    66,     0,     0,     0,
       0,     0,    69,    70,    67,    68,     0,    71,     0,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,    85,
      69,    70,     0,     0,     0,    71,     0,    72,    73,    74,
      61,    62,    63,    64,    65,    66,     0,   166,     0,     0,
       0,     0,     0,    67,    68,     0,     0,     0,    61,    62,
      63,    64,    65,    66,     0,     0,     0,     0,     0,    69,
      70,    67,    68,     0,    71,     0,    72,    73,    74,    28,
       0,     0,     0,     0,     0,     0,   168,    69,    70,     0,
       0,     0,    71,     0,    72,    73,    74,     0,     0,     0,
       0,     0,    29,     0,   177,    30,     0,     0,    31,    32,
      33,     0,    34,     9,     0,     0,     0,     0,    35,    36,
       0,   153,     0,     0,     0,    37,    61,    62,    63,    64,
      65,    66,     0,     0,     0,     0,     0,     0,     0,    67,
      68,     0,     0,     0,    61,    62,    63,    64,    65,    66,
       0,     0,     0,     0,     0,    69,    70,    67,    68,     0,
      71,     0,    72,    73,    74,     0,     0,     0,     0,     0,
     111,     0,     0,    69,    70,     0,     0,     0,    71,     0,
      72,    73,    74,     0,     0,   155,    61,    62,    63,    64,
      65,    66,     0,     0,     0,     0,     0,     0,     0,    67,
      68,     0,     0,     0,    61,    62,    63,    64,    65,    66,
       0,     0,     0,     0,     0,    69,    70,    67,    68,     0,
      71,     0,    72,    73,    74,     0,     0,   159,     0,     0,
       0,     0,     0,    69,    70,     0,     0,     0,    71,     0,
      72,    73,    74,     0,     0,   165,    61,    62,    63,    64,
      65,    66,     0,     0,     0,     0,     0,     0,     0,    67,
      68,    61,    62,    63,    64,    65,    66,     0,     0,     0,
       0,     0,     0,     0,    67,    69,    70,     0,     0,     0,
      71,     0,    72,    73,    74,    63,    64,    65,    66,     0,
      69,    70,     0,     0,     0,    71,     0,    72,    73,    74,
      61,    62,    63,    64,    65,    66,     0,     0,     0,     0,
       0,     0,    69,    70,     0,     0,     0,    71,     0,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,    69,
      70,     0,     0,     0,    71,     0,    72,    73,    74
};

static const yytype_int16 yycheck[] =
{
       1,     2,     3,    54,     2,    28,    24,    25,    31,    24,
      25,    43,    49,    50,    43,    20,   169,    35,    19,    51,
      35,    53,    51,    28,    53,   178,     0,    32,    33,    43,
      35,    41,    37,    56,   125,    37,    38,    51,    28,   190,
      42,    31,    44,   194,    45,    46,    79,    53,    81,    82,
       7,    37,    38,    54,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    40,    41,    71,    72,    73,    74,
      75,    47,   123,    30,    40,   166,    33,   168,    53,    36,
      37,    38,    43,    40,    41,   176,    51,    54,    53,    46,
      47,    48,    52,    49,    50,    50,    53,    24,    25,    24,
      25,   152,   193,     7,    37,    38,    24,    25,   113,    42,
      54,    44,    45,    46,    54,    51,    51,   118,   119,   124,
      51,   119,   123,    55,   129,    54,    30,    50,   179,    33,
      54,    52,    36,    37,    38,    52,    40,    41,    53,   144,
      53,    53,    46,    47,    53,   150,   151,    49,    49,    53,
      15,   152,    49,    53,     4,     3,    54,     5,     6,     7,
      55,    49,   167,    49,   169,    57,    14,    15,    16,    54,
      57,     5,    19,   178,   116,    80,    -1,   181,   179,    27,
      -1,    -1,    30,    -1,    32,    33,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
       3,    49,     5,     6,     7,    53,    -1,    55,    56,    -1,
      -1,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    30,    -1,    32,
      33,    -1,    -1,    36,    37,    38,    -1,    40,    41,    -1,
      -1,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,
      53,    -1,    55,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    -1,    -1,
      -1,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    -1,    37,    38,    21,    22,    -1,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      37,    38,    -1,    -1,    -1,    42,    -1,    44,    45,    46,
       8,     9,    10,    11,    12,    13,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    21,    22,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    37,
      38,    21,    22,    -1,    42,    -1,    44,    45,    46,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    37,    38,    -1,
      -1,    -1,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    54,    33,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
      -1,    49,    -1,    -1,    -1,    53,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      22,    -1,    -1,    -1,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    37,    38,    21,    22,    -1,
      42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    37,    38,    -1,    -1,    -1,    42,    -1,
      44,    45,    46,    -1,    -1,    49,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      22,    -1,    -1,    -1,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    37,    38,    21,    22,    -1,
      42,    -1,    44,    45,    46,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    -1,    -1,    42,    -1,
      44,    45,    46,    -1,    -1,    49,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      22,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    37,    38,    -1,    -1,    -1,
      42,    -1,    44,    45,    46,    10,    11,    12,    13,    -1,
      37,    38,    -1,    -1,    -1,    42,    -1,    44,    45,    46,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    -1,    -1,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    -1,    -1,    42,    -1,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    25,    35,    59,    60,    61,    62,    67,    41,
      63,    64,    66,    63,    64,    64,     0,    61,    49,    50,
      43,    51,    53,    49,    53,    53,    64,    66,     7,    30,
      33,    36,    37,    38,    40,    46,    47,    53,    64,    89,
      90,    91,    92,    40,    65,    24,    25,    35,    68,    69,
      70,    68,    68,    89,    53,    89,    89,    89,    89,    51,
      53,     8,     9,    10,    11,    12,    13,    21,    22,    37,
      38,    42,    44,    45,    46,    43,    52,    64,    64,    54,
      50,    54,    54,    64,    90,    54,    89,    89,    93,    94,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    51,    51,    55,    71,    70,    71,    71,
      54,    52,    54,    50,    52,    52,    72,    89,    24,    25,
      62,    73,     3,     5,     6,    14,    15,    16,    27,    32,
      49,    56,    71,    74,    75,    79,    80,    81,    82,    83,
      85,    86,    88,    89,    53,    90,    48,    87,    89,    74,
      53,    53,    53,    49,    89,    49,    89,    49,    49,    49,
      15,    89,    84,    89,    90,    49,    54,    53,    54,    49,
      54,    74,    89,    74,    84,    55,     4,    54,    49,    28,
      31,    76,    78,    74,    49,    84,    40,    47,    77,    90,
      57,    56,    78,    54,    57,    73,    74,    73
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
#line 90 "cs48.y"
    {
		(yyval) = createNode(ROOT);
		/*root must have a sequence as a child
		and that sequence will have all the declarations*/
		(yyval)->left_child = createNode(SEQ);
		(yyval)->left_child->left_child = (yyvsp[(1) - (1)]); 
		savedTree = (yyval); 
		;}
    break;

  case 3:
#line 103 "cs48.y"
    { YYSTYPE t = (yyvsp[(1) - (2)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(2) - (2)]);
                     (yyval) = (yyvsp[(1) - (2)]); 
		   }
                     else (yyval) = (yyvsp[(2) - (2)]);
                 ;}
    break;

  case 4:
#line 113 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 5:
#line 119 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 6:
#line 121 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 7:
#line 128 "cs48.y"
    {
		/*check for any ARRAY_SIZE nodes and declare those differently*/
		YYSTYPE t = (yyvsp[(2) - (3)]);
		/*this is just a dummy that will get overwritten*/
		(yyval) = createNode(INT_DEC);
		YYSTYPE v = (yyval);
		while(t != NULL)
		{
			/*if the ARRAY_SIZE thing is where expected, then we do an array dec*/
			if(t->left_child != NULL && t->left_child->node_type == ARRAY_SIZE)
			{
				v->right_sibling = createNode(INT_ARRAY_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			else
			{
				v->right_sibling = createNode(INT_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			v=v->right_sibling;
		}
		/*cleanup overwrite dummy original v and start where the good stuff starts*/
		v = (yyval);
		(yyval) = (yyval)->right_sibling;
		free(v);
		;}
    break;

  case 8:
#line 159 "cs48.y"
    {
		/*check for any ARRAY_SIZE nodes and declare those differently*/
		YYSTYPE t = (yyvsp[(2) - (3)]);
		/*this is just a dummy that will get overwritten*/
		(yyval) = createNode(DOU_DEC);
		YYSTYPE v = (yyval);
		while(t != NULL)
		{
			/*if the ARRAY_SIZE thing is where expected, then we do an array dec*/
			if(t->left_child != NULL && t->left_child->node_type == ARRAY_SIZE)
			{
				v->right_sibling = createNode(DOU_ARRAY_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			else
			{
				v->right_sibling = createNode(DOU_DEC); 
				v->right_sibling->left_child = t;
				t=t->right_sibling;
				v->right_sibling->left_child->right_sibling = NULL;
			}
			v=v->right_sibling;
		}
		/*cleanup overwrite dummy original v*/
		v = (yyval);
		(yyval) = (yyval)->right_sibling;
		free(v);
		;}
    break;

  case 9:
#line 193 "cs48.y"
    { YYSTYPE t = (yyvsp[(1) - (3)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(3) - (3)]);
                     (yyval) = (yyvsp[(1) - (3)]); 
		   }
                     else (yyval) = (yyvsp[(3) - (3)]);
                 ;}
    break;

  case 10:
#line 203 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 11:
#line 209 "cs48.y"
    {
		(yyval) = createNode(IDENTIFIER);
                   (yyval)->value.string = 
                         copyString(yytext);
		;}
    break;

  case 12:
#line 218 "cs48.y"
    {
			(yyval) = createNode(INT_LITERAL);
			(yyval)->value.int_value = atoi(yytext);
		;}
    break;

  case 13:
#line 227 "cs48.y"
    { 
		(yyval) = (yyvsp[(1) - (1)]);
                 ;}
    break;

  case 14:
#line 234 "cs48.y"
    {
		(yyval) = (yyvsp[(1) - (3)]);
		(yyval)->left_child = (yyvsp[(3) - (3)]);
		;}
    break;

  case 15:
#line 240 "cs48.y"
    {
			(yyval) = (yyvsp[(1) - (4)]);
			(yyval)->left_child = createNode(ARRAY_SIZE);
			(yyval)->left_child->left_child = (yyvsp[(3) - (4)]);
		;}
    break;

  case 16:
#line 252 "cs48.y"
    {
		(yyval) = createNode(FUNC_DEF);
		(yyval)->left_child = (yyvsp[(2) - (6)]);
		(yyval)->left_child->right_sibling = (yyvsp[(4) - (6)]);
		(yyval)->left_child->right_sibling->right_sibling = (yyvsp[(6) - (6)]);
		;}
    break;

  case 17:
#line 259 "cs48.y"
    {
		(yyval) = createNode(FUNC_DEF);
		(yyval)->left_child = (yyvsp[(2) - (6)]);
		(yyval)->left_child->right_sibling = (yyvsp[(4) - (6)]);
		(yyval)->left_child->right_sibling->right_sibling = (yyvsp[(6) - (6)]);
		;}
    break;

  case 18:
#line 266 "cs48.y"
    {
		(yyval) = createNode(FUNC_DEF);
		(yyval)->left_child = (yyvsp[(2) - (6)]);
		(yyval)->left_child->right_sibling = (yyvsp[(4) - (6)]);
		(yyval)->left_child->right_sibling->right_sibling = (yyvsp[(6) - (6)]);
		;}
    break;

  case 19:
#line 275 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 20:
#line 277 "cs48.y"
    {(yyval) = createNode(FUNC_PARAM);;}
    break;

  case 21:
#line 278 "cs48.y"
    {(yyval) = createNode(FUNC_PARAM);;}
    break;

  case 22:
#line 283 "cs48.y"
    { YYSTYPE t = (yyvsp[(1) - (3)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(3) - (3)]);
                     (yyval) = (yyvsp[(1) - (3)]); 
		   }
                     else (yyval) = (yyvsp[(3) - (3)]);
                 ;}
    break;

  case 23:
#line 293 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 24:
#line 300 "cs48.y"
    {(yyval) = createNode(FUNC_PARAM);;}
    break;

  case 25:
#line 302 "cs48.y"
    {(yyval) = createNode(FUNC_PARAM);;}
    break;

  case 26:
#line 304 "cs48.y"
    {(yyval) = createNode(FUNC_PARAM);;}
    break;

  case 27:
#line 306 "cs48.y"
    {(yyval) = createNode(FUNC_PARAM);;}
    break;

  case 28:
#line 312 "cs48.y"
    {
		(yyval) = createNode(SEQ);
		(yyval)->left_child = (yyvsp[(2) - (4)]);
		YYSTYPE t = (yyvsp[(2) - (4)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(3) - (4)]); 
		   }
		   else
			(yyval)->left_child = (yyvsp[(3) - (4)]);
		;}
    break;

  case 29:
#line 327 "cs48.y"
    { YYSTYPE t = (yyvsp[(1) - (2)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(2) - (2)]);
                     (yyval) = (yyvsp[(1) - (2)]); 
		   }
                     else (yyval) = (yyvsp[(2) - (2)]);
                 ;}
    break;

  case 30:
#line 337 "cs48.y"
    {
		(yyval) = NULL;
		;}
    break;

  case 31:
#line 343 "cs48.y"
    { YYSTYPE t = (yyvsp[(1) - (2)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(2) - (2)]);
                     (yyval) = (yyvsp[(1) - (2)]); 
		   }
                     else (yyval) = (yyvsp[(2) - (2)]);
                 ;}
    break;

  case 32:
#line 353 "cs48.y"
    {
		(yyval) = NULL;
		;}
    break;

  case 33:
#line 360 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 34:
#line 362 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 35:
#line 364 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 36:
#line 366 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 37:
#line 368 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 38:
#line 370 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 39:
#line 372 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 40:
#line 374 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 41:
#line 376 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 42:
#line 378 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 43:
#line 384 "cs48.y"
    {
		(yyval) = createNode(SWITCH_ST);
		(yyval)->left_child = (yyvsp[(3) - (7)]);
		(yyval)->left_child->right_sibling = (yyvsp[(6) - (7)]);
		printf("created switch\n");
		;}
    break;

  case 44:
#line 394 "cs48.y"
    {
		 YYSTYPE t = (yyvsp[(1) - (2)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(2) - (2)]);
                     (yyval) = (yyvsp[(1) - (2)]); 
		   }
                     else (yyval) = (yyvsp[(2) - (2)]);
		;}
    break;

  case 45:
#line 405 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 46:
#line 410 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 47:
#line 412 "cs48.y"
    {(yyval) = createNode(INT_LITERAL);
		(yyval)->value.int_value = atoi(yytext);;}
    break;

  case 48:
#line 415 "cs48.y"
    {(yyval) = createNode(DOUBLE_LITERAL);
		(yyval)->value.double_value = atof(yytext);;}
    break;

  case 49:
#line 422 "cs48.y"
    {
			(yyval) = createNode(SWITCH_CASE);
			(yyval)->left_child = (yyvsp[(2) - (4)]);
			(yyval)->left_child->right_sibling = (yyvsp[(4) - (4)]);
		;}
    break;

  case 50:
#line 430 "cs48.y"
    {
			(yyval) = createNode(SEQ);
			(yyval)->left_child = (yyvsp[(3) - (3)]);
		;}
    break;

  case 51:
#line 438 "cs48.y"
    { (yyval) = (yyvsp[(1) - (2)]); ;}
    break;

  case 52:
#line 440 "cs48.y"
    { (yyval) = NULL;;}
    break;

  case 53:
#line 449 "cs48.y"
    { (yyval) = createNode(IF_S);
		(yyval)->left_child = (yyvsp[(3) - (5)]);
		(yyval)->left_child->right_sibling = (yyvsp[(5) - (5)]);
		;}
    break;

  case 54:
#line 454 "cs48.y"
    { (yyval) = createNode(IF_ELSE);
		(yyval)->left_child = (yyvsp[(3) - (7)]);
		(yyval)->left_child->right_sibling = (yyvsp[(5) - (7)]);
		(yyval)->left_child->right_sibling->right_sibling = (yyvsp[(7) - (7)]);
		;}
    break;

  case 55:
#line 464 "cs48.y"
    {
			(yyval) = createNode(WHILE_LOOP);
			(yyval)->left_child = (yyvsp[(3) - (5)]);
			(yyval)->left_child->right_sibling = (yyvsp[(5) - (5)]);
		;}
    break;

  case 56:
#line 474 "cs48.y"
    {
			(yyval) = createNode(DO_WHILE_LOOP);
			(yyval)->left_child = (yyvsp[(5) - (7)]);
			(yyval)->left_child->right_sibling = (yyvsp[(2) - (7)]);
		;}
    break;

  case 57:
#line 483 "cs48.y"
    {
			(yyval) = createNode(FOR_LOOP);
			(yyval)->left_child = (yyvsp[(3) - (9)]);
			(yyval)->left_child->right_sibling = (yyvsp[(5) - (9)]);
			(yyval)->left_child->right_sibling->right_sibling = (yyvsp[(7) - (9)]);
			(yyval)->left_child->right_sibling->right_sibling->right_sibling = (yyvsp[(9) - (9)]);
		;}
    break;

  case 58:
#line 495 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 59:
#line 497 "cs48.y"
    {
			(yyval) = createNode(INT_LITERAL);
			
		;}
    break;

  case 60:
#line 506 "cs48.y"
    {(yyval) = createNode(RETURN_S);;}
    break;

  case 61:
#line 508 "cs48.y"
    {(yyval) = createNode(RETURN_S);
		(yyval)->left_child = (yyvsp[(2) - (3)]);;}
    break;

  case 62:
#line 514 "cs48.y"
    {
		(yyval) = createNode(READ_S);
		(yyval)->left_child = (yyvsp[(2) - (3)]);
		;}
    break;

  case 63:
#line 522 "cs48.y"
    {
			(yyval) = createNode(STRING_LITERAL);
			(yyval)->value.string = 
                         copyString(yytext);
		;}
    break;

  case 64:
#line 531 "cs48.y"
    {
		(yyval) = createNode(WRITE_S);
		(yyval)->left_child = (yyvsp[(2) - (3)]);
		;}
    break;

  case 65:
#line 536 "cs48.y"
    {
		(yyval) = createNode(WRITE_S);
		(yyval)->left_child = (yyvsp[(2) - (3)]);
		;}
    break;

  case 66:
#line 544 "cs48.y"
    {
		(yyval) = createNode(OP_ASSIGN);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 67:
#line 551 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 68:
#line 556 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 69:
#line 559 "cs48.y"
    {
		(yyval) = createNode(ARRAY_PULL);
		(yyval)->left_child = (yyvsp[(1) - (4)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (4)]);
		;}
    break;

  case 70:
#line 569 "cs48.y"
    {
		(yyval) = createNode(OP_PLUS);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 71:
#line 575 "cs48.y"
    {
		(yyval) = createNode(OP_MINUS);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 72:
#line 581 "cs48.y"
    {
		(yyval) = createNode(OP_TIMES);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 73:
#line 587 "cs48.y"
    {
		(yyval) = createNode(OP_DIVIDE);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 74:
#line 593 "cs48.y"
    {
		(yyval) = createNode(OP_LESS_THAN);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 75:
#line 599 "cs48.y"
    {
		(yyval) = createNode(OP_LESS_EQUALS);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 76:
#line 605 "cs48.y"
    {
		(yyval) = createNode(OP_GREATER_THAN);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 77:
#line 611 "cs48.y"
    {
		(yyval) = createNode(OP_GREATER_EQUALS);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 78:
#line 617 "cs48.y"
    {
		(yyval) = createNode(OP_EQUALS);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 79:
#line 623 "cs48.y"
    {
		(yyval) = createNode(OP_NOT_EQUALS);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 80:
#line 629 "cs48.y"
    {
		(yyval) = createNode(OP_AND);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 81:
#line 635 "cs48.y"
    {
		(yyval) = createNode(OP_OR);
		(yyval)->left_child = (yyvsp[(1) - (3)]);
		(yyval)->left_child->right_sibling = (yyvsp[(3) - (3)]);
		;}
    break;

  case 82:
#line 641 "cs48.y"
    {
		(yyval) = createNode(OP_NOT);
		(yyval)->left_child = (yyvsp[(2) - (2)]);
		;}
    break;

  case 83:
#line 646 "cs48.y"
    {
		(yyval) = createNode(OP_NEGATIVE);
		(yyval)->left_child = (yyvsp[(2) - (2)]);
		;}
    break;

  case 84:
#line 651 "cs48.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 85:
#line 653 "cs48.y"
    {
		(yyval) = createNode(OP_PRE_INCR);
		(yyval)->left_child = (yyvsp[(2) - (2)]);
		;}
    break;

  case 86:
#line 658 "cs48.y"
    {
		(yyval) = createNode(OP_PRE_DECR);
		(yyval)->left_child = (yyvsp[(2) - (2)]);
		;}
    break;

  case 87:
#line 663 "cs48.y"
    {
		(yyval) = createNode(OP_POST_INCR);
		(yyval)->left_child = (yyvsp[(1) - (2)]);
		;}
    break;

  case 88:
#line 668 "cs48.y"
    {
		(yyval) = createNode(OP_POST_DECR);
		(yyval)->left_child = (yyvsp[(1) - (2)]);
		;}
    break;

  case 89:
#line 673 "cs48.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 90:
#line 675 "cs48.y"
    {
			(yyval) = createNode(OP_SIZEOF);
			(yyval)->left_child = (yyvsp[(3) - (4)]);
		;}
    break;

  case 91:
#line 680 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 92:
#line 682 "cs48.y"
    {
		(yyval) = createNode(INT_LITERAL);
		(yyval)->value.int_value = atoi(yytext);
		;}
    break;

  case 93:
#line 687 "cs48.y"
    {
		(yyval) = createNode(DOUBLE_LITERAL);
		(yyval)->value.double_value = atof(yytext);
		;}
    break;

  case 94:
#line 692 "cs48.y"
    {(yyval) = createNode(CONTINUE_ST);;}
    break;

  case 95:
#line 694 "cs48.y"
    {(yyval) = createNode(BREAK_ST);;}
    break;

  case 96:
#line 701 "cs48.y"
    {
			(yyval) = createNode(FUNC_CALL);
			/*as per quads, we put params first, then id*/
			(yyval)->left_child = createNode(FUNC_PARAM);
			YYSTYPE t = (yyvsp[(3) - (4)]);
			YYSTYPE v = (yyval)->left_child;
                 	  if (t != NULL)
                 	  {
			(yyval)->left_child->left_child = t; 
			while (t->right_sibling != NULL)
			{
				YYSTYPE r = t->right_sibling;
				t->right_sibling = NULL;
				v->right_sibling = createNode(FUNC_PARAM);
				v->right_sibling->left_child = r;
                   	     	t = r;
				v=v->right_sibling;
			}
                   	  v->right_sibling = (yyvsp[(1) - (4)]); 
		  	 }
			else
				(yyval)->left_child->right_sibling = (yyvsp[(1) - (4)]);

		;}
    break;

  case 97:
#line 729 "cs48.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 98:
#line 731 "cs48.y"
    { (yyval) = NULL; ;}
    break;

  case 99:
#line 737 "cs48.y"
    { YYSTYPE t = (yyvsp[(1) - (3)]);
                   if (t != NULL)
                   { while (t->right_sibling != NULL)
                        t = t->right_sibling;
                     t->right_sibling = (yyvsp[(3) - (3)]);
                     (yyval) = (yyvsp[(1) - (3)]); 
		   }
                     else (yyval) = (yyvsp[(3) - (3)]);
                 ;}
    break;

  case 100:
#line 747 "cs48.y"
    {
		(yyval) = (yyvsp[(1) - (1)]);
		;}
    break;


/* Line 1267 of yacc.c.  */
#line 2502 "cs48.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 752 "cs48.y"


/*print out the syntax error and what line it occurred on*/
int yyerror(char * message)
{ printf("Syntax error at line %d: %s\n",lineno,message);
  printf("Current token: %s\n", yytext);
  //printToken(yychar,yytext);
  //Error = TRUE;
  return 0;
}

/*yparse() is called which will continue and call yylex() until
it reaches the end of the file*/
ast_node doParse(void)
{ 
	printf("doparse in cs48.y called\n");
	printf("yyparse returned %d\n\n", yyparse());
	return savedTree;
}

/* Function copyString allocates and makes a new
 * copy of an existing string 
	from Louden
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/*create a node of type type with its children set to NULL*/
ast_node createNode(int type)
{
	ast_node new_node = malloc(sizeof(struct ast_node_struct));
	new_node->left_child = new_node->right_sibling = NULL;
	new_node->node_type = type;
}


