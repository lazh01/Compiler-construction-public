#ifndef __frame_h
#define __frame_h

#include "tree.h"
#include "memory.h"
#include <string.h>
/* stackframe layout
Decending order arguments, each 16 bytes long.
Single link to enclosing frame 8 bytes
Return address 8 bytes
previous base pointer 8 bytes       <-stack pointer points here
argument count 8 bytes
local variable count 8 bytes
ascending order locals 16 bytes each
callee save registers 8 bytes
temporary values 8 bytes each
*/
typedef struct linkedlist_ linkedlist;
typedef struct frame_ frame;
typedef struct faccess_ faccess;



typedef struct frame_{
    int level;
    linkedlist *formal;
    linkedlist *local;
    linkedlist *func;
    frame *enclosing;
    COLLECTION *c;
} frame;

typedef struct faccess_{
    int depth;
    int offset;
} faccess;

faccess *getAccess(char *c, frame *f);


typedef struct linkedlist_{char *name; linkedlist *next;} linkedlist;

frame *createFrame(frame *outerframe);
linkedlist *createList(char *c);
void addArg(char *arg, frame *f);
void addVars(linkedlist *list, frame *f);
void addFunc(char *func, frame *f);
void initFrame(HEAD *h, BODY *b, frame *fr);
void buildAccess(char *c, frame *f, faccess *fa);
faccess *getAccess(char *c,frame *f);
void defineLocals(BODY *b, frame *f);
void frameDECL_LIST(DECL_LIST *dl, frame *f);
void frameDECLARATION(DECLARATION *d, frame *f);
void defineParams(HEAD *h, frame *f);
linkedlist *framePAR_DECL_LIST(PAR_DECL_LIST *p, frame *f);
linkedlist *frameVAR_DECL_LIST(VAR_DECL_LIST *vdl, frame *f, linkedlist *list);
char *frameVAR_TYPE(VAR_TYPE *v, frame *f);
int locCount(frame *f);
int argCount(frame *f);
int getFuncDepth(frame *f, char * func, int i);

#endif