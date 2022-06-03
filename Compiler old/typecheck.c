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
     collect = initCOLLECTION();
     checkBODY(b, collect);
}

void checkEXP(EXP *e, COLLECTION *c)
{ switch (e->kind) {
     case binopK:
          checkEXP(e->val.binopE.left, c);
          checkEXP(e->val.binopE.right, c);
          if (EXPtype(e, c)){
               printf("error\n");
          }
          break;
     case termK:
          checkTERM(e->val.termE.left, c);
          e->types.type = getTermType(e->val.termE.left, c);
          break;
  }
}


//Determines the type of an expression and it's children, then verifies that the children are of correct type, returning 1 if they are not.

int EXPtype(EXP *e, COLLECTION *c){
     if (strcmp(e->val.binopE.op, "==")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checksametype;
     }
     if (strcmp(e->val.binopE.op, ">=")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "<=")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "!=")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checksametype;
     }
     if (strcmp(e->val.binopE.op, "<")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, ">")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "-")==0){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "+")==0){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "*")==0){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "/")==0){
          e->types.type=Ty_Int();
          e->types.args=Ty_TyList(Ty_Int(), Ty_TyList(Ty_Int(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "||")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Bool(), Ty_TyList(Ty_Bool(),NULL));
          goto checkexpect;
     }
     if (strcmp(e->val.binopE.op, "&&")==0){
          e->types.type=Ty_Bool();
          e->types.args=Ty_TyList(Ty_Bool(), Ty_TyList(Ty_Bool(),NULL));
          goto checkexpect;
     }
     
     checkexpect: 
     if ((e->val.binopE.left->types.type->kind != e->types.args->head->kind) || (e->val.binopE.right->types.type->kind != e->types.args->tail->head->kind)){
          printf("expression has types %d and %d, expected %d and %d\n", e->val.binopE.left->types.type->kind, e->val.binopE.right->types.type->kind, e->types.args->head->kind, e->types.args->tail->head->kind);
          return 1;
     }
     goto end;

     checksametype: 
     if(e->val.binopE.left->types.type->kind != e->val.binopE.right->types.type->kind){
          printf("Expected same type \n");
          return 1;
     }
     goto end;

     end:
     return 0;
}


Ty_ty *getTermType(TERM *t, COLLECTION *c){
     switch(t->kind){
          case varK:
               return getVarType(t->val.varT.left, c);
          case idfuncK:
               return ((Ty_ty_func*)getSymbol(c->function, t->val.idfuncT.id)->value)->type;
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
               ty = getSymbol(c->var, v->val.idV)->value;
               return ty;
               break;
          case listVK:
               return getVarType(v->val.listV.left, c);
               break;
          case varidVK:
               ty = getVarType(v->val.varidV.left, c);

               while (ty->kind == Ty_name){
                    ty = (Ty_ty*)getSymbol(ty->u.name.table, ty->u.name.name)->value;
               }
               
               Ty_fieldList *fl;
               fl = ty->u.record;
               while(fl != NULL){
                    if (strcmp(fl->head->name, v->val.varidV.id) == 0){
                         return fl->head->ty;
                    }
                    fl = fl->tail;
               }
     }
     return NULL;
}

void checkTERM(TERM *t, COLLECTION *c){
  switch(t->kind){
     Ty_tyList *list;
     Ty_tyList *formals;
    case varK:
          checkVAR(t->val.varT.left, c);
          break;
    case idfuncK:
          
          list = checkACTLIST(t->val.idfuncT.left, c);
          formals = ((Ty_ty_func*) getSymbol(c->function, t->val.idfuncT.id)->value)->formals;
          while((list != NULL) && (formals != NULL)){
               if (list->head->kind != formals->head->kind){
                    printf("wrong parameters for function in %d kind %d and %d\n", t->lineno, list->head->kind, formals->head->kind);
               }
               list=list->tail;
               formals=formals->tail;
          }
          if(list != NULL || formals !=NULL){
               printf("Wrong amount of variables in %d \n", t->lineno);
          }
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
     switch(v->kind){
          case idVK:
               break;
          case listVK:
               checkVAR(v->val.listV.left, c);
               checkEXP(v->val.listV.right, c);
               break;
          case varidVK:
               checkVAR(v->val.varidV.left, c);
               break;
     }
}

Ty_tyList *checkACTLIST(ACTLIST *act, COLLECTION *c){
     switch(act->kind){
          case explistK:
               return checkEXPLIST(act->val.explistA.left, c);
               break;
          case nilK:
               return NULL;
               break;
     }
}

Ty_tyList *checkEXPLIST(EXPLIST *expl, COLLECTION *c){
     switch(expl->kind){
          Ty_tyList *list;
          case expLK:
               checkEXP(expl->val.expL.left, c);
               list = Ty_TyList(expl->val.expL.left->types.type, NULL);
               break;
          case explistLK:
               checkEXP(expl->val.explistL.left, c);
               list=Ty_TyList(expl->val.explistL.left->types.type, checkEXPLIST(expl->val.explistL.right, c));
               break;
     }
}

void checkFunction(FUNCTION *f, COLLECTION *c){
     Ty_fieldList *variables;
     variables = checkHEAD(f->val.function.left, c);
     c=scopeCOLLECTION(c);

     while(variables != NULL){
          putSymbol(c->var, variables->head->name, variables->head->ty);
          variables=variables->tail;
     }
     checkBODY(f->val.function.middle, c);
     c=c->next;
     checkTAIL(f->val.function.right, c);
}

Ty_fieldList *checkHEAD(HEAD *h, COLLECTION *c){
     Ty_fieldList *flist;
     flist = checkPAR_DECL_LIST(h->val.head.left, c);
     putSymbol(c->function, h->val.head.id, Ty_Func(FListToList(flist), checkTYPE(h->val.head.right, c)));
     return flist;
}

void checkTAIL(TAIL *t, COLLECTION *c){
}

Ty_ty *checkTYPE(TYPE *t, COLLECTION *c){
     Ty_ty *ty;
     switch(t->kind){
          case idTyK:
               ty = Ty_Name(t->val.id, c->type);
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
     printf("error return wrong ty \n");
     return ty;
}

Ty_fieldList *checkPAR_DECL_LIST(PAR_DECL_LIST *p, COLLECTION *c){
     switch(p->kind){
          Ty_fieldList *tyfl;
          case nilPK:
               tyfl=NULL;;
               return tyfl;
               break;
          case vdlPK:
               tyfl = checkVAR_DECL_LIST(p->val.vdecl_list.left, c);
               return tyfl;
               break;
     }
}

Ty_fieldList *checkVAR_DECL_LIST(VAR_DECL_LIST *vdl, COLLECTION *c){
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
     return Ty_Field(v->val.typeV.id, checkTYPE(v->val.typeV.left, c));
}

void checkBODY(BODY *b, COLLECTION *c){
     checkDECL_LIST(b->val.body.left, c);
     checkSTATE_LIST(b->val.body.right, c);
}


/*
Functions only map to return type, could augment by pointing to ty_ty list for parameters
*/
void checkDECLARATION(DECLARATION *d, COLLECTION *c){
     Ty_fieldList *tyf;
     switch(d->kind){
          case typeIdK:
               putSymbol(c->type, d->val.typeIdD.id, checkTYPE(d->val.typeIdD.left, c));
               break;
          case declFuncK:
               checkFunction(d->val.declFuncD, c);
               break;
          case declVarK:      
               tyf = checkVAR_DECL_LIST(d->val.declVarD, c);
               while(tyf != NULL){
                    putSymbol(c->var,tyf->head->name, tyf->head->ty);
                    tyf=tyf->tail;
               }           
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
               checkEXP(s->val.returnS, c);
               break;
          case writeK:
               checkEXP(s->val.writeS, c);
               break;
          case allocateK:
               checkVAR(s->val.allocateS, c);
               break;
          case allocOfLengthK:
               checkVAR(s->val.allocOfLengthS.left, c);
               checkEXP(s->val.allocOfLengthS.right, c);
               break;
          case assignK:
               checkEXP(s->val.assignS.right, c);
               if(getVarType(s->val.assignS.left, c)->kind != s->val.assignS.right->types.type->kind){
                    printf("Error assign kind %d to kind %d in line %d\n", getVarType(s->val.assignS.left, c)->kind, s->val.assignS.right->types.type->kind, s->val.assignS.right->lineno);
               }
               break;
          case ifK:
               checkEXP(s->val.ifS.left, c);
               checkSTATE(s->val.ifS.right, c);
               break;
          case ifElseK:
               checkEXP(s->val.ifElseS.left, c);
               checkSTATE(s->val.ifElseS.middle, c);
               checkSTATE(s->val.ifElseS.right, c);
               break;
          case whileK:
               checkEXP(s->val.whileS.left, c);
               checkSTATE(s->val.whileS.right, c);
               break;
          case stateListK:
               checkSTATE_LIST(s->val.stateListS.left, c);
               break;
     }
}
