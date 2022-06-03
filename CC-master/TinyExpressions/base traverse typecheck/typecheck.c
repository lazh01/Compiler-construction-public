#include <stdio.h>
#include "typecheck.h"


COLLECTION *initCOLLECTION(){
     COLLECTION *c;
     c = NEW(COLLECTION);
     c->function=initSymbolTable();
     c->type=initSymbolTable();
     c->var=initSymbolTable();
     c->next=NULL;
     return c;
}

COLLECTION *scopeCOLLECTION(COLLECTION *c){
     COLLECTION *col;
     col=NEW(COLLECTION);
     col->function=scopeSymbolTable(c->function);
     col->type=scopeSymbolTable(c->type);
     col->var=scopeSymbolTable(c->var);
     col->next=c;
     return col;
}

/*
void checkEXP(EXP *e)
{ switch (e->kind) {
    case idK:
         fprintf(stderr,"%s",e->val.idE);
         break;
    case intconstK:
         fprintf(stderr,"%i",e->val.intconstE);
         break;
    case timesK:
         fprintf(stderr,"(");
         checkEXP(e->val.timesE.left);
         fprintf(stderr,"*");
         checkEXP(e->val.timesE.right);
         fprintf(stderr,")");
         break;
    case divK:
         fprintf(stderr,"(");
         checkEXP(e->val.divE.left);
         fprintf(stderr,"/");
         checkEXP(e->val.divE.right);
         fprintf(stderr,")");
         break;
    case plusK:
         fprintf(stderr,"(");
         checkEXP(e->val.plusE.left);
         fprintf(stderr,"+");
         checkEXP(e->val.plusE.right);
         fprintf(stderr,")");
         break;
    case minusK:
         fprintf(stderr,"(");
         checkEXP(e->val.minusE.left);
         fprintf(stderr,"-");
         checkEXP(e->val.minusE.right);
         fprintf(stderr,")");
         break;
  }
}
*/
void checkEXP(EXP *e, COLLECTION *c)
{ switch (e->kind) {
    /*case idK:
         fprintf(stderr,"%s",e->val.idE);
         break;
    case intconstK:
         fprintf(stderr,"%i",e->val.intconstE);
         break;
         
    case timesK:
         fprintf(stderr,"(");
         checkEXP(e->val.timesE.left);
         fprintf(stderr,"*");
         checkEXP(e->val.timesE.right);
         fprintf(stderr,")");
         break;
    case divK:
         fprintf(stderr,"(");
         checkEXP(e->val.divE.left);
         fprintf(stderr,"/");
         checkEXP(e->val.divE.right);
         fprintf(stderr,")");
         break;
    case plusK:
         fprintf(stderr,"(");
         checkEXP(e->val.plusE.left);
         fprintf(stderr,"+");
         checkEXP(e->val.plusE.right);
         fprintf(stderr,")");
         break;
    case minusK:
         fprintf(stderr,"(");
         checkEXP(e->val.minusE.left);
         fprintf(stderr,"-");
         checkEXP(e->val.minusE.right);
         fprintf(stderr,")");
         break;*/
     
     case binopK:
          checkEXP(e->val.binopE.left, c);
          fprintf(stderr," %s ", e->val.binopE.op);
          checkEXP(e->val.binopE.right, c);
          break;
     case termK:
          checkTERM(e->val.termE.left, c);
          break;
  }
}

void checkTREE(BODY *b){
     collect = initCOLLECTION();
     checkBODY(b, collect);
}

void checkTERM(TERM *t, COLLECTION *c){
  switch(t->kind){
    case varK:
          checkVAR(t->val.varT.left, c);
          break;
    case idfuncK:
          fprintf(stderr,"%s (", t->val.idfuncT.id); 
          checkACTLIST(t->val.idfuncT.left, c);
          fprintf(stderr,")");
          break;
    case expK:
          fprintf(stderr,"(");
          checkEXP(t->val.expT.left, c);
          fprintf(stderr,")");
          break;
    case notTermK:
          fprintf(stderr,"!");
          checkTERM(t->val.nTermT.left, c);
          break;
    case lenExpK:
          fprintf(stderr,"|");
          checkEXP(t->val.lenExpT.left, c);
          fprintf(stderr,"|");
          break;
    case numK:
          fprintf(stderr,"%d", t->val.intconstT);
          break;
    case boolK:
          if(t->val.boolconstT == 0){
               fprintf(stderr,"false");
          } else if (t->val.boolconstT == 1)
          {
               fprintf(stderr,"true");
          }
          break;     
    case nullK:
          fprintf(stderr,"null");
          break;
  }
}

void checkVAR(VAR *v, COLLECTION *c){
     switch(v->kind){
          case idVK:
               fprintf(stderr,"%s", v->val.idV);
               break;
          case listVK:
               checkVAR(v->val.listV.left, c);
               fprintf(stderr,"[");
               checkEXP(v->val.listV.right, c);
               fprintf(stderr,"]");
               break;
          case varidVK:
               checkVAR(v->val.varidV.left, c);
               fprintf(stderr,".%s", v->val.varidV.id);
               break;
     }
}

void checkACTLIST(ACTLIST *act, COLLECTION *c){
     switch(act->kind){
          case explistK:
               checkEXPLIST(act->val.explistA.left, c);
               break;
          case nilK:
               break;
     }
}

void checkEXPLIST(EXPLIST *expl, COLLECTION *c){
     switch(expl->kind){
          case expLK:
               checkEXP(expl->val.expL.left, c);
               break;
          case explistLK:
               checkEXP(expl->val.explistL.left, c);
               fprintf(stderr,", ");
               checkEXPLIST(expl->val.explistL.right, c);
               break;
     }
}

void checkFunction(FUNCTION *f, COLLECTION *c){
     checkHEAD(f->val.function.left, c);
     checkBODY(f->val.function.middle, c);
     checkTAIL(f->val.function.right, c);
}

void checkHEAD(HEAD *h, COLLECTION *c){
     fprintf(stderr,"func %s(", h->val.head.id);
     checkPAR_DECL_LIST(h->val.head.left, c);
     fprintf(stderr,") : ");
     checkTYPE(h->val.head.right, c);
     fprintf(stderr,"\n");
}

void checkTAIL(TAIL *t, COLLECTION *c){
     fprintf(stderr,"end %s\n", t->val.tail.id);
}

void checkTYPE(TYPE *t, COLLECTION *c){
     switch(t->kind){
          case idTyK:
               fprintf(stderr,"%s", t->val.id);
               break;
          case intTyK:
               fprintf(stderr,"int");
               break;
          case boolTyK:
               fprintf(stderr,"bool");
               break;
          case arrayTyK:
               fprintf(stderr,"array of ");
               checkTYPE(t->val.array.left, c);
               break;
          case recTyK:
               fprintf(stderr,"record of {");
               checkVAR_DECL_LIST(t->val.record.left, c);
               fprintf(stderr," }");
               break;
     }
}

void checkPAR_DECL_LIST(PAR_DECL_LIST *p, COLLECTION *c){
     switch(p->kind){
          case nilPK:
               break;
          case vdlPK:
               checkVAR_DECL_LIST(p->val.vdecl_list.left, c);
               break;
     }
}

void checkVAR_DECL_LIST(VAR_DECL_LIST *vdl, COLLECTION *c){
     switch(vdl->kind){
          case listVDLK:
               checkVAR_TYPE(vdl->val.listV.left, c);
               fprintf(stderr,", ");
               checkVAR_DECL_LIST(vdl->val.listV.right, c);
               break;
          case vtK:
               checkVAR_TYPE(vdl->val.vtype.left, c);
               break;
     }
}

void checkVAR_TYPE(VAR_TYPE *v, COLLECTION *c){
     fprintf(stderr,"%s : ", v->val.typeV.id);
     checkTYPE(v->val.typeV.left, c);
}

void checkBODY(BODY *b, COLLECTION *c){
     checkDECL_LIST(b->val.body.left, c);
     checkSTATE_LIST(b->val.body.right, c);
}

void checkDECLARATION(DECLARATION *d, COLLECTION *c){
     switch(d->kind){
          case typeIdK:
               fprintf(stderr,"type %s = ", d->val.typeIdD.id);
               checkTYPE(d->val.typeIdD.left, c);
               fprintf(stderr,";\n");
               break;
          case declFuncK:
               checkFunction(d->val.declFuncD, c);
               break;
          case declVarK:
               fprintf(stderr,"var ");
               checkVAR_DECL_LIST(d->val.declVarD, c);
               fprintf(stderr,";\n");
               break;
     }
}

void checkDECL_LIST(DECL_LIST *dl, COLLECTION *c){
     switch(dl->kind){
          case declListK:
               checkDECLARATION(dl->val.declListDL.left, c);
               checkDECL_LIST(dl->val.declListDL.right, c);
               break;
          case nilDK:
               break;
     }
}

void checkSTATE_LIST(STATE_LIST *sl, COLLECTION *c){
  switch(sl->kind){
    case statementK:
          checkSTATE(sl->val.statementSL, c);
          break;
    case statementListK:
          checkSTATE(sl->val.statementListSL.left, c);
          checkSTATE_LIST(sl->val.statementListSL.right, c);
          break;
  }

}

void checkSTATE(STATE *s, COLLECTION *c){
     switch(s->kind){
          case returnK:
               fprintf(stderr,"return ");
               checkEXP(s->val.returnS, c);
               fprintf(stderr,";\n");
               break;
          case writeK:
               fprintf(stderr,"write ");
               checkEXP(s->val.writeS, c);
               fprintf(stderr,";\n");
               break;
          case allocateK:
               fprintf(stderr,"allocate ");
               checkVAR(s->val.allocateS, c);
               fprintf(stderr,";\n");
               break;
          case allocOfLengthK:
               fprintf(stderr,"allocate ");
               checkVAR(s->val.allocOfLengthS.left, c);
               fprintf(stderr,"of length ");
               checkEXP(s->val.allocOfLengthS.right, c);
               fprintf(stderr,";\n");
               break;
          case assignK:
               checkVAR(s->val.assignS.left, c);
               fprintf(stderr," = ");
               checkEXP(s->val.assignS.right, c);
               fprintf(stderr,";\n");
               break;
          case ifK:
               fprintf(stderr,"if ");
               checkEXP(s->val.ifS.left, c);
               fprintf(stderr,"\nthen\n");
               checkSTATE(s->val.ifS.right, c);
               break;
          case ifElseK:
               fprintf(stderr,"if ");
               checkEXP(s->val.ifElseS.left, c);
               fprintf(stderr,"\nthen\n");
               checkSTATE(s->val.ifElseS.middle, c);
               fprintf(stderr,"\nelse\n");
               checkSTATE(s->val.ifElseS.right, c);
               break;
          case whileK:
               fprintf(stderr,"while ");
               checkEXP(s->val.whileS.left, c);
               fprintf(stderr,"\ndo\n");
               checkSTATE(s->val.whileS.right, c);
               break;
          case stateListK:
               fprintf(stderr,"{");
               checkSTATE_LIST(s->val.stateListS.left, c);
               fprintf(stderr,"}");
               break;
     }
}