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
          fprintf(stderr, " %s ", e->val.binopE.op);
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
          fprintf(stderr, "%*s", spaces*indendation,"");
          fprintf(stderr, "%s (", t->val.idfuncT.id);
          prettyACTLIST(t->val.idfuncT.left);
          fprintf(stderr, ")");
          break;
    case expK:
          fprintf(stderr, "(");
          prettyEXP(t->val.expT.left);
          fprintf(stderr, ")");
          break;
    case notTermK:
          fprintf(stderr, "!");
          prettyTERM(t->val.nTermT.left);
          break;
    case lenExpK:
          fprintf(stderr, "|");
          prettyEXP(t->val.lenExpT.left);
          fprintf(stderr, "|");
          break;
    case numK:
          fprintf(stderr, "%d", t->val.intconstT);
          break;
    case boolK:
          if(t->val.boolconstT == 0){
               fprintf(stderr, "false");
          } else if (t->val.boolconstT == 1)
          {
               fprintf(stderr, "true");
          }
          break;
    case nullK:
          fprintf(stderr, "null");
          break;
  }
}

void prettyVAR(VAR *v){
     switch(v->kind){
          case idVK:
               fprintf(stderr, "%s", v->val.idV);
               break;
          case listVK:
               prettyVAR(v->val.listV.left);
               fprintf(stderr, "[");
               prettyEXP(v->val.listV.right);
               fprintf(stderr, "]");
               break;
          case varidVK:
               prettyVAR(v->val.varidV.left);
               fprintf(stderr, ".%s", v->val.varidV.id);
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
               fprintf(stderr, ", ");
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
     fprintf(stderr, "func %s(", h->val.head.id);
     indendation++;
     prettyPAR_DECL_LIST(h->val.head.left);
     fprintf(stderr, ") : ");
     prettyTYPE(h->val.head.right);
     indendation--;
     fprintf(stderr, "\n");
}

void prettyTAIL(TAIL *t){
     fprintf(stderr, "end %s\n", t->val.tail.id);
}

void prettyTYPE(TYPE *t){
     switch(t->kind){
          case idTyK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "%s", t->val.id);
               break;
          case intTyK:
               fprintf(stderr, "int");
               break;
          case boolTyK:
               fprintf(stderr, "bool");
               break;
          case arrayTyK:
               fprintf(stderr, "array of ");
               prettyTYPE(t->val.array.left);
               break;
          case recTyK:
               fprintf(stderr, "record of {\n");
               prettyVAR_DECL_LIST(t->val.record.left);
               fprintf(stderr, " }\n");
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
               fprintf(stderr, ", ");
               prettyVAR_DECL_LIST(vdl->val.listV.right);
               break;
          case vtK:
               prettyVAR_TYPE(vdl->val.vtype.left);
               break;
     }
}

void prettyVAR_TYPE(VAR_TYPE *v){
     fprintf(stderr, "%s : ", v->val.typeV.id);
     prettyTYPE(v->val.typeV.left);
}

void prettyBODY(BODY *b){
     prettyDECL_LIST(b->val.body.left);
     prettySTATE_LIST(b->val.body.right);
}

void prettyDECLARATION(DECLARATION *d){
     switch(d->kind){
          case typeIdK:
               fprintf(stderr, "%*s", (spaces*indendation),"");
               fprintf(stderr, "type %s = ", d->val.typeIdD.id);
               prettyTYPE(d->val.typeIdD.left);
               // fprintf(";\n");
               break;
          case declFuncK:
               prettyFunction(d->val.declFuncD);
               break;
          case declVarK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "var ");
               prettyVAR_DECL_LIST(d->val.declVarD);
               fprintf(stderr, ";\n");
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
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "return ");
               prettyEXP(s->val.returnS);
               fprintf(stderr, ";\n");
               break;
          case writeK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "write ");
               prettyEXP(s->val.writeS);
               fprintf(stderr, ";\n");
               break;
          case allocateK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "allocate ");
               prettyVAR(s->val.allocateS);
               fprintf(stderr, ";\n");
               break;
          case allocOfLengthK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "allocate ");
               prettyVAR(s->val.allocOfLengthS.left);
               fprintf(stderr, " of length ");
               prettyEXP(s->val.allocOfLengthS.right);
               fprintf(stderr, ";\n");
               break;
          case assignK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               prettyVAR(s->val.assignS.left);
               fprintf(stderr, " = ");
               prettyEXP(s->val.assignS.right);
               fprintf(stderr, ";\n");
               break;
          case ifK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "if ");
               prettyEXP(s->val.ifS.left);
               indendation++;
               fprintf(stderr, "\n");
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "then\n");
               prettySTATE(s->val.ifS.right);
               indendation--;
               break;
          case ifElseK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "if ");
               prettyEXP(s->val.ifElseS.left);
               indendation++;
               fprintf(stderr, "\n");
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "then\n");
               prettySTATE(s->val.ifElseS.middle);
               fprintf(stderr, "\n");
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "else\n");
               prettySTATE(s->val.ifElseS.right);
               indendation--;
               break;
          case whileK:
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "while ");
               prettyEXP(s->val.whileS.left);
               indendation++;
               fprintf(stderr, "\n");
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "do\n");
               prettySTATE(s->val.whileS.right);
               indendation--;
               break;
          case stateListK:
               indendation++;
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "{\n");
               prettySTATE_LIST(s->val.stateListS.left);
               fprintf(stderr, "%*s", spaces*indendation,"");
               fprintf(stderr, "}\n");
               indendation--;
               break;
     }
}
