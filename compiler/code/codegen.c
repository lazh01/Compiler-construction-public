#include "codegen.h"

int tempVar = 0;

int writecounter=0;

int ifcount=0;

int whilecount = 0;

void codeGEN(BODY *b){
     frame *fr;
     NestScopeList *nl;
     fr=createFrame(NULL);
     initFrame(NULL, b, fr);
     f = fopen("./output.asm", "w");
     if(f == NULL){
          fprintf(stderr, "error opening file\n");
          return;
     }
     //data section
     fprintf(f, ".section .data\n");
     fprintf(f, "   initialBrk: .quad 0\n");
     fprintf(f, "   currentBrk: .quad 0\n");
     fprintf(f, "   newBrk: .quad 0\n");
     fprintf(f, "   freelist: .quad 0\n");
     fprintf(f, "   Callstack: .space 400\n");
     fprintf(f, "   top: .quad 0\n");
     //text section
     fprintf(f, ".section .text\n");
     fprintf(f, ".globl _start\n\n");

     //main program
     fprintf(f, "_start:\n");
     initProgram();
     fprintf(f, "   push %%rbp\n");
     fprintf(f, "   movq %%rsp, %%rbp\n");
     fprintf(f, "   call pushframe\n");
     fprintf(f, "   push $%d\n", argCount(fr));
     fprintf(f, "   push $%d\n", locCount(fr));

     codeBODY(b, fr);

     fprintf(f, "   pop %%rax\n");
     fprintf(f, "   pop %%rax\n");
     fprintf(f, "   call popframe\n");
     fprintf(f, "   movq %%rbp, %%rsp\n");
     fprintf(f, "   pop %%rbp\n");
     fprintf(f, "   movq $60, %%rax\n");
     fprintf(f, "   movq $0, %%rdi\n");
     fprintf(f, "   syscall\n");
     fprintf(f, "\n");
     getMem();
     allocLength();
     popFrame(fr);
     pushFrame(fr);

     nl=fr->c->nestedlist;

     while(nl != NULL){
          codeFunction(nl->func,fr);
          nl=nl->next;
     }



     fclose(f);
}

void initProgram(){
     fprintf(f, "   movq $12, %%rax\n");
	fprintf(f, "   movq $0, %%rdi\n");
	fprintf(f, "   syscall\n");
     fprintf(f, "   movq %%rax, (initialBrk)\n");
     fprintf(f, "   movq %%rax, (currentBrk)\n");
     fprintf(f, "   movq %%rax, (newBrk)\n");
     fprintf(f, "   movq $Callstack, (top)\n");
}

void pushFrame(frame *fr){
     fprintf(f, "pushframe:\n");
     fprintf(f, "   movq (top), %%rax\n");
     fprintf(f, "   movq %%rbp, (%%rax)\n");
     fprintf(f, "   addq $8, (top)\n");
     fprintf(f, "   ret\n");
}

void popFrame(frame *fr){
     fprintf(f, "popframe:\n");
     fprintf(f, "   subq $8, (top)\n");
     fprintf(f, "   movq (top), %%rax\n");
     fprintf(f, "   movq $0, (%%rax)\n");
     fprintf(f, "   ret\n");
}

void printCaller(){

}

void printCallee(){
     
}

void codeEXP(EXP *e, temp *tem, frame *fr)
{ switch (e->kind) {
     case binopK:
          EXPswitch(e, tem, fr);
          break;
     case termK:
          codeTERM(e->val.termE.left, tem, fr);
          break;
  }
}

void EXPswitch(EXP *e, temp *tem, frame *fr){
     if(strcmp("+", e->val.binopE.op) == 0){
          expADD(e, tem, fr);
     }
     if(strcmp("-", e->val.binopE.op) == 0){
          expSUB(e, tem, fr);
     }
     if(strcmp("*", e->val.binopE.op) == 0){
          expADD(e, tem, fr);
     }
}

void expADD(EXP *e, temp *tem, frame *fr){
     temp *arg1;
     temp *arg2;
     arg1 = requestTemp();
     arg2 = requestTemp();

     codeEXP(e->val.binopE.left, arg1, fr);
     codeEXP(e->val.binopE.right, arg2, fr);

     fprintf(f, "   addq t%d, t%d\n", arg1->num, arg2->num);
     fprintf(f, "   movq t%d, t%d\n", arg2->num, tem->num);

}

void expSUB(EXP *e, temp *tem, frame *fr){
     temp *arg1;
     temp *arg2;
     arg1 = requestTemp();
     arg2 = requestTemp();
     codeEXP(e->val.binopE.left, arg1, fr);
     codeEXP(e->val.binopE.right, arg2, fr);

     fprintf(f, "   subq t%d, t%d\n", arg2->num, arg1->num);
     fprintf(f, "   movq t%d, t%d\n", arg1->num, tem->num);
}

void expMUL(EXP *e, temp *tem, frame *fr){
     temp *arg1;
     temp *arg2;
     arg1 = requestTemp();
     arg2 = requestTemp();
     codeEXP(e->val.binopE.left, arg1, fr);
     codeEXP(e->val.binopE.right, arg2, fr);

     fprintf(f, "   imulq t%d, t%d\n", arg1->num, arg2->num);
     fprintf(f, "   movq t%d, t%d\n", arg2->num, tem->num);
}

void expDIV(EXP *e, temp *tem, frame *fr){
     temp *arg1;
     temp *arg2;
     arg1 = requestTemp();
     arg2 = requestTemp();
     codeEXP(e->val.binopE.left, arg1, fr);
     codeEXP(e->val.binopE.right, arg2, fr);

     fprintf(f, "   push %%rax\n");
     fprintf(f, "   movq t%d, %%rax", arg1->num);
     fprintf(f, "   idivq t%d", arg2->num);
     fprintf(f, "   movq %%rax, t%d", tem->num);
     fprintf(f, "   pop %%rax");
}


void codeTERM(TERM *t, temp *tem, frame *fr){
  temp *var;
  temp *result;
  int depth;
  int count;
  switch(t->kind){
    case varK:
          var = requestTemp();
          codeVAR(t->val.varT.left, fr, var);
          fprintf(f, "   movq t%d, %%rcx\n", var->num);
          fprintf(f, "   movq 8(%%rcx), t%d\n", tem->num);
          break;
    case idfuncK:
          count = codeACTLIST(t->val.idfuncT.left, fr);
          depth = getFuncDepth(fr, t->val.idfuncT.id, 0);
          fprintf(f, "   movq %%rbp, %%rdi\n");
          while(depth != 0){
               fprintf(f, "   movq 16(%%rdi), %%rdi\n");
               depth--;
          }
          fprintf(f, "   push %%rdi\n");
          fprintf(f, "   call %s\n", t->val.idfuncT.id);
          fprintf(f, "   movq %%rax, t%d\n", tem->num);
          fprintf(f, "   addq $8, %%rsp\n");
          fprintf(f, "   addq $%d, %%rsp\n", 16*count);
          break;
    case expK:
          result = requestTemp();
          codeEXP(t->val.expT.left, result, fr);
          fprintf(f, "   movq t%d, t%d\n", result->num, tem->num);
          break;
    case notTermK:
          result = requestTemp();
          codeTERM(t->val.nTermT.left, result, fr);
          fprintf(f, "   movq t%d, t%d\n", result->num, tem->num);
          fprintf(f, "   xor $1, t%d\n",tem->num);
          break;
    case lenExpK:
          result = requestTemp();
          codeEXP(t->val.lenExpT.left, result, fr);
          fprintf(f, "   movq t%d, %%rsi\n", result->num);
          fprintf(f, "   movq 16(%%rsi), t%d\n", tem->num);
          break;
    case numK:
          fprintf(f, "   movq $%d, t%d\n", t->val.intconstT, tem->num);
          break;
    case boolK:
          fprintf(f, "   movq $%d, t%d\n", t->val.boolconstT, tem->num);
          if(t->val.boolconstT == 0){
          } else if (t->val.boolconstT == 1)
          {
          }
          break;
    case nullK:
          fprintf(f, "   movq $0, t%d\n", tem->num);
          break;
  }
}

void codeVAR(VAR *v, frame *fr, temp *tem){
     temp *tvar = requestTemp();
     temp *tlen = requestTemp();
     int recIndex = 0;
     Ty_ty *varTy;
     Ty_fieldList *fl;
     faccess *fa;
     switch(v->kind){
          case idVK:
               fa = getAccess(v->val.idV, fr);
               getVar(fa, tvar);
               fprintf(f, "   movq t%d, %%rdx\n", tvar->num);
               fprintf(f, "   movq %%rdx, t%d\n", tem->num);
               break;
          case listVK:
               codeVAR(v->val.listV.left, fr, tvar);
               codeEXP(v->val.listV.right, tlen, fr);
               fprintf(f, "   movq t%d, %%rdx\n", tvar->num);
               fprintf(f, "   movq 8(%%rdx), %%rsi\n");
               fprintf(f, "   addq $24, %%rsi\n");
               fprintf(f, "   movq t%d, %%rax\n", tlen->num);
               fprintf(f, "   movq $16, %%rdi\n");
               fprintf(f, "   imulq %%rdi\n");
               fprintf(f, "   addq %%rax, %%rsi\n");
               fprintf(f, "   movq %%rsi, t%d\n", tem->num);
               break;
          case varidVK:
               codeVAR(v->val.varidV.left, fr, tvar);
               varTy = getVarType(v->val.varidV.left, fr->c);

               while(varTy->kind == Ty_name){
                    varTy = getSymbol(varTy->u.name.table, varTy->u.name.name)->value;
               }
               fl = varTy->u.record;
               while(strcmp(v->val.varidV.id, fl->head->name) != 0){
                    recIndex++;
                    fl = fl->tail;
               }
               fprintf(f, "   movq t%d, %%rdx\n", tvar->num);
               fprintf(f, "   movq 8(%%rdx), %%rsi\n");
               fprintf(f, "   addq $24, %%rsi\n");
               fprintf(f, "   movq $%d, %%rax\n", recIndex);
               fprintf(f, "   movq $16, %%rdi\n");
               fprintf(f, "   imulq %%rdi\n");
               fprintf(f, "   addq %%rax, %%rsi\n");
               fprintf(f, "   movq %%rsi, t%d\n", tem->num);
               break;
     }
}

void getVar(faccess *fa, temp *tem){
     int depth; 
     depth = fa->depth;
     fprintf(f, "   movq %%rbp, %%rdi\n");
     while(depth != 0){
          fprintf(f, "   movq 16(%%rdi), %%rdi\n");
          depth--;
     }
     fprintf(f, "   addq $%d, %%rdi\n", fa->offset);
     fprintf(f, "   movq %%rdi, t%d\n", tem->num);
}

int codeACTLIST(ACTLIST *act, frame *fr){
     switch(act->kind){
          case explistK:
               return codeEXPLIST(act->val.explistA.left, fr);
               break;
          case nilK:
               return 0;
               break;
     }
}

int codeEXPLIST(EXPLIST *expl, frame *fr){
     temp *arg = requestTemp();
     int i;
     Ty_ty *ty = expl->val.expL.left->types.type;
     while(ty->kind == Ty_name){
          ty= getSymbol(ty->u.name.table, ty->u.name.name)->value;
     }
     switch(expl->kind){
          case expLK:
               codeEXP(expl->val.expL.left, arg, fr);
               fprintf(f, "   push t%d\n", arg->num);
               switch(ty->kind){
                    case Ty_int:
                         fprintf(f, "   push $0\n");
                         break;
                    case Ty_bool:
                         fprintf(f, "   push $0\n");
                         break;
                    case Ty_record:
                         fprintf(f, "   push $1\n");
                         break;
                    case Ty_array:
                         fprintf(f, "   push $1\n");
                         break;                      
                    default:
                         break;
               }
               return 1;
               break;
          case explistLK:
               i = 1 + codeEXPLIST(expl->val.explistL.right, fr);
               codeEXP(expl->val.explistL.left, arg, fr);
               fprintf(f, "   push t%d\n", arg->num);
               switch(ty->kind){
                    case Ty_int:
                         fprintf(f, "   push $0\n");
                         break;
                    case Ty_bool:
                         fprintf(f, "   push $0\n");
                         break;
                    case Ty_record:
                         fprintf(f, "   push $1\n");
                         break;
                    case Ty_array:
                         fprintf(f, "   push $1\n");
                         break;                      
                    default:
                         break;
               }
               return i;
               break;
     }
}

void codeFunction(FUNCTION *fun, frame *fr){
     fprintf(f, "%s:\n", fun->val.function.left->val.head.id); //to be replaced with generated label
     fprintf(f, "   push %%rbp\n");
     fprintf(f, "   movq %%rsp, %%rbp\n");
    //callee save here
     frame *newframe;
     newframe = createFrame(fr);
     initFrame(fun->val.function.left, fun->val.function.middle, newframe);
     fprintf(f, "   push $%d\n", argCount(newframe));
     fprintf(f, "   push $%d\n", locCount(newframe));
     //codeHEAD(fun->val.function.left, newframe);
     codeBODY(fun->val.function.middle, newframe);

     fprintf(f, "   addq $16, %%rsp\n");
     
     fprintf(f, "   movq %%rbp, %%rsp\n");
     fprintf(f, "   pop %%rbp\n");
     //codeTAIL(fun->val.function.right, newframe);
     fprintf(f, "   ret\n");
}

void codeHEAD(HEAD *h, frame *fr){
     codePAR_DECL_LIST(h->val.head.left, fr);
     codeTYPE(h->val.head.right, fr);
}

void codeTAIL(TAIL *t, frame *fr){
}

void codeTYPE(TYPE *t, frame *fr){
     switch(t->kind){
          case idTyK:
               break;
          case intTyK:
               break;
          case boolTyK:
               break;
          case arrayTyK:
               codeTYPE(t->val.array.left, fr);
               break;
          case recTyK:
               codeVAR_DECL_LIST(t->val.record.left, fr);
               break;
     }
}

void codePAR_DECL_LIST(PAR_DECL_LIST *p, frame *fr){
     switch(p->kind){
          case nilPK:
               break;
          case vdlPK:
               codeVAR_DECL_LIST(p->val.vdecl_list.left, fr);
               break;
     }
}

linkedlist *codeVAR_DECL_LIST(VAR_DECL_LIST *vdl, frame *fr){
     linkedlist *list;
     switch(vdl->kind){
          case listVDLK:
               list = createList(codeVAR_TYPE(vdl->val.vtype.left, fr));
               list->next=codeVAR_DECL_LIST(vdl->val.listV.right, fr);
               break;
          case vtK:
               list = createList(codeVAR_TYPE(vdl->val.vtype.left, fr));
               break;
     }
     return list;
}

char *codeVAR_TYPE(VAR_TYPE *v, frame *fr){
     codeTYPE(v->val.typeV.left, fr);
     return v->val.typeV.id;
}

void codeBODY(BODY *b, frame *fr){
     int locals = locCount(fr);
     codeDECL_LIST(b->val.body.left, fr);
     codeSTATE_LIST(b->val.body.right, fr);
     while(locals != 0){
          fprintf(f, "   pop %%rax\n");
          fprintf(f, "   pop %%rax\n");
          locals--;
     }
}

void codeDECLARATION(DECLARATION *d, frame *fr){
     linkedlist *locals;
     switch(d->kind){
          case typeIdK:
               //codeTYPE(d->val.typeIdD.left, fr);
               // printf(";\n");
               break;
          case declFuncK:
               //codeFunction(d->val.declFuncD, fr);
               break;
          case declVarK:
               locals = codeVAR_DECL_LIST(d->val.declVarD, fr);
               while(locals != NULL){
                    generateLocalVariable(locals->name, fr);
                    locals = locals->next;
               }
               break;
     }
}

void generateLocalVariable(char *c, frame *fr){
     int recSize=0;
     int recLength=0;
     int recIndex=0;
     Ty_fieldList *list;
     Ty_ty *ty = getSymbol(fr->c->var, c)->value;
     while(ty->kind == Ty_name){
          ty=getSymbol(ty->u.name.table, ty->u.name.name)->value;
     }
     switch(ty->kind){
          case Ty_int:
               fprintf(f, "   push $0\n");
               fprintf(f, "   push $0\n"); //header
               break;
          case Ty_bool:
               fprintf(f, "   push $0\n"); 
               fprintf(f, "   push $0\n"); //header
               break;
          case Ty_record:
               recSize = 3;
               list = ty->u.record;
               while(list != NULL){
                    recSize = recSize +2;
                    recLength++;
                    list=list->tail;
               }
               fprintf(f, "   movq $%d, %%rax\n", recSize);
               fprintf(f, "   call getMem\n");
               fprintf(f, "   push %%rax\n");
               fprintf(f, "   push $1\n"); //header

               fprintf(f, "   movq $0, (%%rax)\n");
               fprintf(f, "   movq $%d, 8(%%rax)\n", recSize);
               fprintf(f, "   movq $%d, 16(%%rax)\n", recLength);
               list=ty->u.record;
               while(list != NULL){
                    ty = list->head->ty;
                    while(ty->kind == Ty_name){
                         ty=getSymbol(ty->u.name.table, ty->u.name.name)->value;
                    }

                    switch(ty->kind){
                         case Ty_int:
                              fprintf(f, "   movq $0, %d(%%rax)\n", (3+recIndex*2)*8 ); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         case Ty_bool:
                              fprintf(f, "   movq $0, %d(%%rax)\n", (3+recIndex*2)*8); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         case Ty_record:
                              fprintf(f, "   movq $1, %d(%%rax)\n", (3+recIndex*2)*8); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         case Ty_array:
                              fprintf(f, "   movq $1, %d(%%rax)\n", (3+recIndex*2)*8); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         default:
                              break;
                    }
                    recIndex++;
                    list = list->tail;
               }
               break;
          case Ty_array:
               fprintf(f, "   push $0\n");
               fprintf(f, "   push $1\n"); //header
               break;
          default:
               break;

     }
}


//reserves space equal to 8 * rax in bytes, and returns address in rax
void getMem(){
     fprintf(f, "getMem:\n");
     fprintf(f, "   movq (currentBrk), %%rdi\n");
     fprintf(f, "   addq %%rax, %%rdi\n");
     fprintf(f, "   movq $12, %%rax\n");
     fprintf(f, "   syscall\n");
     fprintf(f, "   movq %%rax, (newBrk)\n");
     fprintf(f, "   movq %%rax, (currentBrk);\n");
     fprintf(f, "   ret\n");
}

void codeDECL_LIST(DECL_LIST *dl, frame *fr){
     switch(dl->kind){
          case declListK:
               codeDECLARATION(dl->val.declListDL.left, fr);
               codeDECL_LIST(dl->val.declListDL.right, fr);
               break;
          case nilDK:
               break;
     }
}

void codeSTATE_LIST(STATE_LIST *sl, frame *fr){
  switch(sl->kind){
    case statementK:
          codeSTATE(sl->val.statementSL, fr);
          break;
    case statementListK:
          codeSTATE(sl->val.statementListSL.left, fr);
          codeSTATE_LIST(sl->val.statementListSL.right, fr);
          break;
  }

}

void codeSTATE(STATE *s, frame *fr){
     temp *write;
     temp *wcount;
     temp *tvar;
     temp *argument;
     Ty_ty *varTy;
     switch(s->kind){
          case returnK:
               tvar = requestTemp();
               codeEXP(s->val.returnS, tvar, fr);
               fprintf(f, "   movq t%d, %%rax\n", tvar->num);
               break;
          case writeK:
               write = requestTemp();
               wcount = requestTemp();
               codeEXP(s->val.writeS, write, fr);
               fprintf(f, "   push %%rbp\n");
               fprintf(f, "   movq %%rsp, %%rbp\n");
               fprintf(f, "   push %%rax\n");
               fprintf(f, "   push %%rcx\n");
               fprintf(f, "   push %%rdx\n");
               fprintf(f, "   push %%rdi\n");
               fprintf(f, "   push %%rsi\n");
               fprintf(f, "   push t%d\n", write->num);
               fprintf(f, "   push t%d\n", wcount->num);
               
               fprintf(f, "   movq $0, t%d\n", wcount->num);
               fprintf(f, "   push $10\n");
               fprintf(f, "   addq $1, t%d\n", wcount->num);
               fprintf(f, "   cmp $0, t%d\n", write->num);
               fprintf(f, "   jge positive%d\n", writecounter);
               fprintf(f, "   push $95\n");
               fprintf(f, "   addq $1, t%d\n", wcount->num);
               fprintf(f, "   neg t%d\n", write->num);
               fprintf(f, "   addq $1, t%d\n", write->num);
               fprintf(f, "   movq t%d, %%rax\n", write->num);
               fprintf(f, "   jmp writeloop%d\n", writecounter);
               fprintf(f, "positive%d:\n", writecounter);
               fprintf(f, "   movq t%d, %%rax\n", write->num);
               fprintf(f, "writeloop%d: \n", writecounter);
               fprintf(f, "   movq $0, %%rdx\n");
               fprintf(f, "   movq $10, %%rcx\n");
               fprintf(f, "   idivq %%rcx\n");
               fprintf(f, "   addq $48, %%rdx\n");
               fprintf(f, "   push %%rdx\n");
               fprintf(f, "   addq $1, t%d\n", wcount->num);
               fprintf(f, "   cmp $0, %%rax\n");
               fprintf(f, "   jne writeloop%d\n", writecounter);
               
               fprintf(f, "printloop%d:\n", writecounter);
               fprintf(f, "   movq $1, %%rax\n");
               fprintf(f, "   movq $1, %%rdi\n");
               fprintf(f, "   movq %%rsp, %%rsi\n");
               fprintf(f, "   movq $1, %%rdx\n");
               fprintf(f, "   syscall\n");
               fprintf(f, "   addq $8, %%rsp\n");
               fprintf(f, "   addq $-1, t%d\n", wcount->num);
               fprintf(f, "   jne printloop%d\n", writecounter);

               fprintf(f, "   pop t%d\n", wcount->num);
               fprintf(f, "   pop t%d\n", write->num);
               fprintf(f, "   pop %%rsi\n");
               fprintf(f, "   pop %%rdi\n");
               fprintf(f, "   pop %%rdx\n");
               fprintf(f, "   pop %%rcx\n");
               fprintf(f, "   pop %%rax\n");
               fprintf(f, "   movq %%rbp, %%rsp\n");
               fprintf(f, "   pop %%rbp\n");
               break;
          case allocateK:
               tvar = requestTemp();
               codeVAR(s->val.allocateS, fr, tvar);
               allocate(tvar, fr, s->val.allocateS);
               break;
          case allocOfLengthK:
               tvar = requestTemp();
               argument = requestTemp();
               codeVAR(s->val.allocOfLengthS.left, fr, tvar);
               codeEXP(s->val.allocOfLengthS.right, argument, fr);
               allocOfLength(s->val.allocOfLengthS.left, tvar, argument, fr);
               break;
          case assignK:
               tvar = requestTemp();
               argument = requestTemp();
               codeVAR(s->val.assignS.left, fr, tvar);
               codeEXP(s->val.assignS.right, argument, fr);
               fprintf(f, "   movq t%d, %%rcx\n", tvar->num);
               fprintf(f, "   movq t%d, 8(%%rcx)\n", argument->num);
               break;
          case ifK:
               argument = requestTemp();
               fprintf("if%d:\n", ifcount);
               codeEXP(s->val.ifS.left, argument, fr);
               fprintf("cmp $1, t%d\n", argument->num);
               fprintf("jne ifend%d\n", ifcount);
               codeSTATE(s->val.ifS.right, fr);
               fprintf("ifend%d:\n", ifcount);
               ifcount++;
               break;
          case ifElseK:
               argument= requestTemp();
               fprintf("if%d:\n", ifcount);
               codeEXP(s->val.ifElseS.left, argument, fr);
               fprintf("cmp $1, t%d\n", argument->num);
               fprintf("jne ifelse%d\n", ifcount);
               codeSTATE(s->val.ifElseS.middle, fr);
               fprintf("jmp ifend%d\n", ifcount);
               fprintf("ifelse%d:\n", ifcount);
               codeSTATE(s->val.ifElseS.right, fr);
               fprintf("ifend%d:\n", ifcount);
               ifcount++;
               break;
          case whileK:
               argument = requestTemp();
               fprintf(f, "while%d:\n", whilecount);
               codeEXP(s->val.whileS.left, argument, fr);
               fprintf(f, "cmp $1, t%d\n", argument->num);
               fprintf(f, "jne whileend%d\n", whilecount);
               codeSTATE(s->val.whileS.right, fr);
               fprintf(f, "jmp while%d\n", whilecount);
               fprintf(f, "whileend%d:\n", whilecount);
               whilecount++;
               break;
          case stateListK:
               codeSTATE_LIST(s->val.stateListS.left, fr);
               break;
     }
}

void allocOfLength(VAR *var, temp *tvar, temp *argument, frame *fr){
     Ty_ty *varty = getVarType(var, fr->c);
     while(varty->kind == Ty_name){
          varty = getSymbol(varty->u.name.table, varty->u.name.name)->value;
     }
     fprintf(f, "   movq t%d, %%rax\n", argument->num);
     switch (varty->u.array->kind)
     {
     case Ty_int:
          fprintf(f, "   movq $0, %%rdi\n");
          break;
     case Ty_bool:
          fprintf(f, "   movq $0, %%rdi\n");
          break;
     case Ty_record:
          fprintf(f, "   movq $1, %%rdi\n");
          break;
     case Ty_array:
          fprintf(f, "   movq $1, %%rdi\n");
          break;
     default:
          break;
     }

     fprintf(f, "   call allocL\n");
     fprintf(f, "   movq t%d, %%rdi\n", tvar->num);
     fprintf(f, "   movq %%rax, 8(%%rdi)\n");
}

void allocate(temp *tvar, frame *fr, VAR *v){
     int recSize=0;
     int recLength=0;
     int recIndex=0;
     Ty_fieldList *list;
     Ty_ty *ty = getVarType(v, fr->c);
     while(ty->kind == Ty_name){
          ty=getSymbol(ty->u.name.table, ty->u.name.name)->value;
     }
     switch(ty->kind){
          case Ty_record:
               recSize = 3;
               list = ty->u.record;
               while(list != NULL){
                    recSize = recSize +2;
                    recLength++;
                    list=list->tail;
               }
               list=ty->u.record;
               fprintf(f, "   movq $%d, %%rax\n", recSize);
               fprintf(f, "   call getMem\n");
               fprintf(f, "   movq t%d, %%rcx\n", tvar->num);
               fprintf(f, "   movq %%rax, 8(%%rcx)\n");
               fprintf(f, "   movq $0, (%%rax)\n");
               fprintf(f, "   movq $%d, 8(%%rax)\n", recSize);
               fprintf(f, "   movq $%d, 16(%%rax)\n", recLength);
               while(list != NULL){
                    ty = list->head->ty;
                    while(ty->kind == Ty_name){
                         ty=getSymbol(ty->u.name.table, ty->u.name.name)->value;
                    }

                    switch(ty->kind){
                         case Ty_int:
                              fprintf(f, "   movq $0, %d(%%rax)\n", (3+recIndex*2)*8 ); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         case Ty_bool:
                              fprintf(f, "   movq $0, %d(%%rax)\n", (3+recIndex*2)*8); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         case Ty_record:
                              fprintf(f, "   movq $1, %d(%%rax)\n", (3+recIndex*2)*8); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         case Ty_array:
                              fprintf(f, "   movq $1, %d(%%rax)\n", (3+recIndex*2)*8); //header
                              fprintf(f, "   movq $0, %d(%%rax)\n", (4+recIndex*2)*8 );
                              break;
                         default:
                              break;
                    }
                    recIndex++;
                    list = list->tail;
               }
               break;
          default:
               break;
     }


}

//expects length in %rax, value descriptor in %%rdi, and returns pointer to memory in rax
void allocLength(){
     fprintf(f, "allocL:\n");
     fprintf(f, "   movq %%rax, %%rsi\n");
     fprintf(f, "   movq $2, %%rcx\n");
     fprintf(f, "   imulq %%rcx\n");
     fprintf(f, "   addq $3, %%rax\n");
     fprintf(f, "   movq %%rax, %%rcx\n");
     fprintf(f, "   push %%rdi\n");
     fprintf(f, "   call getMem\n");
     fprintf(f, "   pop %%rdi\n");
     fprintf(f, "   movq $0, (%%rax)\n");
     fprintf(f, "   movq %%rcx, 8(%%rax)\n");
     fprintf(f, "   movq %%rsi, 16(%%rax)\n");
     fprintf(f, "   movq %%rax, %%rcx\n");
     fprintf(f, "   addq $24, %%rcx\n");
     fprintf(f, "allocLloop:\n");
     fprintf(f, "   cmp $0, %%rsi\n");
     fprintf(f, "   je allocLloopEnd\n");
     fprintf(f, "   movq %%rdi, (%%rcx)\n");
     fprintf(f, "   movq $0, 8(%%rcx)\n");
     fprintf(f, "   addq $16, %%rcx\n");
     fprintf(f, "   subq $1, %%rsi\n");
     fprintf(f, "   jmp allocLloop\n");
     fprintf(f, "allocLloopEnd:\n");
     fprintf(f, "   ret\n");
}