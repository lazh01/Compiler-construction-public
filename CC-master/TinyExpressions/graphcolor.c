#include "graphcolor.h"


graph *g;
FILE *file;
int spillcount = 0;

void registerAllocation(){
    livenessNode *node;
    node = livenessAnalysis();
    file = fopen("./final.s", "w");
    buildgraph(node);
    color();
    while(true){
        writefile(node);
        if(node->succ->node == NULL){
            break;
        }else{
            node = node->succ->node;
        }
    } 
}

/*void pushlive(stringBuffer *in){
    if(in == NULL){
        return;
    }
    fprintf(file, "   push ");
    printcolor(getnode(in->buffer));
    fprintf(file, "\n");
    pushlive(in->next);
}

void poplive(stringBuffer *out){
    if(out == NULL){
        return;
    }
    poplive(out->next);
    fprintf(file, "   pop ");
    printcolor(getnode(out->buffer));
    fprintf(file, "\n"); 
}*/

void writefile(livenessNode *lnode){
    char* temp = malloc(sizeof(char)*10);
    node *n;
    int index = 0;
    /*livenessNode *call;
    if(strcmp(lnode->pline->line, "call") == 0){
        pushlive(lnode->in);
        fprintf(file, "%s", lnode->line);
        poplive(lnode->out);
        return;
    }*/

    //currently xor does not use or define

    if((lnode->def == NULL) && (lnode->use == NULL) && strcmp(lnode->pline, "xor") != 0){
        if(strcmp(lnode->pline, "xor") == 0){
            fprintf(stderr, "xor\n");
        }
        fprintf(stdout, "%s", lnode->line);
        if(strcmp(lnode->line, ".section .data\n") == 0){
            fprintf(stdout, "   spilling: .space %d\n", spillcount*8);
        }
        return;
    }
    char *line = lnode->line;
    int unsigned i = 0;
    while(i < strlen(line)){
        if(line[i] == '@'){
            temp[index] = line[i];
            index++;
            i++;
            while((47 < (int) line[i]) && ( (int) line[i] < 58)){
                temp[index] = line[i];
                index++;
                i++;
            }
            temp[index] = '\0';
            fprintf(stderr, "%s\n", temp);
            n = getnode(temp);
            printcolor(n);
            index = 0;
            free(temp);
            temp = malloc(sizeof(char) * 10);
        }else{
            fprintf(stdout, "%c", line[i]);
            i++;
        }
    }
}

void printcolor(node *n){
    if(n->spill == 0){
        switch(n->color)
        {
            case 1:
                fprintf(stdout, "%%r15");
                break;
            case 2:
                fprintf(stdout, "%%r14");
                break;
            case 3:
                fprintf(stdout, "%%r13");
                break;
            case 4:
                fprintf(stdout, "%%r12");
                break;
            case 5:
                fprintf(stdout, "%%r11");
                break;
            case 6:
                fprintf(stdout, "%%r10");
                break;
        }
    } else if(n->spill == 1){
        if(n->spillnumber == 0){
            fprintf(stdout, "(spilling)");
        } else {
            fprintf(stdout, "(spilling+%d)", n->spillnumber*8);
        }
        
    }
}

void pushnode(node *n){
    stack *stck = NEW(stack);
    stck->object=n;
    stck->next = g->stack;
    g->stack = stck;
}

node *popNode(){
    node *n = g->stack->object;
    g->stack = g->stack->next;
    return n;
}

void spillNode(node *n){
    n->spill = 1;
    n->spillnumber = spillcount;
    spillcount++;
    simplifyNode(n);
}

int simplify(){
    nodelist *nodes = g->nodes;
    while(nodes != NULL){
        if((nodes->head->degreelimit > nodes->head->numOfNeighbors) && (nodes->head->onStack == 0)){
            simplifyNode(nodes->head);
            return 0;
        }
        nodes = nodes->tail;
    }
    nodes = g->nodes;
    while(nodes != NULL){
        if(nodes->head->onStack != 1){
            spillNode(nodes->head);
            return 0;
        }
        nodes = nodes->tail;
    }
    return 1;
}

void simplifyNode(node *n){
    edgelist *neighbors = n->neighbors;
    pushnode(n);
    n->onStack = 1;
    while(neighbors != NULL){
        neighbors->head->to->numOfNeighbors = neighbors->head->to->numOfNeighbors - 1;
        //neighbors->head->to->degreelimit = neighbors->head->to->degreelimit - 1;
        neighbors = neighbors->tail;
    }
}

int checkColor(int spilled, int color, node *n){
    edgelist *neighbors = n->neighbors;
    while (neighbors != NULL){
        if( (spilled == neighbors->head->to->spill) && (color == neighbors->head->to->color)){
            return 0;
        }
        neighbors = neighbors->tail;
    }
    return 1;
}

void color(){
    stack *s;
    node *n;
    int simplified = 0;
    int colored;
    nodelist *nl = g->nodes;
    int spillcolor=0;
    while(simplified == 0){
        simplified = simplify();
    }

    s = g->stack;
    while(s != NULL){
        n = s->object;
        //fprintf(stderr, "%s : %d\n", n->id, n->spill);
        s = s->next;
    }

    while(g->stack != NULL){
        n = popNode();
        if(n->spill == 0){
            for(int i = 1; i <= numOfColors; i++){
                colored = checkColor(0, i, n);
                if(colored == 1){
                    n->color=i;
                    break;
                }
            }
        } else if(n->spill == 1){
            spillcolor = 0;
            while(true){
                colored = checkColor(1, spillcolor, n);
                if(colored == 1){
                    n->color = spillcolor;
                    break;
                }
                spillcolor++;
            }
        }
    }

    nl = g->nodes;
    while(nl != NULL){
        fprintf(stderr, "id: %s, spill: %d, color: %d\n", nl->head->id, nl->head->spill, nl->head->color);
        nl = nl->tail;
    }  
}

void addNeighbors(stringBuffer *interference){
    if (interference == NULL){
        return;
    }
    stringBuffer *index = interference;
    stringBuffer *remaining = interference->next;
    if (interference == NULL){
        return;
    }

    while(index != NULL){
        addnode(index->buffer);
        index = index->next;
    }
    index = interference;
    
    while(index != NULL){
        remaining = index->next;
        while(remaining != NULL){
            addedge(index->buffer, remaining->buffer);
            addedge(remaining->buffer, index->buffer);
            remaining=remaining->next;
        }
        index = index->next;
    }

}

void buildgraph(livenessNode *node){
    nodelist *n;
    edgelist *e;
    g = NEW(graph);
    g->edges = NULL;
    g->stack = NULL;
    g->nodes = NULL;
    while(true){
        addNeighbors(node->in);
        addNeighbors(node->out);
        if(node->succ->node == NULL){
            break;
        }else{
            node = node->succ->node;
        }
    }
    
    
    
    n = g->nodes;
    while(n != NULL){
        e = n->head->neighbors;
        fprintf(stderr, "%s with edges", n->head->id);
        while (e != NULL){
            fprintf(stderr, " %s -> %s,", e->head->from->id, e->head->to->id);
            e = e->tail;
        }
        fprintf(stderr, "\n");
        n=n->tail;
    }
}

node *createNode(char *id){
    node *n = NEW(node);
    n->id = id;
    n->numOfNeighbors=0;
    n->onStack=0;
    n->spill=0;
    n->color=0;
    n->spillnumber=0;
    n->degreelimit=numOfColors;
    n->neighbors=NULL;
    return n;
}

nodelist *createNodelist(node *head, nodelist *tail){
    nodelist *nl = NEW(nodelist);
    nl->head=head;
    nl->tail=tail;
    return nl;
}

void addnode(char *id){
    nodelist *d = g->nodes;
    node *n;
    if(d != NULL){
        while(d != NULL){
            if(strcmp(d->head->id, id) == 0){
                return;
            }
            d = d->tail;
        }
    }
    n = createNode(id);
    g->nodes=createNodelist(n, g->nodes);
}

node *getnode(char *id){
    nodelist *nl = g->nodes;
    while(nl != NULL){
        if(strcmp(nl->head->id, id) == 0){
            return nl->head;
        }
        nl = nl->tail;
    }
    //fprintf(stderr, "No such node: %s\n", id);
    return NULL;
}

edge *createEdge(char *id1, char *id2){
    edge *e = NEW(edge);
    e->from = getnode(id1);
    e->from->numOfNeighbors = e->from->numOfNeighbors+1;
    e->to = getnode(id2);
    return e;
}

edgelist *createEdgelist(edge *head, edgelist *tail){
    edgelist *el = NEW(edgelist);
    el->head = head;
    el->tail = tail;
    return el;
}

void addedge(char *id1, char *id2){
    node *n = getnode(id1);
    edge *e;
    edgelist *el = n->neighbors;
    while(el != NULL){
        if (strcmp(el->head->to->id, id2) == 0){
            return;
        }
        el = el->tail;
    }
    e = createEdge(id1, id2);
    n->neighbors = createEdgelist(e, n->neighbors);
}