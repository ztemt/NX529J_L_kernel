#ifndef policy_parse_h
#define policy_parse_h
/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
#line 68 "external/checkpolicy/policy_parse.y"

	unsigned int val;
	uintptr_t valptr;
	void *ptr;
        require_func_t require_func;


/* Line 2058 of yacc.c  */
#line 166 "out/host/linux-x86/obj32/EXECUTABLES/checkpolicy_intermediates/policy_parse.hpp"
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
#endif
