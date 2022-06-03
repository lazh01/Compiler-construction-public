#ifndef __codegen_h
#define __codegen_h
#include "tree.h"
#include "TEMP.h"
#include "frame.h"
#include "typecheck.h"
#include <string.h>
#include "memory.h"
#include <stdio.h>

FILE *f;



void expADD(EXP *e, temp *tem, frame *fr);
void expSUB(EXP *e, temp *tem, frame *fr);
void expMUL(EXP *e, temp *tem, frame *fr);
void expDIV(EXP *e, temp *tem, frame *fr);
void EXPswitch(EXP *e, temp *tem, frame *fr);
void codeEXP(EXP *e, temp *tem, frame *fr);
void codeTERM(TERM *t, temp *tem, frame *fr);
void codeVAR(VAR *v, frame *fr, temp *tem);
int codeACTLIST(ACTLIST *act, frame *fr);
int codeEXPLIST(EXPLIST *expl, frame *fr);
void codeSTATE(STATE *s, frame *fr);
void codeSTATE_LIST(STATE_LIST *sl, frame *fr);
void codeDECLARATION(DECLARATION *d, frame *fr);
void codeDECL_LIST(DECL_LIST *dl, frame *fr);
void codeFunction(FUNCTION *fun, frame *fr);
void codeHEAD(HEAD *h, frame *fr);
void codeTAIL(TAIL *t, frame *fr);
void codeTYPE(TYPE *t, frame *fr);
void codePAR_DECL_LIST(PAR_DECL_LIST *p, frame *fr);
linkedlist *codeVAR_DECL_LIST(VAR_DECL_LIST *vdl, frame *fr);
char *codeVAR_TYPE(VAR_TYPE *v, frame *r);
void codeBODY(BODY *b, frame *f);
void allocLength();
void getMem();
void getVar(faccess *fa, temp *tem);
void generateLocalVariable(char *c, frame *fr);
void allocOfLength(VAR *var, temp *tvar, temp *argument, frame *fr);
void allocate(temp *tvar, frame *fr, VAR *v);
void writer();

#endif