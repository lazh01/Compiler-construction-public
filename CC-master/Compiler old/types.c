#include "types.h"
#include "memory.h"
#include <stdio.h>

Ty_ty *Ty_Nil(void){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_nil;
    return type;
}

Ty_ty *Ty_Int(void){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_int;
    return type;
}

Ty_ty *Ty_String(void){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_string;
    return type;
}

Ty_ty *Ty_Void(void){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_void;
    return type;
}

Ty_ty *Ty_Bool(void){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_bool;
    return type;
}

Ty_ty *Ty_Record(Ty_fieldList *fields){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_record;
    type->u.record=fields;
    return type;
}

Ty_ty *Ty_Array(Ty_ty *ty){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_array;
    type->u.array=ty;
    return type;
}

Ty_ty *Ty_Name(char* name, SymbolTable *table){
    Ty_ty *type;
    type = NEW(Ty_ty);
    type->kind=Ty_name;
    type->u.name.name=name;
    type->u.name.table=table;
    return type;
}

Ty_tyList *Ty_TyList(Ty_ty *head, Ty_tyList *tail){
    Ty_tyList *list;
    list=NEW(Ty_tyList);
    list->head=head;
    list->tail = tail;
    return list;
}

Ty_field *Ty_Field(char* name, Ty_ty *ty){
    Ty_field *field;
    field = NEW(Ty_field);
    field->name=name;
    field->ty=ty;
    return field;
}

Ty_fieldList *Ty_FieldList(Ty_field *head, Ty_fieldList *tail){
    Ty_fieldList *flist;
    flist = NEW(Ty_fieldList);
    flist->head=head;
    flist->tail=tail;
    return flist;
}

Ty_ty_func *Ty_Func(Ty_tyList *formals, Ty_ty *type){
    Ty_ty_func *func;
    func = NEW(Ty_ty_func);
    func->formals=formals;
    func->type=type;
}

Ty_tyList *FListToList(Ty_fieldList *flist){
    Ty_tyList *list = NULL;
    if(flist != NULL){
        list=NEW(Ty_tyList);
        list->head=flist->head->ty;
        list->tail=FListToList(flist->tail);
    }
    return list;
}
/*int main()
{ 
    Ty_ty *t = Ty_Array(Ty_Void());
    if(t->u.array->kind == Ty_void){
        printf("array of void");
    }
  return 0;
}*/
