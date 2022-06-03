#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "registers.h"
#include "symbol.h"
#include <string.h>
#include "memory.h"
#include "liveness.h"

livenessNode *appendLabels(){
    livenessNode *node;
    nodeList *labels;
    nodeList *ret = scanFile("./output.asm");
    node = ret->node;
    labels = ret->next;
    do{
        node = node->succ->node;
        if(node->op == 8){
            jumpCheck(node, labels);
        }
    }while (node->succ->node != NULL);
    return node;
}

void jumpCheck(livenessNode *node, nodeList *labels){
    nodeList *newSucc;
    while(labels != NULL){
        if(strncmp(node->jumpto, labels->label, strlen(node->jumpto)) == 0){
            newSucc = initnodeList();
            node->succ->next = newSucc;
            newSucc->node = labels->node;
        }
        if(labels->next == NULL){
            break;
        }else{
            labels = labels->next;
        }
    }
}

livenessNode *livenessAnalysis(){
    livenessNode *node = appendLabels();
    livenessNode *root = node;
    livenessNode *top;
    stringBuffer *intmp;
    stringBuffer *outtmp;
    stringBuffer *incheck;
    stringBuffer *outcheck;
    int check = 0;
    int firstloop = 0;
    int iteration = 1;
    do{
        check = 0;
        for (int i = node->id; i > 0; i--){
            if(node->pred != NULL){
                node = node->pred->node;
            }
            intmp = node->in;
            outtmp = node->out;
            node->in = in(node);
            node->out = out(node);
            incheck = node->in;
            outcheck = node->out;
            fprintf(stderr,"line no: %d\n", node->id);
            if(intmp->buffer != NULL){
                fprintf(stderr," -intmp: %s", intmp->buffer);
                if(intmp->next != NULL){
                    fprintf(stderr," %s", intmp->next->buffer);
                }fprintf(stderr,"\n");
            }
            if(incheck->buffer != NULL){
                fprintf(stderr," -incheck: %s", incheck->buffer);
                if(incheck->next != NULL){
                    fprintf(stderr," %s", incheck->next->buffer);
                }fprintf(stderr,"\n");
            }if(outtmp->buffer != NULL){
                fprintf(stderr," -outtmp: %s", outtmp->buffer);
                if(outtmp->next != NULL){
                    fprintf(stderr," %s", outtmp->next->buffer);
                }fprintf(stderr,"\n");
            }
            if(outcheck->buffer != NULL){
                fprintf(stderr," -outcheck: %s", outcheck->buffer);
                if(outcheck->next != NULL){
                    fprintf(stderr," %s", outcheck->next->buffer);
                }fprintf(stderr,"\n");
            }
            if(intmp->buffer != NULL && incheck->buffer != NULL){
                //fprintf(stderr," -intmp: %s\n", intmp->buffer);
                //fprintf(stderr," -incheck: %s\n", incheck->buffer);
                while((intmp != NULL) && (incheck != NULL)){
                    if(strcmp(intmp->buffer, incheck->buffer) != 0){
                        check = 1;
                    }
                    intmp = intmp->next;
                    incheck = incheck->next;
                    if(intmp == NULL ^ incheck == NULL){
                        check = 1;
                    }
                }
            } else if(intmp->buffer != NULL ^ incheck->buffer != NULL){
                check = 1;
            }
            if(outtmp->buffer != NULL && outcheck->buffer != NULL){
                //fprintf(stderr," -outtmp: %s\n", outtmp->buffer);
                //fprintf(stderr," -outcheck: %s\n", outcheck->buffer);
                while(outtmp != NULL && outcheck != NULL){
                    if(strcmp(outtmp->buffer, outcheck->buffer) != 0){
                        check = 1;
                    }
                    outtmp = outtmp->next;
                    outcheck = outcheck->next;
                    if(outtmp == NULL ^ outcheck == NULL){
                        check = 1;
                    }
                }
            } else if(outtmp->buffer != NULL ^ outcheck->buffer != NULL){
                check = 1;
            }
        }
        if(firstloop == 0){
            top = node;
            check = 1;
            firstloop = 1;
        }fprintf(stderr,"iteration: %d\n", iteration++);
        node = root;
        fprintf(stderr,"check print: %d\n", check);
    }while(check != 0);
    return top;
}

stringBuffer *in(livenessNode *node){
    stringBuffer *ret = NEW(stringBuffer);
    stringBuffer *right = NEW(stringBuffer);
    right = getSub(node->out, node->def);
    ret = getUnion(node->use, right);
    return ret;
}
stringBuffer *out(livenessNode *node){
    stringBuffer *ret = NEW(stringBuffer);
    stringBuffer *tmp = NEW(stringBuffer);
    nodeList *succ = node->succ;
    livenessNode *succNode = succ->node;
    ret = succNode->in;
    succ = succ->next;
    if(succ != NULL && succ->node != NULL){
        succNode = succ->node;
        tmp = succNode->in;
        ret = getUnion(ret, tmp);
    }
    return ret;
}

stringBuffer *getUnion(stringBuffer *head1, stringBuffer *head2) 
{ 
	stringBuffer *result = NULL; 
	stringBuffer *t1 = head1, *t2 = head2; 

	while (t1 != NULL) { 
		insert(&result, t1->buffer); 
		t1 = t1->next; 
	} 

	while (t2 != NULL) { 
		if (!isPresent(result, t2->buffer)) 
			insert(&result, t2->buffer); 
		t2 = t2->next; 
	} 

	return result; 
} 
stringBuffer *getSub(stringBuffer *head1, stringBuffer *head2) 
{ 
	stringBuffer *result = NULL; 
	stringBuffer *t1 = head1, *t2 = head2; 

	while (t1 != NULL) { 
        if (!isPresent(t2, t1->buffer)) 
			insert(&result, t1->buffer); 
		t1 = t1->next;
	} 

	return result; 
} 

void insert(stringBuffer** head_ref, char *new_data) 
{ 
	struct stringBuffer *new_node = (struct stringBuffer*) malloc(sizeof(struct stringBuffer)); 
    strcpy(new_node->buffer, new_data);

	/* link the old list off the new node */
	new_node->next = (*head_ref); 

	/* move the head to point to the new node */
	(*head_ref) = new_node; 
} 

/* A utility function that returns true if data is 
present in linked list else return false */
bool isPresent (stringBuffer *head, char *data) 
{ 
	stringBuffer *t = head; 
	while (t != NULL) 
	{ 
		if (strcmp(t->buffer, data) == 0) 
			return 1; 
		t = t->next; 
	} 
	return 0; 
} 
