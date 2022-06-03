#ifndef __typecheck_h
#define __typecheck_h
#include "tree.h"
#include "symbol.h"
#include "memory.h"
#include "types.h"
#include <string.h>

COLLECTION *collect;

COLLECTION *initCOLLECTION();
COLLECTION *scopeCOLLECTION(COLLECTION *c, Ty_ty *returntype);

int checkTREE(BODY *b);
void checkEXP(EXP *e, COLLECTION *c);
void checkTERM(TERM *t, COLLECTION *c);
void checkVAR(VAR *v, COLLECTION *c);
Ty_tyList *checkACTLIST(ACTLIST *act, COLLECTION *c);
Ty_tyList *checkEXPLIST(EXPLIST *expl, COLLECTION *c);
void checkSTATE(STATE *s, COLLECTION *c);
void checkSTATE_LIST(STATE_LIST *sl, COLLECTION *c);
void checkDECLARATION(DECLARATION *d, COLLECTION *c);
void checkDECL_LIST(DECL_LIST *dl, COLLECTION *c);
void checkFunction(FUNCTION *f, COLLECTION *c);
Ty_fieldList *checkHEAD(HEAD *h, COLLECTION *c);
void checkTAIL(TAIL *t, COLLECTION *c);
Ty_ty *checkTYPE(TYPE *t, COLLECTION *c);
Ty_fieldList *checkPAR_DECL_LIST(PAR_DECL_LIST *p, COLLECTION *c);
Ty_fieldList *checkVAR_DECL_LIST(VAR_DECL_LIST *vdl, COLLECTION *c);
Ty_field *checkVAR_TYPE(VAR_TYPE *v, COLLECTION *c);
void checkBODY(BODY *b, COLLECTION *c);
Ty_ty *getVarType(VAR *v, COLLECTION *c);
Ty_ty *getTermType(TERM *t, COLLECTION *c);
int EXPtype(EXP *e, COLLECTION *c);
void appendNestList(FUNCTION *head, COLLECTION *c);

#endif