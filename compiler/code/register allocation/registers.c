#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "registers.h"
#include "symbol.h"
#include <string.h>
#include "memory.h"
int nodeCount = 0; // Counter to assign node ID's to the livenessNodes
//nodeList *labels;
//////////////////////////////////////////////////////////////////////
//////  Function that opens/reads the file and scans each line  //////
//////////////////////////////////////////////////////////////////////
nodeList *scanFile(char *file){
    printf("scanFile\n");
    //labelList = initSymbolTable(); // List to store labels in
    FILE *fp;                                   // Pointer to temporary assembly file
    nodeList *ret = NEW(nodeList);
    char * buffer = NULL;                         // This and the next 2 variables are used for file reading
    size_t len = 0;                             //
    size_t read;  
    char *str;                              

    fp = fopen(file, "r");

    if (fp == NULL){                            // Error check for file opening
        printf("Could not open file %s",file);
        exit(1);
    }
    livenessNode *node = NEW(livenessNode);     // Node 0 created as a start for all the livenessNodes.
    node->id = nodeCount;                       // nodecount = 0 here
    nodeList *labels = NEW(nodeList);
    ret->node = node;
    ret->next = labels;
    livenessNode *nodeline;
    stringBuffer *forline;
    //unsigned int x = -1;                        // A variable to make a compatible unsigned to unsigned comparison
    while ((read = getline(&buffer, &len, fp)) != -1) {   // Reading each line
        //char *line = buffer;
        printf("testing buffer = %d\n", strlen(buffer));
        ret = newNode(ret->node, buffer, ret->next);  // Creating nodes for each line

        printf("1 node it::::: %d\n", node->id);
        //char *ptr = "lol";
        //printf("ptr = %d", &line);
        //free(buffer);
        //printf("%d\n", buffer);
        //buffer = buffer + sizeof(buffer);
    }
    //labelptrs(node);
    printf("2 node it::::: %d\n", node->id);
    //ret->node = node;
    livenessNode *tmp = ret->node;
    //ret->next = labels;
    printf("............next node  %d\n", tmp->id);
    printf("............label list %s\n", labels->label);
    return ret;   // Returns last node so that liveness analysis can work backwards through the nodes.
}

/////////////////////////////////////////////////////////////////////////////////////
//////  New node is created and prepared for the liveness analysis iterations  //////
/////////////////////////////////////////////////////////////////////////////////////
nodeList *newNode(livenessNode *predNode, char *txtline, nodeList *predlabels){
    printf("newNode 1\n");
    nodeList *ret = NEW(nodeList);

    //printf("newNode\n");
    // The nodes are put in a linked list, each pointing to the next and to the previous one.
    nodeCount++;
    // All information that can be gathered on the initial file scan added to the node.
    livenessNode *node = NEW(livenessNode);
    printf("newNode 2\n");
    printf("newNode 3\n");
    printf("newNode 4\n");
    nodeList *succ = NEW(nodeList);
    nodeList *prev = NEW(nodeList);
    node->id = nodeCount;
    prev->node = predNode;
    succ->node = node;
    node->pred = prev;
    //6char *newPtr = txtline;
    // Detailed information on what is stored in the node is in the header file.
    printf("newNode = %s\n", txtline);
    //node->line = txtline;
    nodeList *labels = NEW(nodeList);
    nodeList *next = NEW(nodeList);
    nodeList *back = NEW(nodeList);
    labels->node = node;
    back->prev = predlabels;
    next->next = labels;
    labels->prev = back;

    predNode->succ = succ;  // Assigning the "successor" node for the previous node
    predlabels->next = next;
    parseLine(txtline, node, labels); // Next up is parsing the line of code.
    ret->node = node;
    ret->next = labels;
    nodeList *tmp = ret->next;
    livenessNode *tmp2 = tmp->node;
    printf("................................ node id = %d, %d\n", node->id, tmp2->id);
    printf("filescan..... label: %s\n", labels->label);
    return ret;
}
//////////////////////////////////////////////////////////////////////////////////////
//////  Parses each line into strings seperated by a " " and put into an array  //////
//////////////////////////////////////////////////////////////////////////////////////
void parseLine(char *line, livenessNode *node, nodeList *labels){
    //printf("parseLine\n");
    char *buffer;           // One string where the line is broken up
    //char parsedLine[3];     // Array for the strings to be passed to the next function
    int count = 0;          // Count for inserting strings into the array 
    parsedLine *root;
    //char *jump = "j";
    //char *label = ":";

    buffer = strtok(line, " ");    // Line separated by " "

    parsedLine *str = NEW(parsedLine);
    char* operator;
    while (buffer && count <= 2) {  // count only goes up to '2' because we are looking for 3 words max
        int len = strlen(buffer);   // buffer length initialized at the start and after each increment
        int size = sizeof (buffer) / sizeof (char);  // To find number of elements+
        //char* operator;
        //char *stringStart = buffer[0];
        //char *stringEnd = buffer[strlen(buffer) - 1];
        //printf ("length = %d, and size = %d: \n", len, size);  
        //printf ("stringEnd: %s\n", buffer+len-1);
        //printf ("%s\n", buffer);          // process token
        char *rev;
        //buffer[(strlen(buffer)-1)]
        //strcpy(rev, buffer);
        //strrev(rev);
        //printf("rev: %s", rev);
        //printf("lastChar = %s, labelCheck = %d, labelmatch = %d\n",lastChar, labelCheck, labelmatch);
        //printf("label check: %s\n", buffer+len-2);
        //if (strcmp(buffer+len-2, ":")== 0){  // ':' at the end is the id for labels
        //    printf("fileScan label\n");
        //    operator = "label";      // initialize keyword for the next function
        //}

        if (buffer[(strlen(buffer)-2)] == ':' && count == 0){
            operator = "label";      // initialize keyword for the next function
        }
        else if(strncmp(buffer, "j", 1) == 0 && count == 0){ // "j" at the start of an operator is jump
            operator = "jump";
        }else if(count == 0){
            operator = buffer;
        }
        //str = newparsedLine(str, operator);
        str = newparsedLine(str, buffer);
        if(count == 0){
            root = str;
        }

        count++;
        buffer = strtok (NULL, " ");
        //while (buffer && *buffer == '\040')
        //    printf("debug 5\n");
        //    buffer++;
    }
    //node->op = getEnum(root->line);
    node->op = getEnum(operator);
    operatorhandler(root, node, labels);
}

parsedLine *newparsedLine(parsedLine *prev, char* line){
    //printf("parsedLine\n");
    parsedLine *str = NEW(parsedLine);
    
    str->line = line;
    str->prev = prev;
    prev->next = str;

    return str;
}

int getEnum(char *line){
    //printf("getEnum\n");
    // enum {movq, addq, subq, imulq, idivq, cmp, push, pull, jump, label} op;
    if(strcmp(line, "movq") == 0){
        return 0;
    }else if(strcmp(line, "addq") == 0){
        return 1;
    }else if(strcmp(line, "subq") == 0){
        return 2;
    }else if(strcmp(line, "imulq") == 0){
        return 3;
    }else if(strcmp(line, "idivq") == 0){
        return 4;
    }else if(strcmp(line, "cmp") == 0){
        return 5;
    }else if(strcmp(line, "push") == 0){
        return 6;
    }else if(strcmp(line, "pop") == 0){
        return 7;
    }else if(strcmp(line, "jump") == 0){
        return 8;
    }else if(strcmp(line, "label") == 0){
        return 9;
    }else{
        return 10;
    }
}

////////////////////////////////////////////////////////////////////////////////
//////  This function fills in the "use" and "def" variables in the node  //////
//////  depending on what the operator is.                                //////
////////////////////////////////////////////////////////////////////////////////
void operatorhandler(parsedLine *str, livenessNode *node, nodeList *labels){
    //printf("operatorhandler\n");
    //printf("operator = %s\n", line[0]);
    //printf("check 1\n");
    //parsedLine *first = str->next;
    //printf("check 2\n");
    //char *first->line = first->line;
    //printf("check 3\n");
    //parsedLine *second = first->next;
    //printf("check 4\n");
    //char *second->line = second->line;
    //printf("check 5\n");
    printf("%d\n", node->id);
    parsedLine *first;
    parsedLine *second;
    stringBuffer *usebuffer = NEW(stringBuffer);
    stringBuffer *usebuffer2 = NEW(stringBuffer);
    stringBuffer *defbuffer = NEW(stringBuffer);
    stringBuffer *def = node->def;
    stringBuffer *use = node->use;
    switch (node->op)
    {
    case movq:
        first = str->next;
        second = first->next;
        if(strncmp(first->line, "t", 1) == 0){ //  Temporary variables in code start with "t" and are number '1' or '2' in the array
            //node->use[0] = first->line;
            //strcpy(node->use[0], first->line);
            //printf("use = %s\n", node->use[0]);
            strncpy(usebuffer->buffer, first->line, strlen(first->line)-1);

        }if(strncmp(second->line, "t", 1) == 0){
            //node->def = second->line;
            //strcpy(node->def, second->line);
            //printf("def = %s\n", node->def);
            strncpy(defbuffer->buffer, second->line, strlen(second->line)-1);
        }
        usebuffer->next = NULL;
        defbuffer->next = NULL;
        node->use = usebuffer;
        node->def = defbuffer;
        break;

    case addq:
        first = str->next;
        second = first->next;
        if(strncmp(first->line, "t", 1) == 0){
            //node->use[0] = first->line;
            //strcpy(node->use[0], first->line);
            //printf("use = %s\n", node->use[0]);
            strncpy(usebuffer->buffer, first->line, strlen(first->line)-1);
        }if(strncmp(second->line, "t", 1) == 0){
            strncpy(usebuffer2->buffer, second->line, strlen(second->line)-1);
            usebuffer->next = usebuffer2;
            //node->use[1] = second->line;
            //strcpy(node->use[1], second->line);
            //printf("use = %s\n", node->use[1]);
            strncpy(defbuffer->buffer, second->line, strlen(second->line)-1);
            //node->def = second->line;
            //strcpy(node->def, second->line);
            //printf("def = %s\n", node->def);
        }
        usebuffer2->next = NULL;
        defbuffer->next = NULL;
        node->use = usebuffer;
        node->def = defbuffer;
        break;
    
    case subq:
        first = str->next;
        second = first->next;
        if(strncmp(first->line, "t", 1) == 0){
            //node->use[0] = first->line;
            //strcpy(node->use[0], first->line);
            //printf("use = %s\n", node->use[0]);
            strncpy(usebuffer->buffer, first->line, strlen(first->line)-1);
        }if(strncmp(second->line, "t", 1) == 0){
            strncpy(usebuffer2->buffer, second->line, strlen(second->line)-1);
            usebuffer->next = usebuffer2;
            //node->use[1] = second->line;
            //strcpy(node->use[1], second->line);
            //printf("use = %s\n", node->use[1]);
            strncpy(defbuffer->buffer, second->line, strlen(second->line)-1);
            //node->def = second->line;
            //strcpy(node->def, second->line);
            //printf("def = %s\n", node->def);
        }
        usebuffer2->next = NULL;
        defbuffer->next = NULL;
        node->use = usebuffer;
        node->def = defbuffer;
        break;

    case imulq:
        first = str->next;
        second = first->next;
        if(strncmp(first->line, "t", 1) == 0){
            //node->use[0] = first->line;
            //strcpy(node->use[0], first->line);
            //printf("use = %s\n", node->use[0]);
            strncpy(usebuffer->buffer, first->line, strlen(first->line)-1);
        }if(strncmp(second->line, "t", 1) == 0){
            strncpy(usebuffer2->buffer, second->line, strlen(second->line)-1);
            usebuffer->next = usebuffer2;
            //node->use[1] = second->line;
            //strcpy(node->use[1], second->line);
            //printf("use = %s\n", node->use[1]);
            strncpy(defbuffer->buffer, second->line, strlen(second->line)-1);
            //node->def = second->line;
            //strcpy(node->def, second->line);
            //printf("def = %s\n", node->def);
        }
        usebuffer2->next = NULL;
        defbuffer->next = NULL;
        node->use = usebuffer;
        node->def = defbuffer;
        break;
    
    case idivq:
        first = str->next;
        if(strncmp(first->line, "t", 1) == 0){
            //node->use[0] = first->line;
            strncpy(usebuffer->buffer, first->line, strlen(first->line)-1);
            usebuffer->next = NULL;
        }
        usebuffer->next = NULL;
        node->use = usebuffer;
        break;

    case cmp:
        first = str->next;
        second = first->next;
        if(strncmp(first->line, "t", 1) == 0){
            //node->use[0] = first->line;
            //strcpy(node->use[0], first->line);
            strncpy(usebuffer->buffer, first->line, strlen(first->line)-1);
        }if(strncmp(second->line, "t", 1) == 0){
            //node->use[1] = second->line;
            //strcpy(node->use[1], second->line);
            usebuffer->next = usebuffer2;
            strncpy(usebuffer2->buffer, second->line, strlen(second->line)-1);
        }
        usebuffer2->next = NULL;
        node->use = usebuffer;
        break;
    
    case push:
        first = str->next;
        if(strncmp(first->line, "t", 1) == 0){
            //printf("node use address = %p", node->use[0]);
            //node->use[0] = first->line;
            //strcpy(node->use[0], first->line);
            strncpy(usebuffer->buffer, first->line, strlen(first->line)-1);
            //printf("use = %s\n", node->use[0]);
        }
        node->use = usebuffer;
        break;

    case pop:
        first = str->next;
        if(strncmp(first->line, "t", 1) == 0){
            //node->def = first->line;
            //strcpy(node->def, first->line);
            strncpy(defbuffer->buffer, first->line, strlen(first->line)-1);
        }
        node->def = defbuffer;
        break;

    case jump:
        first = str->next;
        strncpy(node->jumpto, first->line, strlen(first->line)-1);
        printf("...........jumpto = %s\n", node->jumpto);
        break;
    
    case label:;
        strcpy(usebuffer->buffer, str->line);
        labels->label = usebuffer;
        //printf("........................................label: %s\n", labels->label);

        break;

    default:
        node->def = NULL;
        node->use = NULL;
        break;
    }
}

nodeList *getLabels(){
    //return labels;
}

void *labelptrs(livenessNode *node){
    nodeList *pred;
    for (int i = node->id; i > 0; i--){
        //printf("jumptolive = %s\n",node->jumpto);
        //jumpCheck(node, labels);
    }
}
void jumpChecks(livenessNode *node, nodeList *labels){
    nodeList *curr = node->succ;
    nodeList *pred;
    nodeList *newSucc = NEW(nodeList);
    livenessNode *newSuccNode;
    nodeList *newPred = NEW(nodeList);
    if(node->op == 8){
        printf("jumpto = %s\n", node->jumpto);
        printf("jump 1.6\n");
        curr->next = newSucc;
        while(labels->next != NULL){
            printf("jump 2\n");
            if(strncmp(node->jumpto, labels->label, strlen(node->jumpto)) == 0){
                printf("jump 3\n");
                newSucc->node = labels->node;
                printf("jump 4\n");
                newSuccNode = newSucc->node;
                printf("jump 5\n");
                pred = newSuccNode->pred;
                printf("jump 6\n");
                while(pred->next != NULL){
                    printf("jump 7\n");
                    pred = pred->next;
                }
                printf("jump 8\n");
                newPred->node = node;
                printf("jump 9\n");
                pred->next = newPred;
                printf("jump 10\n");
            }
            labels = labels->next;
            printf("jump 11\n");
        }
    }
}