#include "symbol.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>

/*
OBS
passed names assumed to not be changed
duplicate names in put get dropped and returns original symbol
names assumed to be strings terminating on "\0"
*/


int Hash(char *str){
    int i = 0;
    int hash = 0;
    while((char) str[i] != '\0'){
        hash = hash + (int) str[i];
        hash = hash*2;
        i++;
    }
    return hash % HashSize;
}

SymbolTable *initSymbolTable(){
    SymbolTable *table = NEW(SymbolTable);
    return table;
}

SymbolTable *scopeSymbolTable(SymbolTable *t){
    SymbolTable *table = NEW(SymbolTable);
    table->next = t;
    return table;
}

/*
beware of contents of pointer to name changing
accounting for duplicate name, currently done by dropping the new symbol and returning the already existing symbol
name assumed to be string ending in "\0"
*/
SYMBOL *putSymbol(SymbolTable *t, char *name, int value){
    SYMBOL *s; 
    int i = Hash(name);
    if(t->table[i] == NULL){
        t->table[i] = NEW(SYMBOL);
        t->table[i]->name = name;
        t->table[i]->value = value;
        s = t->table[i];
    } else {
        SYMBOL *next = t->table[i];

        if(strcmp(name, next->name) == 0){
            return next;
        }

        while(next->next != NULL){
            next = next->next;
            if(strcmp(name, next->name) == 0){
                return next;
            }
        }

        next->next = NEW(SYMBOL);
        next->next->name = name;
        next->next->value = value;
        s = next->next;
    }
    return s;
}


//checks list of symbols with same hash value, returning pointer of symbol if match found.
//If not found, recursively calls next symboltable until match or root reached.
SYMBOL *getSymbol(SymbolTable *t, char *name){
    int i = Hash(name);
    SYMBOL *s = t->table[i];
    while(s != NULL){
        if(strcmp(name, s->name) == 0){
            return s;
        }
        s = s->next;
    }

    if(t->next != NULL){
        s = getSymbol(t->next, name);
        return s;
    } else {
        return NULL;
    }  
}

void dumpSymbolTable(SymbolTable *t){
    printf("New table \n");
    for(int i = 0; i<HashSize; i++){
        SYMBOL *s = t->table[i];
        while(s != NULL){
            printf("Name: %s", s->name);
            printf("Value is: %d \n", s->value);
            s = s->next;
        }
    }
    if(t->next != NULL){
        dumpSymbolTable(t->next);
    } 
}
