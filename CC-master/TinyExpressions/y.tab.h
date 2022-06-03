/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    tINTCONST = 258,
    tIDENTIFIER = 259,
    AND = 260,
    OR = 261,
    EQ = 262,
    LEQ = 263,
    GEQ = 264,
    NEQ = 265,
    INC = 266,
    DEC = 267,
    tBOOL = 268,
    tNULL = 269,
    ERROR = 270,
    RETURN = 271,
    WHILE = 272,
    ALLOCATE = 273,
    WRITE = 274,
    OFLENGTH = 275,
    IF = 276,
    ELSE = 277,
    THEN = 278,
    DO = 279,
    FOR = 280,
    TYPEY = 281,
    ARRAYOF = 282,
    RECORDOF = 283,
    VARI = 284,
    FUNC = 285,
    INT = 286,
    BOOL = 287,
    END = 288
  };
#endif
/* Tokens.  */
#define tINTCONST 258
#define tIDENTIFIER 259
#define AND 260
#define OR 261
#define EQ 262
#define LEQ 263
#define GEQ 264
#define NEQ 265
#define INC 266
#define DEC 267
#define tBOOL 268
#define tNULL 269
#define ERROR 270
#define RETURN 271
#define WHILE 272
#define ALLOCATE 273
#define WRITE 274
#define OFLENGTH 275
#define IF 276
#define ELSE 277
#define THEN 278
#define DO 279
#define FOR 280
#define TYPEY 281
#define ARRAYOF 282
#define RECORDOF 283
#define VARI 284
#define FUNC 285
#define INT 286
#define BOOL 287
#define END 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "compiler.y" /* yacc.c:1909  */

   int intconst;
   char *stringconst;
   int boolconst;
   void *nullconst;
   struct EXP *exp;
   struct TERM *term;
   struct EXPLIST *exp_list;
   struct VAR *variable;
   struct ACTLIST *act_list;
   struct FUNCTION *function;
   struct HEAD *head;
   struct TAIL *tail;
   struct TYPE *type;
   struct PAR_DECL_LIST *par_decl_list;
   struct VAR_DECL_LIST *var_decl_list;
   struct VAR_TYPE *var_type;
   struct BODY *body;
   struct DECLARATION *declaration;
   struct DECL_LIST *decl_list;
   struct STATE *statement;
   struct STATE_LIST *statement_list;

#line 144 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
