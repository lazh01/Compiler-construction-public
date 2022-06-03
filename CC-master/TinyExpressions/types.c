#include "types.h"


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
    type->equal=NULL;
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

/*
1 means types equivalent
*/
int tyComp(Ty_ty *t1, Ty_ty *t2){
    if((t1 == NULL) || (t2 == NULL)){
        return 0;
    }

    while(t1->kind == Ty_name){
        t1=getSymbol(t1->u.name.table, t1->u.name.name)->value;
        if(t1 == NULL){
            return 0;
        }
    }

    while(t2->kind == Ty_name){
        t2=getSymbol(t2->u.name.table, t2->u.name.name)->value;
        if(t2 == NULL){
            return 0;
        }
    }
    
    if(t1->kind == Ty_record && t2->kind ==Ty_nil){
        return 1;
    }

    if(t1->kind == Ty_array && t2->kind ==Ty_nil){
        return 1;
    }
    

    if(t1->kind == Ty_record && t2->kind == Ty_record){
        if(compRecords(t1, t2) == 1){
            return 1;
        }
        return 0;
    }

    if(t1->kind == Ty_array || t2->kind == Ty_array){
        if(compArray(t1, t2) == 1){
            return 1;
        }
        return 0;
    }

    if(t1->kind ==  t2->kind){
        return 1;
    }

    return 0;
}
/*
Return 1 if equivalent
return 0 when not equivalent
!!problem, might endlessly recurse on recursive records
*/
int compRecords(Ty_ty *t1, Ty_ty *t2){
    Ty_fieldList *flist1 = t1->u.record;
    Ty_fieldList *flist2 = t2->u.record;

    Ty_tyList *list1 = t1->equal;
    Ty_tyList *list2 = t2->equal;
    
    while(list1 != NULL){
        if(list1->head == t2){
            return 1;
        }
        list1=list1->tail;
    }

    while(list2 != NULL){
        if(list2->head == t1){
            return 1;
        }
        list2=list2->tail;
    }


    t1->equal=Ty_TyList(t2, t1->equal);
    t2->equal=Ty_TyList(t1, t2->equal);

    while(flist1 != NULL && flist2 != NULL){
        if(tyComp(flist1->head->ty, flist2->head->ty) != 1){
            t1->equal=t1->equal->tail;
            t2->equal=t2->equal->tail;
            return 0;
        }
        flist1=flist1->tail;
        flist2=flist2->tail;
    }

    if(flist1 == NULL && flist2 == NULL){
        t1->equal=t1->equal->tail;
        t2->equal=t2->equal->tail;
        return 1;
    }




    t1->equal=t1->equal->tail;
    t2->equal=t2->equal->tail;
    return 0;
}

int compArray(Ty_ty *t1, Ty_ty *t2){
    while(t1->kind == Ty_array){
        t1 = t1->u.array;
    }

    while(t2->kind == Ty_array){
        t2=t2->u.array;
    }

    if(tyComp(t1, t2) == 1){
        return 1;
    }

    return 0;
}

/*int main()
{ 
    Ty_ty *t = Ty_Array(Ty_Void());
    if(t->u.array->kind == Ty_void){
        printf("array of void");
    }
  return 0;
}*/
