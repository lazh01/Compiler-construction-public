#ifndef __regallocation_h
#define __regallocation_h
#include "registers.h"

typedef struct registerList{
    struct stringBuffer *name;
    struct stringBuffer *tmp;
    int inUse;
    struct registerList *next;
} registerList;

registerList *initRegs(registerList *prevReg, char *name);
void regAllocation();
void *findreg(registerList *regs, char *str);
bool regisPresent (registerList *head, char data[]);
#endif