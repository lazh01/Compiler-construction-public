#ifndef __regallocation_h
#define __regallocation_h
#include "registers.h"

typedef struct registers{
    char reg[5];
    char *temp;
} registers;

void printReg(livenessNode *node);

void regAllocation();
void initRegisters();
void requestRegister(char *str);
void freeRegs(livenessNode *node);
void unassignTemp(char *str);
void regCheck(livenessNode *node);
#endif