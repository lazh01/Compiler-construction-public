#ifndef __TEMP_h
#define __TEMP_h
#include "memory.h"

int count;

typedef struct temp{
    int num;
} temp;

temp *requestTemp();

#endif