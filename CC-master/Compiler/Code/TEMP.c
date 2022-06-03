#include "TEMP.h"


temp *requestTemp(){
    temp *t;
    t = NEW(temp);
    count=count+1;
    t->num=count;
    return t;
}