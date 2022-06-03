#include "memory.h"
#include "tree.h"
extern int lineno;
/*
EXP *makeEXPid(char *id)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = idK;
  e->val.idE = id;
  return e;
}

EXP *makeEXPintconst(int intconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = intconstK;
  e->val.intconstE = intconst;
  return e;
}

EXP *makeEXPtimes(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = timesK;
  e->val.timesE.left = left;
  e->val.timesE.right = right;
  return e;
}

EXP *makeEXPdiv(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = divK;
  e->val.divE.left = left;
  e->val.divE.right = right;
  return e;
}

EXP *makeEXPplus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = plusK;
  e->val.plusE.left = left;
  e->val.plusE.right = right;
  return e;
}

EXP *makeEXPminus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = minusK;
  e->val.minusE.left = left;
  e->val.minusE.right = right;
  return e;
}*/

EXP *makeEXPbinop(EXP *left, char *op, EXP *right){
    EXP *e;
    e=NEW(EXP);
    e->kind=binopK;
    e->lineno=lineno;
    e->val.binopE.left=left;
    e->val.binopE.op=op;
    e->val.binopE.right=right;
    return e;
}

EXP *makeEXPterm(TERM *t){
    EXP *e;
    e = NEW(EXP);
    e->lineno=lineno;
    e->kind=termK;
    e->val.termE.left=t;
    return e;
}

//e.g. 9
TERM *makeTERMnum(int intconst){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind=numK;
    t->val.intconstT = intconst;
    return t;
}

//"id(ACTLIST)"
TERM *makeTERMidfunc(char *id, ACTLIST *left){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind=idfuncK;
    t->val.idfuncT.id=id;
    t->val.idfuncT.left = left;
    return t;
}

//VARIABLE
TERM *makeTERMvar(VAR *left){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind = varK;
    t->val.varT.left=left;
    return t;
}

//"!TERM"
TERM *makeTERMnot(TERM *left){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind = notTermK;
    t->val.nTermT.left=left;
    return t;
}

//"(EXPRESSION)"
TERM *makeTERMexp(EXP *left){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind = expK;
    t->val.expT.left=left;
    return t;
}

//"|expression|"
TERM *makeTERMlenexp(EXP *left){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind = lenExpK;
    t->val.lenExpT.left=left;
    return t;
}

//"true" or "false"
TERM *makeTERMbool(int boolconst){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind = boolK;
    t->val.boolconstT=boolconst;
    return t;
}

//"null"
TERM *makeTERMnull(){
    TERM *t;
    t = NEW(TERM);
    t->lineno = lineno; 
    t->kind = nullK;
    t->val.null=0;
    return t;
}

VAR *makeVARid(char *id){
    VAR *v;
    v=NEW(VAR);
    v->lineno=lineno;
    v->kind=idVK;
    v->val.idV=id;
    return v;
}

VAR *makeVARlist(VAR *left, EXP *right){
    VAR *v;
    v=NEW(VAR);
    v->lineno=lineno;
    v->kind=listVK;
    v->val.listV.left=left;
    v->val.listV.right=right;
    return v;
}

VAR *makeVARvarid(VAR *left, char *id){
    VAR *v;
    v=NEW(VAR);
    v->lineno=lineno;
    v->kind=varidVK;
    v->val.varidV.left=left;
    v->val.varidV.id=id;
    return v;
}

ACTLIST *makeACTLISTlist(EXPLIST *left){
    ACTLIST *a;
    a=NEW(ACTLIST);
    a->lineno=lineno;
    a->kind=explistK;
    a->val.explistA.left=left;
    return a;
}

ACTLIST *makeACTLISTnil(){
    ACTLIST *a;
    a=NEW(ACTLIST);
    a->lineno=lineno;
    a->kind=nilK;
    a->val.nullA = 0;
    return a;
}

EXPLIST *makeEXPLISTexp(EXP *left){
    EXPLIST *e;
    e=NEW(EXPLIST);
    e->lineno=lineno;
    e->kind=expLK;
    e->val.expL.left=left;
    return e;
}

EXPLIST *makeEXPLISTlist(EXP *left, EXPLIST *right){
    EXPLIST *e;
    e=NEW(EXPLIST);
    e->lineno=lineno;
    e->kind=explistLK;
    e->val.explistL.left=left;
    e->val.explistL.right=right;
    return e;
}

FUNCTION *makeFUNCTION(HEAD *h, BODY *b, TAIL*t){
    FUNCTION *f;
    f=NEW(FUNCTION);
    f->lineno=lineno;
    f->val.function.left=h;
    f->val.function.middle=b;
    f->val.function.right=t;
    return f;
}

HEAD *makeHEAD(char *id, PAR_DECL_LIST *left, TYPE *right){
    HEAD *h;
    h=NEW(HEAD);
    h->lineno=lineno;
    h->val.head.id=id;
    h->val.head.left=left;
    h->val.head.right=right;
    return h;
}

TAIL *makeTAIL(char *id){
    TAIL *t;
    t=NEW(TAIL);
    t->lineno=lineno;
    t->val.tail.id=id;
    return t;
}

TYPE *makeTYPEid(char *id){
    TYPE *t;
    t=NEW(TYPE);
    t->lineno=lineno;
    t->kind=idTyK;
    t->val.id=id;
    return t;
}

TYPE *makeTYPEint(){
    TYPE *t;
    t=NEW(TYPE);
    t->lineno=lineno;
    t->kind=intTyK;
    t->val.intconst=0;
    return t;
}

TYPE *makeTYPEbool(){
    TYPE *t;
    t=NEW(TYPE);
    t->lineno=lineno;
    t->kind=boolTyK;
    t->val.boolconst=0;
    return t;
}

TYPE *makeTYPEarrayof(TYPE *left){
    TYPE *t;
    t=NEW(TYPE);
    t->lineno=lineno;
    t->kind=arrayTyK;
    t->val.array.left=left;
    return t;
}

TYPE *makeTYPErecordof(VAR_DECL_LIST *left){
    TYPE *t;
    t=NEW(TYPE);
    t->lineno=lineno;
    t->kind=recTyK;
    t->val.record.left=left;
    return t;
}

PAR_DECL_LIST *makePAR_DECL_LISTnil(){
    PAR_DECL_LIST *p;
    p=NEW(PAR_DECL_LIST);
    p->lineno=lineno;
    p->kind=nilK;
    p->val.nullP=0;
    return p;
}

PAR_DECL_LIST *makePAR_DECL_LISTvdl(VAR_DECL_LIST *left){
    PAR_DECL_LIST *p;
    p=NEW(PAR_DECL_LIST);
    p->lineno=lineno;
    p->kind=vdlPK;
    p->val.vdecl_list.left=left;
    return p;
}

VAR_DECL_LIST *makeVAR_DECL_LISTlist(VAR_TYPE *left, VAR_DECL_LIST *right){
    VAR_DECL_LIST *v;
    v=NEW(VAR_DECL_LIST);
    v->lineno=lineno;
    v->kind=listVDLK;
    v->val.listV.left=left;
    v->val.listV.right=right;
    return v;
}

VAR_DECL_LIST *makeVAR_DECL_LISTvt(VAR_TYPE *left){
    VAR_DECL_LIST *v;
    v=NEW(VAR_DECL_LIST);
    v->lineno=lineno;
    v->kind=vtK;
    v->val.vtype.left=left;
    return v;
}

VAR_TYPE *makeVAR_TYPEid(char *id, TYPE *left){
    VAR_TYPE *v;
    v=NEW(VAR_TYPE);
    v->lineno=lineno;
    v->val.typeV.id=id;
    v->val.typeV.left=left;
    return v;
}

BODY *makeBODY(DECL_LIST *left, STATE_LIST *right){
    BODY *b;
    b=NEW(BODY);
    b->lineno=lineno;
    b->val.body.left=left;
    b->val.body.right=right;
    return b;
}

DECLARATION *makeDECLARATIONtypeId(char *id, TYPE *left){
    DECLARATION *d;
    d = NEW(DECLARATION);
    d->lineno = lineno;
    d->kind = typeIdK;
    d->val.typeIdD.left = left;
    d->val.typeIdD.id=id;
    return d;
}

DECLARATION *makeDECLARATIONdeclFuncD(FUNCTION *left){
    DECLARATION *d;
    d = NEW(DECLARATION);
    d->lineno = lineno;
    d->kind = declFuncK;
    d->val.declFuncD = left;
    return d;
}

DECLARATION *makeDECLARATIONdeclVarD(VAR_DECL_LIST *left){
    DECLARATION *d;
    d = NEW(DECLARATION);
    d->lineno = lineno;
    d->kind = declVarK;
    d->val.declVarD = left;
    return d;
}

DECL_LIST *makeDECL_LISTdeclList(DECLARATION *left, DECL_LIST *right){
    DECL_LIST *dl;
    dl = NEW(DECL_LIST);
    dl->lineno = lineno;
    dl->kind = declListK;
    dl->val.declListDL.left = left;
    dl->val.declListDL.right = right;
    return dl;
}

DECL_LIST *makeDECL_LISTnil(){
    DECL_LIST *dl;
    dl = NEW(DECL_LIST);
    dl->lineno = lineno;
    dl->kind = nilDK;
    dl->val.declListDL.left = 0;
    return dl;
}

STATE *makeSTATEreturn(EXP *left){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = returnK;
    s->val.returnS = left;
    return s;
}
STATE *makeSTATEwrite(EXP *left){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = writeK;
    s->val.writeS = left;
    return s;
}
STATE *makeSTATEallocate(VAR *left){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = allocateK;
    s->val.allocateS = left;
    return s;
}

STATE *makeSTATEallocOfLength(VAR *left, EXP *right){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = allocOfLengthK;
    s->val.allocOfLengthS.left = left;
    s->val.allocOfLengthS.right = right;
    return s;
}
STATE *makeSTATEassign(VAR *left, EXP *right){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = assignK;
    s->val.assignS.left = left;
    s->val.assignS.right = right;
    return s;
}

STATE *makeSTATEif(EXP *left, STATE *right){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = ifK;
    s->val.ifS.left = left;
    s->val.ifS.right = right;
    return s;
}
STATE *makeSTATEifElse(EXP *left, STATE *middle, STATE *right){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = ifElseK;
    s->val.ifElseS.left = left;
    s->val.ifElseS.middle = middle;
    s->val.ifElseS.right = right;
    return s;
}

STATE *makeSTATEwhile(EXP *left, STATE *right){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = whileK;
    s->val.whileS.left = left;
    s->val.whileS.right = right;
    return s;
}

STATE *makeSTATEstateList(STATE_LIST *left){
    STATE *s;
    s = NEW(STATE);
    s->lineno = lineno;
    s->kind = stateListK;
    s->val.stateListS.left = left;
    return s;
}

STATE_LIST *makeSTATE_LISTstatement(STATE *left){
    STATE_LIST *s;
    s = NEW(STATE_LIST);
    s->lineno = lineno;
    s->kind = statementK;
    s->val.statementSL = left;
    return s;
}

STATE_LIST *makeSTATE_LISTstatementList(STATE *left, STATE_LIST *right){
    STATE_LIST *s;
    s = NEW(STATE_LIST);
    s->lineno = lineno;
    s->kind = statementListK;
    s->val.statementListSL.left = left;
    s->val.statementListSL.right = right;
    return s;
}