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
#line 31 "external/checkpolicy/policy_parse.y"

#include <sys/types.h>
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <sepol/policydb/expand.h>
#include <sepol/policydb/policydb.h>
#include <sepol/policydb/services.h>
#include <sepol/policydb/conditional.h>
#include <sepol/policydb/flask.h>
#include <sepol/policydb/hierarchy.h>
#include <sepol/policydb/polcaps.h>
#include "queue.h"
#include "checkpolicy.h"
#include "module_compiler.h"
#include "policy_define.h"

extern policydb_t *policydbp;
extern unsigned int pass;

extern char yytext[];
extern int yylex(void);
extern int yywarn(char *msg);
extern int yyerror(char *msg);

typedef int (* require_func_t)();


/* Line 371 of yacc.c  */
#line 105 "out/host/linux-x86/obj32/EXECUTABLES/checkpolicy_intermediates/policy_parse.cpp"

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
   by #include "policy_parse.hpp".  */
#ifndef YY_YY_OUT_HOST_LINUX_X86_OBJ32_EXECUTABLES_CHECKPOLICY_INTERMEDIATES_POLICY_PARSE_HPP_INCLUDED
# define YY_YY_OUT_HOST_LINUX_X86_OBJ32_EXECUTABLES_CHECKPOLICY_INTERMEDIATES_POLICY_PARSE_HPP_INCLUDED
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
     PATH = 258,
     FILENAME = 259,
     CLONE = 260,
     COMMON = 261,
     CLASS = 262,
     CONSTRAIN = 263,
     VALIDATETRANS = 264,
     INHERITS = 265,
     SID = 266,
     ROLE = 267,
     ROLEATTRIBUTE = 268,
     ATTRIBUTE_ROLE = 269,
     ROLES = 270,
     TYPEALIAS = 271,
     TYPEATTRIBUTE = 272,
     TYPEBOUNDS = 273,
     TYPE = 274,
     TYPES = 275,
     ALIAS = 276,
     ATTRIBUTE = 277,
     BOOL = 278,
     TUNABLE = 279,
     IF = 280,
     ELSE = 281,
     TYPE_TRANSITION = 282,
     TYPE_MEMBER = 283,
     TYPE_CHANGE = 284,
     ROLE_TRANSITION = 285,
     RANGE_TRANSITION = 286,
     SENSITIVITY = 287,
     DOMINANCE = 288,
     DOM = 289,
     DOMBY = 290,
     INCOMP = 291,
     CATEGORY = 292,
     LEVEL = 293,
     RANGE = 294,
     MLSCONSTRAIN = 295,
     MLSVALIDATETRANS = 296,
     USER = 297,
     NEVERALLOW = 298,
     ALLOW = 299,
     AUDITALLOW = 300,
     AUDITDENY = 301,
     DONTAUDIT = 302,
     SOURCE = 303,
     TARGET = 304,
     SAMEUSER = 305,
     FSCON = 306,
     PORTCON = 307,
     NETIFCON = 308,
     NODECON = 309,
     PIRQCON = 310,
     IOMEMCON = 311,
     IOPORTCON = 312,
     PCIDEVICECON = 313,
     FSUSEXATTR = 314,
     FSUSETASK = 315,
     FSUSETRANS = 316,
     GENFSCON = 317,
     U1 = 318,
     U2 = 319,
     U3 = 320,
     R1 = 321,
     R2 = 322,
     R3 = 323,
     T1 = 324,
     T2 = 325,
     T3 = 326,
     L1 = 327,
     L2 = 328,
     H1 = 329,
     H2 = 330,
     NOT = 331,
     AND = 332,
     OR = 333,
     XOR = 334,
     CTRUE = 335,
     CFALSE = 336,
     IDENTIFIER = 337,
     NUMBER = 338,
     EQUALS = 339,
     NOTEQUAL = 340,
     IPV4_ADDR = 341,
     IPV6_ADDR = 342,
     MODULE = 343,
     VERSION_IDENTIFIER = 344,
     REQUIRE = 345,
     OPTIONAL = 346,
     POLICYCAP = 347,
     PERMISSIVE = 348,
     FILESYSTEM = 349,
     DEFAULT_USER = 350,
     DEFAULT_ROLE = 351,
     DEFAULT_TYPE = 352,
     DEFAULT_RANGE = 353,
     LOW_HIGH = 354,
     LOW = 355,
     HIGH = 356
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 68 "external/checkpolicy/policy_parse.y"

	unsigned int val;
	uintptr_t valptr;
	void *ptr;
        require_func_t require_func;


/* Line 387 of yacc.c  */
#line 257 "out/host/linux-x86/obj32/EXECUTABLES/checkpolicy_intermediates/policy_parse.cpp"
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

#endif /* !YY_YY_OUT_HOST_LINUX_X86_OBJ32_EXECUTABLES_CHECKPOLICY_INTERMEDIATES_POLICY_PARSE_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 285 "out/host/linux-x86/obj32/EXECUTABLES/checkpolicy_intermediates/policy_parse.cpp"

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1025

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  179
/* YYNRULES -- Number of rules.  */
#define YYNRULES  369
/* YYNRULES -- Number of states.  */
#define YYNSTATES  733

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   356

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     107,   108,   111,     2,   106,   109,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   105,   104,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   102,     2,   103,   110,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     8,     9,    10,    28,    30,
      33,    36,    38,    41,    44,    47,    49,    50,    52,    55,
      61,    63,    66,    72,    77,    85,    87,    88,    90,    92,
      94,    96,    99,   102,   105,   108,   113,   118,   123,   128,
     133,   138,   144,   150,   156,   162,   168,   174,   176,   177,
     183,   185,   188,   193,   197,   200,   203,   208,   210,   211,
     213,   216,   221,   225,   227,   230,   236,   240,   242,   245,
     247,   249,   255,   260,   262,   265,   267,   269,   271,   273,
     275,   277,   279,   281,   283,   285,   287,   289,   291,   293,
     295,   297,   299,   301,   303,   305,   307,   309,   311,   313,
     317,   323,   328,   333,   338,   343,   346,   347,   352,   357,
     359,   361,   368,   373,   374,   378,   381,   385,   389,   393,
     397,   401,   403,   405,   408,   409,   411,   413,   415,   424,
     432,   440,   448,   450,   452,   454,   456,   464,   472,   480,
     488,   497,   505,   513,   521,   527,   535,   537,   539,   541,
     543,   545,   553,   561,   569,   577,   585,   589,   595,   600,
     605,   611,   619,   624,   626,   629,   633,   639,   644,   646,
     647,   649,   652,   654,   656,   662,   667,   671,   674,   678,
     682,   684,   688,   692,   696,   697,   702,   703,   708,   709,
     714,   715,   720,   721,   726,   727,   732,   733,   738,   739,
     744,   745,   750,   752,   753,   758,   759,   764,   767,   768,
     773,   774,   779,   783,   787,   791,   795,   799,   803,   805,
     807,   809,   811,   813,   815,   817,   820,   827,   832,   833,
     835,   838,   842,   844,   845,   847,   850,   852,   854,   856,
     858,   862,   866,   872,   876,   882,   886,   888,   889,   891,
     894,   900,   904,   906,   907,   909,   912,   917,   924,   926,
     927,   929,   932,   937,   939,   940,   942,   945,   950,   955,
     957,   958,   960,   963,   968,   973,   978,   980,   981,   983,
     986,   993,   994,  1002,  1007,  1009,  1016,  1019,  1020,  1024,
    1026,  1030,  1032,  1034,  1038,  1040,  1042,  1044,  1046,  1048,
    1051,  1054,  1055,  1060,  1062,  1064,  1066,  1070,  1072,  1075,
    1080,  1082,  1085,  1087,  1089,  1092,  1096,  1098,  1101,  1103,
    1104,  1108,  1110,  1112,  1114,  1116,  1118,  1120,  1122,  1124,
    1128,  1132,  1135,  1140,  1142,  1144,  1146,  1149,  1152,  1154,
    1156,  1158,  1160,  1162,  1164,  1166,  1171,  1174,  1176,  1179,
    1183,  1187,  1189,  1191,  1193,  1195,  1197,  1199,  1201,  1203,
    1205,  1207,  1211,  1212,  1219,  1224,  1225,  1227,  1229,  1232
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     113,     0,    -1,   114,    -1,   273,    -1,    -1,    -1,    -1,
     115,   118,   120,   122,   116,   128,   134,   149,   213,   191,
     117,   216,   225,   238,   241,   228,   218,    -1,   119,    -1,
     118,   119,    -1,     7,   265,    -1,   121,    -1,   120,   121,
      -1,    11,   265,    -1,   123,   126,    -1,   124,    -1,    -1,
     125,    -1,   124,   125,    -1,     6,   265,   102,   260,   103,
      -1,   127,    -1,   126,   127,    -1,     7,   265,   102,   260,
     103,    -1,     7,   265,    10,   265,    -1,     7,   265,    10,
     265,   102,   260,   103,    -1,   129,    -1,    -1,   130,    -1,
     131,    -1,   132,    -1,   133,    -1,   129,   130,    -1,   129,
     131,    -1,   129,   132,    -1,   129,   133,    -1,    95,   253,
      48,   104,    -1,    95,   253,    49,   104,    -1,    96,   253,
      48,   104,    -1,    96,   253,    49,   104,    -1,    97,   253,
      48,   104,    -1,    97,   253,    49,   104,    -1,    98,   253,
      48,   100,   104,    -1,    98,   253,    48,   101,   104,    -1,
      98,   253,    48,    99,   104,    -1,    98,   253,    49,   100,
     104,    -1,    98,   253,    49,   101,   104,    -1,    98,   253,
      49,    99,   104,    -1,   135,    -1,    -1,   136,   139,   140,
     143,   145,    -1,   137,    -1,   136,   137,    -1,    32,   265,
     138,   104,    -1,    32,   265,   104,    -1,    21,   253,    -1,
      33,   265,    -1,    33,   102,   260,   103,    -1,   141,    -1,
      -1,   142,    -1,   141,   142,    -1,    37,   265,   138,   104,
      -1,    37,   265,   104,    -1,   144,    -1,   143,   144,    -1,
      38,   265,   105,   250,   104,    -1,    38,   265,   104,    -1,
     146,    -1,   145,   146,    -1,   147,    -1,   148,    -1,    40,
     253,   253,   196,   104,    -1,    41,   253,   196,   104,    -1,
     150,    -1,   149,   150,    -1,   152,    -1,   151,    -1,   162,
      -1,   285,    -1,   271,    -1,   104,    -1,   182,    -1,   183,
      -1,   185,    -1,   186,    -1,   187,    -1,   190,    -1,   184,
      -1,   153,    -1,   154,    -1,   155,    -1,   156,    -1,   157,
      -1,   159,    -1,   160,    -1,   174,    -1,   175,    -1,   176,
      -1,   272,    -1,    22,   265,   104,    -1,    19,   265,   138,
     158,   104,    -1,    19,   265,   158,   104,    -1,    16,   265,
     138,   104,    -1,    17,   265,   250,   104,    -1,    18,   265,
     250,   104,    -1,   106,   250,    -1,    -1,    23,   265,   161,
     104,    -1,    24,   265,   161,   104,    -1,    80,    -1,    81,
      -1,    25,   164,   102,   166,   103,   163,    -1,    26,   102,
     166,   103,    -1,    -1,   107,   164,   108,    -1,    76,   164,
      -1,   164,    77,   164,    -1,   164,    78,   164,    -1,   164,
      79,   164,    -1,   164,    84,   164,    -1,   164,    85,   164,
      -1,   165,    -1,   265,    -1,   166,   167,    -1,    -1,   168,
      -1,   169,    -1,   279,    -1,    27,   253,   253,   105,   253,
     265,   268,   104,    -1,    27,   253,   253,   105,   253,   265,
     104,    -1,    28,   253,   253,   105,   253,   265,   104,    -1,
      29,   253,   253,   105,   253,   265,   104,    -1,   170,    -1,
     171,    -1,   172,    -1,   173,    -1,    44,   253,   253,   105,
     253,   253,   104,    -1,    45,   253,   253,   105,   253,   253,
     104,    -1,    46,   253,   253,   105,   253,   253,   104,    -1,
      47,   253,   253,   105,   253,   253,   104,    -1,    27,   253,
     253,   105,   253,   265,   268,   104,    -1,    27,   253,   253,
     105,   253,   265,   104,    -1,    28,   253,   253,   105,   253,
     265,   104,    -1,    29,   253,   253,   105,   253,   265,   104,
      -1,    31,   253,   253,   248,   104,    -1,    31,   253,   253,
     105,   253,   248,   104,    -1,   177,    -1,   178,    -1,   179,
      -1,   180,    -1,   181,    -1,    44,   253,   253,   105,   253,
     253,   104,    -1,    45,   253,   253,   105,   253,   253,   104,
      -1,    46,   253,   253,   105,   253,   253,   104,    -1,    47,
     253,   253,   105,   253,   253,   104,    -1,    43,   253,   253,
     105,   253,   253,   104,    -1,    14,   265,   104,    -1,    12,
     265,    20,   253,   104,    -1,    12,   265,   158,   104,    -1,
      33,   102,   188,   103,    -1,    30,   253,   253,   265,   104,
      -1,    30,   253,   253,   105,   253,   265,   104,    -1,    44,
     253,   253,   104,    -1,   189,    -1,   188,   189,    -1,    12,
     259,   104,    -1,    12,   259,   102,   188,   103,    -1,    13,
     265,   250,   104,    -1,   192,    -1,    -1,   193,    -1,   192,
     193,    -1,   194,    -1,   195,    -1,     8,   253,   253,   196,
     104,    -1,     9,   253,   196,   104,    -1,   107,   196,   108,
      -1,    76,   196,    -1,   196,    77,   196,    -1,   196,    78,
     196,    -1,   197,    -1,    63,   211,    64,    -1,    66,   212,
      67,    -1,    69,   211,    70,    -1,    -1,    63,   211,   198,
     257,    -1,    -1,    64,   211,   199,   257,    -1,    -1,    65,
     211,   200,   257,    -1,    -1,    66,   211,   201,   257,    -1,
      -1,    67,   211,   202,   257,    -1,    -1,    68,   211,   203,
     257,    -1,    -1,    69,   211,   204,   257,    -1,    -1,    70,
     211,   205,   257,    -1,    -1,    71,   211,   206,   257,    -1,
      50,    -1,    -1,    48,    12,   207,   257,    -1,    -1,    49,
      12,   208,   257,    -1,    12,   212,    -1,    -1,    48,    19,
     209,   257,    -1,    -1,    49,    19,   210,   257,    -1,    72,
     212,    73,    -1,    72,   212,    75,    -1,    74,   212,    73,
      -1,    74,   212,    75,    -1,    72,   212,    74,    -1,    73,
     212,    75,    -1,    84,    -1,    85,    -1,   211,    -1,    34,
      -1,    35,    -1,    36,    -1,   214,    -1,   213,   214,    -1,
      42,   265,    15,   253,   215,   104,    -1,    38,   249,    39,
     248,    -1,    -1,   217,    -1,   216,   217,    -1,    11,   265,
     246,    -1,   219,    -1,    -1,   220,    -1,   219,   220,    -1,
     221,    -1,   222,    -1,   223,    -1,   224,    -1,    55,   269,
     246,    -1,    56,   269,   246,    -1,    56,   269,   109,   269,
     246,    -1,    57,   269,   246,    -1,    57,   269,   109,   269,
     246,    -1,    58,   269,   246,    -1,   226,    -1,    -1,   227,
      -1,   226,   227,    -1,    51,   269,   269,   246,   246,    -1,
     229,   232,   235,    -1,   230,    -1,    -1,   231,    -1,   230,
     231,    -1,    52,   265,   269,   246,    -1,    52,   265,   269,
     109,   269,   246,    -1,   233,    -1,    -1,   234,    -1,   233,
     234,    -1,    53,   265,   246,   246,    -1,   236,    -1,    -1,
     237,    -1,   236,   237,    -1,    54,   245,   245,   246,    -1,
      54,   270,   270,   246,    -1,   239,    -1,    -1,   240,    -1,
     239,   240,    -1,    59,   266,   246,   104,    -1,    60,   265,
     246,   104,    -1,    61,   265,   246,   104,    -1,   242,    -1,
      -1,   243,    -1,   242,   243,    -1,    62,   266,   267,   109,
     265,   246,    -1,    -1,    62,   266,   267,   109,   109,   244,
     246,    -1,    62,   266,   267,   246,    -1,    86,    -1,   265,
     105,   265,   105,   265,   247,    -1,   105,   248,    -1,    -1,
     249,   109,   249,    -1,   249,    -1,   265,   105,   250,    -1,
     265,    -1,   265,    -1,   250,   106,   265,    -1,   110,    -1,
     111,    -1,   265,    -1,   261,    -1,   252,    -1,   251,   265,
      -1,   251,   261,    -1,    -1,   265,   109,   254,   265,    -1,
     251,    -1,   252,    -1,   259,    -1,   102,   258,   103,    -1,
     256,    -1,   255,   259,    -1,   255,   102,   258,   103,    -1,
     259,    -1,   258,   259,    -1,    82,    -1,   265,    -1,   260,
     265,    -1,   102,   262,   103,    -1,   263,    -1,   262,   263,
      -1,   265,    -1,    -1,   109,   264,   265,    -1,   261,    -1,
      82,    -1,    94,    -1,    82,    -1,     3,    -1,     4,    -1,
      83,    -1,    87,    -1,    92,   265,   104,    -1,    93,   265,
     104,    -1,   274,   276,    -1,    88,   265,   275,   104,    -1,
      89,    -1,   269,    -1,   245,    -1,   277,   290,    -1,   277,
     278,    -1,   278,    -1,   151,    -1,   152,    -1,   162,    -1,
     279,    -1,   285,    -1,   104,    -1,    90,   102,   280,   103,
      -1,   280,   281,    -1,   281,    -1,   282,   104,    -1,   283,
     284,   104,    -1,     7,   265,   253,    -1,    12,    -1,    19,
      -1,    22,    -1,    14,    -1,    42,    -1,    23,    -1,    24,
      -1,    32,    -1,    37,    -1,   265,    -1,   284,   106,   265,
      -1,    -1,   288,   102,   276,   103,   286,   287,    -1,   289,
     102,   276,   103,    -1,    -1,    91,    -1,    26,    -1,   214,
     290,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   155,   155,   156,   158,   160,   163,   158,   167,   168,
     170,   173,   174,   176,   179,   181,   182,   184,   185,   187,
     190,   191,   193,   195,   197,   200,   201,   203,   204,   205,
     206,   207,   208,   209,   210,   212,   214,   217,   219,   222,
     224,   227,   229,   231,   233,   235,   237,   240,   241,   243,
     245,   246,   248,   250,   253,   255,   257,   260,   261,   263,
     264,   266,   268,   271,   272,   274,   276,   279,   280,   282,
     283,   285,   288,   291,   292,   294,   295,   296,   297,   298,
     299,   301,   302,   303,   304,   305,   306,   307,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   321,
     324,   326,   329,   332,   335,   338,   339,   341,   344,   347,
     349,   352,   355,   358,   359,   361,   364,   367,   370,   373,
     376,   379,   382,   386,   389,   391,   393,   395,   398,   401,
     404,   407,   411,   413,   415,   417,   420,   424,   428,   432,
     437,   439,   441,   443,   446,   448,   451,   452,   453,   454,
     455,   457,   460,   463,   466,   469,   472,   475,   478,   481,
     483,   485,   488,   491,   493,   496,   498,   501,   504,   505,
     507,   508,   510,   511,   513,   516,   519,   521,   524,   527,
     530,   533,   536,   539,   542,   542,   545,   545,   548,   548,
     551,   551,   554,   554,   557,   557,   560,   560,   563,   563,
     566,   566,   569,   572,   572,   575,   575,   578,   581,   581,
     584,   584,   587,   590,   593,   596,   599,   602,   606,   608,
     611,   613,   615,   617,   620,   621,   623,   626,   627,   629,
     630,   632,   635,   635,   637,   638,   640,   641,   642,   643,
     645,   648,   650,   653,   655,   658,   661,   662,   664,   665,
     667,   670,   672,   673,   675,   676,   678,   680,   683,   684,
     686,   687,   689,   692,   693,   695,   696,   698,   700,   703,
     704,   706,   707,   709,   711,   713,   716,   717,   719,   720,
     722,   724,   724,   726,   729,   732,   734,   735,   737,   739,
     742,   744,   747,   748,   750,   752,   754,   756,   758,   761,
     764,   767,   767,   770,   773,   776,   777,   778,   779,   780,
     782,   783,   785,   788,   789,   791,   793,   793,   795,   795,
     795,   795,   797,   800,   802,   805,   808,   811,   814,   817,
     820,   825,   830,   833,   835,   837,   839,   841,   842,   844,
     845,   846,   847,   848,   849,   851,   853,   854,   856,   857,
     859,   862,   863,   864,   865,   866,   867,   868,   869,   870,
     872,   874,   878,   877,   882,   884,   886,   889,   892,   893
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PATH", "FILENAME", "CLONE", "COMMON",
  "CLASS", "CONSTRAIN", "VALIDATETRANS", "INHERITS", "SID", "ROLE",
  "ROLEATTRIBUTE", "ATTRIBUTE_ROLE", "ROLES", "TYPEALIAS", "TYPEATTRIBUTE",
  "TYPEBOUNDS", "TYPE", "TYPES", "ALIAS", "ATTRIBUTE", "BOOL", "TUNABLE",
  "IF", "ELSE", "TYPE_TRANSITION", "TYPE_MEMBER", "TYPE_CHANGE",
  "ROLE_TRANSITION", "RANGE_TRANSITION", "SENSITIVITY", "DOMINANCE", "DOM",
  "DOMBY", "INCOMP", "CATEGORY", "LEVEL", "RANGE", "MLSCONSTRAIN",
  "MLSVALIDATETRANS", "USER", "NEVERALLOW", "ALLOW", "AUDITALLOW",
  "AUDITDENY", "DONTAUDIT", "SOURCE", "TARGET", "SAMEUSER", "FSCON",
  "PORTCON", "NETIFCON", "NODECON", "PIRQCON", "IOMEMCON", "IOPORTCON",
  "PCIDEVICECON", "FSUSEXATTR", "FSUSETASK", "FSUSETRANS", "GENFSCON",
  "U1", "U2", "U3", "R1", "R2", "R3", "T1", "T2", "T3", "L1", "L2", "H1",
  "H2", "NOT", "AND", "OR", "XOR", "CTRUE", "CFALSE", "IDENTIFIER",
  "NUMBER", "EQUALS", "NOTEQUAL", "IPV4_ADDR", "IPV6_ADDR", "MODULE",
  "VERSION_IDENTIFIER", "REQUIRE", "OPTIONAL", "POLICYCAP", "PERMISSIVE",
  "FILESYSTEM", "DEFAULT_USER", "DEFAULT_ROLE", "DEFAULT_TYPE",
  "DEFAULT_RANGE", "LOW_HIGH", "LOW", "HIGH", "'{'", "'}'", "';'", "':'",
  "','", "'('", "')'", "'-'", "'~'", "'*'", "$accept", "policy",
  "base_policy", "$@1", "$@2", "$@3", "classes", "class_def",
  "initial_sids", "initial_sid_def", "access_vectors", "opt_common_perms",
  "common_perms", "common_perms_def", "av_perms", "av_perms_def",
  "opt_default_rules", "default_rules", "default_user_def",
  "default_role_def", "default_type_def", "default_range_def", "opt_mls",
  "mls", "sensitivities", "sensitivity_def", "alias_def", "dominance",
  "opt_categories", "categories", "category_def", "levels", "level_def",
  "mlspolicy", "mlspolicy_decl", "mlsconstraint_def",
  "mlsvalidatetrans_def", "te_rbac", "te_rbac_decl", "rbac_decl",
  "te_decl", "attribute_def", "type_def", "typealias_def",
  "typeattribute_def", "typebounds_def", "opt_attr_list", "bool_def",
  "tunable_def", "bool_val", "cond_stmt_def", "cond_else", "cond_expr",
  "cond_expr_prim", "cond_pol_list", "cond_rule_def",
  "cond_transition_def", "cond_te_avtab_def", "cond_allow_def",
  "cond_auditallow_def", "cond_auditdeny_def", "cond_dontaudit_def",
  "transition_def", "range_trans_def", "te_avtab_def", "allow_def",
  "auditallow_def", "auditdeny_def", "dontaudit_def", "neverallow_def",
  "attribute_role_def", "role_type_def", "role_attr_def", "role_dominance",
  "role_trans_def", "role_allow_def", "roles", "role_def",
  "roleattribute_def", "opt_constraints", "constraints", "constraint_decl",
  "constraint_def", "validatetrans_def", "cexpr", "cexpr_prim", "$@4",
  "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13",
  "$@14", "$@15", "$@16", "op", "role_mls_op", "users", "user_def",
  "opt_mls_user", "initial_sid_contexts", "initial_sid_context_def",
  "opt_dev_contexts", "dev_contexts", "dev_context_def",
  "pirq_context_def", "iomem_context_def", "ioport_context_def",
  "pci_context_def", "opt_fs_contexts", "fs_contexts", "fs_context_def",
  "net_contexts", "opt_port_contexts", "port_contexts", "port_context_def",
  "opt_netif_contexts", "netif_contexts", "netif_context_def",
  "opt_node_contexts", "node_contexts", "node_context_def", "opt_fs_uses",
  "fs_uses", "fs_use_def", "opt_genfs_contexts", "genfs_contexts",
  "genfs_context_def", "$@17", "ipv4_addr_def", "security_context_def",
  "opt_mls_range_def", "mls_range_def", "mls_level_def", "id_comma_list",
  "tilde", "asterisk", "names", "$@18", "tilde_push", "asterisk_push",
  "names_push", "identifier_list_push", "identifier_push",
  "identifier_list", "nested_id_set", "nested_id_list",
  "nested_id_element", "$@19", "identifier", "filesystem", "path",
  "filename", "number", "ipv6_addr", "policycap_def", "permissive_def",
  "module_policy", "module_def", "version_identifier", "avrules_block",
  "avrule_decls", "avrule_decl", "require_block", "require_list",
  "require_decl", "require_class", "require_decl_def", "require_id_list",
  "optional_block", "$@20", "optional_else", "optional_decl", "else_decl",
  "avrule_user_defs", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   123,   125,    59,    58,    44,    40,    41,    45,
     126,    42
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   112,   113,   113,   115,   116,   117,   114,   118,   118,
     119,   120,   120,   121,   122,   123,   123,   124,   124,   125,
     126,   126,   127,   127,   127,   128,   128,   129,   129,   129,
     129,   129,   129,   129,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   133,   133,   133,   133,   134,   134,   135,
     136,   136,   137,   137,   138,   139,   139,   140,   140,   141,
     141,   142,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   147,   148,   149,   149,   150,   150,   150,   150,   150,
     150,   151,   151,   151,   151,   151,   151,   151,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     154,   154,   155,   156,   157,   158,   158,   159,   160,   161,
     161,   162,   163,   163,   164,   164,   164,   164,   164,   164,
     164,   164,   165,   166,   166,   167,   167,   167,   168,   168,
     168,   168,   169,   169,   169,   169,   170,   171,   172,   173,
     174,   174,   174,   174,   175,   175,   176,   176,   176,   176,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   186,   187,   188,   188,   189,   189,   190,   191,   191,
     192,   192,   193,   193,   194,   195,   196,   196,   196,   196,
     196,   197,   197,   197,   198,   197,   199,   197,   200,   197,
     201,   197,   202,   197,   203,   197,   204,   197,   205,   197,
     206,   197,   197,   207,   197,   208,   197,   197,   209,   197,
     210,   197,   197,   197,   197,   197,   197,   197,   211,   211,
     212,   212,   212,   212,   213,   213,   214,   215,   215,   216,
     216,   217,   218,   218,   219,   219,   220,   220,   220,   220,
     221,   222,   222,   223,   223,   224,   225,   225,   226,   226,
     227,   228,   229,   229,   230,   230,   231,   231,   232,   232,
     233,   233,   234,   235,   235,   236,   236,   237,   237,   238,
     238,   239,   239,   240,   240,   240,   241,   241,   242,   242,
     243,   244,   243,   243,   245,   246,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   252,   253,   253,   253,   253,
     253,   254,   253,   255,   256,   257,   257,   257,   257,   257,
     258,   258,   259,   260,   260,   261,   262,   262,   263,   264,
     263,   263,   265,   266,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   275,   275,   276,   277,   277,   278,
     278,   278,   278,   278,   278,   279,   280,   280,   281,   281,
     282,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     284,   284,   286,   285,   287,   287,   288,   289,   290,   290
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     0,     0,     0,    17,     1,     2,
       2,     1,     2,     2,     2,     1,     0,     1,     2,     5,
       1,     2,     5,     4,     7,     1,     0,     1,     1,     1,
       1,     2,     2,     2,     2,     4,     4,     4,     4,     4,
       4,     5,     5,     5,     5,     5,     5,     1,     0,     5,
       1,     2,     4,     3,     2,     2,     4,     1,     0,     1,
       2,     4,     3,     1,     2,     5,     3,     1,     2,     1,
       1,     5,     4,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       5,     4,     4,     4,     4,     2,     0,     4,     4,     1,
       1,     6,     4,     0,     3,     2,     3,     3,     3,     3,
       3,     1,     1,     2,     0,     1,     1,     1,     8,     7,
       7,     7,     1,     1,     1,     1,     7,     7,     7,     7,
       8,     7,     7,     7,     5,     7,     1,     1,     1,     1,
       1,     7,     7,     7,     7,     7,     3,     5,     4,     4,
       5,     7,     4,     1,     2,     3,     5,     4,     1,     0,
       1,     2,     1,     1,     5,     4,     3,     2,     3,     3,
       1,     3,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     0,     4,     2,     0,     4,
       0,     4,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     6,     4,     0,     1,
       2,     3,     1,     0,     1,     2,     1,     1,     1,     1,
       3,     3,     5,     3,     5,     3,     1,     0,     1,     2,
       5,     3,     1,     0,     1,     2,     4,     6,     1,     0,
       1,     2,     4,     1,     0,     1,     2,     4,     4,     1,
       0,     1,     2,     4,     4,     4,     1,     0,     1,     2,
       6,     0,     7,     4,     1,     6,     2,     0,     3,     1,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     2,
       2,     0,     4,     1,     1,     1,     3,     1,     2,     4,
       1,     2,     1,     1,     2,     3,     1,     2,     1,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     2,     4,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     2,     1,     2,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     6,     4,     0,     1,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,     2,     0,     3,     0,   322,     0,     1,
       0,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   366,     0,   344,   339,
     340,    88,    89,    90,    91,    92,    93,    94,   341,    95,
      96,    97,   146,   147,   148,   149,   150,    81,    82,    87,
      83,    84,    85,    86,    98,   331,   369,   338,   342,   343,
       0,   327,   284,   333,   335,   334,     0,    10,     0,     9,
      16,    11,   106,     0,     0,     0,     0,     0,   106,     0,
       0,     0,     0,     0,     0,   121,   122,     0,   294,   295,
       0,   298,     0,   297,   296,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   369,   337,
     336,     0,   332,    13,     0,    12,     5,     0,    15,    17,
       0,     0,     0,     0,   292,   156,     0,     0,     0,     0,
     106,     0,    99,   109,   110,     0,     0,   115,     0,     0,
       0,     0,     0,     0,   124,   319,   321,     0,   316,   318,
     300,   299,     0,   301,     0,     0,     0,     0,     0,     0,
     163,     0,     0,     0,     0,     0,     0,   351,   354,   352,
     353,   356,   357,   358,   359,   355,     0,   347,     0,     0,
     330,     0,   368,     0,     0,    26,     0,    14,    20,    18,
       0,   105,   158,   167,     0,    54,   102,   103,   104,     0,
     101,   107,   108,   114,   116,   117,   118,   119,   120,     0,
       0,   315,   317,     0,     0,     0,     0,     0,     0,     0,
       0,   289,   291,   312,     0,   159,   164,     0,   162,     0,
       0,     0,     0,     0,   345,   346,   348,   360,     0,     0,
     362,     0,     0,     0,     0,     0,    48,    25,    27,    28,
      29,    30,     0,    21,   157,   293,   100,     0,     0,     0,
       0,     0,     0,     0,   113,   123,   125,   126,   132,   133,
     134,   135,   127,   320,     0,   302,     0,     0,     0,   160,
       0,   144,     0,     0,     0,   165,     0,     0,     0,     0,
       0,   350,   349,     0,   228,   365,     0,   313,     0,     0,
       0,     0,     0,     0,    47,     0,    50,    31,    32,    33,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   111,     0,     0,     0,     0,     0,   288,   290,     0,
       0,     0,     0,     0,     0,   361,     0,     0,   367,   363,
       0,    19,   314,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    80,     0,    73,    76,    75,    77,    79,
      78,     0,    51,    58,    23,     0,     0,     0,     0,     0,
       0,     0,     0,   124,   326,   141,     0,   142,   143,   161,
     145,   166,   155,   151,   152,   153,   154,     0,   226,     0,
      35,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,    53,     0,     0,    74,   169,   224,     0,    55,
       0,     0,    57,    59,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,   140,     0,     0,    43,    41,    42,
      46,    44,    45,    52,   329,     0,     0,     6,   168,   170,
     172,   173,   225,     0,     0,     0,     0,    63,    60,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   227,   364,
       0,     0,     0,   171,    56,    62,     0,     0,     0,     0,
      64,    49,    67,    69,    70,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,     0,   247,   229,    61,    66,     0,
       0,     0,    68,   129,     0,   130,   131,   136,   137,   138,
     139,     0,   221,   222,   223,   218,   219,   220,   207,   203,
     208,   205,   210,   184,   186,   188,   190,     0,   192,   194,
     196,   198,   200,     0,     0,     0,   177,     0,     0,     0,
     175,     0,     0,   230,   270,   246,   248,     0,     0,     0,
     128,   174,     0,     0,     0,     0,   181,     0,     0,     0,
       0,   182,     0,     0,   183,     0,     0,     0,   212,   216,
     213,   217,   214,   215,   176,   178,   179,   231,     0,     0,
       0,     0,     0,   277,   269,   271,   249,    65,     0,    72,
       0,   303,   304,     0,   307,   204,   305,   209,   206,   211,
     185,   187,   189,   191,   193,   195,   197,   199,   201,     0,
       0,   324,   323,     0,     0,     0,     0,   253,   276,   278,
     272,    71,     0,   310,     0,   308,     0,     0,     0,     0,
       0,     0,     0,   233,   259,   252,   254,   279,   306,   311,
       0,     0,   250,   273,   274,   275,   325,     0,     0,     0,
       0,     0,     0,     7,   232,   234,   236,   237,   238,   239,
       0,   264,   258,   260,   255,   309,   287,     0,   283,     0,
       0,     0,     0,     0,   235,     0,     0,   251,   263,   265,
     261,     0,   285,   281,     0,     0,   256,   240,     0,   241,
       0,   243,   245,     0,   328,     0,     0,   266,   286,     0,
     280,     0,     0,     0,   262,     0,     0,   282,   257,   242,
     244,   267,   268
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,   195,   472,    11,    12,    80,    81,
     126,   127,   128,   129,   197,   198,   256,   257,   258,   259,
     260,   261,   313,   314,   315,   316,   137,   373,   421,   422,
     423,   456,   457,   481,   482,   483,   484,   364,   365,    39,
      40,    41,    42,    43,    44,    45,   132,    46,    47,   145,
      48,   331,    94,    95,   219,   275,   276,   277,   278,   279,
     280,   281,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,   169,   170,    63,   447,
     448,   449,   450,   451,   512,   513,   577,   578,   579,   580,
     582,   583,   585,   586,   587,   572,   574,   573,   575,   537,
     538,   416,   118,   347,   515,   516,   673,   674,   675,   676,
     677,   678,   679,   564,   565,   566,   653,   654,   655,   656,
     681,   682,   683,   697,   698,   699,   603,   604,   605,   637,
     638,   639,   719,    74,   597,   702,   230,   231,   133,   100,
     101,   102,   224,   613,   614,   615,   642,   616,   306,   103,
     157,   158,   220,   104,   633,   667,   386,    75,   716,   369,
      64,     5,     6,    76,    65,    66,    67,    68,   186,   187,
     188,   189,   248,    69,   305,   349,    70,   350,   120
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -552
static const yytype_int16 yypact[] =
{
     -54,    -9,   107,  -552,   137,  -552,   478,  -552,   211,  -552,
      -9,   302,  -552,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    71,    79,    79,    79,    79,    79,    56,
      79,    79,    79,    79,    79,    95,  -552,    -9,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,   310,  -552,  -552,  -552,
     152,  -552,  -552,  -552,  -552,  -552,    76,  -552,    -9,  -552,
      52,  -552,    26,    -9,   142,   249,    -9,    -9,    23,   176,
     130,   130,    71,    71,   288,  -552,  -552,    -8,  -552,  -552,
      80,  -552,    79,  -552,   194,    79,    79,    79,    79,   307,
      79,    79,    79,    79,    79,   408,   221,    -9,   294,  -552,
    -552,   478,  -552,  -552,    -9,  -552,  -552,   323,   342,  -552,
      79,    -9,   247,   158,  -552,  -552,    79,   271,   206,   292,
     273,   295,  -552,  -552,  -552,   301,   329,   -17,   -13,    71,
      71,    71,    71,    71,  -552,  -552,  -552,    82,  -552,  -552,
    -552,  -552,   371,  -552,   373,   399,    81,   111,   359,    25,
    -552,   405,   191,   409,   410,   411,    -9,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,    19,  -552,   413,    -9,
    -552,   497,  -552,   416,   424,   341,    -9,   323,  -552,  -552,
     423,   422,  -552,  -552,    -9,  -552,  -552,  -552,  -552,   425,
    -552,  -552,  -552,  -552,   -17,   222,   265,  -552,  -552,   214,
      -9,  -552,  -552,    79,    -9,    79,    79,    79,   430,    79,
     436,   432,   415,  -552,   300,  -552,  -552,    79,  -552,    79,
      79,    79,    79,    79,  -552,  -552,  -552,  -552,   312,    79,
    -552,    -9,    79,    79,    79,    79,   510,   341,  -552,  -552,
    -552,  -552,    13,  -552,  -552,  -552,  -552,    79,    79,    79,
      79,    79,    79,    79,   517,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,    -9,  -552,    -9,    -9,    -9,  -552,
      -9,  -552,    -9,    -9,   307,  -552,    79,    79,    79,    79,
      79,  -552,  -552,    -9,   506,   519,   -20,  -552,   320,   336,
     380,   418,    -9,   534,  -552,   437,  -552,  -552,  -552,  -552,
    -552,    -9,    -9,    79,    79,    79,    79,    79,    79,    79,
     447,  -552,    20,   450,   451,   462,   466,  -552,   422,    28,
     468,   469,   470,   471,   472,  -552,    -9,   483,  -552,  -552,
     490,  -552,  -552,   491,   495,   498,   499,   500,   501,   259,
     263,     7,    -9,  -552,   364,  -552,  -552,  -552,  -552,  -552,
    -552,   124,  -552,   569,   507,   165,   503,   509,   515,   516,
     518,   525,   526,  -552,  -552,  -552,   520,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,   583,  -552,   478,
    -552,  -552,  -552,  -552,  -552,  -552,   532,   533,   535,   536,
     550,   554,  -552,   555,   557,  -552,    51,  -552,    -9,  -552,
      -9,   624,   569,  -552,    -9,  -552,    79,    79,    79,    79,
      79,    79,    79,   228,  -552,    -9,   568,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,    79,    79,  -552,   404,  -552,
    -552,  -552,  -552,   181,    29,    -9,   306,  -552,  -552,   185,
      -9,    -9,    -9,    79,    79,    79,    79,  -552,  -552,  -552,
      79,   164,   663,  -552,  -552,  -552,   574,   367,    79,    79,
    -552,   433,  -552,  -552,  -552,  -552,    21,   576,   577,   578,
     579,   580,   581,   164,    18,    57,   115,  -552,   414,   414,
     414,    18,   414,   414,   414,   414,   414,    18,    18,    18,
     164,   164,   140,  -552,    -9,    24,  -552,  -552,  -552,    -9,
      79,   164,  -552,  -552,   589,  -552,  -552,  -552,  -552,  -552,
    -552,   144,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,   623,  -552,  -552,   628,   629,  -552,  -552,
     627,  -552,  -552,   351,   626,   369,  -552,    65,   164,   164,
    -552,    -9,   615,  -552,   388,   648,  -552,   347,   164,   147,
    -552,  -552,    97,    97,    97,    97,  -552,    97,    97,    97,
      97,  -552,    97,    97,  -552,    97,    97,    97,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,   625,  -552,   599,   615,
     199,    -9,    -9,   643,   388,  -552,  -552,  -552,   175,  -552,
     359,  -552,  -552,   163,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,    -9,
      -9,  -552,  -552,    -9,    -9,    -9,   199,   654,   643,  -552,
    -552,  -552,   187,  -552,   359,  -552,   602,    -9,   604,   605,
     606,   708,    -9,   407,   660,   654,  -552,  -552,  -552,  -552,
     195,    -9,  -552,  -552,  -552,  -552,  -552,    -4,   615,   615,
     615,   615,   615,  -552,   407,  -552,  -552,  -552,  -552,  -552,
      -9,   661,   660,  -552,  -552,  -552,   609,    78,  -552,    85,
      -9,   157,   167,    -9,  -552,    -9,   402,  -552,   661,  -552,
    -552,    -9,  -552,  -552,    -9,   615,  -552,  -552,   615,  -552,
     615,  -552,  -552,    -9,  -552,   630,   632,  -552,  -552,    -9,
    -552,    -9,    -9,    -9,  -552,    -9,    -9,  -552,  -552,  -552,
    -552,  -552,  -552
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -552,  -552,  -552,  -552,  -552,  -552,  -552,   706,  -552,   646,
    -552,  -552,  -552,   595,  -552,   530,  -552,  -552,   476,   479,
     480,   481,  -552,  -552,  -552,   420,   -83,  -552,  -552,  -552,
     317,  -552,   284,  -552,   248,  -552,  -552,  -552,   377,  -274,
    -264,  -552,  -552,  -552,  -552,  -552,   -61,  -552,  -552,   652,
    -258,  -552,   -12,  -552,   366,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,   456,  -162,  -552,  -552,
    -552,   303,  -552,  -552,  -423,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,   -19,
    -193,  -552,  -319,  -552,  -552,   237,  -552,  -552,    87,  -552,
    -552,  -552,  -552,  -552,  -552,   188,  -552,  -552,  -552,   100,
    -552,  -552,    74,  -552,  -552,    64,  -552,  -552,   159,  -552,
    -552,   126,  -552,  -500,  -521,  -552,  -280,  -262,   -84,    11,
      70,   505,  -552,  -552,  -552,    90,   121,  -167,  -314,   -68,
    -552,   610,  -552,    -1,   132,  -552,   280,  -551,    53,  -552,
    -552,  -552,  -552,  -552,  -117,  -552,   704,  -213,  -552,   585,
    -552,  -552,  -552,  -256,  -552,  -552,  -552,  -552,   662
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -221
static const yytype_int16 yytable[] =
{
       8,   234,   138,   139,   193,   140,   282,   236,   375,    77,
     336,   599,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    96,   321,   384,   384,   176,   141,   136,   156,
     337,   177,   160,   178,     1,   514,   116,   168,   179,   366,
     168,   180,   181,   182,   136,   417,   130,   201,   630,   367,
     136,   183,   532,   533,   534,   368,   184,   370,   124,   445,
     446,   185,     7,    78,   149,   150,   151,   152,   153,   539,
     531,   152,   153,     7,     7,   562,   540,   123,     7,   209,
     147,   148,   134,   351,   397,   134,   134,   556,   557,   156,
     366,    96,    96,   117,    97,   213,   159,   452,   569,   161,
     367,   155,   535,   536,   453,   687,   368,     9,   370,   647,
     459,   412,   648,   649,   650,   322,   191,   689,   690,   691,
     692,   693,   244,   194,   385,   523,   662,   541,   235,   131,
     134,   391,   131,   475,   542,   595,   596,   214,   215,   216,
     217,   218,   558,   559,    10,   608,   688,    92,    96,    96,
      96,    96,    96,     7,   721,   468,   159,   722,   109,   723,
       7,     7,     7,     7,     7,   228,   232,     7,   706,   707,
     709,   711,   712,   594,   713,   243,   494,   236,    93,   233,
     122,    97,    97,   720,    97,   221,   227,   703,   247,    98,
      99,   155,   724,     7,   705,   262,   715,   115,   727,   610,
     728,   729,   730,   265,   731,   732,     7,    98,    99,   338,
     143,   144,   495,   496,   497,   725,   229,   558,   559,   283,
     282,   558,   559,   285,   558,   559,   418,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,     7,
     510,   267,   268,   269,   560,   233,   135,     7,   571,     7,
     307,   609,   558,   559,   121,   267,   268,   269,   270,   271,
     272,   273,   203,     7,   204,   644,   708,     7,   425,   233,
     136,   511,   270,   271,   272,   273,   710,   233,   413,   641,
     142,   631,   436,   332,   474,   333,   334,   335,   485,   232,
     658,   232,   134,   632,    71,   238,   239,    72,   685,   149,
      73,   151,   345,   163,    35,   352,   152,   153,   547,    10,
     207,   361,   204,    78,   553,   554,   555,   274,    35,   168,
     374,   307,    13,    14,    15,   190,    16,    17,    18,    19,
     196,   467,    20,    21,    22,    23,   117,    24,    25,    26,
      27,    28,   149,    29,   455,   232,   478,   479,   124,   152,
     153,   202,   117,    30,    31,    32,    33,    34,   406,   407,
     408,   414,   409,   410,   411,   149,   150,   151,   353,   354,
     419,   476,   152,   153,   352,   206,    13,    14,    15,   131,
      16,    17,    18,    19,   355,   356,    20,    21,    22,    23,
     154,    24,    25,    26,    27,    28,   208,    29,   204,   210,
      35,    36,   294,    37,   295,   211,   117,    30,    31,    32,
      33,    34,   445,   446,    38,   176,   302,   307,   303,   454,
     177,   718,   178,   307,   588,   589,   590,   179,   357,   358,
     180,   181,   182,   212,   232,   567,   252,   253,   254,   255,
     183,   233,   592,   643,   593,   184,   645,   600,   601,   602,
     185,   607,   352,   204,   477,    36,   362,    37,   352,   486,
     487,   488,   669,   670,   671,   672,   359,   360,   363,   312,
     371,   518,   519,   478,   479,   659,   223,   643,   225,   543,
     544,   545,   546,   548,   549,   550,   551,   552,    72,   714,
      13,    14,    15,   659,    16,    17,    18,    19,   535,   536,
      20,    21,    22,    23,   226,    24,    25,    26,    27,    28,
     237,    29,   249,   561,   240,   241,   242,   246,   134,   250,
     293,    30,    31,    32,    33,    34,   251,   264,   204,   266,
     105,   106,   107,   108,   289,   110,   111,   112,   113,   114,
     291,   292,   312,   330,   346,   348,    13,    14,    15,   383,
      16,    17,    18,    19,   387,   388,    20,    21,    22,    23,
     598,    24,    25,    26,    27,    28,   389,    29,    35,    36,
     390,    37,   392,   393,   394,   395,   396,    30,    31,    32,
      33,    34,    38,   611,   611,   611,   611,   398,   611,   611,
     611,   611,   399,   611,   611,   400,   611,   611,   611,   401,
     634,   635,   402,   403,   404,   405,   420,   162,   426,   424,
     164,   165,   166,   167,   427,   171,   172,   173,   174,   175,
     428,   429,   435,   430,   434,    36,   362,    37,   646,   598,
     431,   432,   598,   598,   598,   200,   437,   438,   363,   439,
     440,   205,   612,   612,   612,   612,   598,   612,   612,   612,
     612,   668,   612,   612,   441,   612,   612,   612,   442,   443,
     686,   444,   455,   617,   618,   619,   598,   620,   621,   622,
     623,   469,   624,   625,   514,   626,   627,   628,   517,   695,
     525,   526,   527,   528,   529,   530,   704,   576,   598,   598,
     598,   598,   598,   570,   598,  -220,   581,   584,    71,   562,
     232,   591,   558,   598,   629,   636,   652,   661,   663,   664,
     665,   666,   598,   680,   701,   696,    72,    79,   598,   714,
     598,   598,   598,   199,   598,   598,   125,   263,   284,   522,
     286,   287,   288,   317,   290,   372,   318,   319,   320,   458,
     480,   415,   296,   146,   297,   298,   299,   300,   301,   433,
     339,   473,   563,   606,   304,   684,   700,   308,   309,   310,
     311,   694,   717,   640,   657,   660,   524,   222,   651,   726,
     119,   245,   323,   324,   325,   326,   327,   328,   329,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   340,   341,   342,   343,   344,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   376,   377,
     378,   379,   380,   381,   382,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   460,   461,   462,   463,   464,   465,   466,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     470,   471,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   489,   490,
     491,   492,     0,     0,     0,   493,     0,     0,     0,     0,
       0,     0,     0,   520,   521,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   568
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-552)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,   168,    86,    87,   121,    88,   219,   169,   322,    10,
     290,   562,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    10,     4,     4,     7,    88,    21,    97,
     292,    12,   100,    14,    88,    11,    37,    12,    19,   313,
      12,    22,    23,    24,    21,   364,    20,   131,   599,   313,
      21,    32,    34,    35,    36,   313,    37,   313,     6,     8,
       9,    42,    82,    11,    77,    78,    79,    84,    85,    12,
     493,    84,    85,    82,    82,    51,    19,    78,    82,   140,
      92,    93,    83,   103,   346,    86,    87,   510,   511,   157,
     364,    92,    93,    42,   102,   108,    97,   416,   521,   100,
     364,   109,    84,    85,   418,   109,   364,     0,   364,   630,
     424,   104,   633,   634,   635,   102,   117,   668,   669,   670,
     671,   672,   103,   124,   104,   104,   647,    12,   103,   106,
     131,   103,   106,   104,    19,   558,   559,   149,   150,   151,
     152,   153,    77,    78,     7,   568,   667,    76,   149,   150,
     151,   152,   153,    82,   705,   435,   157,   708,   102,   710,
      82,    82,    82,    82,    82,   166,   167,    82,   689,   690,
     691,   692,   693,   108,   695,   176,    12,   339,   107,    82,
     104,   102,   102,   704,   102,   103,   105,   109,   189,   110,
     111,   109,   713,    82,   109,   196,   696,   102,   719,   102,
     721,   722,   723,   204,   725,   726,    82,   110,   111,   293,
      80,    81,    48,    49,    50,   715,   105,    77,    78,   220,
     433,    77,    78,   224,    77,    78,   102,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    82,
      76,    27,    28,    29,   104,    82,   104,    82,   104,    82,
     251,   104,    77,    78,   102,    27,    28,    29,    44,    45,
      46,    47,   104,    82,   106,   102,   109,    82,   103,    82,
      21,   107,    44,    45,    46,    47,   109,    82,   361,   104,
     104,    82,   399,   284,   103,   286,   287,   288,   103,   290,
     103,   292,   293,    94,    83,   104,   105,    86,   103,    77,
      89,    79,   303,   109,    90,   306,    84,    85,   501,     7,
     104,   312,   106,    11,   507,   508,   509,   103,    90,    12,
     321,   322,    12,    13,    14,   104,    16,    17,    18,    19,
       7,   103,    22,    23,    24,    25,    42,    27,    28,    29,
      30,    31,    77,    33,    38,   346,    40,    41,     6,    84,
      85,   104,    42,    43,    44,    45,    46,    47,    99,   100,
     101,   362,    99,   100,   101,    77,    78,    79,    48,    49,
     371,   454,    84,    85,   375,   104,    12,    13,    14,   106,
      16,    17,    18,    19,    48,    49,    22,    23,    24,    25,
     102,    27,    28,    29,    30,    31,   104,    33,   106,   104,
      90,    91,   102,    93,   104,   104,    42,    43,    44,    45,
      46,    47,     8,     9,   104,     7,   104,   418,   106,   420,
      12,   701,    14,   424,    73,    74,    75,    19,    48,    49,
      22,    23,    24,   104,   435,   519,    95,    96,    97,    98,
      32,    82,    73,   610,    75,    37,   613,    59,    60,    61,
      42,   104,   453,   106,   455,    91,    92,    93,   459,   460,
     461,   462,    55,    56,    57,    58,    48,    49,   104,    32,
      33,   104,   105,    40,    41,   642,   105,   644,   105,   498,
     499,   500,   501,   502,   503,   504,   505,   506,    86,    87,
      12,    13,    14,   660,    16,    17,    18,    19,    84,    85,
      22,    23,    24,    25,   105,    27,    28,    29,    30,    31,
     105,    33,    15,   514,   105,   105,   105,   104,   519,   103,
     105,    43,    44,    45,    46,    47,   102,   104,   106,   104,
      25,    26,    27,    28,   104,    30,    31,    32,    33,    34,
     104,   109,    32,    26,    38,    26,    12,    13,    14,   102,
      16,    17,    18,    19,   104,   104,    22,    23,    24,    25,
     561,    27,    28,    29,    30,    31,   104,    33,    90,    91,
     104,    93,   104,   104,   104,   104,   104,    43,    44,    45,
      46,    47,   104,   572,   573,   574,   575,   104,   577,   578,
     579,   580,   102,   582,   583,   104,   585,   586,   587,   104,
     601,   602,   104,   104,   104,   104,    37,   102,   105,   102,
     105,   106,   107,   108,   105,   110,   111,   112,   113,   114,
     105,   105,    39,   105,   104,    91,    92,    93,   629,   630,
     105,   105,   633,   634,   635,   130,   104,   104,   104,   104,
     104,   136,   572,   573,   574,   575,   647,   577,   578,   579,
     580,   652,   582,   583,   104,   585,   586,   587,   104,   104,
     661,   104,    38,   573,   574,   575,   667,   577,   578,   579,
     580,   103,   582,   583,    11,   585,   586,   587,   104,   680,
     104,   104,   104,   104,   104,   104,   687,    64,   689,   690,
     691,   692,   693,   104,   695,    67,    67,    70,    83,    51,
     701,    75,    77,   704,   105,    62,    52,   105,   104,   104,
     104,     3,   713,    53,   105,    54,    86,    11,   719,    87,
     721,   722,   723,   128,   725,   726,    80,   197,   223,   481,
     225,   226,   227,   257,   229,   315,   257,   257,   257,   422,
     456,   364,   237,    91,   239,   240,   241,   242,   243,   383,
     294,   448,   515,   565,   249,   655,   682,   252,   253,   254,
     255,   674,   698,   604,   638,   644,   486,   157,   636,   716,
      66,   186,   267,   268,   269,   270,   271,   272,   273,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   296,   297,   298,   299,   300,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,   324,
     325,   326,   327,   328,   329,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   426,   427,   428,   429,   430,   431,   432,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     445,   446,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   463,   464,
     465,   466,    -1,    -1,    -1,   470,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   478,   479,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   520
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    88,   113,   114,   115,   273,   274,    82,   265,     0,
       7,   118,   119,    12,    13,    14,    16,    17,    18,    19,
      22,    23,    24,    25,    27,    28,    29,    30,    31,    33,
      43,    44,    45,    46,    47,    90,    91,    93,   104,   151,
     152,   153,   154,   155,   156,   157,   159,   160,   162,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   190,   272,   276,   277,   278,   279,   285,
     288,    83,    86,    89,   245,   269,   275,   265,    11,   119,
     120,   121,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,    76,   107,   164,   165,   265,   102,   110,   111,
     251,   252,   253,   261,   265,   253,   253,   253,   253,   102,
     253,   253,   253,   253,   253,   102,   265,    42,   214,   278,
     290,   102,   104,   265,     6,   121,   122,   123,   124,   125,
      20,   106,   158,   250,   265,   104,    21,   138,   250,   250,
     138,   158,   104,    80,    81,   161,   161,   164,   164,    77,
      78,    79,    84,    85,   102,   109,   261,   262,   263,   265,
     261,   265,   253,   109,   253,   253,   253,   253,    12,   188,
     189,   253,   253,   253,   253,   253,     7,    12,    14,    19,
      22,    23,    24,    32,    37,    42,   280,   281,   282,   283,
     104,   265,   290,   276,   265,   116,     7,   126,   127,   125,
     253,   250,   104,   104,   106,   253,   104,   104,   104,   158,
     104,   104,   104,   108,   164,   164,   164,   164,   164,   166,
     264,   103,   263,   105,   254,   105,   105,   105,   265,   105,
     248,   249,   265,    82,   259,   103,   189,   105,   104,   105,
     105,   105,   105,   265,   103,   281,   104,   265,   284,    15,
     103,   102,    95,    96,    97,    98,   128,   129,   130,   131,
     132,   133,   265,   127,   104,   265,   104,    27,    28,    29,
      44,    45,    46,    47,   103,   167,   168,   169,   170,   171,
     172,   173,   279,   265,   253,   265,   253,   253,   253,   104,
     253,   104,   109,   105,   102,   104,   253,   253,   253,   253,
     253,   253,   104,   106,   253,   286,   260,   265,   253,   253,
     253,   253,    32,   134,   135,   136,   137,   130,   131,   132,
     133,    10,   102,   253,   253,   253,   253,   253,   253,   253,
      26,   163,   265,   265,   265,   265,   248,   249,   250,   188,
     253,   253,   253,   253,   253,   265,    38,   215,    26,   287,
     289,   103,   265,    48,    49,    48,    49,    48,    49,    48,
      49,   265,    92,   104,   149,   150,   151,   152,   162,   271,
     285,    33,   137,   139,   265,   260,   253,   253,   253,   253,
     253,   253,   253,   102,     4,   104,   268,   104,   104,   104,
     104,   103,   104,   104,   104,   104,   104,   249,   104,   102,
     104,   104,   104,   104,   104,   104,    99,   100,   101,    99,
     100,   101,   104,   138,   265,   150,   213,   214,   102,   265,
      37,   140,   141,   142,   102,   103,   105,   105,   105,   105,
     105,   105,   105,   166,   104,    39,   276,   104,   104,   104,
     104,   104,   104,   104,   104,     8,     9,   191,   192,   193,
     194,   195,   214,   260,   265,    38,   143,   144,   142,   260,
     253,   253,   253,   253,   253,   253,   253,   103,   248,   103,
     253,   253,   117,   193,   103,   104,   138,   265,    40,    41,
     144,   145,   146,   147,   148,   103,   265,   265,   265,   253,
     253,   253,   253,   253,    12,    48,    49,    50,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      76,   107,   196,   197,    11,   216,   217,   104,   104,   105,
     253,   253,   146,   104,   268,   104,   104,   104,   104,   104,
     104,   196,    34,    35,    36,    84,    85,   211,   212,    12,
      19,    12,    19,   211,   211,   211,   211,   212,   211,   211,
     211,   211,   211,   212,   212,   212,   196,   196,    77,    78,
     104,   265,    51,   217,   225,   226,   227,   250,   253,   196,
     104,   104,   207,   209,   208,   210,    64,   198,   199,   200,
     201,    67,   202,   203,    70,   204,   205,   206,    73,    74,
      75,    75,    73,    75,   108,   196,   196,   246,   265,   269,
      59,    60,    61,   238,   239,   240,   227,   104,   196,   104,
     102,   251,   252,   255,   256,   257,   259,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   105,
     269,    82,    94,   266,   265,   265,    62,   241,   242,   243,
     240,   104,   258,   259,   102,   259,   265,   246,   246,   246,
     246,   266,    52,   228,   229,   230,   231,   243,   103,   259,
     258,   105,   246,   104,   104,   104,     3,   267,   265,    55,
      56,    57,    58,   218,   219,   220,   221,   222,   223,   224,
      53,   232,   233,   234,   231,   103,   265,   109,   246,   269,
     269,   269,   269,   269,   220,   265,    54,   235,   236,   237,
     234,   105,   247,   109,   265,   109,   246,   246,   109,   246,
     109,   246,   246,   246,    87,   245,   270,   237,   248,   244,
     246,   269,   269,   269,   246,   245,   270,   246,   246,   246,
     246,   246,   246
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
        case 4:
/* Line 1792 of yacc.c  */
#line 158 "external/checkpolicy/policy_parse.y"
    { if (define_policy(pass, 0) == -1) return -1; }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 160 "external/checkpolicy/policy_parse.y"
    { if (pass == 1) { if (policydb_index_classes(policydbp)) return -1; }
                            else if (pass == 2) { if (policydb_index_others(NULL, policydbp, 0)) return -1; }}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 163 "external/checkpolicy/policy_parse.y"
    { if (pass == 1) { if (policydb_index_bools(policydbp)) return -1;}
			   else if (pass == 2) { if (policydb_index_others(NULL, policydbp, 0)) return -1;}}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 171 "external/checkpolicy/policy_parse.y"
    {if (define_class()) return -1;}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 177 "external/checkpolicy/policy_parse.y"
    {if (define_initial_sid()) return -1;}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 188 "external/checkpolicy/policy_parse.y"
    {if (define_common_perms()) return -1;}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 194 "external/checkpolicy/policy_parse.y"
    {if (define_av_perms(FALSE)) return -1;}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 196 "external/checkpolicy/policy_parse.y"
    {if (define_av_perms(TRUE)) return -1;}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 198 "external/checkpolicy/policy_parse.y"
    {if (define_av_perms(TRUE)) return -1;}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 213 "external/checkpolicy/policy_parse.y"
    {if (define_default_user(DEFAULT_SOURCE)) return -1; }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 215 "external/checkpolicy/policy_parse.y"
    {if (define_default_user(DEFAULT_TARGET)) return -1; }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 218 "external/checkpolicy/policy_parse.y"
    {if (define_default_role(DEFAULT_SOURCE)) return -1; }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 220 "external/checkpolicy/policy_parse.y"
    {if (define_default_role(DEFAULT_TARGET)) return -1; }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 223 "external/checkpolicy/policy_parse.y"
    {if (define_default_type(DEFAULT_SOURCE)) return -1; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 225 "external/checkpolicy/policy_parse.y"
    {if (define_default_type(DEFAULT_TARGET)) return -1; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 228 "external/checkpolicy/policy_parse.y"
    {if (define_default_range(DEFAULT_SOURCE_LOW)) return -1; }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 230 "external/checkpolicy/policy_parse.y"
    {if (define_default_range(DEFAULT_SOURCE_HIGH)) return -1; }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 232 "external/checkpolicy/policy_parse.y"
    {if (define_default_range(DEFAULT_SOURCE_LOW_HIGH)) return -1; }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 234 "external/checkpolicy/policy_parse.y"
    {if (define_default_range(DEFAULT_TARGET_LOW)) return -1; }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 236 "external/checkpolicy/policy_parse.y"
    {if (define_default_range(DEFAULT_TARGET_HIGH)) return -1; }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 238 "external/checkpolicy/policy_parse.y"
    {if (define_default_range(DEFAULT_TARGET_LOW_HIGH)) return -1; }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 249 "external/checkpolicy/policy_parse.y"
    {if (define_sens()) return -1;}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 251 "external/checkpolicy/policy_parse.y"
    {if (define_sens()) return -1;}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 256 "external/checkpolicy/policy_parse.y"
    {if (define_dominance()) return -1;}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 258 "external/checkpolicy/policy_parse.y"
    {if (define_dominance()) return -1;}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 267 "external/checkpolicy/policy_parse.y"
    {if (define_category()) return -1;}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 269 "external/checkpolicy/policy_parse.y"
    {if (define_category()) return -1;}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 275 "external/checkpolicy/policy_parse.y"
    {if (define_level()) return -1;}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 277 "external/checkpolicy/policy_parse.y"
    {if (define_level()) return -1;}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 286 "external/checkpolicy/policy_parse.y"
    { if (define_constraint((constraint_expr_t*)(yyvsp[(4) - (5)].valptr))) return -1; }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 289 "external/checkpolicy/policy_parse.y"
    { if (define_validatetrans((constraint_expr_t*)(yyvsp[(3) - (4)].valptr))) return -1; }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 322 "external/checkpolicy/policy_parse.y"
    { if (define_attrib()) return -1;}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 325 "external/checkpolicy/policy_parse.y"
    {if (define_type(1)) return -1;}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 327 "external/checkpolicy/policy_parse.y"
    {if (define_type(0)) return -1;}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 330 "external/checkpolicy/policy_parse.y"
    {if (define_typealias()) return -1;}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 333 "external/checkpolicy/policy_parse.y"
    {if (define_typeattribute()) return -1;}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 336 "external/checkpolicy/policy_parse.y"
    {if (define_typebounds()) return -1;}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 342 "external/checkpolicy/policy_parse.y"
    { if (define_bool_tunable(0)) return -1; }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 345 "external/checkpolicy/policy_parse.y"
    { if (define_bool_tunable(1)) return -1; }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 348 "external/checkpolicy/policy_parse.y"
    { if (insert_id("T",0)) return -1; }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 350 "external/checkpolicy/policy_parse.y"
    { if (insert_id("F",0)) return -1; }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 353 "external/checkpolicy/policy_parse.y"
    { if (pass == 2) { if (define_conditional((cond_expr_t*)(yyvsp[(2) - (6)].ptr), (avrule_t*)(yyvsp[(4) - (6)].ptr), (avrule_t*)(yyvsp[(6) - (6)].ptr)) < 0) return -1;  }}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 356 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(3) - (4)].ptr); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 358 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = NULL; }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 360 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(2) - (3)].ptr);}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 362 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_expr(COND_NOT, (yyvsp[(2) - (2)].ptr), 0);
			  if ((yyval.ptr) == 0) return -1; }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 365 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_expr(COND_AND, (yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr));
			  if ((yyval.ptr) == 0) return  -1; }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 368 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_expr(COND_OR, (yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr));
			  if ((yyval.ptr) == 0) return   -1; }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 371 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_expr(COND_XOR, (yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr));
			  if ((yyval.ptr) == 0) return  -1; }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 374 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_expr(COND_EQ, (yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr));
			  if ((yyval.ptr) == 0) return  -1; }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 377 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_expr(COND_NEQ, (yyvsp[(1) - (3)].ptr), (yyvsp[(3) - (3)].ptr));
			  if ((yyval.ptr) == 0) return  -1; }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 380 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 383 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_expr(COND_BOOL,0, 0);
			  if ((yyval.ptr) == COND_ERR) return   -1; }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 387 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_pol_list((avrule_t *)(yyvsp[(1) - (2)].ptr), (avrule_t *)(yyvsp[(2) - (2)].ptr)); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 389 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = NULL; }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 392 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 394 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 396 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = NULL; }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 399 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_filename_trans() ;
                          if ((yyval.ptr) == COND_ERR) return -1;}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 402 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_compute_type(AVRULE_TRANSITION) ;
                          if ((yyval.ptr) == COND_ERR) return -1;}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 405 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_compute_type(AVRULE_MEMBER) ;
                          if ((yyval.ptr) ==  COND_ERR) return -1;}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 408 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_compute_type(AVRULE_CHANGE) ;
                          if ((yyval.ptr) == COND_ERR) return -1;}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 412 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 414 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 416 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 418 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 421 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_te_avtab(AVRULE_ALLOWED) ;
                          if ((yyval.ptr) == COND_ERR) return -1; }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 425 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_te_avtab(AVRULE_AUDITALLOW) ;
                          if ((yyval.ptr) == COND_ERR) return -1; }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 429 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_te_avtab(AVRULE_AUDITDENY) ;
                          if ((yyval.ptr) == COND_ERR) return -1; }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 433 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = define_cond_te_avtab(AVRULE_DONTAUDIT);
                          if ((yyval.ptr) == COND_ERR) return -1; }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 438 "external/checkpolicy/policy_parse.y"
    {if (define_filename_trans()) return -1; }
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 440 "external/checkpolicy/policy_parse.y"
    {if (define_compute_type(AVRULE_TRANSITION)) return -1;}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 442 "external/checkpolicy/policy_parse.y"
    {if (define_compute_type(AVRULE_MEMBER)) return -1;}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 444 "external/checkpolicy/policy_parse.y"
    {if (define_compute_type(AVRULE_CHANGE)) return -1;}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 447 "external/checkpolicy/policy_parse.y"
    { if (define_range_trans(0)) return -1; }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 449 "external/checkpolicy/policy_parse.y"
    { if (define_range_trans(1)) return -1; }
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 458 "external/checkpolicy/policy_parse.y"
    {if (define_te_avtab(AVRULE_ALLOWED)) return -1; }
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 461 "external/checkpolicy/policy_parse.y"
    {if (define_te_avtab(AVRULE_AUDITALLOW)) return -1; }
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 464 "external/checkpolicy/policy_parse.y"
    {if (define_te_avtab(AVRULE_AUDITDENY)) return -1; }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 467 "external/checkpolicy/policy_parse.y"
    {if (define_te_avtab(AVRULE_DONTAUDIT)) return -1; }
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 470 "external/checkpolicy/policy_parse.y"
    {if (define_te_avtab(AVRULE_NEVERALLOW)) return -1; }
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 473 "external/checkpolicy/policy_parse.y"
    {if (define_attrib_role()) return -1; }
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 476 "external/checkpolicy/policy_parse.y"
    {if (define_role_types()) return -1;}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 479 "external/checkpolicy/policy_parse.y"
    {if (define_role_attr()) return -1;}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 484 "external/checkpolicy/policy_parse.y"
    {if (define_role_trans(0)) return -1; }
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 486 "external/checkpolicy/policy_parse.y"
    {if (define_role_trans(1)) return -1;}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 489 "external/checkpolicy/policy_parse.y"
    {if (define_role_allow()) return -1; }
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 492 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = (yyvsp[(1) - (1)].ptr); }
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 494 "external/checkpolicy/policy_parse.y"
    { (yyval.ptr) = merge_roles_dom((role_datum_t*)(yyvsp[(1) - (2)].ptr), (role_datum_t*)(yyvsp[(2) - (2)].ptr)); if ((yyval.ptr) == 0) return -1;}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 497 "external/checkpolicy/policy_parse.y"
    {(yyval.ptr) = define_role_dom(NULL); if ((yyval.ptr) == 0) return -1;}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 499 "external/checkpolicy/policy_parse.y"
    {(yyval.ptr) = define_role_dom((role_datum_t*)(yyvsp[(4) - (5)].ptr)); if ((yyval.ptr) == 0) return -1;}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 502 "external/checkpolicy/policy_parse.y"
    {if (define_roleattribute()) return -1;}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 514 "external/checkpolicy/policy_parse.y"
    { if (define_constraint((constraint_expr_t*)(yyvsp[(4) - (5)].valptr))) return -1; }
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 517 "external/checkpolicy/policy_parse.y"
    { if (define_validatetrans((constraint_expr_t*)(yyvsp[(3) - (4)].valptr))) return -1; }
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 520 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = (yyvsp[(2) - (3)].valptr); }
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 522 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NOT, (yyvsp[(2) - (2)].valptr), 0);
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 525 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_AND, (yyvsp[(1) - (3)].valptr), (yyvsp[(3) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 528 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_OR, (yyvsp[(1) - (3)].valptr), (yyvsp[(3) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 531 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = (yyvsp[(1) - (1)].valptr); }
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 534 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_USER, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 537 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_ROLE, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 540 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_TYPE, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 542 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 543 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, CEXPR_USER, (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 545 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 546 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_USER | CEXPR_TARGET), (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 548 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 549 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_USER | CEXPR_XTARGET), (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 551 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 552 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, CEXPR_ROLE, (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 554 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 555 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_ROLE | CEXPR_TARGET), (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 557 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 558 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_ROLE | CEXPR_XTARGET), (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 560 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 561 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, CEXPR_TYPE, (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 563 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 564 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_TYPE | CEXPR_TARGET), (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 566 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 567 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_TYPE | CEXPR_XTARGET), (yyvsp[(2) - (4)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 570 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_USER, CEXPR_EQ);
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 572 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 573 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, CEXPR_ROLE, CEXPR_EQ);
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 575 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 576 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_ROLE | CEXPR_TARGET), CEXPR_EQ);
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 579 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_ROLE, (yyvsp[(2) - (2)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 581 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 582 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, CEXPR_TYPE, CEXPR_EQ);
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 584 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(1)) return -1; }
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 585 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_NAMES, (CEXPR_TYPE | CEXPR_TARGET), CEXPR_EQ);
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 588 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_L1L2, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 591 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_L1H2, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 594 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_H1L2, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 597 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_H1H2, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 600 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_L1H1, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 603 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = define_cexpr(CEXPR_ATTR, CEXPR_L2H2, (yyvsp[(2) - (3)].valptr));
			  if ((yyval.valptr) == 0) return -1; }
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 607 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = CEXPR_EQ; }
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 609 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = CEXPR_NEQ; }
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 612 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = (yyvsp[(1) - (1)].valptr); }
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 614 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = CEXPR_DOM; }
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 616 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = CEXPR_DOMBY; }
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 618 "external/checkpolicy/policy_parse.y"
    { (yyval.valptr) = CEXPR_INCOMP; }
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 624 "external/checkpolicy/policy_parse.y"
    {if (define_user()) return -1;}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 633 "external/checkpolicy/policy_parse.y"
    {if (define_initial_sid_context()) return -1;}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 646 "external/checkpolicy/policy_parse.y"
    {if (define_pirq_context((yyvsp[(2) - (3)].val))) return -1;}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 649 "external/checkpolicy/policy_parse.y"
    {if (define_iomem_context((yyvsp[(2) - (3)].val),(yyvsp[(2) - (3)].val))) return -1;}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 651 "external/checkpolicy/policy_parse.y"
    {if (define_iomem_context((yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].val))) return -1;}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 654 "external/checkpolicy/policy_parse.y"
    {if (define_ioport_context((yyvsp[(2) - (3)].val),(yyvsp[(2) - (3)].val))) return -1;}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 656 "external/checkpolicy/policy_parse.y"
    {if (define_ioport_context((yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].val))) return -1;}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 659 "external/checkpolicy/policy_parse.y"
    {if (define_pcidevice_context((yyvsp[(2) - (3)].val))) return -1;}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 668 "external/checkpolicy/policy_parse.y"
    {if (define_fs_context((yyvsp[(2) - (5)].val),(yyvsp[(3) - (5)].val))) return -1;}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 679 "external/checkpolicy/policy_parse.y"
    {if (define_port_context((yyvsp[(3) - (4)].val),(yyvsp[(3) - (4)].val))) return -1;}
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 681 "external/checkpolicy/policy_parse.y"
    {if (define_port_context((yyvsp[(3) - (6)].val),(yyvsp[(5) - (6)].val))) return -1;}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 690 "external/checkpolicy/policy_parse.y"
    {if (define_netif_context()) return -1;}
    break;

  case 267:
/* Line 1792 of yacc.c  */
#line 699 "external/checkpolicy/policy_parse.y"
    {if (define_ipv4_node_context()) return -1;}
    break;

  case 268:
/* Line 1792 of yacc.c  */
#line 701 "external/checkpolicy/policy_parse.y"
    {if (define_ipv6_node_context()) return -1;}
    break;

  case 273:
/* Line 1792 of yacc.c  */
#line 710 "external/checkpolicy/policy_parse.y"
    {if (define_fs_use(SECURITY_FS_USE_XATTR)) return -1;}
    break;

  case 274:
/* Line 1792 of yacc.c  */
#line 712 "external/checkpolicy/policy_parse.y"
    {if (define_fs_use(SECURITY_FS_USE_TASK)) return -1;}
    break;

  case 275:
/* Line 1792 of yacc.c  */
#line 714 "external/checkpolicy/policy_parse.y"
    {if (define_fs_use(SECURITY_FS_USE_TRANS)) return -1;}
    break;

  case 280:
/* Line 1792 of yacc.c  */
#line 723 "external/checkpolicy/policy_parse.y"
    {if (define_genfs_context(1)) return -1;}
    break;

  case 281:
/* Line 1792 of yacc.c  */
#line 724 "external/checkpolicy/policy_parse.y"
    {insert_id("-", 0);}
    break;

  case 282:
/* Line 1792 of yacc.c  */
#line 725 "external/checkpolicy/policy_parse.y"
    {if (define_genfs_context(1)) return -1;}
    break;

  case 283:
/* Line 1792 of yacc.c  */
#line 727 "external/checkpolicy/policy_parse.y"
    {if (define_genfs_context(0)) return -1;}
    break;

  case 284:
/* Line 1792 of yacc.c  */
#line 730 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 288:
/* Line 1792 of yacc.c  */
#line 738 "external/checkpolicy/policy_parse.y"
    {if (insert_separator(0)) return -1;}
    break;

  case 289:
/* Line 1792 of yacc.c  */
#line 740 "external/checkpolicy/policy_parse.y"
    {if (insert_separator(0)) return -1;}
    break;

  case 290:
/* Line 1792 of yacc.c  */
#line 743 "external/checkpolicy/policy_parse.y"
    {if (insert_separator(0)) return -1;}
    break;

  case 291:
/* Line 1792 of yacc.c  */
#line 745 "external/checkpolicy/policy_parse.y"
    {if (insert_separator(0)) return -1;}
    break;

  case 296:
/* Line 1792 of yacc.c  */
#line 755 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(0)) return -1; }
    break;

  case 297:
/* Line 1792 of yacc.c  */
#line 757 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(0)) return -1; }
    break;

  case 298:
/* Line 1792 of yacc.c  */
#line 759 "external/checkpolicy/policy_parse.y"
    { if (insert_id("*", 0)) return -1; 
			  if (insert_separator(0)) return -1; }
    break;

  case 299:
/* Line 1792 of yacc.c  */
#line 762 "external/checkpolicy/policy_parse.y"
    { if (insert_id("~", 0)) return -1;
			  if (insert_separator(0)) return -1; }
    break;

  case 300:
/* Line 1792 of yacc.c  */
#line 765 "external/checkpolicy/policy_parse.y"
    { if (insert_id("~", 0)) return -1; 
			  if (insert_separator(0)) return -1; }
    break;

  case 301:
/* Line 1792 of yacc.c  */
#line 767 "external/checkpolicy/policy_parse.y"
    { if (insert_id("-", 0)) return -1; }
    break;

  case 302:
/* Line 1792 of yacc.c  */
#line 768 "external/checkpolicy/policy_parse.y"
    { if (insert_separator(0)) return -1; }
    break;

  case 303:
/* Line 1792 of yacc.c  */
#line 771 "external/checkpolicy/policy_parse.y"
    { if (insert_id("~", 1)) return -1; }
    break;

  case 304:
/* Line 1792 of yacc.c  */
#line 774 "external/checkpolicy/policy_parse.y"
    { if (insert_id("*", 1)) return -1; }
    break;

  case 312:
/* Line 1792 of yacc.c  */
#line 786 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext, 1)) return -1; }
    break;

  case 319:
/* Line 1792 of yacc.c  */
#line 795 "external/checkpolicy/policy_parse.y"
    { if (insert_id("-", 0)) return -1; }
    break;

  case 322:
/* Line 1792 of yacc.c  */
#line 798 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 323:
/* Line 1792 of yacc.c  */
#line 801 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 324:
/* Line 1792 of yacc.c  */
#line 803 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 325:
/* Line 1792 of yacc.c  */
#line 806 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 326:
/* Line 1792 of yacc.c  */
#line 809 "external/checkpolicy/policy_parse.y"
    { yytext[strlen(yytext) - 1] = '\0'; if (insert_id(yytext + 1,0)) return -1; }
    break;

  case 327:
/* Line 1792 of yacc.c  */
#line 812 "external/checkpolicy/policy_parse.y"
    { (yyval.val) = strtoul(yytext,NULL,0); }
    break;

  case 328:
/* Line 1792 of yacc.c  */
#line 815 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 329:
/* Line 1792 of yacc.c  */
#line 818 "external/checkpolicy/policy_parse.y"
    {if (define_polcap()) return -1;}
    break;

  case 330:
/* Line 1792 of yacc.c  */
#line 821 "external/checkpolicy/policy_parse.y"
    {if (define_permissive()) return -1;}
    break;

  case 331:
/* Line 1792 of yacc.c  */
#line 826 "external/checkpolicy/policy_parse.y"
    { if (end_avrule_block(pass) == -1) return -1;
                          if (policydb_index_others(NULL, policydbp, 0)) return -1;
                        }
    break;

  case 332:
/* Line 1792 of yacc.c  */
#line 831 "external/checkpolicy/policy_parse.y"
    { if (define_policy(pass, 1) == -1) return -1; }
    break;

  case 333:
/* Line 1792 of yacc.c  */
#line 834 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 334:
/* Line 1792 of yacc.c  */
#line 836 "external/checkpolicy/policy_parse.y"
    { if (insert_id(yytext,0)) return -1; }
    break;

  case 350:
/* Line 1792 of yacc.c  */
#line 860 "external/checkpolicy/policy_parse.y"
    { if (require_class(pass)) return -1; }
    break;

  case 351:
/* Line 1792 of yacc.c  */
#line 862 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_role; }
    break;

  case 352:
/* Line 1792 of yacc.c  */
#line 863 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_type; }
    break;

  case 353:
/* Line 1792 of yacc.c  */
#line 864 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_attribute; }
    break;

  case 354:
/* Line 1792 of yacc.c  */
#line 865 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_attribute_role; }
    break;

  case 355:
/* Line 1792 of yacc.c  */
#line 866 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_user; }
    break;

  case 356:
/* Line 1792 of yacc.c  */
#line 867 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_bool; }
    break;

  case 357:
/* Line 1792 of yacc.c  */
#line 868 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_tunable; }
    break;

  case 358:
/* Line 1792 of yacc.c  */
#line 869 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_sens; }
    break;

  case 359:
/* Line 1792 of yacc.c  */
#line 870 "external/checkpolicy/policy_parse.y"
    { (yyval.require_func) = require_cat; }
    break;

  case 360:
/* Line 1792 of yacc.c  */
#line 873 "external/checkpolicy/policy_parse.y"
    { if ((yyvsp[(0) - (1)].require_func) (pass)) return -1; }
    break;

  case 361:
/* Line 1792 of yacc.c  */
#line 875 "external/checkpolicy/policy_parse.y"
    { if ((yyvsp[(0) - (3)].require_func) (pass)) return -1; }
    break;

  case 362:
/* Line 1792 of yacc.c  */
#line 878 "external/checkpolicy/policy_parse.y"
    { if (end_avrule_block(pass) == -1) return -1; }
    break;

  case 363:
/* Line 1792 of yacc.c  */
#line 880 "external/checkpolicy/policy_parse.y"
    { if (end_optional(pass) == -1) return -1; }
    break;

  case 364:
/* Line 1792 of yacc.c  */
#line 883 "external/checkpolicy/policy_parse.y"
    { if (end_avrule_block(pass) == -1) return -1; }
    break;

  case 366:
/* Line 1792 of yacc.c  */
#line 887 "external/checkpolicy/policy_parse.y"
    { if (begin_optional(pass) == -1) return -1; }
    break;

  case 367:
/* Line 1792 of yacc.c  */
#line 890 "external/checkpolicy/policy_parse.y"
    { if (begin_optional_else(pass) == -1) return -1; }
    break;


/* Line 1792 of yacc.c  */
#line 3567 "out/host/linux-x86/obj32/EXECUTABLES/checkpolicy_intermediates/policy_parse.cpp"
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


