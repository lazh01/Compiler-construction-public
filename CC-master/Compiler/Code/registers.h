#ifndef __registers_h
#define __registers_h

typedef struct livenessNode{
    int id;
    char line[100];
    struct parsedLine *pline;
    struct stringBuffer *use;
    struct stringBuffer *def;
    struct stringBuffer *out;
    struct stringBuffer *in;
    struct nodeList *succ;
    struct nodeList *pred;
    char jumpto[100];
    enum {movq, addq, subq, imulq, idivq, cmp, push, pop, jump, label, XOR, AND, OR, neg} op;
} livenessNode;

typedef struct stringBuffer{
    char buffer[100];
    struct stringBuffer *next;
    struct stringBuffer *prev;
} stringBuffer;

typedef struct nodeList{
    char label[100];
    struct livenessNode *node;
    struct nodeList *next;
    struct nodeList *prev;
} nodeList;

typedef struct parsedLine{
    char line[100];
    struct parsedLine *next;
} parsedLine;
livenessNode *initNode(char *buffer);
nodeList *initnodeList();
stringBuffer *initstringBuffer();
parsedLine *initparsedLine();
nodeList *scanFile(char *file);

char *getString(char *str);
parsedLine *parseLine(livenessNode *node);
void operatorhandler(livenessNode *node);
int operator(livenessNode *node);
void printer(livenessNode *node);
int getEnum(char *line);
#endif