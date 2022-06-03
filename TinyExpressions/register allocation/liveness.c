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
    nodeList *pred;
    nodeList *labels;
    nodeList *prevLabel;
    nodeList *ret = NEW(nodeList);
    ret = scanFile("./output.asm");
    node = ret->node;
    labels = ret->next;
    for (int i = node->id; i > 0; i--)
    {
        pred = node->pred;
        node = pred->node;
        labels = labels->prev;
        stringBuffer *buf = labels->label;
        jumpCheck(node, labels);
        stringBuffer *def = node->def;
        stringBuffer *use = node->use;
        stringBuffer *use2;
        if(use != NULL){
            use2 = use->next;
        }else{
            use2 = NULL;
        }
    }
    return node;
}
void jumpCheck(livenessNode *node, nodeList *labels){
    nodeList *curr = node->succ;
    nodeList *pred;
    nodeList *newSucc = NEW(nodeList);
    livenessNode *newSuccNode;
    nodeList *newPred = NEW(nodeList);
    stringBuffer *buffer;
    if(node->op == 8){
        curr->next = newSucc;
        while(labels->next != NULL){
            buffer = labels->label;
            if(buffer->buffer != NULL && strncmp(node->jumpto, buffer->buffer, strlen(node->jumpto)) == 0){
                newSucc->node = labels->node;
                newSuccNode = newSucc->node;
                pred = newSuccNode->pred;
                while(pred->next != NULL){
                    pred = pred->next;
                }
                newPred->node = node;
                pred->next = newPred;
            }
            labels = labels->next;
        }
    }
}

livenessNode *livenessAnalysis(){
    livenessNode *node = appendLabels();
    nodeList *succ;
    nodeList *pred;
    stringBuffer *intmp;
    stringBuffer *outtmp;
    stringBuffer *incheck;
    stringBuffer *outcheck;
    while(node->succ != NULL){
        succ = node->succ;
        node = succ->node;
    }
    int check = 0;
    int firstloop = 0;
    do{
        check = 0;
        for (int i = node->id; i > 0; i--){
            pred = node->pred;
            node = pred->node;
            intmp = node->in;
            outtmp = node->out;
            node->in = in(node);
            node->out = out(node);
            incheck = node->in;
            outcheck = node->out;
            if(intmp != NULL && incheck != NULL){
                while((intmp->next != NULL) && (incheck->next != NULL)){
                    if(strcmp(intmp->buffer, incheck->buffer) != 0){
                        check = 1;
                    }
                    intmp = intmp->next;
                    incheck = incheck->next;
                    if(intmp != NULL && incheck == NULL){
                        check = 1;
                    }else if(intmp == NULL && incheck != NULL){
                        check = 1;
                    }
                }
            }
            if(outtmp != NULL && outcheck != NULL){
                while(outtmp->next != NULL && outcheck->next != NULL){
                    if(strcmp(outtmp->buffer, outcheck->buffer) != 0){
                        check = 1;
                    }
                    outtmp = outtmp->next;
                    outcheck = outcheck->next;
                    if(outtmp != NULL && outcheck == NULL){
                        check = 1;
                    }else if(outtmp == NULL && outcheck != NULL){
                        check = 1;
                    }
                }
            }
        }
        while(node->succ != NULL){
            succ = node->succ;
            node = succ->node;
        }
        if(firstloop == 0){
            check = 1;
            firstloop = 1;
        }
    }while(check != 0);

    return node;
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
