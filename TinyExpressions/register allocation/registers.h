#ifndef __registers_h
#define __registers_h
#include "symbol.h"

typedef struct livenessNode{
    int id;                    // -node id
    //struct stringbuffer *line;                 // -Line of code is stored in node
    struct stringBuffer *use;               // -Variables used in node
    struct stringBuffer *def;                  // -Variables defined in node
    struct stringBuffer *out;                  // Live variables going out of node
    struct stringBuffer *in;                   // Live variables coing in to node
    struct nodeList *succ;  // -The next node(line in code)
    struct nodeList *pred;  // -The previous node
    char jumpto[100];
    enum {movq, addq, subq, imulq, idivq, cmp, push, pop, jump, label} op;
} livenessNode;

typedef struct stringBuffer{
    char buffer[100];
    struct stringBuffer *next;
    struct stringBuffer *prev;
} stringBuffer;

typedef struct nodeList{
    struct stringBuffer *label;
    struct livenessNode *node;
    struct nodeList *next;
    struct nodeList *prev;
} nodeList;

typedef struct parsedLine{
    char* line;
    struct parsedLine *next;
    struct parsedLine *prev;
} parsedLine;

int getEnum(char *line);
parsedLine *newparsedLine(parsedLine *prev, char* line);
nodeList *scanFile(char *file);
nodeList *newNode(livenessNode *predNode, char *txtline, nodeList *predlabels);
void operatorhandler(parsedLine *str, livenessNode *node, nodeList *labels);
char nodeOut();
char nodeIn();
void parseLine(char *line, livenessNode *node, nodeList *labels);
nodeList *getLabels();
void *labelptrs(livenessNode *node);
void jumpChecks(livenessNode *node, nodeList *labels);

void readFile();

#endif