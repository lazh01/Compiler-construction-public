#include <stdio.h>
#include "typecheck.h"

int error = 0;

COLLECTION *initCOLLECTION(){
     COLLECTION *c;
     c = NEW(COLLECTION);
     c->function=initSymbolTable();
     c->type=initSymbolTable();
     c->var=initSymbolTable();
     c->nestedlist=NULL;
     c->returns=Ty_Nil();
     c->next=NULL;
     return c;
}

COLLECTION *scopeCOLLECTION(COLLECTION *c, Ty_ty *returntype){
     COLLECTION *col;
     col=NEW(COLLECTION);
     col->function=scopeSymbolTable(c->function);
     col->type=scopeSymbolTable(c->type);
     col->var=scopeSymbolTable(c->var);
     col->nestedlist=NULL;
     col->returns=returntype;
     col->next=c;
     return col;
}

void appendNestList(FUNCTION *head, COLLECTION *c){
     NestScopeList *list;
     list = NEW(NestScopeList);
     list->func=head;
     list->next=c->nestedlist;
     c->nestedlist = list;
}

int checkTREE(BODY *b){
     collect = initCOLLECTION();
     checkBODY(b, collect);
     return error;
}

void checkEXP(EXP *e, COLLECTION *c)
{ switch (e->kind) {
     case binopK:
          checkEXP(e->val.binopE.left, c);
          checkEXP(e->val.binopE.right, c);
          if (EXPtype(e, c)){
               fprintf(stderr, "Error unexpected types in binary expression, in line %d\n", e->lineno);
               error=1;
          }
          break;
     case termK:
          //printf("Here\n");
          checkTERM(e->val.termE.left, c);
          e->types.type = getTermType(e->val.termE.left, c);
          //printf("%d\n", e->types.type->kind);
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
     if (strcmp(e->val.binopE.op, " || ")==0){
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
     //printf("%d, %d, %s\n", e->val.binopE.left->types.type->kind, e->val.binopE.right->types.type->kind, e->val.binopE.op);
     if (tyComp(e->val.binopE.left->types.type, e->types.args->head) != 1 || tyComp(e->val.binopE.right->types.type, e->types.args->tail->head) != 1){
          fprintf(stderr, "expression has unexpected types in line %d\n", e->lineno);
          error = 1;
          return 1;
     }
     goto end;

     checksametype: 
     if(tyComp(e->val.binopE.left->types.type, e->val.binopE.right->types.type) != 1){
          fprintf(stderr, "Expected same type in line %d\n", e->lineno);
          error = 1;
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
     SYMBOL *s;
     switch(v->kind){
          case idVK:
               s = getSymbol(c->var, v->val.idV);
               if (s == NULL){
                    fprintf(stderr, "No variable %s, in line %d\n", v->val.idV, v->lineno);
                    ty = NULL;
                    error = 1;
               } else {
                    ty = s->value;
               }
               return ty;
               break;
          case listVK:
               return Ty_Array(getVarType(v->val.listV.left, c));
               break;
          case varidVK:
               ty = getVarType(v->val.varidV.left, c);
               while (ty->kind == Ty_name || ty->kind == Ty_array){
                    if(ty->kind == Ty_name){
                         ty = (Ty_ty*)getSymbol(ty->u.name.table, ty->u.name.name)->value;
                    }

                    if(ty->kind == Ty_array){
                         ty= ty->u.array;
                    }
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
                    fprintf(stderr, "wrong parameters for function in %d kind %d and %d\n", t->lineno, list->head->kind, formals->head->kind);
                    error = 1;
               }
               list=list->tail;
               formals=formals->tail;
          }
          if(list != NULL || formals !=NULL){
               fprintf(stderr, "Wrong amount of variables in %d \n", t->lineno);
               error = 1;
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
     c=scopeCOLLECTION(c, checkTYPE(f->val.function.left->val.head.right, c));

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
     fprintf(stderr, "error unusable type in line %d\n", t->lineno);
     error=1;
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
     b->c=c;
     NestScopeList *nl;
     SymbolList *sl;
     Ty_ty *ty;
     Ty_tyList *TypesSeen = NULL;
     Ty_tyList *NameCheck;
     checkDECL_LIST(b->val.body.left, c);
     //check for name types with no actual type
     sl = AllSymbolsInScope(c->type);
     while(sl != NULL){
          ty = sl->head->value;
          while(ty->kind == Ty_name){
               NameCheck = TypesSeen;
               while(NameCheck != NULL){
                    if(NameCheck->head == ty){
                         fprintf(stderr, "name recursion\n");
                         break;
                    }
                    NameCheck = NameCheck->tail;
               }
               if(NameCheck != NULL){
                    error = 1;
                    break;
               }
               TypesSeen = Ty_TyList(ty, TypesSeen);
               ty = getSymbol(ty->u.name.table, ty->u.name.name)->value;
          }
          TypesSeen = NULL;
          sl = sl->tail;
     }
     //end check for name types with no actual type
     checkSTATE_LIST(b->val.body.right, c);
     nl = c->nestedlist;
     while(nl != NULL){
          checkFunction(nl->func, c);
          nl=nl->next;
     }
}

void declareFunction(FUNCTION *func, COLLECTION *c){
     HEAD *h = func->val.function.left;
     Ty_fieldList *flist;
     flist = checkPAR_DECL_LIST(h->val.head.left, c);
     putSymbol(c->function, h->val.head.id, Ty_Func(FListToList(flist), checkTYPE(h->val.head.right, c)));
     appendNestList(func, c);
}

void checkDECLARATION(DECLARATION *d, COLLECTION *c){
     Ty_fieldList *tyf;
     switch(d->kind){
          case typeIdK:
               putSymbol(c->type, d->val.typeIdD.id, checkTYPE(d->val.typeIdD.left, c));
               break;
          case declFuncK:
               declareFunction(d->val.declFuncD, c);
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
               if(tyComp(c->returns, s->val.returnS->types.type) != 1){
                    fprintf(stderr, "Error wrong return type in line %d\n", s->lineno);
                    error=1;
               }
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
               if(tyComp(s->val.allocOfLengthS.right->types.type, Ty_Int()) != 1){
                    fprintf(stderr, "Error length not int in line %d \n", s->lineno);
                    error = 1;
               }
               break;
          case assignK:
               checkEXP(s->val.assignS.right, c);
               if(tyComp(getVarType(s->val.assignS.left, c), s->val.assignS.right->types.type) != 1){
                    fprintf(stderr, "Error assign in line %d\n", s->val.assignS.right->lineno);
                    error = 1;
               }
               break;
          case ifK:
               checkEXP(s->val.ifS.left, c);
               if(tyComp(s->val.ifS.left->types.type, Ty_Bool()) != 1){
                    fprintf(stderr, "Error if without bool expression in line %d \n", s->lineno);
                    error=1;
               }
               checkSTATE(s->val.ifS.right, c);
               break;
          case ifElseK:
               checkEXP(s->val.ifElseS.left, c);
               if(tyComp(s->val.ifElseS.left->types.type, Ty_Bool()) != 1){
                    fprintf(stderr, "Error if without bool expression in line %d \n", s->lineno);
                    error = 1;
               }
               checkSTATE(s->val.ifElseS.middle, c);
               checkSTATE(s->val.ifElseS.right, c);
               break;
          case whileK:
               checkEXP(s->val.whileS.left, c);
               if(tyComp(s->val.whileS.left->types.type, Ty_Bool()) != 1){
                    fprintf(stderr, "Error while without bool expression in line %d \n", s->lineno);
                    error=1;
               }
               checkSTATE(s->val.whileS.right, c);
               break;
          case stateListK:
               checkSTATE_LIST(s->val.stateListS.left, c);
               break;
     }
}
