#ifndef __liveness_h
#define __liveness_h
#include "registers.h"
#include<stdbool.h> 


livenessNode *appendLabels();
void jumpCheck(livenessNode *node, nodeList *labels);
livenessNode *livenessAnalysis();
stringBuffer *in(livenessNode *node);
stringBuffer *out(livenessNode *node);
void insert(stringBuffer** head_ref, char *new_data); 
bool isPresent(stringBuffer *head, char *data); 
stringBuffer *getUnion(stringBuffer *head1, stringBuffer *head2);
stringBuffer *getSub(stringBuffer *head1, stringBuffer *head2); 

#endif