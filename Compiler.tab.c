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
#line 1 "compiler.y"

#define YYSTYPE attributes
#include <cstdio>
#include <map>
#include "tree.h"
#include "table.h"
#include "draw.h" 
#include "interRepre.h"
 
using namespace std;

extern char *yytext;
extern int column;
extern FILE * yyin;
extern int yylineno;

treeNode *root;//the root node of the syntax tree
SymbolTable symTable;// the symbol table
int resState;//the buffer to show the state of the symbol in table (found or not found)
vector<string> funcPaTypes;// buffer of the parameters of the function, used to insert paras into tables when function declaration
vector<string> funcPaNames;// buffer of the parameters of the function, used to insert paras into tables when function declaration
int isFuncStatement = 0;//to show if a compound statement belongs to a function delaration, which compiler need to add the parameters into the symbol table 
map<string,bool> funcDefined;//to show a function is defined or not
bool has_error = false;

int yylex(void);
void yyerror(const char*); 

template <class Type>  
Type stringToNum(const string& str)  
{  
    istringstream iss(str);  
    Type num;  
    iss >> num;  
    return num;      
}  

template <class Type>
string constFold(string left, string op, string right){
	Type leftConst = stringToNum<Type>(left);
	Type rightConst = stringToNum<Type>(right);
	string res;
	if(op == "+")
		res = to_string(leftConst+rightConst);
	else if (op == "-")
		res = to_string(leftConst-rightConst);
	else if(op == "*")
		res = to_string(leftConst*rightConst);
	else if(op == "/")
		res = to_string(leftConst/rightConst);
	else if(op == ">"){
		if(leftConst > rightConst)
			res = "true";
		else 
			res = "false";
	}
	else if(op == "<"){
		if(leftConst < rightConst)
			res = "true";
		else 
			res = "false";
	}
	else if(op == ">="){
		if(leftConst >= rightConst)
			res = "true";
		else 
			res = "false";
	}
	else if(op == "<="){
		if(leftConst <= rightConst)
			res = "true";
		else 
			res = "false";
	}
	else if(op == "=="){
		if(leftConst == rightConst)
			res = "true";
		else 
			res = "false";
	}
	else if(op == "!="){
		if(leftConst != rightConst)
			res == "true";
		else 
			res = "false";
	}
	return res;
	
}


/* Line 371 of yacc.c  */
#line 160 "compiler.tab.c"

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
   by #include "compiler.tab.h".  */
#ifndef YY_YY_COMPILER_TAB_H_INCLUDED
# define YY_YY_COMPILER_TAB_H_INCLUDED
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
     IDENTIFIER = 258,
     CONSTANT_INT = 259,
     CONSTANT_DOUBLE = 260,
     CONSTANT_BOOL = 261,
     ADD_OP = 262,
     MUL_OP = 263,
     REL_OP = 264,
     BOOL_OP = 265,
     BOOL = 266,
     INT = 267,
     DOUBLE = 268,
     VOID = 269,
     CHAR = 270,
     IF = 271,
     ELSE = 272,
     WHILE = 273,
     RETURN = 274,
     LOWER_THAN_ELSE = 275
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
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

#endif /* !YY_YY_COMPILER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 246 "compiler.tab.c"

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,     2,     2,    21,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    20,
       2,    22,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    20,
      26,    33,    35,    37,    39,    41,    43,    51,    54,    61,
      62,    64,    66,    70,    72,    75,    80,    85,    87,    89,
      90,    93,    94,    97,    99,   101,   103,   105,   107,   110,
     112,   118,   126,   132,   135,   139,   143,   145,   147,   152,
     156,   158,   162,   164,   168,   170,   174,   176,   180,   182,
     184,   186,   188,   190,   195,   196,   198,   202
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      31,     0,    -1,    32,    -1,    32,    33,    -1,    33,    -1,
      34,    -1,    37,    -1,    36,    -1,    35,     3,    20,    -1,
      35,     3,    22,    55,    20,    -1,    35,     3,    23,     4,
      24,    20,    -1,    12,    -1,    14,    -1,    11,    -1,    13,
      -1,    15,    -1,    35,     3,    27,    39,    40,    28,    20,
      -1,    38,    43,    -1,    35,     3,    27,    39,    40,    28,
      -1,    -1,    41,    -1,    14,    -1,    41,    21,    42,    -1,
      42,    -1,    35,     3,    -1,    35,     3,    23,    24,    -1,
      44,    46,    47,    45,    -1,    25,    -1,    26,    -1,    -1,
      46,    34,    -1,    -1,    47,    48,    -1,    49,    -1,    43,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    20,    -1,
      20,    -1,    16,    27,    53,    28,    48,    -1,    16,    27,
      53,    28,    48,    17,    48,    -1,    18,    27,    53,    28,
      48,    -1,    19,    20,    -1,    19,    53,    20,    -1,    54,
      22,    53,    -1,    55,    -1,     3,    -1,     3,    23,    53,
      24,    -1,    56,    10,    56,    -1,    56,    -1,    57,     9,
      57,    -1,    57,    -1,    57,     7,    58,    -1,    58,    -1,
      58,     8,    59,    -1,    59,    -1,    27,    53,    28,    -1,
      54,    -1,    60,    -1,     4,    -1,     5,    -1,     6,    -1,
       3,    27,    61,    28,    -1,    -1,    62,    -1,    62,    21,
      53,    -1,    53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   112,   117,   123,   127,   131,   138,   150,
     178,   191,   196,   201,   206,   211,   218,   235,   251,   267,
     272,   278,   288,   295,   303,   312,   324,   333,   355,   359,
     362,   368,   373,   400,   407,   413,   419,   425,   433,   437,
     440,   461,   502,   516,   523,   532,   546,   554,   570,   605,
     646,   654,   685,   693,   724,   732,   764,   772,   778,   784,
     790,   795,   800,   807,   880,   885,   893,   900
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT_INT",
  "CONSTANT_DOUBLE", "CONSTANT_BOOL", "ADD_OP", "MUL_OP", "REL_OP",
  "BOOL_OP", "BOOL", "INT", "DOUBLE", "VOID", "CHAR", "IF", "ELSE",
  "WHILE", "RETURN", "';'", "','", "'='", "'['", "']'", "'{'", "'}'",
  "'('", "')'", "LOWER_THAN_ELSE", "$accept", "Program",
  "declaration_list", "declaration", "var_declaration", "type_specifier",
  "fun_declaration", "fun_definition", "fun_definition_head",
  "para_starts", "params", "params_list", "param", "compound_stmt",
  "compound_stmt_start", "compound_stmt_end", "local_declarations",
  "statement_list", "statement", "expression_stmt", "selection_stmt",
  "iteration_stmt", "return_stmt", "expression", "var",
  "simple_expression", "relation_expression", "additive_expression",
  "term", "factor", "call", "args", "arg_list", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      59,    44,    61,    91,    93,   123,   125,    40,    41,   275
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    33,    34,    34,
      34,    35,    35,    35,    35,    35,    36,    37,    38,    39,
      40,    40,    41,    41,    42,    42,    43,    44,    45,    46,
      46,    47,    47,    48,    48,    48,    48,    48,    49,    49,
      50,    50,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    60,    61,    61,    62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     5,
       6,     1,     1,     1,     1,     1,     7,     2,     6,     0,
       1,     1,     3,     1,     2,     4,     4,     1,     1,     0,
       2,     0,     2,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     5,     2,     3,     3,     1,     1,     4,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     4,     0,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    13,    11,    14,    12,    15,     0,     2,     4,     5,
       0,     7,     6,     0,     1,     3,     0,    27,    17,    29,
       8,     0,     0,    19,    31,    47,    60,    61,    62,     0,
      58,     0,    50,    52,    54,    56,    59,     0,     0,    30,
       0,     0,     0,    64,     0,    58,    46,     9,     0,     0,
       0,     0,     0,    12,     0,     0,    20,    23,     0,     0,
       0,     0,    39,    28,    34,    26,    32,    33,    35,    36,
      37,     0,     0,    67,     0,    65,    57,     0,    49,    53,
      51,    55,    10,    24,    18,     0,     0,     0,    43,     0,
      38,    48,    63,     0,    45,     0,    16,    22,     0,     0,
      44,    66,    25,     0,     0,    40,    42,     0,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    38,
      55,    56,    57,    64,    19,    65,    24,    41,    66,    67,
      68,    69,    70,    71,    45,    46,    32,    33,    34,    35,
      36,    74,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -87
static const yytype_int8 yypact[] =
{
      64,   -87,   -87,   -87,   -87,   -87,     3,    64,   -87,   -87,
       8,   -87,   -87,    -6,   -87,   -87,    43,   -87,   -87,   -87,
     -87,    47,    50,   -87,    64,   -11,   -87,   -87,   -87,    47,
     -87,    35,    46,    30,    51,   -87,   -87,    37,    69,   -87,
      65,     4,    47,    47,    41,    49,   -87,   -87,    47,    47,
      47,    47,    52,    45,    82,    58,    66,   -87,   -18,    61,
      62,    40,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,    70,    67,   -87,    68,    71,   -87,    47,   -87,    51,
      86,   -87,   -87,    72,    74,    64,    47,    47,   -87,    77,
     -87,   -87,   -87,    47,   -87,    75,   -87,   -87,    73,    76,
     -87,   -87,   -87,    22,    22,    81,   -87,    22,   -87
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -87,   -87,   -87,    93,    78,   -23,   -87,   -87,   -87,   -87,
     -87,   -87,    18,    92,   -87,   -87,   -87,   -87,   -86,   -87,
     -87,   -87,   -87,   -29,   -15,    85,    59,    60,    63,    57,
     -87,   -87,   -87
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -22
static const yytype_int8 yytable[] =
{
      44,    40,    20,    14,    21,    22,    30,    25,    26,    27,
      28,    16,    42,    72,    73,    54,    43,   105,   106,    17,
      59,   108,    60,    61,    62,    25,    26,    27,    28,    17,
      63,    29,    89,    30,    30,    30,    30,    49,    59,    50,
      60,    61,    62,    25,    26,    27,    28,    17,    94,    29,
      25,    26,    27,    28,    37,    47,    48,    98,    99,    51,
      88,    52,    54,    20,   101,    21,    22,    29,    58,    76,
      23,    77,    82,   -21,    29,     1,     2,     3,     4,     5,
       1,     2,     3,    53,     5,    83,    84,    85,    86,    87,
      90,    91,    93,    49,    96,    95,    92,   100,   107,   102,
      15,   103,    39,    97,   104,    18,    31,    78,    81,     0,
      80,     0,    79
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-87)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      29,    24,    20,     0,    22,    23,    21,     3,     4,     5,
       6,     3,    23,    42,    43,    38,    27,   103,   104,    25,
      16,   107,    18,    19,    20,     3,     4,     5,     6,    25,
      26,    27,    61,    48,    49,    50,    51,     7,    16,     9,
      18,    19,    20,     3,     4,     5,     6,    25,    77,    27,
       3,     4,     5,     6,     4,    20,    10,    86,    87,     8,
      20,    24,    85,    20,    93,    22,    23,    27,     3,    28,
      27,    22,    20,    28,    27,    11,    12,    13,    14,    15,
      11,    12,    13,    14,    15,     3,    28,    21,    27,    27,
      20,    24,    21,     7,    20,    23,    28,    20,    17,    24,
       7,    28,    24,    85,    28,    13,    21,    48,    51,    -1,
      50,    -1,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    12,    13,    14,    15,    31,    32,    33,    34,
      35,    36,    37,    38,     0,    33,     3,    25,    43,    44,
      20,    22,    23,    27,    46,     3,     4,     5,     6,    27,
      54,    55,    56,    57,    58,    59,    60,     4,    39,    34,
      35,    47,    23,    27,    53,    54,    55,    20,    10,     7,
       9,     8,    24,    14,    35,    40,    41,    42,     3,    16,
      18,    19,    20,    26,    43,    45,    48,    49,    50,    51,
      52,    53,    53,    53,    61,    62,    28,    22,    56,    58,
      57,    59,    20,     3,    28,    21,    27,    27,    20,    53,
      20,    24,    28,    21,    53,    23,    20,    42,    53,    53,
      20,    53,    24,    28,    28,    48,    48,    17,    48
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
#line 105 "compiler.y"
    { 
		root = create_tree("Program", 1, -1, (yyvsp[(1) - (1)]).st);
		
		root->nodeType = "PROGRAM";
	}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 112 "compiler.y"
    {
		(yyval).st = create_tree("declaration_list", 2, -1, (yyvsp[(1) - (2)]).st, (yyvsp[(2) - (2)]).st);
		(yyval).st->nodeType = "DECLARATION";
		(yyval).lineNo = (yyvsp[(1) - (2)]).lineNo;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 117 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 123 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 127 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 131 "compiler.y"
    {
		//TODO
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 138 "compiler.y"
    {
		(yyval).st = create_tree("var_declaration", 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(2) - (3)]).st);
		(yyval).st->nodeType = "VAR_DECLARATION";
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		//insert into symbol table
		resState = symTable.insertSymbol((yyvsp[(2) - (3)]).st->nodeName, (yyvsp[(1) - (3)]).st->nodeName);
		if(resState == -1){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " variable " << (yyvsp[(2) - (3)]).st->nodeName << " has been defined." << endl; 
			has_error = true;
		}
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 150 "compiler.y"
    {
		//TODO
		(yyval).st = create_tree("var_declaration_with_initial", 3, -1, (yyvsp[(1) - (5)]).st, (yyvsp[(2) - (5)]).st, (yyvsp[(4) - (5)]).st);
		(yyval).st->nodeType = "VAR_DECLARATION_WITH_INITIAL";
		(yyval).lineNo = (yyvsp[(1) - (5)]).lineNo;
		
		//insert into symbol table
		resState = symTable.insertSymbol((yyvsp[(2) - (5)]).st->nodeName, (yyvsp[(1) - (5)]).st->nodeName);
		if(resState == -1){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " variable " << (yyvsp[(2) - (5)]).st->nodeName << " has been defined." << endl; 
			has_error = true;
		}
		else{
			//check type
			if((yyvsp[(1) - (5)]).st->nodeName =="CHAR" && (yyvsp[(4) - (5)]).type == "INT"){
				cout << "[Compile Warning] Line:" << (yyval).lineNo << " Initialize a char with a constant int which may be out of char range. " << endl;
				has_error = true;
			}
			else if((yyvsp[(1) - (5)]).st->nodeName == "DOUBLE" && (yyvsp[(4) - (5)]).type == "INT"){
				cout << "[Compile Warning] Line:" << (yyval).lineNo << " Initialize a double with a int, append a dot to parse a const int to double." << endl;
				has_error = true;
			}
			else if((yyvsp[(1) - (5)]).st->nodeName != (yyvsp[(4) - (5)]).type){
				cout << "[Compile Error] Line:" << (yyval).lineNo << " initializer should be type " << (yyvsp[(1) - (5)]).st->nodeName << " but not " << (yyvsp[(4) - (5)]).type << endl; 
				has_error = true;
			}
		}	
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 178 "compiler.y"
    {
		(yyval).st = create_tree("var_declaration", 3, -1, (yyvsp[(1) - (6)]).st, (yyvsp[(2) - (6)]).st, (yyvsp[(4) - (6)]).st);
		(yyval).st->nodeType = "VAR_ARRAY_DECLARATION";
		(yyval).lineNo = (yyvsp[(1) - (6)]).lineNo;
		
		resState = symTable.insertSymbol((yyvsp[(2) - (6)]).st->nodeName, (yyvsp[(1) - (6)]).st->nodeName+"*");
		if(resState == -1){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " variable " << (yyvsp[(2) - (6)]).st->nodeName << " has been defined." << endl; 
			has_error = true;
		}
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 191 "compiler.y"
    {
		(yyval).st = create_tree("INT", 0, -1);
		(yyval).st->nodeType = "TYPE";
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 196 "compiler.y"
    {
		(yyval).st = create_tree("VOID", 0, -1);
		(yyval).st->nodeType = "TYPE";
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 201 "compiler.y"
    {
		(yyval).st = create_tree("BOOL", 0, -1);
		(yyval).st->nodeType = "TYPE";
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 206 "compiler.y"
    {
		(yyval).st = create_tree("DOUBLE", 0, -1);
		(yyval).st->nodeType = "TYPE";
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 211 "compiler.y"
    {
		(yyval).st = create_tree("CHAR", 0, -1);
		(yyval).st->nodeType = "TYPE";
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 218 "compiler.y"
    {
		//TODO
		(yyval).st = create_tree("fun_declaration", 3, -1, (yyvsp[(1) - (7)]).st, (yyvsp[(2) - (7)]).st, (yyvsp[(5) - (7)]).st);
		(yyval).st->nodeType = "FUN_DECLARATION";
		(yyval).lineNo = (yyvsp[(1) - (7)]).lineNo;
		
		resState = symTable.insertSymbol((yyvsp[(2) - (7)]).st->nodeName, (yyvsp[(1) - (7)]).st->nodeName + " " + (yyvsp[(5) - (7)]).funcParas);
		if(resState == -1){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " function " << (yyvsp[(2) - (7)]).st->nodeName << " has been declared." << endl; 
			has_error = true;
		}
		else{
			funcDefined[(yyvsp[(2) - (7)]).st->nodeName]=false;
		}
		
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 235 "compiler.y"
    {
		(yyval).st = create_tree("fun_definition", 4, -1, (yyvsp[(1) - (2)]).st->child[0], (yyvsp[(1) - (2)]).st->child[1], (yyvsp[(1) - (2)]).st->child[2], (yyvsp[(2) - (2)]).st);
		(yyval).st->nodeType = "FUN_DEFINITION";
		(yyval).lineNo = (yyvsp[(1) - (2)]).lineNo;

		if((yyvsp[(2) - (2)]).type == "STATEMENT" && (yyvsp[(1) - (2)]).st->child[0]->nodeName!="VOID"){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " a return statement is expected." << endl; 
			has_error = true;
		}
		else if((yyvsp[(2) - (2)]).type != (yyvsp[(1) - (2)]).st->child[0]->nodeName){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " return value type(" << (yyvsp[(2) - (2)]).type <<") in statement is not " << (yyvsp[(1) - (2)]).st->child[0]->nodeName << endl; 
			has_error = true;
		}
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 251 "compiler.y"
    {
		(yyval).st = create_tree("fun_definition", 3, -1, (yyvsp[(1) - (6)]).st, (yyvsp[(2) - (6)]).st, (yyvsp[(5) - (6)]).st);
		(yyval).lineNo = (yyvsp[(1) - (6)]).lineNo;
		
		resState = symTable.insertSymbol((yyvsp[(2) - (6)]).st->nodeName, (yyvsp[(1) - (6)]).st->nodeName + " " + (yyvsp[(5) - (6)]).funcParas);
		if(resState == -1 && funcDefined[(yyvsp[(2) - (6)]).st->nodeName] == true){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " function " << (yyvsp[(2) - (6)]).st->nodeName << " has been defined." << endl; 
			has_error = true;
		}
		
		funcDefined[(yyvsp[(2) - (6)]).st->nodeName]=true;
	
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 267 "compiler.y"
    {
		isFuncStatement = 1;
	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 272 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).funcParas = (yyvsp[(1) - (1)]).funcParas;
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 278 "compiler.y"
    {
		(yyval).st = create_tree("VOID", 0, -1);
		(yyval).st->nodeType = "VOID";
		
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).funcParas = "VOID";
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 288 "compiler.y"
    {
		(yyval).st = create_tree("params_list", 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(3) - (3)]).st);
		(yyval).st->nodeType = "PARAMS";
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		(yyval).funcParas = (yyvsp[(1) - (3)]).funcParas + " " + (yyvsp[(3) - (3)]).funcParas;
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 295 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).funcParas = (yyvsp[(1) - (1)]).funcParas;
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 303 "compiler.y"
    {
		(yyval).st = create_tree("param", 2, -1, (yyvsp[(1) - (2)]).st, (yyvsp[(2) - (2)]).st);
		(yyval).st->nodeType = "PARAM";
		(yyval).lineNo = (yyvsp[(1) - (2)]).lineNo;
		
		(yyval).funcParas = (yyvsp[(1) - (2)]).st->nodeName;
		funcPaTypes.push_back((yyvsp[(1) - (2)]).st->nodeName);
		funcPaNames.push_back((yyvsp[(2) - (2)]).st->nodeName);	
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 312 "compiler.y"
    {
		(yyval).st = create_tree("param_array", 2, -1, (yyvsp[(1) - (4)]).st, (yyvsp[(2) - (4)]).st);
		(yyvsp[(1) - (4)]).st->nodeName = (yyvsp[(1) - (4)]).st->nodeName + "*"; 
		(yyval).st->nodeType = "PARAM";
		(yyval).lineNo = (yyvsp[(1) - (4)]).lineNo;
		
		(yyval).funcParas = (yyvsp[(1) - (4)]).st->nodeName;
		funcPaTypes.push_back((yyvsp[(1) - (4)]).st->nodeName);
		funcPaNames.push_back((yyvsp[(2) - (4)]).st->nodeName);	
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 324 "compiler.y"
    {
		(yyval).st = create_tree("compound_stmt",2,-1,(yyvsp[(2) - (4)]).st,(yyvsp[(3) - (4)]).st);
		(yyval).st->nodeType = "COM_STATEMENTS";
		(yyval).lineNo = (yyvsp[(1) - (4)]).lineNo;	 
		
		(yyval).type = (yyvsp[(3) - (4)]).type; 
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 333 "compiler.y"
    {
		symTable.createTable();
		
		if(isFuncStatement == 1){
			for(int i = 0; i < funcPaTypes.size(); i++){
				resState = symTable.insertSymbol(funcPaNames[i], funcPaTypes[i]);
				if(resState == -1){
					cout << "[Compile Error] Line:" << (yyvsp[(1) - (1)]).lineNo << " function parameters name should be different." << endl; 
					has_error = true;
				}
			}
			int parasCount = funcPaTypes.size();
			for(int i = 0; i < parasCount; i++){
				funcPaTypes.pop_back();
				funcPaNames.pop_back();
			}
			isFuncStatement = 0;
		}
		
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 355 "compiler.y"
    {
		symTable.deleteTable();
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 359 "compiler.y"
    {
		(yyval).st = NULL;
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 362 "compiler.y"
    {
		(yyval).st = create_tree("local_declarations",2,-1,(yyvsp[(1) - (2)]).st,(yyvsp[(2) - (2)]).st);
		(yyval).st->nodeType = "DECLARATION";
		(yyval).lineNo = (yyvsp[(1) - (2)]).lineNo;
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 368 "compiler.y"
    {
		(yyval).st = NULL;
		
		(yyval).type = "STATEMENT";
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 373 "compiler.y"
    {
		(yyval).st = create_tree("statement_list",2,-1,(yyvsp[(1) - (2)]).st,(yyvsp[(2) - (2)]).st);
		(yyval).st->nodeType = "STATEMENTS";
		(yyval).lineNo = (yyvsp[(1) - (2)]).lineNo;
		
		if((yyvsp[(1) - (2)]).type != "STATEMENT" && (yyvsp[(2) - (2)]).type != "STATEMENT"){
			if((yyvsp[(1) - (2)]).type != (yyvsp[(2) - (2)]).type){
				cout << "[Compile Error] Line:" << (yyvsp[(2) - (2)]).lineNo << " there exist two return statement with different value." << endl; 
				has_error = true;
				(yyval).type = (yyvsp[(1) - (2)]).type; 
			}
			else{
				(yyval).type = (yyvsp[(1) - (2)]).type; 
			}
		}
		else if((yyvsp[(1) - (2)]).type == "STATEMENT" && (yyvsp[(2) - (2)]).type == "STATEMENT"){
			(yyval).type = "STATEMENT";
		}
		else if((yyvsp[(1) - (2)]).type == "STATEMENT" && (yyvsp[(2) - (2)]).type != "STATEMENT"){
			(yyval).type = (yyvsp[(2) - (2)]).type;
		}
		else{
			(yyval).type = (yyvsp[(1) - (2)]).type;
		}
	}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 400 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = "STATEMENT"; 
		
	}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 407 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 413 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 419 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 425 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 433 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (2)]).st;
		(yyval).lineNo = (yyvsp[(1) - (2)]).lineNo;
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 437 "compiler.y"
    {(yyval).st = NULL;(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 440 "compiler.y"
    {
		//deadcode detecting
		if((yyvsp[(3) - (5)]).st->nodeName == "true" && (yyvsp[(3) - (5)]).st->nodeType == "CONSTANT"){
			(yyval).st = (yyvsp[(5) - (5)]).st;
		}
		else if((yyvsp[(3) - (5)]).st->nodeName == "false" && (yyvsp[(3) - (5)]).st->nodeType == "CONSTANT"){
			(yyval).st = NULL;
			(yyval).type = "STATEMENT";
		}
		else{
			(yyval).st = create_tree("IF", 2, -1, (yyvsp[(3) - (5)]).st, (yyvsp[(5) - (5)]).st);
			(yyval).st->nodeType = "IF";
		}
		(yyval).lineNo = (yyvsp[(1) - (5)]).lineNo;
		
		if((yyvsp[(3) - (5)]).type != "BOOL"){
			cout << "[Compile Error] Line:" << (yyvsp[(3) - (5)]).lineNo << " the value of the branch condition should be a bool" << endl; 
			has_error = true;
		}
		(yyval).type = (yyvsp[(5) - (5)]).type;
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 461 "compiler.y"
    {
		//deadcode detecting
		if((yyvsp[(3) - (7)]).st->nodeName == "true" && (yyvsp[(3) - (7)]).st->nodeType == "CONSTANT"){
			(yyval).st = (yyvsp[(5) - (7)]).st;
		}
		else if((yyvsp[(3) - (7)]).st->nodeName == "false" && (yyvsp[(3) - (7)]).st->nodeType == "CONSTANT"){
			(yyval).st = (yyvsp[(7) - (7)]).st;
		}
		else{
			(yyval).st = create_tree("IF_ELSE", 3, -1, (yyvsp[(3) - (7)]).st, (yyvsp[(5) - (7)]).st, (yyvsp[(7) - (7)]).st);
			(yyval).st->nodeType = "IF_ELSE";
		}	
		(yyval).lineNo = (yyvsp[(1) - (7)]).lineNo;
		
		if((yyvsp[(3) - (7)]).type != "BOOL"){
			cout << "[Compile Error] Line:" << (yyvsp[(3) - (7)]).lineNo << " the value of the branch condition should be a bool" << endl; 
			has_error = true;
		}
		
		if((yyvsp[(5) - (7)]).type != "STATEMENT" && (yyvsp[(7) - (7)]).type != "STATEMENT"){
			if((yyvsp[(5) - (7)]).type != (yyvsp[(7) - (7)]).type){
				cout << "[Compile Error] Line:" << (yyvsp[(5) - (7)]).lineNo << " there exist two return statement with different value." << endl; 
				has_error = true;
				(yyval).type = (yyvsp[(5) - (7)]).type; 
			}
			else{
				(yyval).type = (yyvsp[(5) - (7)]).type; 
			}
		}
		else if((yyvsp[(5) - (7)]).type == "STATEMENT" && (yyvsp[(7) - (7)]).type == "STATEMENT"){
			(yyval).type = "STATEMENT";
		}
		else if((yyvsp[(5) - (7)]).type == "STATEMENT" && (yyvsp[(7) - (7)]).type != "STATEMENT"){
			(yyval).type = (yyvsp[(7) - (7)]).type;
		}
		else{
			(yyval).type = (yyvsp[(5) - (7)]).type;
		}
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 502 "compiler.y"
    {
		(yyval).st = create_tree("WHILE", 2, -1, (yyvsp[(3) - (5)]).st, (yyvsp[(5) - (5)]).st);
		(yyval).st->nodeType = "WHILE";
		(yyval).lineNo = (yyvsp[(1) - (5)]).lineNo;
		
		if((yyvsp[(3) - (5)]).type != "BOOL"){
			cout << "[Compile Error] Line:" << (yyvsp[(3) - (5)]).lineNo << " the value of the branch condition should be a bool" << endl; 
			has_error = true;
		}
		
		(yyval).type = (yyvsp[(5) - (5)]).type;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 516 "compiler.y"
    {
		(yyval).st = create_tree("RETURN", 0, -1);
		(yyval).st->nodeType = "RETURN";
		(yyval).lineNo = (yyvsp[(1) - (2)]).lineNo;
		
		(yyval).type = "VOID";
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 523 "compiler.y"
    {
		(yyval).st = create_tree("RETURN", 1, -1, (yyvsp[(2) - (3)]).st);
		(yyval).st->nodeType = "RETURN";
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		(yyval).type = (yyvsp[(2) - (3)]).type;
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 532 "compiler.y"
    {
		(yyval).st = create_tree("=", 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(3) - (3)]).st);
		(yyval).st->nodeType = "ASSIGNMENT";
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		if((yyvsp[(3) - (3)]).type != "READ_RETURN_TYPE" && (yyvsp[(1) - (3)]).type != (yyvsp[(3) - (3)]).type){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " type " << (yyvsp[(3) - (3)]).type << " cannot assigned to variable " << (yyvsp[(1) - (3)]).st->nodeName << endl; 
			has_error = true;
			(yyval).type = "UNDEFINED";
		}
		else{
			(yyval).type = (yyvsp[(1) - (3)]).type;		
		}
	}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 546 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 554 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).st->varType=symTable.getSymbolType((yyval).st->nodeName);
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		//check symbol defined and get type
		resState = symTable.findSymbol((yyvsp[(1) - (1)]).st->nodeName);
		if(resState == 0){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " variable " << (yyvsp[(1) - (1)]).st->nodeName << " is not defined." << endl; 
			has_error = true;
			(yyval).type = "UNDEFINED";
		}
		else{
			(yyval).type = symTable.getSymbolType((yyvsp[(1) - (1)]).st->nodeName);
		} 
	}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 570 "compiler.y"
    {
		(yyval).st = create_tree((yyvsp[(1) - (4)]).st->nodeName, 2, -1, (yyvsp[(1) - (4)]).st, (yyvsp[(3) - (4)]).st);
		(yyval).st->nodeType = "ARRAY";
		string buff1 = symTable.getSymbolType((yyval).st->nodeName);
		(yyvsp[(1) - (4)]).st->varType=buff1.substr(0,buff1.size()-1);
		(yyval).lineNo = (yyvsp[(1) - (4)]).lineNo;
		
		string buff;
		//check symbol defined 
		resState = symTable.findSymbol((yyvsp[(1) - (4)]).st->nodeName);
		if(resState == 0){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " variable " << (yyvsp[(1) - (4)]).st->nodeName << " is not defined." << endl; 
			has_error = true;
			(yyval).type = "UNDEFINED";
		}
		else{
			buff = symTable.getSymbolType((yyvsp[(1) - (4)]).st->nodeName);
			//check if type is array and get type
			
			if(buff[buff.size()-1] != '*'){
				cout << "[Compile Error] Line:" << (yyval).lineNo << " variable " << (yyvsp[(1) - (4)]).st->nodeName << " is not array type." << endl; 
				has_error = true;
				(yyval).type = buff;
			}
			else{
				(yyval).type = buff.substr(0,buff.size()-1);
			} 
		}
		
		if((yyvsp[(3) - (4)]).type != "INT"){
				cout << "[Compile Error] Line:" << (yyval).lineNo << " array index type should be int but not " << (yyvsp[(3) - (4)]).type << endl; 
				has_error = true;
		}
	}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 605 "compiler.y"
    {
		//const fold
		if((yyvsp[(1) - (3)]).st->nodeType == "CONSTANT" && (yyvsp[(3) - (3)]).st->nodeType == "CONSTANT"){
			string new_const;
			if((yyvsp[(1) - (3)]).type == "BOOL" && (yyvsp[(3) - (3)]).type == "BOOL"){
				if((yyvsp[(2) - (3)]).tokenContent == "||"){
					if((yyvsp[(1) - (3)]).st->nodeName == "true" || (yyvsp[(2) - (3)]).st->nodeName == "true")
						new_const = "true";
					else 
						new_const = "false";
				}
				else if((yyvsp[(2) - (3)]).tokenContent == "&&"){
					if((yyvsp[(1) - (3)]).st->nodeName == "false" || (yyvsp[(2) - (3)]).st->nodeName == "false")
						new_const = "false";
					else 
						new_const = "true";
				}
			}
			else{
				new_const = "true";
				cout << "[Compile Error] Line:" << (yyval).lineNo << " BOOL_OP can only operate on bool expressions" << endl;
				has_error = true;
			}
			(yyval).st = create_tree(new_const,0,-1);
			(yyval).st->nodeType = "CONSTANT";
		}
		else{
			(yyval).st = create_tree((yyvsp[(2) - (3)]).tokenContent, 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(3) - (3)]).st);
			(yyval).st->nodeType = "OPERATOR";
		}
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		if((yyvsp[(1) - (3)]).type != (yyvsp[(3) - (3)]).type){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " BOOL_OP cannot operate on type " << (yyvsp[(1) - (3)]).type << " and type " << (yyvsp[(3) - (3)]).type << endl;
			has_error = true;
			(yyval).type = "UNDEFINED"; 
		}
		else{
			(yyval).type = "BOOL";		
		}
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 646 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 654 "compiler.y"
    {
		//const fold
		if((yyvsp[(1) - (3)]).st->nodeType == "CONSTANT" && (yyvsp[(3) - (3)]).st->nodeType == "CONSTANT"){
			string new_const;
			if((yyvsp[(1) - (3)]).type == "INT" && (yyvsp[(3) - (3)]).type == "INT"){
				new_const = constFold<int>((yyvsp[(1) - (3)]).st->nodeName, (yyvsp[(2) - (3)]).tokenContent, (yyvsp[(3) - (3)]).st->nodeName);
			}
			else if((yyvsp[(1) - (3)]).type == "DOUBLE" && (yyvsp[(3) - (3)]).type == "DOUBLE"){
				new_const = constFold<double>((yyvsp[(1) - (3)]).st->nodeName, (yyvsp[(2) - (3)]).tokenContent, (yyvsp[(3) - (3)]).st->nodeName);
			}
			else{
				new_const = "true";
			}
			(yyval).st = create_tree(new_const,0,-1);
			(yyval).st->nodeType = "CONSTANT";
		}
		else{
			(yyval).st = create_tree((yyvsp[(2) - (3)]).tokenContent, 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(3) - (3)]).st);
			(yyval).st->nodeType = "OPERATOR";
		}
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		if((yyvsp[(1) - (3)]).type != (yyvsp[(3) - (3)]).type){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " REL_OP cannot operate on type " << (yyvsp[(1) - (3)]).type << " and type " << (yyvsp[(3) - (3)]).type << endl;
			has_error = true;
			(yyval).type = "UNDEFINED"; 
		}
		else{
			(yyval).type = "BOOL";		
		}
	}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 685 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 693 "compiler.y"
    {
		//const fold
		if((yyvsp[(1) - (3)]).st->nodeType == "CONSTANT" && (yyvsp[(3) - (3)]).st->nodeType == "CONSTANT"){
			string new_const;
			if((yyvsp[(1) - (3)]).type == "INT" && (yyvsp[(3) - (3)]).type == "INT"){
				new_const = constFold<int>((yyvsp[(1) - (3)]).st->nodeName, (yyvsp[(2) - (3)]).tokenContent, (yyvsp[(3) - (3)]).st->nodeName);
			}
			else if((yyvsp[(1) - (3)]).type == "DOUBLE" && (yyvsp[(3) - (3)]).type == "DOUBLE"){
				new_const = constFold<double>((yyvsp[(1) - (3)]).st->nodeName, (yyvsp[(2) - (3)]).tokenContent, (yyvsp[(3) - (3)]).st->nodeName);
			}
			else{
				new_const = "404";
			}
			(yyval).st = create_tree(new_const,0,-1);
			(yyval).st->nodeType = "CONSTANT";
		}
		else{
			(yyval).st = create_tree((yyvsp[(2) - (3)]).tokenContent, 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(3) - (3)]).st);
			(yyval).st->nodeType = "OPERATOR";
		}
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		if((yyvsp[(1) - (3)]).type != (yyvsp[(3) - (3)]).type){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " ADD_OP cannot operate on type " << (yyvsp[(1) - (3)]).type << " and type " << (yyvsp[(3) - (3)]).type << endl;
			has_error = true;
			(yyval).type = "UNDEFINED"; 
		}
		else{
			(yyval).type = (yyvsp[(1) - (3)]).type;		
		}		
	}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 724 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 732 "compiler.y"
    {
		//const fold
		if((yyvsp[(1) - (3)]).st->nodeType == "CONSTANT" && (yyvsp[(3) - (3)]).st->nodeType == "CONSTANT"){
			string new_const;
			if((yyvsp[(1) - (3)]).type == "INT" && (yyvsp[(3) - (3)]).type == "INT"){
				new_const = constFold<int>((yyvsp[(1) - (3)]).st->nodeName, (yyvsp[(2) - (3)]).tokenContent, (yyvsp[(3) - (3)]).st->nodeName);
			}
			else if((yyvsp[(1) - (3)]).type == "DOUBLE" && (yyvsp[(3) - (3)]).type == "DOUBLE"){
				new_const = constFold<double>((yyvsp[(1) - (3)]).st->nodeName, (yyvsp[(2) - (3)]).tokenContent, (yyvsp[(3) - (3)]).st->nodeName);
			}
			else{
				new_const = "404";
			}
			(yyval).st = create_tree(new_const,0,-1);
			(yyval).st->nodeType = "CONSTANT";
		}
		else{
			(yyval).st = create_tree((yyvsp[(2) - (3)]).tokenContent, 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(3) - (3)]).st);
			(yyval).st->nodeType = "OPERATOR";
		}
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		//type check
		if((yyvsp[(1) - (3)]).type != (yyvsp[(3) - (3)]).type){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " MUL_OP cannot operate on type " << (yyvsp[(1) - (3)]).type << " and type " << (yyvsp[(3) - (3)]).type << endl;
			has_error = true;
			(yyval).type = "UNDEFINED"; 
		}
		else{
			(yyval).type = (yyvsp[(1) - (3)]).type;		
		}
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 764 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 772 "compiler.y"
    {
		(yyval).st = (yyvsp[(2) - (3)]).st;
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		(yyval).type = (yyvsp[(2) - (3)]).type;
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 778 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;

		(yyval).type = (yyvsp[(1) - (1)]).type;		
	}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 784 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type; 
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 790 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;	
		(yyval).type = "INT";
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 795 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;	
		(yyval).type = "DOUBLE";
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 800 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;	
		(yyval).type = "BOOL";
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 807 "compiler.y"
    {
		(yyval).st = create_tree("call", 2, -1, (yyvsp[(1) - (4)]).st, (yyvsp[(3) - (4)]).st);
		(yyval).st->nodeType = "FUN_CALL";
		(yyval).lineNo = (yyvsp[(1) - (4)]).lineNo;
		
		resState = symTable.findSymbol((yyvsp[(1) - (4)]).st->nodeName);
		if((yyvsp[(1) - (4)]).st->nodeName == "read"){
			if((yyvsp[(3) - (4)]).type != "VOID"){
				cout << "[Compile Error] Line:" << (yyval).lineNo << " read function takes no arguments! " << endl; 
				has_error = true;
			}
			(yyval).type = "READ_RETURN_TYPE";
		}
		else if((yyvsp[(1) - (4)]).st->nodeName == "print"){
			(yyval).type = "PRINT_RETURN_TYPE";
			vector<string> splitArgs;
			SplitString((yyvsp[(3) - (4)]).type,splitArgs," ");
			if(splitArgs.size() != 1 || (yyvsp[(3) - (4)]).type == "VOID"){
				cout << "[Compile Error] Line:" << (yyval).lineNo << " print function must take one and only one argument one time. " << endl; 
				has_error = true;
			}
			else{
				for(int i = 0;i < splitArgs.size(); i++){
					if(splitArgs[i] != "INT" && splitArgs[i] != "DOUBLE" && splitArgs[i] != "CHAR"){
						cout << "[Compile Error] Line:" << (yyval).lineNo << " print function can only take int, double or char argument. "<< endl; 
						has_error = true;
						break;
					}
				}
			}
		}
		else if(resState == 0){
			cout << "[Compile Error] Line:" << (yyval).lineNo << " function " << (yyvsp[(1) - (4)]).st->nodeName << " is not declared." << endl; 
			has_error = true;
			(yyval).type = "UNDEFINED"; 
		}
		else if(funcDefined.find((yyvsp[(1) - (4)]).st->nodeName) == funcDefined.end()){
			cout << "[Compile Error] Line:" << (yyval).lineNo  << " "<< (yyvsp[(1) - (4)]).st->nodeName << " is not a function." << endl; 
			has_error = true;
			(yyval).type = "UNDEFINED"; 
		}
		else{
			string resType = symTable.getSymbolType((yyvsp[(1) - (4)]).st->nodeName);
			
			if(funcDefined[(yyvsp[(1) - (4)]).st->nodeName] == false){
				cout << "[Compile Error] Line:" << (yyval).lineNo << " function " << (yyvsp[(1) - (4)]).st->nodeName << " is not defined." << endl; 
				has_error = true;
			}
			
			vector<string> splitType;
			SplitString(resType,splitType," ");
			(yyval).type = splitType[0];
			
			vector<string> splitArgs;
			SplitString((yyvsp[(3) - (4)]).type,splitArgs," ");
			if(splitArgs.size() != splitType.size() - 1){
				cout << "[Debug Message] Line:" << (yyval).lineNo << " " << resType << " || " << (yyvsp[(3) - (4)]).type << endl; 
				cout << "[Compile Error] Line:" << (yyval).lineNo << " the number of the parameters does not match the defination of the " << (yyvsp[(1) - (4)]).st->nodeName << endl; 
				has_error = true;
			}
			else{
				for(int i = 0;i < splitArgs.size(); i++){
					if(splitArgs[i] != splitType[i+1]){
						cout << "[Compile Error] Line:" << (yyval).lineNo << " the " << i << "th parameter should be " << splitType[i+1] << " but not " << splitArgs[i] << endl; 
						has_error = true;
						break;
					}
				}
			}
		} 
		
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 880 "compiler.y"
    {
		(yyval).st = create_tree("NO_ARGS", 0, -1);
		(yyval).st->nodeType = "ARGS";
		(yyval).type = "VOID";
	}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 885 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 893 "compiler.y"
    {
		(yyval).st = create_tree("arg_list", 2, -1, (yyvsp[(1) - (3)]).st, (yyvsp[(3) - (3)]).st);
		(yyval).st->nodeType = "ARGS";
		(yyval).lineNo = (yyvsp[(1) - (3)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (3)]).type + " " + (yyvsp[(3) - (3)]).type;
	}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 900 "compiler.y"
    {
		(yyval).st = (yyvsp[(1) - (1)]).st;
		(yyval).lineNo = (yyvsp[(1) - (1)]).lineNo;
		
		(yyval).type = (yyvsp[(1) - (1)]).type;
	}
    break;


/* Line 1792 of yacc.c  */
#line 2611 "compiler.tab.c"
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
#line 907 "compiler.y"

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


int main(int argc,char* argv[]) {

	yyin = fopen(argv[1],"r");
	cout << "Open File" << endl;
	
	yyparse();
	
	//root->printTree2(0);
	
	ofstream out("a.gv");
	out << "digraph AST {" << endl;
	DrawTree(out, root, NULL, 0);
	out << "}" << endl;
	out.close();
	if(!has_error){
		interRepre IR = interRepre(root);
		IR.print_code();
	}
	fclose(yyin);
	return 0;
}


