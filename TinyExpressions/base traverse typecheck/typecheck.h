#include "tree.h"
#include "symbol.h"
#include "memory.h"
#include "types.h"

typedef struct COLLECTION_ COLLECTION;

typedef struct COLLECTION_{
    SymbolTable *var;
    SymbolTable *type; 
    SymbolTable *function;
    COLLECTION *next;
} COLLECTION;

COLLECTION *collect;

COLLECTION *initCOLLECTION();
COLLECTION *scopeCOLLECTION(COLLECTION *c);

void checkTREE(BODY *b);
void checkEXP(EXP *e, COLLECTION *c);
void checkTERM(TERM *t, COLLECTION *c);
void checkVAR(VAR *v, COLLECTION *c);
void checkACTLIST(ACTLIST *act, COLLECTION *c);
void checkEXPLIST(EXPLIST *expl, COLLECTION *c);
void checkSTATE(STATE *s, COLLECTION *c);
void checkSTATE_LIST(STATE_LIST *sl, COLLECTION *c);
void checkDECLARATION(DECLARATION *d, COLLECTION *c);
void checkDECL_LIST(DECL_LIST *dl, COLLECTION *c);
void checkFunction(FUNCTION *f, COLLECTION *c);
void checkHEAD(HEAD *h, COLLECTION *c);
void checkTAIL(TAIL *t, COLLECTION *c);
void checkTYPE(TYPE *t, COLLECTION *c);
void checkPAR_DECL_LIST(PAR_DECL_LIST *p, COLLECTION *c);
void checkVAR_DECL_LIST(VAR_DECL_LIST *vdl, COLLECTION *c);
void checkVAR_TYPE(VAR_TYPE *v, COLLECTION *c);
void checkBODY(BODY *b, COLLECTION *c);