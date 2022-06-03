#include "tree.h"
#include "pretty.h"
#include "weed.h"
#include "typecheck.h"
#include "codegen.h"
#include <stdio.h>
#include "regallocation.h"
#include "graphcolor.h"
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

void errComp(){
    //fprintf(stdout, ".globl _start\n\n");
    fprintf(stdout, ".globl main\n\n");

    //main program
    //fprintf(stdout, "_start:\n");
    fprintf(stdout, "main:\n");
    fprintf(stdout, "   push %%rbp\n");
    fprintf(stdout, "   movq %%rsp, %%rbp\n");
    fprintf(stdout, "   push $10\n");
    fprintf(stdout, "   push $114\n");
    fprintf(stdout, "   push $111\n");
    fprintf(stdout, "   push $114\n");
    fprintf(stdout, "   push $114\n");
    fprintf(stdout, "   push $101\n");
    fprintf(stdout, "   movq $6, %%r12\n");

    fprintf(stdout, "printloop:\n");
    fprintf(stdout, "   movq $1, %%rax\n");
    fprintf(stdout, "   movq $1, %%rdi\n");
    fprintf(stdout, "   movq %%rsp, %%rsi\n");
    fprintf(stdout, "   movq $1, %%rdx\n");
    fprintf(stdout, "   syscall\n");
    fprintf(stdout, "   addq $8, %%rsp\n");
    fprintf(stdout, "   addq $-1, %%r12\n");
    fprintf(stdout, "   cmp $0, %%r12\n");
    fprintf(stdout, "   jne printloop\n");


    fprintf(stdout, "   movq %%rbp, %%rsp\n");
    fprintf(stdout, "   pop %%rbp\n");
    fprintf(stdout, "   movq $60, %%rax\n");
    fprintf(stdout, "   movq $0, %%rdi\n");
    fprintf(stdout, "   syscall\n");
}

int main()
{ lineno = 1;
  fprintf(stderr, "Parsing\n");
  if(yyparse()){
      errComp();
      return 0;
  }
  fprintf(stderr, "Weeding\n");
  weedBODY(theexpression);
  fprintf(stderr, "Typechecking\n");
  if(checkTREE(theexpression)){
      errComp();
      return 0;
  }
  prettyBODY(theexpression);
  fprintf(stderr, "Generating code\n");
  codeGEN(theexpression);
  //regAllocation();
  registerAllocation();
  return 0;
}
