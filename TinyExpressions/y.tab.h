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
    tBOOL = 266,
    tNULL = 267,
    ERROR = 268,
    RETURN = 269,
    WHILE = 270,
    ALLOCATE = 271,
    WRITE = 272,
    OFLENGTH = 273,
    IF = 274,
    ELSE = 275,
    THEN = 276,
    DO = 277,
    TYPEY = 278,
    ARRAYOF = 279,
    RECORDOF = 280,
    VARI = 281,
    FUNC = 282,
    INT = 283,
    BOOL = 284,
    END = 285
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
#define tBOOL 266
#define tNULL 267
#define ERROR 268
#define RETURN 269
#define WHILE 270
#define ALLOCATE 271
#define WRITE 272
#define OFLENGTH 273
#define IF 274
#define ELSE 275
#define THEN 276
#define DO 277
#define TYPEY 278
#define ARRAYOF 279
#define RECORDOF 280
#define VARI 281
#define FUNC 282
#define INT 283
#define BOOL 284
#define END 285

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

#line 138 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
