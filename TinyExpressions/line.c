#include "line.h"
#include "memory.h"
#include "stdio.h"

line *currentline;

void printLines(line *root){
    line *lin = root;
    while(lin != NULL){
        printline(lin);
        lin = lin->next;
    }
}

void printline(line *line){
    switch(line->kind){
        case other:
            fprintf(stderr, line->operand);
    }

    fprintf(stderr, "\n");
}

line *makeLine(int type, char *op, arg *src, arg *dst, int args, int srckind, int dstkind){
    line *newline = NEW(line);
    newline->args=args;
    newline->dest=dst;
    newline->kind=type;
    newline->operand=op;
    newline->source=src;
    newline->skind=srckind;
    newline->dkind=dstkind;
    
    if(currentline == NULL){
        currentline = newline;
    } else {
        currentline->next=newline;
        currentline=newline;
    }
    
    return newline;
}

arg *makeTempArg(int ismem, temp *tem, int offset){
    arg *a=NEW(arg);
    a->regkind=tempo;
    a->memkind=ismem;
    a->memoffset=offset;
    a->u.tmp=tem;
    return a;
}

arg *makeRegArg(int ismem, reg *r, int offset){
    arg *a=NEW(arg);
    a->regkind=regi;
    a->memkind=ismem;
    a->memoffset=offset;
    a->u.reg=r;
    return a;
}

arg *makeLitArg(int ismem, char *name, int offset){
    arg *a=NEW(arg);
    a->regkind=lit;
    a->memkind=ismem;
    a->memoffset=offset;
    a->u.literal==name;
    return a;
}

reg *makeReg(char *id){
    reg *r = NEW(reg);
    r->name=id;
}