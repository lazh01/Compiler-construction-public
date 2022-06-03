#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "registers.h"
#include "symbol.h"
#include <string.h>
#include "memory.h"
#include "liveness.h"
#include "regallocation.h"
#include "graphcolor.h"

/*
currently only uses registers 12-15, to avoid syscalls overwriting contents. currently register might not be the same if temporary dies so code generation must be careful
might use graph coloring to assign specific register to temporary, then would be able to push and pop into same register.
*/
registers regs[4];
FILE *file;

void regAllocation(){
    livenessNode *node;
    node = livenessAnalysis();
    livenessNode *node1 = node;
    initRegisters();
    file = fopen("./final.s", "w");

    while(true){
        regCheck(node);
        if(node->succ->node == NULL){
            break;
        }else{
            node = node->succ->node;
        }
    }

    close(file);
    
    
    buildgraph(node1);
    color();
    writefile(node1);
}

void initRegisters(){
    for(int i = 0; i < 4; i++){
        sprintf(regs[i].reg, "%%r%d", i +12);
        regs[i].temp = NULL;
    }
}

void regCheck(livenessNode *node){
    if(node->def != NULL){
        requestRegister(node->def->buffer);
    }
    if(node->use != NULL){
        requestRegister(node->use->buffer);
        if(node->use->next != NULL){
            requestRegister(node->use->next->buffer);
        }
    }
    printReg(node);
    freeRegs(node);
}

void printReg(livenessNode *node){
    char* temp = malloc(sizeof(char)*10);
    int index = 0;
    if((node->def == NULL) && (node->use == NULL)){
        fprintf(file, "%s", node->line);
        return;
    }
    char *line = node->line;
    int unsigned i = 0;
    while(i < strlen(line)){
        if(line[i] == '@'){
            temp[index] = line[i];
            index++;
            i++;
            while((47 < (int) line[i]) && ( (int) line[i] < 58)){
                temp[index] = line[i];
                index++;
                i++;
            }
            temp[index] = '\0';
            for(int y = 0; y < 4; y++){
                if(regs[y].temp != NULL){
                    if(strcmp(regs[y].temp, temp) == 0){
                    fprintf(file, "%s" ,regs[y].reg);
                    }
                }
                
            }
            index = 0;
            free(temp);
            temp = malloc(sizeof(char) * 10);
        }else{
            fprintf(file, "%c", line[i]);
            i++;
        }
    }
}

void requestRegister(char *str){
    for(int i = 0; i < 4; i++){
        if(regs[i].temp != NULL){
            if(strcmp(regs[i].temp, str) == 0){
                return;
            }
        }
    }
    for(int i = 0; i < 4; i++){
        if(regs[i].temp == NULL){
            regs[i].temp = str;
            return;
        }
    }
    fprintf(stderr, "No available register.\n");
}

void freeRegs(livenessNode *node){
    stringBuffer *in = node->in;
    while(in != NULL){
        if(!isPresent(node->out, in->buffer)){
            unassignTemp(in->buffer);
        }
        in = in->next;
    }
}

void unassignTemp(char *str){
    for(int i = 0; i < 4; i++){
        if(regs[i].temp != NULL){
            if(strcmp(regs[i].temp, str) == 0){
                regs[i].temp = NULL;
                return;
            }
        }
    }
    fprintf(stderr, "No matching temporary.\n");
}