#include "tree.h"
#include <stdbool.h>


void weedEXP(EXP *e);
void weedTERM(TERM *t);
void weedVAR(VAR *v);
void weedACTLIST(ACTLIST *act);
void weedEXPLIST(EXPLIST *expl);
void weedSTATE(STATE *s);
void weedSTATE_LIST(STATE_LIST *sl);
void weedDECLARATION(DECLARATION *d);
void weedDECL_LIST(DECL_LIST *dl);
void weedFunction(FUNCTION *f);
void weedHEAD(HEAD *h);
void weedTAIL(TAIL *t);
void weedTYPE(TYPE *t);
void weedPAR_DECL_LIST(PAR_DECL_LIST *p);
void weedVAR_DECL_LIST(VAR_DECL_LIST *vdl);
void weedVAR_TYPE(VAR_TYPE *v);
void weedBODY(BODY *b);

// Next three are for looking for return statements.
bool statementListChecker(STATE_LIST *sl);
bool ifChecker(STATE *s);
bool thenElseChecker(STATE *s);