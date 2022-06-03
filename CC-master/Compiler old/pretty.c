#include <stdio.h>
#include "pretty.h"
int indendation= 0;
int spaces = 2;
#ifndef debug
#define debug
int db = 1;
#endif

void prettyEXP(EXP *e)
{ switch (e->kind) {
     case binopK:
          prettyEXP(e->val.binopE.left);
          printf(" %s ", e->val.binopE.op);
          prettyEXP(e->val.binopE.right);
          break;
     case termK:
          prettyTERM(e->val.termE.left);
          break;
  }
}

void prettyTERM(TERM *t){
  switch(t->kind){
    case varK:
          prettyVAR(t->val.varT.left);
          break;
    case idfuncK:
          printf("%*s", spaces*indendation,"");
          printf("%s (", t->val.idfuncT.id);
          prettyACTLIST(t->val.idfuncT.left);
          printf(")");
          break;
    case expK:
          printf("(");
          prettyEXP(t->val.expT.left);
          printf(")");
          break;
    case notTermK:
          printf("!");
          prettyTERM(t->val.nTermT.left);
          break;
    case lenExpK:
          printf("|");
          prettyEXP(t->val.lenExpT.left);
          printf("|");
          break;
    case numK:
          printf("%d", t->val.intconstT);
          break;
    case boolK:
          if(t->val.boolconstT == 0){
               printf("false");
          } else if (t->val.boolconstT == 1)
          {
               printf("true");
          }
          break;
    case nullK:
          printf("null");
          break;
  }
}

void prettyVAR(VAR *v){
     switch(v->kind){
          case idVK:
               printf("%s", v->val.idV);
               break;
          case listVK:
               prettyVAR(v->val.listV.left);
               printf("[");
               prettyEXP(v->val.listV.right);
               printf("]");
               break;
          case varidVK:
               prettyVAR(v->val.varidV.left);
               printf(".%s", v->val.varidV.id);
               break;
     }
}

void prettyACTLIST(ACTLIST *act){
     switch(act->kind){
          case explistK:
               prettyEXPLIST(act->val.explistA.left);
               break;
          case nilK:
               break;
     }
}

void prettyEXPLIST(EXPLIST *expl){
     switch(expl->kind){
          case expLK:
               prettyEXP(expl->val.expL.left);
               break;
          case explistLK:
               prettyEXP(expl->val.explistL.left);
               printf(", ");
               prettyEXPLIST(expl->val.explistL.right);
               break;
     }
}

void prettyFunction(FUNCTION *f){
     prettyHEAD(f->val.function.left);
     prettyBODY(f->val.function.middle);
     prettyTAIL(f->val.function.right);
}

void prettyHEAD(HEAD *h){
     printf("func %s(", h->val.head.id);
     indendation++;
     prettyPAR_DECL_LIST(h->val.head.left);
     printf(") : ");
     prettyTYPE(h->val.head.right);
     indendation--;
     printf("\n");
}

void prettyTAIL(TAIL *t){
     printf("end %s\n", t->val.tail.id);
}

void prettyTYPE(TYPE *t){
     switch(t->kind){
          case idTyK:
               printf("%*s", spaces*indendation,"");
               printf("%s", t->val.id);
               break;
          case intTyK:
               printf("int");
               break;
          case boolTyK:
               printf("bool");
               break;
          case arrayTyK:
               printf("array of ");
               prettyTYPE(t->val.array.left);
               break;
          case recTyK:
               printf("record of {\n");
               prettyVAR_DECL_LIST(t->val.record.left);
               printf(" }\n");
               break;
     }
}

void prettyPAR_DECL_LIST(PAR_DECL_LIST *p){
     switch(p->kind){
          case nilPK:
               break;
          case vdlPK:
               prettyVAR_DECL_LIST(p->val.vdecl_list.left);
               break;
     }
}

void prettyVAR_DECL_LIST(VAR_DECL_LIST *vdl){
     switch(vdl->kind){
          case listVDLK:
               prettyVAR_TYPE(vdl->val.listV.left);
               printf(", ");
               prettyVAR_DECL_LIST(vdl->val.listV.right);
               break;
          case vtK:
               prettyVAR_TYPE(vdl->val.vtype.left);
               break;
     }
}

void prettyVAR_TYPE(VAR_TYPE *v){
     printf("%s : ", v->val.typeV.id);
     prettyTYPE(v->val.typeV.left);
}

void prettyBODY(BODY *b){
     prettyDECL_LIST(b->val.body.left);
     prettySTATE_LIST(b->val.body.right);
}

void prettyDECLARATION(DECLARATION *d){
     switch(d->kind){
          case typeIdK:
               printf("%*s", (spaces*indendation),"");
               printf("type %s = ", d->val.typeIdD.id);
               prettyTYPE(d->val.typeIdD.left);
               // printf(";\n");
               break;
          case declFuncK:
               prettyFunction(d->val.declFuncD);
               break;
          case declVarK:
               printf("%*s", spaces*indendation,"");
               printf("var ");
               prettyVAR_DECL_LIST(d->val.declVarD);
               printf(";\n");
               break;
     }
}

void prettyDECL_LIST(DECL_LIST *dl){
     switch(dl->kind){
          case declListK:
               prettyDECLARATION(dl->val.declListDL.left);
               prettyDECL_LIST(dl->val.declListDL.right);
               break;
          case nilDK:
               break;
     }
}

void prettySTATE_LIST(STATE_LIST *sl){
  switch(sl->kind){
    case statementK:
          prettySTATE(sl->val.statementSL);
          break;
    case statementListK:
          prettySTATE(sl->val.statementListSL.left);
          prettySTATE_LIST(sl->val.statementListSL.right);
          break;
  }

}

void prettySTATE(STATE *s){
     switch(s->kind){
          case returnK:
               printf("%*s", spaces*indendation,"");
               printf("return ");
               prettyEXP(s->val.returnS);
               printf(";\n");
               break;
          case writeK:
               printf("%*s", spaces*indendation,"");
               printf("write ");
               prettyEXP(s->val.writeS);
               printf(";\n");
               break;
          case allocateK:
               printf("%*s", spaces*indendation,"");
               printf("allocate ");
               prettyVAR(s->val.allocateS);
               printf(";\n");
               break;
          case allocOfLengthK:
               printf("%*s", spaces*indendation,"");
               printf("allocate ");
               prettyVAR(s->val.allocOfLengthS.left);
               printf(" of length ");
               prettyEXP(s->val.allocOfLengthS.right);
               printf(";\n");
               break;
          case assignK:
               printf("%*s", spaces*indendation,"");
               prettyVAR(s->val.assignS.left);
               printf(" = ");
               prettyEXP(s->val.assignS.right);
               printf(";\n");
               break;
          case ifK:
               printf("%*s", spaces*indendation,"");
               printf("if ");
               prettyEXP(s->val.ifS.left);
               indendation++;
               printf("\n");
               printf("%*s", spaces*indendation,"");
               printf("then\n");
               prettySTATE(s->val.ifS.right);
               indendation--;
               break;
          case ifElseK:
               printf("%*s", spaces*indendation,"");
               printf("if ");
               prettyEXP(s->val.ifElseS.left);
               indendation++;
               printf("\n");
               printf("%*s", spaces*indendation,"");
               printf("then\n");
               prettySTATE(s->val.ifElseS.middle);
               printf("\n");
               printf("%*s", spaces*indendation,"");
               printf("else\n");
               prettySTATE(s->val.ifElseS.right);
               indendation--;
               break;
          case whileK:
               printf("%*s", spaces*indendation,"");
               printf("while ");
               prettyEXP(s->val.whileS.left);
               indendation++;
               printf("\n");
               printf("%*s", spaces*indendation,"");
               printf("do\n");
               prettySTATE(s->val.whileS.right);
               indendation--;
               break;
          case stateListK:
               indendation++;
               printf("%*s", spaces*indendation,"");
               printf("{\n");
               prettySTATE_LIST(s->val.stateListS.left);
               printf("%*s", spaces*indendation,"");
               printf("}\n");
               indendation--;
               break;
     }
}
