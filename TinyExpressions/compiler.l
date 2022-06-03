%{
#include "y.tab.h"
#include <string.h>
extern int comment = 0;
extern int lineno;
extern int fileno();
%}

%option noyywrap nounput noinput
%x COMMENT

%%
[ \t]+        /* ignore */;
\n              lineno++;

"*"             { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return '*'; };
"/"             { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return '/'; }
"+"             { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return '+'; }
"-"             { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return '-'; };
"=="            { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return EQ; };
"!="            { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return NEQ; };
">"             { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return '>'; };
"<"             { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return '<'; };
">="            { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return GEQ; };
"<="            { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return LEQ; };
"&&"            { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return AND; };
" || "            { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return OR; };
"("             return '(';
")"             return ')';
"["             return '[';
"]"             return ']';
"{"             return '{';
"}"             return '}';
"|"             return '|';
"!"             return '!';
","             return ',';
"."             return '.';
"="             return '=';
":"             return ':';
";"             return ';';
"of length"     return OFLENGTH;
"allocate"      return ALLOCATE;
"write"         return WRITE;
"while"         return WHILE;
"do"            return DO;
"return"        return RETURN;
"if"            return IF;
"else"          return ELSE;
"then"          return THEN;
"var"           return VARI;
"record of"     return RECORDOF;
"array of"      return ARRAYOF;
"func"          return FUNC;
"int"           return INT;
"bool"          return BOOL;
"end"           return END;
"type"          return TYPEY;

"true"             { yylval.boolconst = 1;
                       return tBOOL; }

"false"             { yylval.boolconst = 0;
                       return tBOOL; }

"null"              { yylval.nullconst = NULL;
                       return tNULL; }

0|([1-9][0-9]*)        { yylval.intconst = atoi(yytext);
                       return tINTCONST; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return tIDENTIFIER; }
"#".*

"(*"                  {BEGIN(COMMENT);
                        comment++;}
<COMMENT>"*)"         { comment--;
                        if(comment == 0){BEGIN(INITIAL);}
                        }
<COMMENT>"(*"           {comment++;}
<COMMENT>(.|\n)      ;
<COMMENT><<EOF>>      return ERROR;


.                     return ERROR;/* ignore */;

%%
