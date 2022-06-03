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

void checkTREE(BODY *b){
     printf("checktree \n");
     collect = initCOLLECTION();
     checkBODY(b, collect);
}

void checkEXP(EXP *e, COLLECTION *c)
{ switch (e->kind) {
     case binopK:
          printf("binop exp \n");
          checkEXP(e->val.binopE.left, c);
          checkEXP(e->val.binopE.right, c);
          /*if (EXPtype(e, c)){
               printf("error\n");
          }*/
          break;
     case termK:
          printf("term exp\n");
          checkTERM(e->val.termE.left, c);
          printf("term exp after check term \n");
          //e->types.type = getTermType(e->val.termE.left, c);
          break;
  }
}


//Determines the type of an expression and it's children, then verifies that the children are of correct type, returning 1 if they are not.
/*
int EXPtype(EXP *e, COLLECTION *c){
     if (strcmp(e->val.binopE.op, "==")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, ">=")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "<=")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "!=")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "<")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, ">")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "-")){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "+")){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "*")){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "/")){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
     }
     if (strcmp(e->val.binopE.op, "||")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Bool(), Ty_TyList(Ty_Bool(),NULL));
     }
     if (strcmp(e->val.binopE.op, "&&")){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Bool(), Ty_TyList(Ty_Bool(),NULL));
     }
     
     if ((e->val.binopE.left->types.type->kind != e->types.args->head->kind) || (e->val.binopE.right->types.type->kind != e->types.args->tail->head->kind)){
          return 1;
     }

     return 0;
}*/


Ty_ty *getTermType(TERM *t, COLLECTION *c){
     switch(t->kind){
          case varK:
               return getVarType(t->val.varT.left, c);
          case idfuncK:
               return getSymbol(c->function, t->val.idfuncT.id);
          case expK:
               return t->val.expT.left->types.type;
          case notTermK:
               return Ty_Bool(); //getTermType(t->val.nTermT.left, c);
          case lenExpK:
               return Ty_Int();
          case numK:
               return Ty_Int();
          case boolK:
               return Ty_Bool();
          case nullK:
               return Ty_Nil();
     }
}

// Returns the type of a variable. Returns NULL if no type found.
Ty_ty *getVarType(VAR *v, COLLECTION *c){
     Ty_ty *ty;
     switch(v->kind){
          case idVK:
               return getSymbol(c->var, v->val.idV);
               break;
          case listVK:
               return getVarType(v->val.listV.left, c);
               break;
          case varidVK:
               ty = getVarType(v->val.varidV.left, c);
               Ty_fieldList *fl;
               fl = ty->u.record;
               while(fl != NULL){
                    if (strcmp(fl->head->name, v->val.varidV.id)){
                         return fl->head->ty;
                    }
                    fl = fl->tail;
               }
     }
     return NULL;
}

void checkTERM(TERM *t, COLLECTION *c){
  printf("check term \n");
  switch(t->kind){
    case varK:
          checkVAR(t->val.varT.left, c);
          break;
    case idfuncK:
          checkACTLIST(t->val.idfuncT.left, c);
          break;
    case expK:
          checkEXP(t->val.expT.left, c);
          break;
    case notTermK:
          checkTERM(t->val.nTermT.left, c);
          break;
    case lenExpK:
          checkEXP(t->val.lenExpT.left, c);
          break;
    case numK:
          break;
    case boolK:
          break;     
    case nullK:
          break;
  }
}

void checkVAR(VAR *v, COLLECTION *c){
     printf("check var\n");
     switch(v->kind){
          case idVK:
               printf("%s \n", v->val.idV);
               break;
          case listVK:
               checkVAR(v->val.listV.left, c);
               checkEXP(v->val.listV.right, c);
               break;
          case varidVK:
               checkVAR(v->val.varidV.left, c);
               printf(".%s \n", v->val.varidV.id);
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
               printf(", ");
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
     checkPAR_DECL_LIST(h->val.head.left, c);
     checkTYPE(h->val.head.right, c);
}

void checkTAIL(TAIL *t, COLLECTION *c){
     printf("check tail \n");
}

Ty_ty *checkTYPE(TYPE *t, COLLECTION *c){
     printf("chech type \n");
     Ty_ty *ty;
     switch(t->kind){
          case idTyK:
               printf("%s \n", t->val.id);
               ty = Ty_Name(t->val.id, NULL);
               return ty;
               break;
          case intTyK:
               ty=Ty_Int();
               return ty;
          case boolTyK:
               ty = Ty_Bool();
               return ty;
               break;
          case arrayTyK:
               ty = Ty_Array(checkTYPE(t->val.array.left, c));
               return ty;
               break;
          case recTyK:
               ty = Ty_Record(checkVAR_DECL_LIST(t->val.record.left, c));
               return ty;
               break;
     }
     return ty;
}

void checkPAR_DECL_LIST(PAR_DECL_LIST *p, COLLECTION *c){
     printf("check pardecllist \n");
     switch(p->kind){
          Ty_fieldList *tyfl;
          case nilPK:
               break;
          case vdlPK:
               
               tyfl = checkVAR_DECL_LIST(p->val.vdecl_list.left, c);
               while(tyfl->tail != NULL){
                    putSymbol(c->var, tyfl->head->name, tyfl->head->ty);
                    tyfl=tyfl->tail;
               }
               putSymbol(c->var, tyfl->head->name, tyfl->head->ty);
               break;
     }
}

Ty_fieldList *checkVAR_DECL_LIST(VAR_DECL_LIST *vdl, COLLECTION *c){
     printf("check vardecllist \n");
     switch(vdl->kind){
          case listVDLK:
               return Ty_FieldList(checkVAR_TYPE(vdl->val.listV.left, c), checkVAR_DECL_LIST(vdl->val.listV.right, c));
               break;
          case vtK:
               return Ty_FieldList(checkVAR_TYPE(vdl->val.vtype.left, c), NULL);
               break;
     }
}

Ty_field *checkVAR_TYPE(VAR_TYPE *v, COLLECTION *c){
     printf("check var type \n");
     return Ty_Field(v->val.typeV.id, checkTYPE(v->val.typeV.left, c));
}

void checkBODY(BODY *b, COLLECTION *c){
     printf("check body \n");
     checkDECL_LIST(b->val.body.left, c);
     checkSTATE_LIST(b->val.body.right, c);
}


/*
Functions only map to return type, could augment by pointing to ty_ty list for parameters
*/
void checkDECLARATION(DECLARATION *d, COLLECTION *c){
     Ty_fieldList *tyf;
     printf("check declaration \n");
     switch(d->kind){
          case typeIdK:
               putSymbol(c->type, d->val.typeIdD.id, checkTYPE(d->val.typeIdD.left, c));
               break;
          case declFuncK:
               putSymbol(c->function, d->val.declFuncD->val.function.left->val.head.id, checkTYPE(d->val.declFuncD->val.function.left->val.head.right, c));
               c=scopeCOLLECTION(c);
               checkFunction(d->val.declFuncD, c);
               dumpSymbolTable(c->var);
               dumpSymbolTable(c->type);
               dumpSymbolTable(c->function);
               break;
          case declVarK:
               
               tyf = checkVAR_DECL_LIST(d->val.declVarD, c);
               while(tyf->tail != NULL){
                    putSymbol(c->var,tyf->head->name, tyf->head->ty);
                    tyf=tyf->tail;
               }
               putSymbol(c->var,tyf->head->name, tyf->head->ty);           
               break;
     }
}

void checkDECL_LIST(DECL_LIST *dl, COLLECTION *c){
     printf("check decllist \n");
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
  printf("check state list \n");
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
     printf("check state \n");
     switch(s->kind){
          case returnK:
               printf("returnK \n");
               checkEXP(s->val.returnS, c);
               break;
          case writeK:
               printf("writeK \n");
               checkEXP(s->val.writeS, c);
               break;
          case allocateK:
               printf("allocateK \n");
               checkVAR(s->val.allocateS, c);
               break;
          case allocOfLengthK:
               printf("allocOfLengthK \n");
               checkVAR(s->val.allocOfLengthS.left, c);
               checkEXP(s->val.allocOfLengthS.right, c);
               break;
          case assignK:
               printf("assignK \n");
               checkVAR(s->val.assignS.left, c);
               checkEXP(s->val.assignS.right, c);
               break;
          case ifK:
               printf("ifK \n");
               checkEXP(s->val.ifS.left, c);
               checkSTATE(s->val.ifS.right, c);
               break;
          case ifElseK:
               printf("ifElseK \n");
               checkEXP(s->val.ifElseS.left, c);
               checkSTATE(s->val.ifElseS.middle, c);
               checkSTATE(s->val.ifElseS.right, c);
               break;
          case whileK:
               printf("whileK \n");
               checkEXP(s->val.whileS.left, c);
               checkSTATE(s->val.whileS.right, c);
               break;
          case stateListK:
               printf("stateListK \n");
               checkSTATE_LIST(s->val.stateListS.left, c);
               break;
     }
}
