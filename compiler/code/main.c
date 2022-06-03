#include "tree.h"
#include "pretty.h"
#include "weed.h"
#include "typecheck.h"
#include "codegen.h"
#include <stdio.h>
/*
Compiler with finished parsing, weeding and typechecking
Code generation currently writes to file output.asm, 
this was done with the intention of replacing temporaries using 
liveness analysis and register allocation, which were not completed.
It is possible to run some programs by manually replacing temporaries with registers
*/

int lineno;

int yyparse();

BODY *theexpression;

int main()
{ lineno = 1;
  fprintf(stderr, "Parsing\n");
  if(yyparse()){
      return 1;
  }
  fprintf(stderr, "Weeding\n");
  weedBODY(theexpression);
  fprintf(stderr, "Typechecking\n");
  if(checkTREE(theexpression)){
      return 1;
  }
  prettyBODY(theexpression);
  fprintf(stderr, "Generating code\n");
  codeGEN(theexpression);
  return 0;
}
