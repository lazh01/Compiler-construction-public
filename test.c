#include "symbol.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>


/*
Tests getSymbol for returning the earliest matching symbol from the path from
the current hash table to the hash table in root
*/
int test_search(){
    printf("Search test");
    printf("Entering first scope\n");
    SymbolTable *t = initSymbolTable();
    printf("putSymbol(t, Henry, 25)\n");
    putSymbol(t, "Henry", 25);
    printf("Entering second scope\n");
    t = scopeSymbolTable(t);
    printf("putSymbol(t, Henry, 35)\n");
    putSymbol(t, "Henry", 35);
    printf("Entering third scope\n");
    t = scopeSymbolTable(t);
    printf("Get Henry from current scope\n");
    SYMBOL *s = getSymbol(t, "Henry");
    printf("Returned %s %d \n",s->name,s->value);
    if(s->value != 35){
        return -1;
    }

    return 0;
}



/*
Tests that puts of matching symbols in same table are dropped
*/
int test_duplicate(){
    SymbolTable *t = initSymbolTable();
    putSymbol(t, "test", 23);
    putSymbol(t, "test", 35);
    SYMBOL *s = getSymbol(t, "test");
    if(s->value != 23){
        return -1;
    }
    return 0;
}


/*
Builds a branching tree and verifies that other branches are not reached when calling getSymbol()
*/
int test_struct(){
    SymbolTable *root = initSymbolTable();
    SymbolTable *t1[3];
    for(int i = 0; i<3; i++){
        t1[i] = scopeSymbolTable(root);
    }
    SymbolTable *t2[4];
    t2[0] = scopeSymbolTable(t1[0]);
    for(int i = 1; i<4; i++){
        t2[i]=scopeSymbolTable(t1[1]);
    }
    SymbolTable *t3[2];
    for(int i = 0; i<2; i++){
        t3[i]=scopeSymbolTable(t2[2]);
    }
    putSymbol(root, "test", 100);
    putSymbol(t1[0], "test", 35);
    putSymbol(t1[2], "test", 42);
    putSymbol(t2[1], "test", 56);
    putSymbol(t2[3], "test", 23);
    putSymbol(t3[1], "test", 300);
    SYMBOL *s = getSymbol(t3[0], "test");
    if(s->value != 100){
        return -1;
    }
    return 0;
}



/*
Tests for putting symbol in a table
*/
int test_initSymbolTable(){

    SYMBOL *test = NEW(SYMBOL);
    test->name = "test";
    test->value = 10;
    test->next = NULL;

    //initSymbolTable();
    SymbolTable *table = initSymbolTable();
    SymbolTable *table2 = initSymbolTable();

    table->table[0] = test;
    table->next = table2;

    if (strcmp(table->table[0]->name, "test") != 0){
        return -1;
    }
    if ((table->table[0])->value != 10){
        return -1;
    }
    if ((table->table[0])->next != NULL){
        return -1;
    }
    return 0;
}
/*
Tests whether scopeSystemTable properly assigns the declared table as next
*/
int test_scopeSymbolTable(){
    SymbolTable *table = NEW(SymbolTable);
    SymbolTable *table2 = scopeSymbolTable(table);

    if((table2->next) != table){
        return -1;
    }

    return 0;
}

int main() {
    if(test_initSymbolTable()==0){
        printf("initSymbolTable test SUCCESSFUL\n");
    }else{
        printf("initSymbolTable test FAILED\n");
    }

    if(test_scopeSymbolTable()==0){
        printf("scopeSymbolTable test SUCCESSFUL\n");
    }else{
        printf("scopeSymbolTable test FAILED\n");
    }

    if(test_duplicate()==0){
        printf("Duplicate test SUCCESFUL\n");
    } else {
        printf("Duplicate test FAILED\n");
    }

    if(test_search()==0){
        printf("Search test SUCCESFUL\n");
    } else {
        printf("Search test FAILED\n");
    }

    if(test_struct()==0){
        printf("Structure test SUCCESFUL\n");
    } else {
        printf("Structure test FAILED\n");
    }

    return 0;
}