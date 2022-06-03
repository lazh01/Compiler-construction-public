#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "registers.h"
#include "symbol.h"
#include <string.h>
#include "memory.h"
int nodeCount = 0;
nodeList *labels;

nodeList *scanFile(char *file){
    FILE *fp;
    nodeList *ret = NEW(nodeList);
    char * buffer = NULL;
    size_t len = 0;
    size_t read;  
    fp = fopen(file, "r");

    if (fp == NULL){
        fprintf(stderr,"Could not open file %s",file);
        exit(1);
    }
    livenessNode *temp;
    livenessNode *node;
    livenessNode *root;
    while ((read = getline(&buffer, &len, fp)) != -1) {

        // 1. making the node //
        ////////////////////////
        node = initNode(buffer);
        if(nodeCount == 1){
            node->pred = NULL;
            root = node;
        }else{
            temp->succ->node = node;
            node->pred->node = temp;
        }
        ////////////////////////

        // 2. parsing the line //
        /////////////////////////
        node->pline = parseLine(node);
        /////////////////////////

        // 3. get operand enum //
        /////////////////////////
        node->op = operator(node);
        /////////////////////////

        // 4. argument handler //
        /////////////////////////
        operatorhandler(node);
        /////////////////////////
        temp = node;
    }
    ret->node = root;
    ret->next = labels;
    return ret;
}



// 1. ///////////////////////////////
livenessNode *initNode(char *buffer){
    livenessNode *n = NEW(livenessNode);
    n->id = ++nodeCount;
    strcpy(n->line, buffer);
    n->pline = initparsedLine();
    n->use = NULL;
    n->def = NULL;
    n->out = NULL;
    n->in = NULL;
    n->succ = initnodeList();
    n->pred = initnodeList();
    return n;
}

nodeList *initnodeList(){
    nodeList *nl = NEW(nodeList);
    nl->next = NULL;
    nl->node = NULL;
    nl->prev = NULL;
    return nl;
}

stringBuffer *initstringBuffer(){
    stringBuffer *sb = NEW(stringBuffer);
    sb->next = NULL;
    sb->prev = NULL;
    return sb;
}
/////////////////////////////////////



// 2. ///////////////////////////////
parsedLine *parseLine(livenessNode *node){
    char *buffer;
    char tmpstr[100];
    parsedLine *root;
    parsedLine *temp;
    int count = 0;

    strcpy(tmpstr, node->line);
    buffer = strtok(tmpstr, " ");

    parsedLine *str = NEW(parsedLine);
    while (buffer) {
        str = initparsedLine();
        if(count == 0){
            root = str;
            strcpy(str->line, buffer);
        }else{
            temp->next = str;
            strncpy(str->line, buffer, strlen(buffer)-1);
        }
        temp = str;
        count++;
        buffer = strtok (NULL, " ");
    }
    return root;
}

parsedLine *initparsedLine(){
    parsedLine *pl = NEW(parsedLine);
    pl->next = NULL;
    return pl;
}
/////////////////////////////////////


// 3. ///////////////////////////////
int operator(livenessNode *node){
    parsedLine *pl = node->pline;
    char *op;
    if(pl->next == NULL && pl->line[(strlen(pl->line)-2)] == ':'){
        op = "label";
    }else if((pl->line[0] == 'j') || (strncmp(pl->line, "ca", 2)) == 0){
        op = "jump";
    }else{
        op = pl->line;
    }
    return getEnum(op);
}

int getEnum(char *line){

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
    }else if(strcmp(line, "XOR") == 0){
        return 10;
    }else if(strcmp(line, "AND") == 0){
        return 11;
    }else if(strcmp(line, "OR") == 0){
        return 12;
    }else if(strcmp(line, "neg") == 0){
        return 13;
    }else{
        return 14;
    }
}
/////////////////////////////////////



// 4. ///////////////////////////////
char *getString(char *str){
    char *ret = malloc(sizeof(char)*100);
    int retpos = 0;
    for (unsigned int i = 0; i < strlen(str); i++){
        if( str[i] == '('  && str[i+1] == '@'){
            while(str[i] != ')'){
                i++;
                ret[retpos] = str[i];
                retpos++;  
            }
            ret[retpos] = '\0';
        }
    }
    if(strncmp(ret, "@", 1) != 0){
        strcpy(ret, str);
    }
    return ret;
}

void operatorhandler(livenessNode *node){//REFACTOR!!!

    parsedLine *line = node->pline;
    char first[30];
    char second[30];
    nodeList *tmp;
    stringBuffer *s;

    switch (node->op)
    {
    case movq:

        strcpy(first, getString(line->next->line));
        strcpy(second, getString(line->next->next->line));
        
        if(strncmp(first, "@", 1) == 0){
            node->use = initstringBuffer();
            strcpy(node->use->buffer, first);
        }if(strncmp(second, "@", 1) == 0){
            node->def = initstringBuffer();
            strcpy(node->def->buffer, second);
        }
        break;

    case addq:
        strcpy(first, getString(line->next->line));
        strcpy(second, getString(line->next->next->line));
        if(strncmp(first, "@", 1) == 0){
            s = initstringBuffer();
            s->next=node->use;
            node->use=s;
            strcpy(node->use->buffer, first);
        }if(strncmp(second, "@", 1) == 0){
            if(strncmp(first, "@", 1) == 0){
                node->use->next = initstringBuffer();
                strcpy(node->use->next->buffer, second);
            }else{
                node->use = initstringBuffer();
                strcpy(node->use->buffer, second);
            }
        }
        break;
    
    case subq:
        strcpy(first, getString(line->next->line));
        strcpy(second, getString(line->next->next->line));
        if(strncmp(first, "@", 1) == 0){
            s = initstringBuffer();
            s->next=node->use;
            node->use=s;
            strcpy(node->use->buffer, first);
        }if(strncmp(second, "@", 1) == 0){
            if(strncmp(first, "@", 1) == 0){
                node->use->next = initstringBuffer();
                strcpy(node->use->next->buffer, second);
            }else{
                node->use = initstringBuffer();
                strcpy(node->use->buffer, second);
            }
        }
        break;

    case imulq:
        strcpy(first, getString(line->next->line));
        if(strncmp(first, "@", 1) == 0){
            s = initstringBuffer();
            s->next=node->use;
            node->use=s;
            strcpy(node->use->buffer, first);
        }
        if(line->next->next != NULL){
            strcpy(second, getString(line->next->next->line));
            if(strncmp(second, "@", 1) == 0){
                if(strncmp(first, "@", 1) == 0){
                    node->use->next = initstringBuffer();
                    strcpy(node->use->next->buffer, second);
                }else{
                    node->use = initstringBuffer();
                    strcpy(node->use->buffer, second);
            }
        }
        }
        break;
    
    case idivq:
        strcpy(first, getString(line->next->line));
        if(strncmp(first, "@", 1) == 0){
            node->use = initstringBuffer();
            strcpy(node->use->buffer, first);
        }
        break;

    case cmp:
        strcpy(first, getString(line->next->line));
        strcpy(second, getString(line->next->next->line));
        if(strncmp(first, "@", 1) == 0){
            s = initstringBuffer();
            s->next=node->use;
            node->use=s;
            strcpy(node->use->buffer, first);
        }if(strncmp(second, "@", 1) == 0){
            if(strncmp(first, "@", 1) == 0){
                node->use->next = initstringBuffer();
                strcpy(node->use->next->buffer, second);
            }else{
                node->use = initstringBuffer();
                strcpy(node->use->buffer, second);
            }
        }
        break;
    
    case push:
        strcpy(first, getString(line->next->line));
        if(strncmp(first, "@", 1) == 0){
            node->use = initstringBuffer();
            strcpy(node->use->buffer, first);
        }
        break;

    case pop:
        strcpy(first, getString(line->next->line));
        if(strncmp(first, "@", 1) == 0){
            node->def = initstringBuffer();
            strcpy(node->def->buffer, first);
        }
        break;

    case jump:
        strcpy(first, getString(line->next->line));
        strcpy(node->jumpto, first);
        break;
    
    case label:
        tmp = initnodeList();
        tmp->node = node;
        tmp->next = labels;
        strncpy(tmp->label, line->line, strlen(line->line) -1);
        labels = tmp;
        break;

    case XOR:
        strcpy(first, getString(line->next->line));
        strcpy(second, getString(line->next->next->line));
        if(strncmp(first, "@", 1) == 0){
            s = initstringBuffer();
            s->next=node->use;
            node->use=s;
            strcpy(node->use->buffer, first);
        }if(strncmp(second, "@", 1) == 0){
            if(strncmp(first, "@", 1) == 0){
                node->use->next = initstringBuffer();
                strcpy(node->use->next->buffer, second);
            }else{
                node->use = initstringBuffer();
                strcpy(node->use->buffer, second);
            }
        }
        break;

    case AND:
        strcpy(first, getString(line->next->line));
        strcpy(second, getString(line->next->next->line));
        if(strncmp(first, "@", 1) == 0){
            s = initstringBuffer();
            s->next=node->use;
            node->use=s;
            strcpy(node->use->buffer, first);
        }if(strncmp(second, "@", 1) == 0){
            if(strncmp(first, "@", 1) == 0){
                node->use->next = initstringBuffer();
                strcpy(node->use->next->buffer, second);
            }else{
                node->use = initstringBuffer();
                strcpy(node->use->buffer, second);
            }
        }
        break;

    case OR:
        strcpy(first, getString(line->next->line));
        strcpy(second, getString(line->next->next->line));
        if(strncmp(first, "@", 1) == 0){
            s = initstringBuffer();
            s->next=node->use;
            node->use=s;
            strcpy(node->use->buffer, first);
        }if(strncmp(second, "@", 1) == 0){
            if(strncmp(first, "@", 1) == 0){
                node->use->next = initstringBuffer();
                strcpy(node->use->next->buffer, second);
            }else{
                node->use = initstringBuffer();
                strcpy(node->use->buffer, second);
            }
        }
        break;

    case neg:
        strcpy(first, getString(line->next->line));
        if(strncmp(first, "@", 1) == 0){
            node->use = initstringBuffer();
            strcpy(node->use->buffer, first);
        }
        break;

    default:
        break;
    }
}
/////////////////////////////////////

// Extra for debugging //////////////
void printer(livenessNode *node){
    fprintf(stderr,"node->id = %d\n", node->id);
    fprintf(stderr,"node->line = %s", node->line);
    parsedLine *tmp = node->pline;
    while(tmp->line != NULL){
        fprintf(stderr,"node->pline = %s\n", tmp->line);
        tmp = tmp->next;
    }
    if(node->use != NULL){
        fprintf(stderr,"node->use = %s", node->use->buffer);
        if(node->use->next != NULL){
            fprintf(stderr," %s", node->use->next->buffer);
        }fprintf(stderr,"\n");
    }if(node->def != NULL){
        fprintf(stderr,"node->def = %s\n", node->def->buffer);
    }
    fprintf(stderr,"node->jumpto = %s\n", node->jumpto);
    fprintf(stderr,"node->op = %d\n", node->op);

    fprintf(stderr,"\n");
}
/////////////////////////////////////