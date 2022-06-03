#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "weed.h"

// Color palette
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void weedEXP(EXP *e)
{ switch (e->kind) {
     case binopK:
          weedEXP(e->val.binopE.left);
          weedEXP(e->val.binopE.right);
          break;
     case termK:
          weedTERM(e->val.termE.left);
          break;
  }
}

void weedTERM(TERM *t){
  switch(t->kind){
    case varK:
          weedVAR(t->val.varT.left);
          break;
    case idfuncK:
          weedACTLIST(t->val.idfuncT.left);
          break;
    case expK:
          weedEXP(t->val.expT.left);
          break;
    case notTermK:
          weedTERM(t->val.nTermT.left);
          break;
    case lenExpK:
          weedEXP(t->val.lenExpT.left);
          break;
    case numK:
          break;
    case boolK:
          break;     
    case nullK:
          break;
  }
}

void weedVAR(VAR *v){
     switch(v->kind){
          case idVK:
               break;
          case listVK:
               weedVAR(v->val.listV.left);
               weedEXP(v->val.listV.right);
               break;
          case varidVK:
               weedVAR(v->val.varidV.left);
               break;
     }
}

void weedACTLIST(ACTLIST *act){
     switch(act->kind){
          case explistK:
               weedEXPLIST(act->val.explistA.left);
               break;
          case nilK:
               break;
     }
}

void weedEXPLIST(EXPLIST *expl){
     switch(expl->kind){
          case expLK:
               weedEXP(expl->val.expL.left);
               break;
          case explistLK:
               weedEXP(expl->val.explistL.left);
               weedEXPLIST(expl->val.explistL.right);
               break;
     }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// This function iterates through a statement list and looks for if/else- and return statements.//
//////////////////////////////////////////////////////////////////////////////////////////////////
bool statementListChecker(STATE_LIST *sl){
     STATE *slLeft = sl->val.statementListSL.left;
     STATE_LIST *slRight = sl->val.statementListSL.right;

     if(slLeft->kind == ifElseK){
          // Passes both then- and else statement to ifChecker().
          if(ifChecker(slLeft) == true){
               if(slRight != NULL){
               fprintf(stderr, CYN "Note: Return statement on line %d does not allow the end of code to be reached.\n" RESET, slLeft->lineno);
               }
               return true;
          }
     }
     if(slLeft->kind == returnK){
          if(slRight != NULL){
               fprintf(stderr, CYN "Note: Return statement on line %d does not allow the end of code to be reached.\n" RESET, slLeft->lineno);
          }
          return true;
     }
     if(slRight != NULL){
          statementListChecker(slRight);
     }else{
          return false;
     }
}

////////////////////////////////////////////////////////////////
// This function checks both then and else.                   //
// It returns true only if they both end with a return stament//
////////////////////////////////////////////////////////////////
bool ifChecker(STATE *s){
     STATE *middle = s->val.ifElseS.middle;
     STATE *right = s->val.ifElseS.right;

     if(thenElseChecker(middle) == true){
          if(thenElseChecker(right) == true){
               return true;
          }
     }
     return false;
}

////////////////////////////////////////////////////////////////////////////////////////
// This function checks the current state for a return statement or a statement list. //
////////////////////////////////////////////////////////////////////////////////////////
bool thenElseChecker(STATE *s){
     if(s->kind == returnK){
          return true;
     }
     else if(s->kind == ifElseK){
          if(ifChecker(s) == true){
               return true;
          }
     }
     else if(s->kind == stateListK){
          if(statementListChecker(s->val.stateListS.left) == true){
               return true;
          }
     }
     return false;
}


void weedFunction(FUNCTION *f){
    char *headID = (f->val.function.left)->val.head.id;
    char *tailID = (f->val.function.right)->val.tail.id;
    if(strcmp(headID,tailID) != 0){
        fprintf(stderr, RED "Error: Id of function:" RESET);
        fprintf(stderr, BLU " \"%s\" ", headID);
        fprintf(stderr, RED "does not match end id. line %d\n" RESET, (f->val.function.left)->lineno);
        fprintf(stderr, "exiting...\n");
        exit(0);
    }
     weedHEAD(f->val.function.left);
     if(statementListChecker((f->val.function.middle)->val.body.right) == false){
          fprintf(stderr, MAG "Warning: Function: " RESET);
          fprintf(stderr, BLU "\"%s\" ", headID);
          fprintf(stderr, MAG "might not end with a return statement. line %d\n" RESET, (f->val.function.left)->lineno);
     }
     weedBODY(f->val.function.middle);
     weedTAIL(f->val.function.right);
}

void weedHEAD(HEAD *h){
     weedPAR_DECL_LIST(h->val.head.left);
     weedTYPE(h->val.head.right);
}

void weedTAIL(TAIL *t){
}

void weedTYPE(TYPE *t){
     switch(t->kind){
          case idTyK:
               break;
          case intTyK:
               break;
          case boolTyK:
               break;
          case arrayTyK:
               weedTYPE(t->val.array.left);
               break;
          case recTyK:
               weedVAR_DECL_LIST(t->val.record.left);
               break;
     }
}

void weedPAR_DECL_LIST(PAR_DECL_LIST *p){
     switch(p->kind){
          case nilPK:
               break;
          case vdlPK:
               weedVAR_DECL_LIST(p->val.vdecl_list.left);
               break;
     }
}

void weedVAR_DECL_LIST(VAR_DECL_LIST *vdl){
     switch(vdl->kind){
          case listVDLK:
               weedVAR_TYPE(vdl->val.listV.left);
               weedVAR_DECL_LIST(vdl->val.listV.right);
               break;
          case vtK:
               weedVAR_TYPE(vdl->val.vtype.left);
               break;
     }
}

void weedVAR_TYPE(VAR_TYPE *v){
     weedTYPE(v->val.typeV.left);
}

void weedBODY(BODY *b){
     weedDECL_LIST(b->val.body.left);
     weedSTATE_LIST(b->val.body.right);
}

void weedDECLARATION(DECLARATION *d){
     switch(d->kind){
          case typeIdK:
               weedTYPE(d->val.typeIdD.left);
               break;
          case declFuncK:
               weedFunction(d->val.declFuncD);
               break;
          case declVarK:
               weedVAR_DECL_LIST(d->val.declVarD);
               break;
     }
}

void weedDECL_LIST(DECL_LIST *dl){
     switch(dl->kind){
          case declListK:
               weedDECLARATION(dl->val.declListDL.left);
               weedDECL_LIST(dl->val.declListDL.right);
               break;
          case nilDK:
               break;
     }
}

void weedSTATE_LIST(STATE_LIST *sl){
  switch(sl->kind){
    case statementK:
          weedSTATE(sl->val.statementSL);
          break;
    case statementListK:
          weedSTATE(sl->val.statementListSL.left);
          weedSTATE_LIST(sl->val.statementListSL.right);
          break;
  }

}

void weedSTATE(STATE *s){
     switch(s->kind){
          case returnK:
               weedEXP(s->val.returnS);
               break;
          case writeK:
               weedEXP(s->val.writeS);
               break;
          case allocateK:
               weedVAR(s->val.allocateS);
               break;
          case allocOfLengthK:
               weedVAR(s->val.allocOfLengthS.left);
               weedEXP(s->val.allocOfLengthS.right);
               break;
          case assignK:
               weedVAR(s->val.assignS.left);
               weedEXP(s->val.assignS.right);
               break;
          case ifK:
               weedEXP(s->val.ifS.left);
               weedSTATE(s->val.ifS.right);
               break;
          case ifElseK:
               weedEXP(s->val.ifElseS.left);
               weedSTATE(s->val.ifElseS.middle);
               weedSTATE(s->val.ifElseS.right);
               break;
          case whileK:
               weedEXP(s->val.whileS.left);
               weedSTATE(s->val.whileS.right);
               break;
          case stateListK:
               weedSTATE_LIST(s->val.stateListS.left);
               break;
     }
}