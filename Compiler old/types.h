#ifndef __types_h
#define __types_h

#include "symbol.h"

typedef struct Ty_ty_ Ty_ty;
typedef struct Ty_tyList_ Ty_tyList;
typedef struct Ty_field_ Ty_field;
typedef struct Ty_fieldList_ Ty_fieldList;
typedef struct Ty_ty_func_ Ty_ty_func;


typedef struct Ty_ty_ {
        enum {Ty_record, Ty_nil, Ty_int, Ty_string, Ty_array, Ty_name, Ty_void, Ty_bool} kind;
        union {Ty_fieldList *record;
                Ty_ty *array;
                struct {char* name; SymbolTable *table;} name;
        } u;
} Ty_ty;

typedef struct Ty_ty_func_{
        Ty_tyList *formals;
        Ty_ty *type;
} Ty_ty_func;

Ty_ty *Ty_Nil(void);
Ty_ty *Ty_Int(void);
Ty_ty *Ty_String(void);
Ty_ty *Ty_Void(void);
Ty_ty *Ty_Bool(void);

Ty_ty *Ty_Record(Ty_fieldList *fields);
Ty_ty *Ty_Array(Ty_ty *ty);
Ty_ty *Ty_Name(char* name, SymbolTable *table);

Ty_ty_func *Ty_Func(Ty_tyList *formals, Ty_ty *type);

typedef struct Ty_tyList_ {Ty_ty *head; Ty_tyList *tail;} Ty_tyList;
Ty_tyList *Ty_TyList(Ty_ty *head, Ty_tyList *tail);

typedef struct Ty_field_ {char* name; Ty_ty *ty;} Ty_field;
Ty_field *Ty_Field(char* name, Ty_ty *ty);

typedef struct Ty_fieldList_ {Ty_field *head; Ty_fieldList *tail;} Ty_fieldList;
Ty_fieldList *Ty_FieldList(Ty_field *head, Ty_fieldList *tail);

Ty_tyList *FListToList(Ty_fieldList *list);

#endif
