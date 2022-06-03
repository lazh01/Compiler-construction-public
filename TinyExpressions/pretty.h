#include "tree.h"

void prettyEXP(EXP *e);
void prettyTERM(TERM *t);
void prettyVAR(VAR *v);
void prettyACTLIST(ACTLIST *act);
void prettyEXPLIST(EXPLIST *expl);
void prettySTATE(STATE *s);
void prettySTATE_LIST(STATE_LIST *sl);
void prettyDECLARATION(DECLARATION *d);
void prettyDECL_LIST(DECL_LIST *dl);
void prettyFunction(FUNCTION *f);
void prettyHEAD(HEAD *h);
void prettyTAIL(TAIL *t);
void prettyTYPE(TYPE *t);
void prettyPAR_DECL_LIST(PAR_DECL_LIST *p);
void prettyVAR_DECL_LIST(VAR_DECL_LIST *vdl);
void prettyVAR_TYPE(VAR_TYPE *v);
void prettyBODY(BODY *b);