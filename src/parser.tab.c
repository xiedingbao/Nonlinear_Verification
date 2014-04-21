/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include "Automaton.h"

	#define DEBUG false

	bool syntax_error=false;
	extern int yylex();
	extern int inputbound;
  	extern unsigned int line_number;
	Automaton *aut;	
	string target;

	void yyerror(const char *msg){	
		syntax_error=true;
     		printf("Parse error in line %d: ", line_number);
      		printf("%s\n", msg);
		exit(1);
	}
	void yyerror(const string s){
     		yyerror(s.c_str());
	}
	int check_var(string name){
		int id = aut->getIDForVar(name);
		if(id < 0){
			yyerror("Unknown identifier '" + name +"'.");;
			exit(1);
		}
		return id;
	}


/* Line 371 of yacc.c  */
#line 102 "parser.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EVENTS = 258,
     AUTOMATON = 259,
     VAR = 260,
     SYNCLABS = 261,
     INITIALLY = 262,
     LOC = 263,
     WHILE = 264,
     WAIT = 265,
     WHEN = 266,
     DO = 267,
     SYNC = 268,
     GOTO = 269,
     END = 270,
     ASSIGN = 271,
     FORBIDDEN = 272,
     TRUE = 273,
     FALSE = 274,
     AND = 275,
     NUM = 276,
     IDENT = 277,
     OEQ2 = 278,
     OEQ = 279,
     OLT = 280,
     OGT = 281,
     OLE = 282,
     OGE = 283,
     PRIM = 284,
     uminus = 285
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 49 "parser.y"

	char * mystring;
	Automaton* automaton;
	vector<State>* locationlist;
	vector<string>* varlist;
	vector<Solution>* ODElist;
	vector<Transition>* transitionlist;
	vector<PolynomialConstraint>* conlist;
	vector<resetMap>* resetlist;
	resetMap* reset;
	Solution* ODE;	
	State* state;
	Transition* transition;	
	Polynomial* poly;
	PolynomialConstraint* polycon;


/* Line 387 of yacc.c  */
#line 193 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 221 "parser.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   164

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  148

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,     2,     2,     2,    23,     2,
      35,    36,    32,    30,    45,    31,    40,    33,    47,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    43,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    39,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    46,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    24,    25,
      26,    27,    28,    29,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    23,    24,
      30,    34,    35,    38,    41,    46,    50,    52,    57,    61,
      63,    68,    70,    73,    75,    78,    82,    92,    95,    96,
     108,   116,   120,   122,   127,   129,   131,   133,   137,   139,
     143,   145,   149,   153,   157,   161,   165,   167,   171,   175,
     179,   183,   187,   190,   192,   194,   198,   200,   207,   211,
     215,   219,   223,   227,   230,   232,   237
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    50,    51,    -1,    51,    -1,
      52,    -1,    53,    -1,    17,    24,    22,    40,    41,    22,
      42,    43,    -1,    -1,     4,    22,    54,    55,    15,    -1,
      56,    63,    61,    -1,    -1,    56,    59,    -1,    56,    57,
      -1,     6,    44,    58,    43,    -1,    58,    45,    22,    -1,
      22,    -1,     5,    44,    60,    43,    -1,    60,    45,    22,
      -1,    22,    -1,     7,    44,    62,    43,    -1,    22,    -1,
      63,    64,    -1,    64,    -1,    65,    66,    -1,    65,    43,
      66,    -1,     8,    22,    44,     9,    70,    10,    41,    76,
      42,    -1,    66,    67,    -1,    -1,    11,    71,    13,    22,
      12,    41,    68,    42,    14,    22,    43,    -1,    11,    71,
      13,    22,    14,    22,    43,    -1,    68,    23,    69,    -1,
      69,    -1,    22,    37,    16,    75,    -1,    72,    -1,    18,
      -1,    72,    -1,    73,    23,    72,    -1,    73,    -1,    35,
      72,    36,    -1,    74,    -1,    75,    29,    21,    -1,    75,
      28,    21,    -1,    75,    27,    21,    -1,    75,    26,    21,
      -1,    75,    25,    21,    -1,    18,    -1,    75,    30,    75,
      -1,    75,    31,    75,    -1,    35,    75,    36,    -1,    75,
      32,    75,    -1,    75,    39,    21,    -1,    31,    75,    -1,
      22,    -1,    21,    -1,    76,    20,    77,    -1,    77,    -1,
      22,    35,    46,    36,    24,    78,    -1,    78,    30,    78,
      -1,    78,    31,    78,    -1,    35,    78,    36,    -1,    78,
      32,    78,    -1,    78,    39,    21,    -1,    31,    78,    -1,
      46,    -1,    22,    35,    47,    36,    -1,    21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   107,   108,   112,   113,   118,   134,   134,
     148,   151,   153,   154,   158,   162,   166,   171,   178,   183,
     191,   195,   214,   215,   219,   229,   233,   259,   265,   269,
     280,   292,   298,   306,   316,   320,   323,   330,   337,   344,
     352,   359,   364,   369,   374,   379,   384,   388,   395,   402,
     407,   414,   434,   441,   457,   465,   471,   479,   487,   494,
     501,   506,   513,   534,   540,   554,   568
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EVENTS", "AUTOMATON", "VAR", "SYNCLABS",
  "INITIALLY", "LOC", "WHILE", "WAIT", "WHEN", "DO", "SYNC", "GOTO", "END",
  "ASSIGN", "FORBIDDEN", "TRUE", "FALSE", "AND", "NUM", "IDENT", "'&'",
  "OEQ2", "OEQ", "OLT", "OGT", "OLE", "OGE", "'+'", "'-'", "'*'", "'/'",
  "'!'", "'('", "')'", "PRIM", "uminus", "'^'", "'.'", "'{'", "'}'", "';'",
  "':'", "','", "'t'", "'0'", "$accept", "program", "commands", "command",
  "forbidden", "automaton", "$@1", "automaton_body", "declaration",
  "synclab", "ident_list", "vars", "var_list", "initial", "initial_state",
  "location_list", "location_block", "location", "transition_list",
  "transition", "assign_set", "assign_set_no_and", "invariant_set",
  "guard_set", "constr_list", "constr_list_no_and", "constraint",
  "polynomial", "ODES", "ODEsolution", "ODEpolynomial", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    38,   278,   279,   280,   281,   282,   283,
      43,    45,    42,    47,    33,    40,    41,   284,   285,    94,
      46,   123,   125,    59,    58,    44,   116,    48
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    54,    53,
      55,    56,    56,    56,    57,    58,    58,    59,    60,    60,
      61,    62,    63,    63,    64,    64,    65,    66,    66,    67,
      67,    68,    68,    69,    70,    70,    71,    72,    72,    72,
      73,    74,    74,    74,    74,    74,    74,    75,    75,    75,
      75,    75,    75,    75,    75,    76,    76,    77,    78,    78,
      78,    78,    78,    78,    78,    78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     8,     0,     5,
       3,     0,     2,     2,     4,     3,     1,     4,     3,     1,
       4,     1,     2,     1,     2,     3,     9,     2,     0,    11,
       7,     3,     1,     4,     1,     1,     1,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     3,     2,     1,     1,     3,     1,     6,     3,     3,
       3,     3,     3,     2,     1,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     5,     6,     8,     0,
       1,     3,    11,     0,     0,     0,     0,     9,     0,     0,
       0,    13,    12,     0,    23,    28,     0,     0,     0,     0,
       0,    10,    22,    28,    24,     0,    19,     0,    16,     0,
       0,     0,    25,     0,    27,     0,    17,     0,    14,     0,
       0,    21,     0,    46,    54,    53,     0,     0,     0,    36,
      38,    40,     0,     7,    18,    15,    35,     0,    34,    20,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    49,     0,
      37,    45,    44,    43,    42,    41,    47,    48,    50,    51,
       0,     0,     0,     0,     0,    56,     0,     0,     0,     0,
      26,     0,     0,    32,    30,     0,    55,     0,     0,     0,
       0,     0,    31,     0,     0,    33,     0,    66,     0,     0,
       0,    64,    57,    29,     0,    63,     0,     0,     0,     0,
       0,     0,    60,    58,    59,    61,    62,    65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    12,    14,    15,    21,
      39,    22,    37,    31,    52,    23,    24,    25,    34,    44,
     112,   113,    67,    58,    59,    60,    61,    62,   104,   105,
     132
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int8 yypact[] =
{
       7,    23,    22,    67,     7,   -67,   -67,   -67,   -67,    46,
     -67,   -67,   -67,    38,    77,    74,    42,   -67,    49,    51,
      79,   -67,   -67,    25,   -67,    53,    80,    81,    82,    61,
      62,   -67,   -67,   -67,    97,    69,   -67,   -27,   -67,   -23,
     100,    88,    97,   -12,   -67,    70,   -67,    90,   -67,    92,
      13,   -67,    72,   -67,   -67,   -67,    39,   -12,   103,   -67,
      94,   -67,    27,   -67,   -67,   -67,    95,   109,   -67,   -67,
      39,    83,    84,    11,    99,   -12,   102,   104,   105,   106,
     107,    39,    39,    39,   108,    89,    45,   -67,   -67,    37,
     -67,   -67,   -67,   -67,   -67,   -67,   -24,   -24,    83,   -67,
     110,    93,   111,    96,   -13,   -67,   113,    98,    78,   110,
     -67,   101,   -21,   -67,   -67,   112,   -67,   120,   113,   123,
     115,    39,   -67,   118,   -18,    58,   114,   -67,   116,   -18,
     -18,   -67,    68,   -67,   117,   119,    55,   -18,   -18,   -18,
     121,   124,   -67,    30,    30,   119,   -67,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   139,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   122,   -67,   126,   -67,
     -67,    26,   -67,   -67,   -45,   -67,   -67,   -56,   -67,    40,
     -66
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int16 yytable[] =
{
      71,    73,   118,   127,   128,    68,    53,   109,    83,    54,
      55,     1,    72,   129,    86,    84,    46,   130,    47,    56,
      48,   119,    49,    57,     2,    96,    97,    98,   131,   110,
      90,    66,    30,    20,    54,    55,    76,    77,    78,    79,
      80,    81,    82,    83,    56,     8,     9,    88,    57,   101,
      84,   102,    76,    77,    78,    79,    80,    81,    82,    83,
      54,    55,   139,   135,   136,   125,    84,    10,    13,   140,
      56,   143,   144,   145,    70,    81,    82,    83,    16,    18,
      19,    88,    20,    26,    84,   137,   138,   139,    81,    82,
      83,   142,    17,    27,   140,    28,    33,    84,   137,   138,
     139,    29,    35,    36,    38,    40,    41,   140,    43,    50,
      51,    45,    64,    63,    65,    69,    74,    75,   -46,    85,
      87,    89,    84,    91,   115,    92,    93,    94,    95,    99,
     100,   108,   103,   107,   106,   111,   121,   123,   117,   124,
     126,   114,   146,    11,   122,    32,     0,     0,   120,   116,
       0,   134,     0,     0,     0,     0,     0,   133,   140,    42,
     147,     0,     0,     0,   141
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-67)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      56,    57,    23,    21,    22,    50,    18,    20,    32,    21,
      22,     4,    57,    31,    70,    39,    43,    35,    45,    31,
      43,    42,    45,    35,    17,    81,    82,    83,    46,    42,
      75,    18,     7,     8,    21,    22,    25,    26,    27,    28,
      29,    30,    31,    32,    31,    22,    24,    36,    35,    12,
      39,    14,    25,    26,    27,    28,    29,    30,    31,    32,
      21,    22,    32,   129,   130,   121,    39,     0,    22,    39,
      31,   137,   138,   139,    35,    30,    31,    32,    40,     5,
       6,    36,     8,    41,    39,    30,    31,    32,    30,    31,
      32,    36,    15,    44,    39,    44,    43,    39,    30,    31,
      32,    22,    22,    22,    22,    44,    44,    39,    11,     9,
      22,    42,    22,    43,    22,    43,    13,    23,    23,    10,
      36,    22,    39,    21,    46,    21,    21,    21,    21,    21,
      41,    35,    22,    22,    41,    22,    16,    14,    37,    24,
      22,    43,    21,     4,   118,    23,    -1,    -1,    36,   109,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    43,    39,    33,
      36,    -1,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    17,    49,    50,    51,    52,    53,    22,    24,
       0,    51,    54,    22,    55,    56,    40,    15,     5,     6,
       8,    57,    59,    63,    64,    65,    41,    44,    44,    22,
       7,    61,    64,    43,    66,    22,    22,    60,    22,    58,
      44,    44,    66,    11,    67,    42,    43,    45,    43,    45,
       9,    22,    62,    18,    21,    22,    31,    35,    71,    72,
      73,    74,    75,    43,    22,    22,    18,    70,    72,    43,
      35,    75,    72,    75,    13,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    39,    10,    75,    36,    36,    22,
      72,    21,    21,    21,    21,    21,    75,    75,    75,    21,
      41,    12,    14,    22,    76,    77,    41,    22,    35,    20,
      42,    22,    68,    69,    43,    46,    77,    37,    23,    42,
      36,    16,    69,    14,    24,    75,    22,    21,    22,    31,
      35,    46,    78,    43,    35,    78,    78,    30,    31,    32,
      39,    47,    36,    78,    78,    78,    21,    36
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 102 "parser.y"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 119 "parser.y"
    { 	
		target=(yyvsp[(6) - (8)].mystring);
		State* st=aut->getState(target);
		if(st==NULL){
			yyerror("The target is not a location of the automaton!");
			exit(1);
		}
		if(inputbound == 0){
			fprintf(stderr,"You should input an integer as the threshold!\n");
			exit(1);
		}

	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 134 "parser.y"
    {aut=new Automaton((yyvsp[(2) - (2)].mystring));}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 135 "parser.y"
    {
		if(syntax_error||!aut->init()){
			fprintf(stderr,"Syntax Error!\n");
			exit(1);
		}
		if(DEBUG)		
			aut->print();					
		(yyval.automaton)=aut;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 153 "parser.y"
    {aut->vars=*(yyvsp[(2) - (2)].varlist);delete (yyvsp[(2) - (2)].varlist);}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 163 "parser.y"
    {
                           
        }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 167 "parser.y"
    {          
        }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 172 "parser.y"
    {
		(yyval.varlist)=(yyvsp[(3) - (4)].varlist);
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 179 "parser.y"
    {
		(yyval.varlist)=(yyvsp[(1) - (3)].varlist); 
		(yyval.varlist)->push_back((yyvsp[(3) - (3)].mystring)); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 184 "parser.y"
    {  
		(yyval.varlist)=new vector<string>();
		(yyval.varlist)->push_back((yyvsp[(1) - (1)].mystring));
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 196 "parser.y"
    { 
		State* st=NULL;
		for(unsigned i=0;i<aut->states.size();i++){
			if(aut->states[i].name == (yyvsp[(1) - (1)].mystring)){
				st = &aut->states[i];
				break;
			}
		}
		if(st == NULL)
			yyerror("The intial location is not declared");
		else{		
			st->is_init=true;			
		}
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 220 "parser.y"
    {
		aut->states.push_back(*(yyvsp[(1) - (2)].state));		
		for(unsigned i=0;i<(yyvsp[(2) - (2)].transitionlist)->size();i++){
			(*(yyvsp[(2) - (2)].transitionlist))[i].from=(yyvsp[(1) - (2)].state)->name;
			aut->transitions.push_back((*(yyvsp[(2) - (2)].transitionlist))[i]);
		}	
		delete (yyvsp[(1) - (2)].state);
		delete (yyvsp[(2) - (2)].transitionlist);
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 234 "parser.y"
    { 
		(yyval.state)=new State((yyvsp[(2) - (9)].mystring));		
		if((yyvsp[(5) - (9)].conlist)!=NULL){
			(yyval.state)->invariants=*(yyvsp[(5) - (9)].conlist);
			delete (yyvsp[(5) - (9)].conlist);
		}				
		for(unsigned i=0;i<aut->vars.size();i++){		
			bool succ=false;
			for(unsigned j=0;j<(yyvsp[(8) - (9)].ODElist)->size();j++){			
				if((*(yyvsp[(8) - (9)].ODElist))[j].var == aut->vars[i]){									
					succ=true;
					break;
				}
			}
			if(!succ){
				yyerror("Error in location:"+(string)(yyvsp[(2) - (9)].mystring)+": every continuous variable must have solution!");
				break;
			}				
		}
		(yyval.state)->ODEs=*(yyvsp[(8) - (9)].ODElist);
		delete (yyvsp[(8) - (9)].ODElist);
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 260 "parser.y"
    {
		(yyval.transitionlist)=(yyvsp[(1) - (2)].transitionlist);
		(yyval.transitionlist)->push_back(*(yyvsp[(2) - (2)].transition));
		delete (yyvsp[(2) - (2)].transition);
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 265 "parser.y"
    {(yyval.transitionlist)=new vector<Transition>();}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 270 "parser.y"
    { 
		(yyval.transition)=new Transition((yyvsp[(10) - (11)].mystring),(yyvsp[(4) - (11)].mystring));
		if((yyvsp[(2) - (11)].conlist)!=NULL){
			(yyval.transition)->guards=*(yyvsp[(2) - (11)].conlist);
			delete (yyvsp[(2) - (11)].conlist);
		}
		(yyval.transition)->resets = *(yyvsp[(7) - (11)].resetlist);
		delete (yyvsp[(7) - (11)].resetlist);
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 281 "parser.y"
    { 
		(yyval.transition)=new Transition((yyvsp[(6) - (7)].mystring),(yyvsp[(4) - (7)].mystring));
		if((yyvsp[(2) - (7)].conlist)!=NULL){
			(yyval.transition)->guards=*(yyvsp[(2) - (7)].conlist);
			delete (yyvsp[(2) - (7)].conlist);
		}
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 293 "parser.y"
    {
		(yyval.resetlist)=(yyvsp[(1) - (3)].resetlist);
		(yyval.resetlist)->push_back(*(yyvsp[(3) - (3)].reset));
		delete (yyvsp[(3) - (3)].reset);
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 299 "parser.y"
    {
		(yyval.resetlist)=new vector<resetMap>();
		(yyval.resetlist)->push_back(*(yyvsp[(1) - (1)].reset));
		delete (yyvsp[(1) - (1)].reset);
	}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 307 "parser.y"
    {
		check_var((yyvsp[(1) - (4)].mystring));
			
		(yyval.reset)=new resetMap((yyvsp[(1) - (4)].mystring),*(yyvsp[(4) - (4)].poly));
		
	}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 317 "parser.y"
    { 
		(yyval.conlist)=(yyvsp[(1) - (1)].conlist);
	}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 320 "parser.y"
    {(yyval.conlist)=NULL;}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 324 "parser.y"
    { 
		(yyval.conlist)=(yyvsp[(1) - (1)].conlist);
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 331 "parser.y"
    { 
		(yyval.conlist)=(yyvsp[(3) - (3)].conlist);
		if((yyvsp[(1) - (3)].polycon)!=NULL)
			(yyval.conlist)->push_back(*(yyvsp[(1) - (3)].polycon));
		delete (yyvsp[(1) - (3)].polycon);
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 338 "parser.y"
    {
		(yyval.conlist)=new vector<PolynomialConstraint>();
		if((yyvsp[(1) - (1)].polycon)!=NULL)		
			(yyval.conlist)->push_back(*(yyvsp[(1) - (1)].polycon));
		delete (yyvsp[(1) - (1)].polycon);
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 345 "parser.y"
    {
		(yyval.conlist)=(yyvsp[(2) - (3)].conlist);
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 353 "parser.y"
    { 	
		(yyval.polycon)=(yyvsp[(1) - (1)].polycon);
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 360 "parser.y"
    {
		(yyval.polycon)=new PolynomialConstraint(*(yyvsp[(1) - (3)].poly),GE,(yyvsp[(3) - (3)].mystring));
		delete (yyvsp[(1) - (3)].poly);	
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 365 "parser.y"
    {	
		(yyval.polycon)=new PolynomialConstraint(*(yyvsp[(1) - (3)].poly),LE,(yyvsp[(3) - (3)].mystring));
		delete (yyvsp[(1) - (3)].poly);
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 370 "parser.y"
    {
		(yyval.polycon)=new PolynomialConstraint(*(yyvsp[(1) - (3)].poly),GT,(yyvsp[(3) - (3)].mystring));
		delete (yyvsp[(1) - (3)].poly);	
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 375 "parser.y"
    {
		(yyval.polycon)=new PolynomialConstraint(*(yyvsp[(1) - (3)].poly),LT,(yyvsp[(3) - (3)].mystring));
		delete (yyvsp[(1) - (3)].poly);
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 380 "parser.y"
    {	
		(yyval.polycon)=new PolynomialConstraint(*(yyvsp[(1) - (3)].poly),EQ,(yyvsp[(3) - (3)].mystring));
		delete (yyvsp[(1) - (3)].poly);	
	}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 384 "parser.y"
    {(yyval.polycon) = NULL;}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 389 "parser.y"
    {
	(yyval.poly) = (yyvsp[(1) - (3)].poly);
	(*(yyval.poly)) += (*(yyvsp[(3) - (3)].poly));
	delete (yyvsp[(3) - (3)].poly);
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 396 "parser.y"
    {
	(yyval.poly) = (yyvsp[(1) - (3)].poly);
	(*(yyval.poly)) -= (*(yyvsp[(3) - (3)].poly));
	delete (yyvsp[(3) - (3)].poly);
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 403 "parser.y"
    {
	(yyval.poly) = (yyvsp[(2) - (3)].poly); 
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 408 "parser.y"
    {
	(yyval.poly) = (yyvsp[(1) - (3)].poly);
	(*(yyval.poly)) *= (*(yyvsp[(3) - (3)].poly));
	delete (yyvsp[(3) - (3)].poly);
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 415 "parser.y"
    {
	int exp = atoi((yyvsp[(3) - (3)].mystring));
	if(exp == 0)
	{
		int I = 1;
		int numVars = aut->dimension();
		(yyval.poly) = new Polynomial(I,numVars );
	}
	else
	{
		(yyval.poly) = new Polynomial(*(yyvsp[(1) - (3)].poly));
		for(int i=1; i<exp; ++i)
		{
			(*(yyval.poly)) *= (*(yyvsp[(1) - (3)].poly));
		}
	}
	delete (yyvsp[(1) - (3)].poly);
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 435 "parser.y"
    {
	int I = -1;
	(yyval.poly) = (yyvsp[(2) - (2)].poly);
	(yyval.poly)->mul_assign(I);
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 442 "parser.y"
    {	
	int id = check_var((yyvsp[(1) - (1)].mystring));
	int numVars = aut->dimension();
	int I=1;
	vector<int> degrees;
	for(int i=0; i<numVars; ++i)
	{
		degrees.push_back(0);
	}
	degrees[id] = 1;
	Monomial monomial(I, degrees);
	(yyval.poly) = new Polynomial(monomial);
	delete (yyvsp[(1) - (1)].mystring);
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 458 "parser.y"
    {
	int numVars = aut->dimension();
	int I = atoi((yyvsp[(1) - (1)].mystring));
	(yyval.poly) = new Polynomial(I, numVars);
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 466 "parser.y"
    {
	(yyval.ODElist)=(yyvsp[(1) - (3)].ODElist);
	(yyval.ODElist)->push_back(*(yyvsp[(3) - (3)].ODE));
	delete (yyvsp[(3) - (3)].ODE);
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 472 "parser.y"
    {
	(yyval.ODElist)=new vector<Solution>();
	(yyval.ODElist)->push_back(*(yyvsp[(1) - (1)].ODE));
	delete (yyvsp[(1) - (1)].ODE);
}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 480 "parser.y"
    {
	check_var((yyvsp[(1) - (6)].mystring));
	(yyval.ODE) = new Solution((yyvsp[(1) - (6)].mystring),*(yyvsp[(6) - (6)].poly));
	delete (yyvsp[(6) - (6)].poly);
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 488 "parser.y"
    {
	(yyval.poly) = (yyvsp[(1) - (3)].poly);
	(*(yyval.poly)) += (*(yyvsp[(3) - (3)].poly));
	delete (yyvsp[(3) - (3)].poly);
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 495 "parser.y"
    {
	(yyval.poly) = (yyvsp[(1) - (3)].poly);
	(*(yyval.poly)) -= (*(yyvsp[(3) - (3)].poly));
	delete (yyvsp[(3) - (3)].poly);
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 502 "parser.y"
    {
	(yyval.poly) = (yyvsp[(2) - (3)].poly); 
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 507 "parser.y"
    {
	(yyval.poly) = (yyvsp[(1) - (3)].poly);
	(*(yyval.poly)) *= (*(yyvsp[(3) - (3)].poly));
	delete (yyvsp[(3) - (3)].poly);
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 514 "parser.y"
    {
	int exp = atoi((yyvsp[(3) - (3)].mystring));
	if(exp == 0)
	{
		int I=1;
		(yyval.poly) = new Polynomial(I, aut->dimension()+1);
	}
	else
	{
		(yyval.poly) = new Polynomial(*(yyvsp[(1) - (3)].poly));

		for(int i=1; i<exp; ++i)
		{
			(*(yyval.poly)) *= (*(yyvsp[(1) - (3)].poly));
		}
	}

	delete (yyvsp[(1) - (3)].poly);
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 535 "parser.y"
    {
	int I = -1;
	(yyval.poly) = (yyvsp[(2) - (2)].poly);
	(yyval.poly)->mul_assign(I);
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 541 "parser.y"
    {
	int numVars = aut->dimension()+1;
	int I = 1;
	vector<int> degrees;
	for(int i=0; i<numVars; ++i)
	{
		degrees.push_back(0);
	}
	degrees[numVars-1] = 1;
	Monomial monomial(I, degrees);
	(yyval.poly) = new Polynomial(monomial);
	
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 555 "parser.y"
    {
	int id = check_var((yyvsp[(1) - (4)].mystring));
	int numVars = aut->dimension()+1;
	int I = 1;
	vector<int> degrees;
	for(int i=0; i<numVars; ++i)
	{
		degrees.push_back(0);
	}
	degrees[id] = 1;
	Monomial monomial(I, degrees);
	(yyval.poly) = new Polynomial(monomial);
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 569 "parser.y"
    {
	int numVars = aut->dimension()+1;
	int I = atoi((yyvsp[(1) - (1)].mystring));
	(yyval.poly) = new Polynomial(I, numVars);
}
    break;


/* Line 1792 of yacc.c  */
#line 2124 "parser.tab.c"
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 576 "parser.y"

