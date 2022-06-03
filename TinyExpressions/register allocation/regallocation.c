#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "registers.h"
#include "symbol.h"
#include <string.h>
#include "memory.h"
#include "liveness.h"
#include "regallocation.h"
/*
typedef struct registerList{
    struct stringBuffer *name;
    struct stringBuffer *tmp;
    int inUse;
    struct registerList *next;
} registerList;
*/
registerList *initRegs(registerList *prevReg, char *name){
    registerList *reg = NEW(registerList);
    prevReg->next = reg;
    strcpy(reg->name->buffer, name);
    strcpy(reg->tmp->buffer, "unassigned");
    reg->inUse = 0;
    return reg;
}

void *findreg(registerList *regs, char *str){
    printf("findreg 1\n");
    while(regs->next != NULL){
        printf("findreg 2\n");
        if(regs->inUse == 0){
            printf("findreg 3\n");
            strcpy(regs->tmp, str);
            printf("findreg 4\n");
            regs->inUse = 1;
            printf("findreg 5\n");
            return;
        }
        printf("findreg 6\n");
        regs = regs->next;
        printf("findreg 7\n");
    }
}

void regAllocation(){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    char *p;
    FILE * fPtr = fopen("final.txt", "w");
    fp = fopen("./output.asm", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    livenessNode *node = NEW(livenessNode);
    node = livenessAnalysis();
    printf("regAllo 1\n");
    registerList *regs = NEW(registerList);
    printf("regAllo 2\n");
    regs = initRegs(regs, "%%r11");
    printf("regAllo 3\n");
    registerList *reg = NEW(registerList);
    reg = regs;
    regs = initRegs(regs, "%%r12");
    regs = initRegs(regs, "%%r13");
    regs = initRegs(regs, "%%r14");
    regs = initRegs(regs, "%%r15");
    stringBuffer *test = regs->name;
    printf("test printbelow\n");
    printf("test print: %s\n", test->buffer);

    nodeList *pred = NEW(nodeList);
    nodeList *succ = NEW(nodeList);
    stringBuffer *inlist = NEW(stringBuffer);
    stringBuffer *outlist = NEW(stringBuffer);
    while(node->pred != NULL){
        pred = node->pred;
        node = pred->node;
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        int counter = 0;
        printf("reg allo node id = %d\n", node->id);
        if(node->succ != NULL){
            if(node->in != NULL){
                printf("check 1\n");
                inlist = node->in;
                while(inlist->next != NULL){
                    if(inlist->buffer != NULL){
                        if(!regisPresent(regs, inlist->buffer)){
                            findreg(regs, inlist->buffer);
                        }
                    }
                    inlist = inlist->next;
                }
            }printf("check 2\n");
            if(node->out != NULL){
                printf("check 2.1\n");
                outlist = node->out;
                printf("check 2.2\n");
                while(outlist->next != NULL){
                    printf("check 2.3\n");
                    if(outlist->buffer != NULL){
                        printf("check 2.4\n");
                        if(!regisPresent(regs, outlist->buffer)){
                            printf("check 2.5\n");
                            findreg(regs, outlist->buffer);
                            printf("check 2.6.\n");
                        }
                    }
                    outlist = outlist->next;
                }
            }
        }printf("check 3\n");
    
        p = strtok (line," ");
        while (p!= NULL)
        {
            printf("check 4\n");
            if(counter == 0){
                fputs(p, fPtr);
            }else if(counter == 1){
                fputs(" ", fPtr);
                if(strncmp(p, "t", 1) == 0){
                    registerList *t = regs; 
	                while (t != NULL){ 
		                if (strncmp(t->tmp, p, t->tmp) == 0) 
			                fputs(t->name, fPtr);
                            fputs(", ", fPtr);
		                t = t->next; 
	                } 
                }else{
                    fputs(p, fPtr);
                    fputs(" ", fPtr);
                }
            }else if(counter == 2){
                fputs(" ", fPtr);
                if(strncmp(p, "t", 1) == 0){
                    registerList *t = regs; 
	                while (t != NULL){ 
		                if (strncmp(t->tmp, p, t->tmp) == 0) 
			                fputs(t->name, fPtr);
                            fputs("\n", fPtr);
		                t = t->next; 
	                } 
                }else{
                    fputs(p, fPtr);
                    fputs("\n", fPtr);
                }
            }
            p = strtok (NULL, " ");
            counter++;
        }
        succ = node->succ;
        node = succ->node;
        
    }
    //succ = node->succ;
    //node = succ->node;
}

bool regisPresent(registerList *head, char data[]){ 
    printf("regisPresent 1\n");
	registerList *t = head; 
    stringBuffer *str;
    printf("regisPresent 2\n");
	while (t != NULL) {
        str = t->tmp;
        //printf("regisPresent 3, %d\n", t->tmp); 
        if(str->buffer != NULL){
            printf("regisPresent 3.5\n");
		    if (strcmp(str->buffer, data) == 0){
                printf("regisPresent 4\n");
			    return 1; 
            }
        }
        printf("regisPresent 5\n");
		t = t->next; 
        printf("regisPresent 6\n");
	} 
    printf("regisPresent 7\n");
	return 0; 
} 
