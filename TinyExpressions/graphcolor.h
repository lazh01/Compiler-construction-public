#ifndef __graphcolor_h
#define __graphcolor_h
#include "registers.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "memory.h"
#include "liveness.h"
#include <string.h>

#define numOfColors 4

typedef struct edgelist_ edgelist;
typedef struct nodelist_ nodelist;
typedef struct node_ node;
typedef struct edge_ edge;
typedef struct stack_ stack;

typedef struct stack_{
    node *object;
    stack *next;
};

typedef struct graph{
    nodelist *nodes;
    edgelist *edges;
    stack *stack;
}graph;

typedef struct node_{
    char *id;
    int onStack;
    int spill;
    int spillnumber;
    int color;
    edgelist *neighbors;
    int numOfNeighbors;
    int degreelimit;
}node;

typedef struct nodelist_{
    node *head;
    nodelist *tail;
}nodelist;

typedef struct edge_{
    node *from;
    node *to;
}edge;

typedef struct edgelist_{
    edge *head;
    edgelist *tail;
}edgelist;


void buildgraph(livenessNode *node);
void addnode(char *id);
void addedge(char *id1, char *id2);
edgelist *createEdgelist(edge *head, edgelist *tail);
nodelist *createNodelist(node *head, nodelist *tail);
node *createNode(char *id);
edge *createEdge(char *id1, char *id2);
node *getnode(char *id);
void simplifyNode(node *n);
int simplify();
void pushnode(node *n);
void color();
void spillNode(node *n);
node *popNode();
int checkColor(int spilled, int color, node *n);
void registerAllocation();
void writefile(livenessNode *lnode);
void printcolor(node *n);

#endif