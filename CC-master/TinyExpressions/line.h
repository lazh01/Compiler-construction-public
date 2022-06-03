#include "TEMP.h"


typedef struct line{
    enum{other, movq, operation, label, root, jump} kind;
    char *operand;
    linkedlist *useargs;
    linkedlist *defargs;
    line *next;
} line;

typedef struct reg{
    char *name;
} reg;

typedef struct arg_{
    enum {tempo, regi, lit} regkind;
    enum {notmem, mem} memkind;
    union{
        struct temp *tmp;
        struct reg *reg;
        char *literal;
    } u;
    int memoffset;
} arg;


#define makeArg(...) OVERLOAD(makeArg, (__VA_ARGS__), \
    (print_ii, (int, int)), \
    (print_id, (int, double)), \
    (print_di, (double, int)), \
    (print_dd, (double, double)), \
    (print_iii, (int, int, int)) \
)

line *makeLine(int type, char *op, arg *src, arg *dst, int args, int srckind, int dstkind);

arg *makeTempArg(int ismem, temp *tem, int offset);

arg *makeRegArg(int ismem, reg *r, int offset);

arg *makeLitArg(int ismem, char *name, int offset);

reg *makeReg(char *id);

