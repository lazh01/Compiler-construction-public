%{
#include <stdio.h>
#include "tree.h"

extern char *yytext;
extern BODY *theexpression;
extern int lineno;

void yyerror() {
   fprintf(stderr, "syntax error before %s, at line %d \n", yytext, lineno);
}
%}

%union {
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
}

%token <intconst> tINTCONST
%token <stringconst> tIDENTIFIER '+' '-' '*' '/' AND OR EQ LEQ GEQ NEQ '<' '>'
%token <boolconst> tBOOL
%token <nullconst>  tNULL
%token <error> ERROR

%token RETURN WHILE ALLOCATE WRITE OFLENGTH IF ELSE THEN DO TYPEY ARRAYOF RECORDOF VARI FUNC INT BOOL END
%type <exp> expression

%type <variable> variable
%type <term> term
%type <act_list> act_list
%type <exp_list> exp_list
%type <function> function
%type <head> head
%type <tail> tail
%type <type> type
%type <par_decl_list> par_decl_list
%type <var_decl_list> var_decl_list
%type <var_type> var_type
%type <body> body program
%type <declaration> declaration
%type <decl_list> decl_list
%type <statement> statement
%type <statement_list> statement_list

%start program

%nonassoc OR EQ LEQ GEQ NEQ
%right '<' '>'
%left '+' '-'
%left '*' '/' AND
%right '[' '{' '('
%left ']' '}' ')'
%nonassoc THEN 
%nonassoc ELSE


%%
program: body
         { theexpression = $1;}
;


variable : tIDENTIFIER
            {$$ = makeVARid($1);}
         | variable '[' expression ']'
            {$$ = makeVARlist($1, $3);}
         | variable '.' tIDENTIFIER
            {$$ = makeVARvarid($1, $3);}
;

expression  : expression '+' expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression '-' expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression '*' expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression '/' expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression '<' expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression '>' expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression AND expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression OR expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression GEQ expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression LEQ expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression NEQ expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | expression EQ expression
               {$$ = makeEXPbinop($1,$2,$3);}
            | term
               {$$ = makeEXPterm($1);}
;

exp_list : expression
            {$$ = makeEXPLISTexp($1);}
         | expression ',' exp_list
            {$$ = makeEXPLISTlist($1, $3);}
;

term  : variable
            {$$ = makeTERMvar($1);}
      | tINTCONST
            {$$ = makeTERMnum($1);}
      | tIDENTIFIER '(' act_list ')'
            {$$ = makeTERMidfunc($1, $3);}
      | '(' expression ')'
            {$$ = makeTERMexp($2);}
      | '!' term
            {$$ = makeTERMnot($2);}
      | '|' expression '|'
            {$$ = makeTERMlenexp($2);}
      | tBOOL
            {$$ = makeTERMbool($1);}
      | tNULL
            {$$ = makeTERMnull($1);}
;

act_list : exp_list
            {$$ = makeACTLISTlist($1);}
         | %empty
            {$$ = makeACTLISTnil();}
;

statement : RETURN expression ';'
                  {$$ = makeSTATEreturn($2);}
            | WRITE expression ';'
                  {$$ = makeSTATEwrite($2);}
            | ALLOCATE variable ';'
                  {$$ = makeSTATEallocate($2);}
            | ALLOCATE variable OFLENGTH expression ';'
                  {$$ = makeSTATEallocOfLength($2,$4);}
            | variable '=' expression ';'
                  {$$ = makeSTATEassign($1,$3);}
            | IF expression THEN statement
                  {$$ = makeSTATEif($2,$4);}
            | IF expression THEN statement ELSE statement
                  {$$ = makeSTATEifElse($2,$4,$6);}
            | WHILE expression DO statement
                  {$$ = makeSTATEwhile($2,$4);}
            | '{' statement_list '}'
                  {$$ = makeSTATEstateList($2);}
;

statement_list : statement
                  {$$ = makeSTATE_LISTstatement($1);}
               | statement statement_list
                  {$$ = makeSTATE_LISTstatementList($1,$2);}
;

declaration : TYPEY tIDENTIFIER '=' type ';'
                  {$$ = makeDECLARATIONtypeId($2, $4);}
         | function
                  {$$ = makeDECLARATIONdeclFuncD($1);}
         | VARI var_decl_list ';'
                  {$$ = makeDECLARATIONdeclVarD($2);}
;

decl_list : declaration decl_list
                  {$$ = makeDECL_LISTdeclList($1, $2);}
            | %empty
                  {$$ = makeDECL_LISTnil();}
;

body : decl_list statement_list
      {$$ = makeBODY($1, $2);}
;

var_type : tIDENTIFIER ':' type
            {$$ = makeVAR_TYPEid($1, $3);}
;

var_decl_list : var_type ',' var_decl_list
                  {$$ = makeVAR_DECL_LISTlist($1, $3);}
               | var_type
                  {$$ = makeVAR_DECL_LISTvt($1);}
;

par_decl_list : var_decl_list
                  {$$ = makePAR_DECL_LISTvdl($1);}
               | %empty
                  {$$ = makePAR_DECL_LISTnil();}
;

type : tIDENTIFIER
            {$$ = makeTYPEid($1);}
      | INT
            {$$ = makeTYPEint();}
      | BOOL
            {$$ = makeTYPEbool();}
      | ARRAYOF type
            {$$ = makeTYPEarrayof($2);}
      | RECORDOF '{' var_decl_list '}'
            {$$ = makeTYPErecordof($3);}
;

function : head body tail
            {$$ = makeFUNCTION($1, $2, $3);}
;

head : FUNC tIDENTIFIER '(' par_decl_list ')' ':' type
      {$$ = makeHEAD($2, $4, $7);}
;

tail : END tIDENTIFIER
            {$$ = makeTAIL($2);}
;
%%
