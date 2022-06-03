#include "frame.h"


int const argdist = 24; //distance to 1 argument from frame pointer
int const localdist = 32; //distance in bytes to first local
int const size = 16; //size of values in bytes

int getFuncDepth(frame *f, char * func, int i){
    frame *fr = f;
    linkedlist *list = f->func;
    while( list != NULL){
        if(strcmp(func, list->name) == 0){
            return i;
        }
        list = list->next;
    }

    if(f->level>0){
        return getFuncDepth(f->enclosing, func, i++);
    }

    return -1;
}

int argCount(frame *f){
    linkedlist *l;
    int i = 0;
    l=f->formal;
    while(l != NULL){
        i++;
        l=l->next;
    }
    return i;
}

int locCount(frame *f){
    linkedlist *l;
    int i =0;
    l=f->local;
    while(l != NULL){
        i++;
        l=l->next;
    }
    return i;
}

faccess *getAccess(char *c,frame *f){
    faccess *fa;
    fa=NEW(faccess);
    fa->depth=0;
    buildAccess(c, f, fa);
    return fa;
}

void buildAccess(char *c, frame *f, faccess *fa){
    linkedlist *list;
    list = f->formal;
    int i = 0;
    while(list != NULL){
        if(strcmp(c, list->name) == 0){
            fa->offset=size*i+argdist;
            return;
        }
        i++;
        list = list->next;
    }
    
    i = 0;
    list = f->local;
    while(list != NULL){
        if(strcmp(c, list->name) == 0){
            fa->offset=size*i-localdist;
            return;
        }
        i--;
        list = list->next;
    }

    if(f->level != 0){
        fa->depth++;
        buildAccess(c,f->enclosing,fa);
        return;
    }

}



void initFrame(HEAD *h, BODY *b, frame *fr){
    if (h != NULL){
        defineParams(h, fr);
    }
    if(b != NULL){
        defineLocals(b, fr);
    }
    fr->c=b->c;
}

frame  *createFrame(frame *f){
    frame *nf;
    nf = NEW(frame);
    nf->enclosing=f;
    if(f==NULL){
        nf->level=0;
    } else {
        nf->level=f->level + 1;
    }
    nf->local=NULL;
    nf->func=NULL;
    nf->formal=NULL;
    return nf;
}

linkedlist *createList(char *c){
    linkedlist *list;
    list = NEW(linkedlist);
    list->name=c;
    return list;
}

void addVars(linkedlist *list, frame *f){
    linkedlist *l;

    if(f->local == NULL){
        f->local = list;
        return;
    }

    l=f->local;
    while(l->next != NULL){
        l=l->next;
    }
    l->next=list;
}

void addFunc(char *c, frame *f){
    linkedlist *list;

    if(f->func == NULL){
        f->func = createList(c);
        return;
    }

    list = f->func;
    while(list->next != NULL){
        list=list->next;
    }
    list->next=createList(c);
}

void defineLocals(BODY *b, frame *f){
    frameDECL_LIST(b->val.body.left, f);
}

void frameDECL_LIST(DECL_LIST *dl, frame *f){
     switch(dl->kind){
          case declListK:
               frameDECLARATION(dl->val.declListDL.left, f);
               frameDECL_LIST(dl->val.declListDL.right, f);
               break;
          case nilDK:
               break;
     }
}

void frameDECLARATION(DECLARATION *d, frame *f){
     switch(d->kind){
          case typeIdK:
               break;
          case declFuncK:
               addFunc(d->val.declFuncD->val.function.left->val.head.id, f);
               break;
          case declVarK:
               addVars(frameVAR_DECL_LIST(d->val.declVarD, f, NULL), f);
               break;
     }
}


void defineParams(HEAD *h, frame *f){
    f->formal = framePAR_DECL_LIST(h->val.head.left, f);
}

linkedlist *framePAR_DECL_LIST(PAR_DECL_LIST *p, frame *f){
     linkedlist *list;
     list=NULL;
     switch(p->kind){
          case nilPK:
               break;
          case vdlPK:
               list = frameVAR_DECL_LIST(p->val.vdecl_list.left, f, list);
               break;
     }
     return list;
}

linkedlist *frameVAR_DECL_LIST(VAR_DECL_LIST *vdl, frame *f, linkedlist *list){
     switch(vdl->kind){
          case listVDLK:
               list = createList(frameVAR_TYPE(vdl->val.vtype.left, f));
               list->next = frameVAR_DECL_LIST(vdl->val.listV.right, f, list->next);
               break;
          case vtK:
               list = createList(frameVAR_TYPE(vdl->val.vtype.left, f));
               break;
     }
     return list;
}

char *frameVAR_TYPE(VAR_TYPE *v, frame *f){
     return v->val.typeV.id;
}