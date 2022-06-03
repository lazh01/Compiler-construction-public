#ifndef __tree_h
#define __tree_h

#include "types.h"


typedef struct NestScopeList_ NestScopeList;
typedef struct COLLECTION_ COLLECTION;


/*included for saving type collection in body node for codegen*/

/*typedef struct EXP {
  int lineno;
  enum {timesK,divK,plusK,minusK, termK} kind;
  union {
    struct {struct EXP *left; struct EXP *right;} timesE;
    struct {struct EXP *left; struct EXP *right;} divE;
    struct {struct EXP *left; struct EXP *right;} plusE;
    struct {struct EXP *left; struct EXP *right;} minusE;
    struct {struct TERM *left;} termE;
  } val;
} EXP;*/

typedef struct EXP {
  int lineno;
  enum {binopK, termK} kind;
  struct {Ty_ty *type; Ty_tyList *args;} types;
  union {
    struct {struct EXP *left; char *op; struct EXP *right;} binopE;
    struct {struct TERM *left;} termE;
  } val;
} EXP;

typedef struct ACTLIST{
  int lineno;
  enum{explistK, nilK} kind;
  union{
    struct{struct EXPLIST *left;} explistA;
    char *nullA;
  } val;
} ACTLIST;


typedef struct TERM{
  int lineno;
  enum{varK, idfuncK, expK, notTermK, lenExpK, numK, boolK, nullK} kind;
  union {
  int intconstT;
  int boolconstT;
  char *null;
  struct {struct VAR *left;} varT;
  struct {struct TERM *left;} nTermT;
  struct {struct EXP *left;} lenExpT;
  struct {struct EXP *left;} expT;
  struct {char *id; struct ACTLIST *left;} idfuncT;
  } val;
} TERM;

typedef struct VAR{
  int lineno;
  enum{idVK, listVK, varidVK} kind;
  union{
    char *idV;
    struct {struct VAR *left; struct EXP *right;} listV;
    struct {struct VAR *left; char *id;} varidV;
  } val;
} VAR;

typedef struct EXPLIST{
  int lineno;
  enum{expLK, explistLK} kind;
  union{
    struct {struct EXP *left;} expL;
    struct {struct EXP *left; struct EXPLIST *right;} explistL;
  } val;
} EXPLIST;

typedef struct FUNCTION{
  int lineno;
  union{
    struct {struct HEAD *left; struct BODY *middle; struct TAIL *right;} function;
  } val;
} FUNCTION;

typedef struct HEAD {
  int lineno;
  union{
    struct {char *id; struct PAR_DECL_LIST *left; struct TYPE *right;} head;
  } val;
} HEAD;

typedef struct TAIL {
  int lineno;
  union{
    struct {char *id;} tail;
  }val;
} TAIL;

typedef struct TYPE {
  int lineno;
  enum {idTyK, intTyK, boolTyK, arrayTyK, recTyK} kind;
  union{
    char *id;
    int intconst;
    int boolconst;
    struct {struct TYPE *left;} array;
    struct {struct VAR_DECL_LIST *left;} record;
  } val;
} TYPE;

typedef struct PAR_DECL_LIST{
  int lineno;
  enum{vdlPK, nilPK} kind;
  union{
    struct {struct VAR_DECL_LIST *left;} vdecl_list;
    char *nullP;
  } val;
} PAR_DECL_LIST;

typedef struct VAR_DECL_LIST{
  int lineno;
  enum{listVDLK, vtK} kind;
  union{
    struct {struct VAR_TYPE *left; struct VAR_DECL_LIST *right;} listV;
    struct {struct VAR_TYPE *left;} vtype;
  } val;
} VAR_DECL_LIST;

typedef struct VAR_TYPE{
  int lineno;
  union{
    struct {char *id; struct TYPE *left;} typeV;
  } val;
} VAR_TYPE;

typedef struct BODY{
  int lineno;
  union{
    struct{struct DECL_LIST *left; struct STATE_LIST *right;} body;
  } val;
  COLLECTION *c;
} BODY;

typedef struct DECLARATION {
  int lineno;
  enum {typeIdK, declFuncK, declVarK} kind;
  union {
    struct{char *id; struct TYPE *left;} typeIdD;
    FUNCTION *declFuncD;
    VAR_DECL_LIST *declVarD;
  } val;
} DECLARATION;

typedef struct DECL_LIST {
  int lineno;
  enum {declListK, nilDK} kind;
  union {
    struct {struct DECLARATION *left; struct DECL_LIST *right;} declListDL;
    char* nilDL;

  } val;
} DECL_LIST;

typedef struct STATE {
  int lineno;
  enum {returnK, writeK, allocateK, allocOfLengthK,  assignK, ifK, ifElseK, whileK,stateListK, incK, decK, forincK, fordecK} kind;
  union {
    //struct {struct EXP *left;} returnS;
    EXP *returnS;
    //struct {struct EXP *left;} writeS;
    EXP *writeS;
    //struct {struct VAR *left;} allocateS;
    VAR *allocateS;

    VAR *incS;

    VAR *decS;

    struct {struct VAR *left; struct EXP *right;} allocOfLengthS;
    struct {struct VAR *left; struct EXP *right;} assignS;
    struct {struct EXP *left; struct STATE *right;} ifS;
    struct {struct EXP *left; struct STATE *middle; struct STATE *right;} ifElseS;
    struct {struct EXP *left; struct STATE *right;} whileS;
    struct {struct STATE_LIST *left;} stateListS;
    struct {struct TERM *first; struct TERM *second; struct TERM *third; struct STATE *fourth;} forincS;
    struct {struct TERM *first; struct TERM *second; struct TERM *third; struct STATE *fourth;} fordecS;
  } val;
} STATE;

typedef struct STATE_LIST {
  int lineno;
  enum {statementK, statementListK} kind;
  union {
    STATE *statementSL;
    struct {struct STATE *left; struct STATE_LIST *right;} statementListSL;
  } val;
} STATE_LIST;

typedef struct NestScopeList_{
    FUNCTION *func;
    NestScopeList *next;
} NestScopeList;

typedef struct COLLECTION_{
    SymbolTable *var;
    SymbolTable *type; 
    SymbolTable *function;
    NestScopeList *nestedlist;
    Ty_ty *returns;
    COLLECTION *next;
} COLLECTION;

/*EXP *makeEXPtimes(EXP *left, EXP *right);

EXP *makeEXPdiv(EXP *left, EXP *right);

EXP *makeEXPplus(EXP *left, EXP *right);

EXP *makeEXPminus(EXP *left, EXP *right);*/

EXP *makeEXPbinop(EXP *left, char *op, EXP *right);

EXP *makeEXPterm(TERM *left);



TERM *makeTERMnum(int intconst);

TERM *makeTERMidfunc(char *id, ACTLIST *left);

TERM *makeTERMvar(VAR *left);

TERM *makeTERMnot(TERM *left);

TERM *makeTERMexp(EXP *left);

TERM *makeTERMlenexp(EXP *left);

TERM *makeTERMbool(int boolconst);

TERM *makeTERMnull();



VAR *makeVARid(char *id);

VAR *makeVARlist(VAR *left, EXP *right);

VAR *makeVARvarid(VAR *left, char *id);



ACTLIST *makeACTLISTlist(EXPLIST *left);

ACTLIST *makeACTLISTnil();



EXPLIST *makeEXPLISTexp(EXP *left);

EXPLIST *makeEXPLISTlist(EXP *left, EXPLIST *right);


FUNCTION *makeFUNCTION(HEAD *h, BODY *b, TAIL *t);


HEAD *makeHEAD(char *id, PAR_DECL_LIST *left, TYPE *right);


TAIL *makeTAIL(char *id);


TYPE *makeTYPEid(char *id);

TYPE *makeTYPEint();

TYPE *makeTYPEbool();

TYPE *makeTYPEarrayof(TYPE *left);

TYPE *makeTYPErecordof(VAR_DECL_LIST *left);


PAR_DECL_LIST *makePAR_DECL_LISTvdl(VAR_DECL_LIST *left);

PAR_DECL_LIST *makePAR_DECL_LISTnil();


VAR_DECL_LIST *makeVAR_DECL_LISTlist(VAR_TYPE *left, VAR_DECL_LIST *right);

VAR_DECL_LIST *makeVAR_DECL_LISTvt(VAR_TYPE *left);


VAR_TYPE *makeVAR_TYPEid(char *id, TYPE *left);


BODY *makeBODY(DECL_LIST *left, STATE_LIST *right);


DECLARATION *makeDECLARATIONtypeId(char *id, TYPE *left);

DECLARATION *makeDECLARATIONdeclFuncD(FUNCTION *left);

DECLARATION *makeDECLARATIONdeclVarD(VAR_DECL_LIST *left);


DECL_LIST *makeDECL_LISTdeclList(DECLARATION *left, DECL_LIST *right);

DECL_LIST *makeDECL_LISTnil();


STATE *makeSTATEreturn(EXP *left);

STATE *makeSTATEwrite(EXP *left);

STATE *makeSTATEallocate(VAR *left);

STATE *makeSTATEallocOfLength(VAR *left, EXP *right);

STATE *makeSTATEassign(VAR *left, EXP *right);

STATE *makeSTATEif(EXP *left, STATE *right);

STATE *makeSTATEifElse(EXP *left, STATE *middle, STATE *right);

STATE *makeSTATEwhile(EXP *left, STATE *right);

STATE *makeSTATEstateList(STATE_LIST *left);

STATE *makeSTATEinc(VAR *left);

STATE *makeSTATEdec(VAR *left);

STATE *makeSTATEforinc(DECL_LIST *first, TERM *second, TERM *third, STATE *fourth);

STATE *makeSTATEfordec(DECL_LIST *first, TERM *second, TERM *third, STATE *fourth);


STATE_LIST *makeSTATE_LISTstatement(STATE *left);

STATE_LIST *makeSTATE_LISTstatementList(STATE *left, STATE_LIST *right);
#endif
