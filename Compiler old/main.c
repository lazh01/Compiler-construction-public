#include "tree.h"
#include "pretty.h"
#include "weed.h"
#include "typecheck.h"

int lineno;

void yyparse();

BODY *theexpression;

int main()
{ lineno = 1;
  yyparse();
  weedBODY(theexpression);
  prettyBODY(theexpression);
  checkTREE(theexpression);
  return 0;
}
