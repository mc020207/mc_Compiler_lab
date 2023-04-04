#include "typecheck.h"
#include <stdlib.h>
#include <string.h>
void printError(A_pos pos,const char* message){
    printf("error on line %d and pos %d , %s\n",pos->line,pos->pos,message);
    exit(0);
}
node typeCheckExp(A_exp x){
    node ans;
    ans.location=0;
    ans.value=Ty_Nil();
    if (x==NULL){
        return ans;
    }
    switch (x->kind){
        case A_opExp:{
            node t1=typeCheckExp(x->u.op.left);
            node t2=typeCheckExp(x->u.op.right);
            if (t1.value->kind==Ty_int&&t2.value->kind==Ty_int){
                ans.location=0;
                ans.value=Ty_Int();
            }
            else if (t1.value->kind!=Ty_int){
                printError(x->u.op.left->pos,"the left EXP does not have an integer value");
            }
            else printError(x->u.op.right->pos,"the right EXP does not have an integer value");
            break;
        }
        case A_arrayExp:{
            node t1=typeCheckExp(x->u.array_pos.arr);
            node t2=typeCheckExp(x->u.array_pos.arr_pos);
            if (t1.value->kind==Ty_array&&t2.value->kind==Ty_int){
                ans.value=t1.value->u.array;
                ans.location=1;
            }
            else if (t1.value->kind!=Ty_array){
                printError(x->u.array_pos.arr->pos,"the EXP does not have an array value");
            }
            else printError(x->u.array_pos.arr_pos->pos,"the EXP does not have an integer value");
            break;
        }
        case A_callExp:{
            node t1=typeCheckExp(x->u.call.obj);
            if (t1.value->kind!=Ty_name){
                printError(x->pos,"the EXP does not have a class value");
            }
            S_table table=S_look(classtable,t1.value->u.name.sym);
            Ty_ty ty=S_look(table,S_Symbol(x->u.call.fun));
            if (ty==NULL){
                printError(x->pos,"the class does not have this fuction");
            }
            else if (ty->kind!=Ty_record){
                printError(x->pos,"it is a Var name in this class");
            }
            ans.location=0;
            ans.value=ty->u.record->head->ty;
            typeCheckExpList(x->u.call.el,ty->u.record->tail,0);
            break;
        }
        case A_classVarExp:{
            node t1=typeCheckExp(x->u.classvar.obj);
            if (t1.value->kind!=Ty_name){
                printError(x->pos,"the EXP does not have a class value");
            }
            S_table table=S_look(classtable,t1.value->u.name.sym);
            Ty_ty ty=S_look(table,S_Symbol(x->u.call.fun));
            if (ty==NULL){
                printError(x->pos,"the class does not have this Var");
            }
            else if (ty->kind==Ty_record){
                printError(x->pos,"it is a fuction name in this class");
            }
            ans.location=1;
            ans.value=ty;
            break;
        }
        case A_boolConst:{
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
        case A_numConst:{
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
        case A_idExp:{
            Ty_ty ty=S_look(t,S_Symbol(x->u.v));
            if (ty==NULL){
                printError(x->pos,"get an undefined id");
            }
            ans.value=ty;
            ans.location=1;
            break;
        }
        case A_thisExp:{
            ans.location=0;
            if(nowclass==NULL){
                printError(x->pos,"can not use \'this\' in mainmethod");
            }
            ans.value=Ty_Name(S_Symbol(nowclass->id),Ty_Nil());
            break;
        }
        case A_lengthExp:{
            node t1=typeCheckExp(x->u.e);
            if (t1.value->kind!=Ty_array){
                printError(x->u.e->pos,"the EXP does not have an array value");
            }
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
        case A_newIntArrExp:{
            node t1=typeCheckExp(x->u.e);
            if (t1.value->kind!=Ty_int){
                printError(x->u.e->pos,"the EXP does not have an Integer value");
            }
            ans.location=0;
            ans.value=Ty_Array(Ty_Int());
            break;
        }
        case A_newObjExp:{
            ans.location=0;
            if (S_look(classtable,S_Symbol(x->u.v))==NULL){
                printError(x->pos,"does not have this kind of class");
            }
            ans.value=Ty_Name(S_Symbol(x->u.v),Ty_Nil());
            break;
        }
        case A_notExp:{
            node t1=typeCheckExp(x->u.e);
            if (t1.value->kind!=Ty_int){
                printError(x->u.e->pos,"the EXP does not have an Integer value");
            }
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
        case A_minusExp:{
            node t1=typeCheckExp(x->u.e);
            if (t1.value->kind!=Ty_int){
                printError(x->u.e->pos,"the EXP does not have an Integer value");
            }
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
        case A_escExp:{
            typeCheckStmList(x->u.escExp.ns);
            ans=typeCheckExp(x->u.escExp.exp);
            break;
        }
        case A_getint:{
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
        case A_getch:{
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
        case A_getarray:{
            node t1=typeCheckExp(x->u.e);
            if (t1.location==0){
                printError(x->u.e->pos,"the EXP does not have location");
            }
            if (t1.value->kind!=Ty_array){
                printError(x->u.e->pos,"the EXP does not have an array value");
            }
            ans.location=0;
            ans.value=Ty_Int();
            break;
        }
    }
    return ans;
}
node typeCheckExpList(A_expList x,Ty_fieldList l,bool intlist){
    node ans;ans.location=0;
    if (intlist){
        if (!x){
            ans.value=Ty_Nil();
            return ans;
        }
        node t1=typeCheckExp(x->head);
        if (t1.value->kind!=Ty_int){
            printError(x->head->pos,"the EXP does not have an integer value");
        }
        node t2=typeCheckExpList(x->tail,NULL,1);
        ans.location=0;
        if (t2.value->kind==Ty_nil){
            ans.value=t1.value;
        }else{
            ans.value=Ty_Array(t1.value);
        }
    }else{
        if (x==NULL&&l==NULL) return ans;
        node t1=typeCheckExp(x->head);
        checkTwoType(x->head->pos,"the parameter list mismatch",l->head->ty,t1.value);
        if ((x->tail==NULL&&l->tail)||(x->tail&&l->tail==NULL)){
            printError(x->head->pos,"the parameter list mismatch");
        }
        typeCheckExpList(x->tail,l->tail,0);
    }
    return ans;
}
void typeCheckStmList(A_stmList x){
    if (!x) return ;
    typeCheckStm(x->head);
    typeCheckStmList(x->tail);
}
void typeCheckStm(A_stm x){
    if (!x) return ;
    switch (x->kind){
        case A_nestedStm:{
            typeCheckStmList(x->u.ns);
            break;
        }
        case A_ifStm:{
            node t1=typeCheckExp(x->u.if_stat.e);
            if (t1.value->kind!=Ty_int){
                printError(x->u.if_stat.e->pos,"the EXP does not have an integer value");
            }
            typeCheckStm(x->u.if_stat.s1);
            typeCheckStm(x->u.if_stat.s2);
            break;
        }
        case A_whileStm:{
            node t1=typeCheckExp(x->u.while_stat.e);
            if (t1.value->kind!=Ty_int){
                printError(x->u.while_stat.e->pos,"the EXP does not have an integer value");
            }
            typeCheckStm(x->u.while_stat.s);
            break;
        }
        case A_assignStm:{
            node t1=typeCheckExp(x->u.assign.arr);
            if (t1.location==0){
                printError(x->u.assign.arr->pos,"the EXP does not have location");
            }
            node t2=typeCheckExp(x->u.assign.value);
            // must be changed if class_type appear
            checkTwoType(x->pos,"assign Stm's two EXP have different type",t1.value,t2.value);
            break;
        }
        case A_arrayInit:{
            node t1=typeCheckExp(x->u.array_init.arr);
            if (t1.location==0){
                printError(x->u.array_init.arr->pos,"the EXP does not have location");
            }
            if (t1.value->kind!=Ty_array){
                printError(x->u.array_init.arr->pos,"the EXP does not have an array value");
            }
            if (x->u.array_init.init_values==NULL){
                break;
            }
            node t2=typeCheckExpList(x->u.array_init.init_values,NULL,1);
            if (!(t2.value->kind==Ty_int||(t2.value->kind==Ty_array&&t2.value->u.array->kind==Ty_int))){
                printError(x->u.array_init.init_values->head->pos,"the EXPLIST is not a intlist");
            }
            break;
        }
        case A_callStm:{
            node t1=typeCheckExp(x->u.call_stat.obj);
            if (t1.value->kind!=Ty_name){
                printError(x->pos,"the EXP does not have a class value");
            }
            S_table table=S_look(classtable,t1.value->u.name.sym);
            Ty_ty ty=S_look(table,S_Symbol(x->u.call_stat.fun));
            if (ty==NULL){
                printError(x->pos,"the class does not have this fuction");
            }
            else if (ty->kind!=Ty_record){
                printError(x->pos,"it is a Var name in this class");
            }
            typeCheckExpList(x->u.call_stat.el,ty->u.record->tail,0);
            break;
        }
        case A_continue:{

            break;
        }
        case A_break:{

            break;
        }
        case A_return:{
            // if fuction can return void we shoule add special check there
            node t1=typeCheckExp(x->u.e);
            checkTwoType(x->pos,"return a wrong type",returnType,t1.value);
            // if (t1.value->kind!=returnType->kind){
            //     printError(x->pos,"return a wrong type value");
            // }
            // if (t1.value->kind==Ty_name&&t1.value->u.name.sym!=returnType->u.name.sym){
            //     printError(x->pos,"return a wrong type value");
            // }
            break;
        }
        case A_putint:{
            node t1=typeCheckExp(x->u.e);
            if (t1.value->kind!=Ty_int){
                printError(x->u.e->pos,"the EXP does not have an integer value");
            }
            break;
        }
        case A_putarray:{
            node t1=typeCheckExp(x->u.putarray.e1);
            node t2=typeCheckExp(x->u.putarray.e2);
            if (t1.value->kind!=Ty_int){
                printError(x->u.putarray.e1->pos,"the EXP does not have an integer value");
            }
            if (t2.value->kind!=Ty_array){
                printError(x->u.putarray.e2->pos,"the EXP does not have an array value");
            }
            break;
        }
        case A_putch:{
            node t1=typeCheckExp(x->u.e);
            if (t1.value->kind!=Ty_int){
                printError(x->u.e->pos,"the EXP does not have an string value");
            }
            break;
            break;
        }
        case A_starttime:{
            
            break;
        }
        case A_stoptime:{

            break;
        }
    }
}
void typeCheckMethodDecl(A_methodDecl x){
    if (t) free(t);
    t=S_empty();
    switch (x->t->t){
        case A_intType:{
            returnType=Ty_Int();
            break;
        } 
        case A_idType:{
            if (S_look(classPos,S_Symbol(x->t->id))==NULL){
                printError(x->t->pos,"this class does not defined");
            }
            returnType=Ty_Name(S_Symbol(x->t->id),Ty_Nil());
            break;
        } 
        case A_intArrType:{
            returnType=Ty_Array(Ty_Int());
            break;
        }
    }
    A_formalList list=x->fl;
    for (;list;list=list->tail){
        A_formal now=list->head;
        if (S_look(t,S_Symbol(now->id))){
            printError(now->pos,"this id has been defined");
        }
        Ty_ty value;
        switch (now->t->t){
            case A_intType:{
                S_enter(t,S_Symbol(now->id),Ty_Int());
                break;
            } 
            case A_idType:{
                if (S_look(classPos,S_Symbol(now->t->id))==NULL){
                    printError(now->t->pos,"this class does not defined");
                }
                S_enter(t,S_Symbol(now->id),Ty_Name(S_Symbol(now->t->id),Ty_Nil()));
                break;
            } 
            case A_intArrType:{
                S_enter(t,S_Symbol(now->id),Ty_Array(Ty_Int()));
                break;
            }
        }
    }
    typeCheckVarDeclList(x->vdl,t);
    checkExistVarList(x->vdl);
    typeCheckStmList(x->sl);
}
void typeCheckMethodDeclList(A_methodDeclList list){
    if (list==NULL) return ;
    typeCheckMethodDecl(list->head);
    typeCheckMethodDeclList(list->tail);
}
void typeCheckClassDecl(A_classDecl x){
    nowclass=x;
    typeCheckMethodDeclList(x->mdl);
}
void typeCheckClassDeclList(A_classDeclList list){
    if (list==NULL) return ;
    typeCheckClassDecl(list->head);
    typeCheckClassDeclList(list->tail);
}
void typeCheckVarDecl(A_varDecl x,S_table table){
    if(S_look(table,S_Symbol(x->v))){
        printError(x->pos,"this id has been defined");
    }
    switch (x->t->t){
        case A_intType:{
            if (x->elist){
                node t1=typeCheckExpList(x->elist,NULL,1);
                if (t1.value->kind!=Ty_int){
                    printError(x->elist->head->pos,"the EXP does not have an integer value");
                }
            }
            S_enter(table,S_Symbol(x->v),Ty_Int());
            break;
        } 
        case A_idType:{
            S_enter(table,S_Symbol(x->v),Ty_Name(S_Symbol(x->t->id),Ty_Nil()));
            break;
        } 
        case A_intArrType:{
            if (x->elist){
                node t1=typeCheckExpList(x->elist,NULL,1);
                if (!(t1.value->kind==Ty_int||(t1.value->kind==Ty_array&&t1.value->u.array->kind==Ty_int))){
                    printError(x->elist->head->pos,"the EXPLIST is not a intlist");
                }
            }
            S_enter(table,S_Symbol(x->v),Ty_Array(Ty_Int()));
            break;
        }
    }
}
void typeCheckVarDeclList(A_varDeclList x,S_table table){
    if (!x) return ;
    typeCheckVarDecl(x->head,table);
    typeCheckVarDeclList(x->tail,table);
}
void typeCheckMainMethod(A_mainMethod x){
    returnType=Ty_Int();
    nowclass=NULL;
    if (t) free(t);
    t=S_empty();
    typeCheckVarDeclList(x->vdl,t);
    checkExistVarList(x->vdl);
    typeCheckStmList(x->sl);
}
void typeCheckProg(A_prog root){
    fillTable(root->cdl);
    solveExtendsList(root->cdl);
    typeCheckClassDeclList(root->cdl);
    typeCheckMainMethod(root->m);
}
Ty_fieldList getTyFieldList(A_formalList list){
    if (!list) return NULL;
    A_formal x=list->head;
    Ty_ty ty;
    switch (x->t->t){
        case A_intType:{
            ty=Ty_Int();
            break;
        }
        case A_idType:{
            ty=Ty_Name(S_Symbol(x->t->id),Ty_Nil());
            break;
        }
        case A_intArrType:{
            ty=Ty_Array(Ty_Int());
            break;
        }
    }
    Ty_fieldList ans=Ty_FieldList(Ty_Field(x->id?S_Symbol(x->id):NULL,ty),getTyFieldList(list->tail));
}
void filltableMethod(A_methodDecl x,S_table table){
    A_formalList now=checked_malloc(sizeof(*now));
    if (S_look(table,S_Symbol(x->id))){
        printError(x->pos,"this function name has been used");
    }
    now->head=A_Formal(NULL,x->t,NULL);now->tail=x->fl;
    getTyFieldList(now);
    S_enter(table,S_Symbol(x->id),Ty_Record(getTyFieldList(now)));
}   
void filltableMethodList(A_methodDeclList list,S_table table){
    if (!list) return ;
    filltableMethod(list->head,table);
    filltableMethodList(list->tail,table);
}
void fillTable(A_classDeclList list){
    if (!list) return ;
    A_classDecl x=list->head;
    S_enter(classPos,S_Symbol(x->id),x);
    if (S_look(classtable,S_Symbol(x->id))){
        printError(x->pos,"this class name has been used");
    }
    S_table table=S_empty();
    typeCheckVarDeclList(x->vdl,table);
    filltableMethodList(x->mdl,table);
    S_enter(classtable,S_Symbol(x->id),table);
    if (x->parentID){
        tree now=checked_malloc(sizeof(*now));
        now->faname=S_Symbol(x->parentID);
        now->name=S_Symbol(x->id);
        now->vs=0;
        now->finish=0;
        S_enter(extends,S_Symbol(x->id),now);
    }
    fillTable(list->tail);
}
void checkExistVarList(A_varDeclList list){
    for (;list;list=list->tail){
        A_varDecl x=list->head;
        if (x->t->t==A_idType){
            if (S_look(classtable,S_Symbol(x->t->id))==NULL){
                printError(x->t->pos,"this class does not define");
            }
        }
    }
}
void checkExistMethodList(A_methodDeclList list){
    for (;list;list=list->tail){
        A_methodDecl x=list->head;
        if (x->t->t==A_idType){
            if (S_look(classtable,S_Symbol(x->t->id))==NULL){
                printError(x->t->pos,"this class does not define");
            }
        }
        A_formalList flist=x->fl;
        for (;flist;flist=flist->tail){
            A_formal fnow=flist->head;
            if (fnow->t->t==A_idType){
                if (S_look(classtable,S_Symbol(fnow->t->id))==NULL){
                    printError(fnow->t->pos,"this class does not define");
                }
            }
        }
    }
}
void solveExtendsList(A_classDeclList list){
    if (!list) return ;
    solveExtends(list->head);
    solveExtendsList(list->tail);
}
void solveExtends(A_classDecl x){
    if (x->parentID==NULL){
        checkExistVarList(x->vdl);
        checkExistMethodList(x->mdl);
        return ;
    }
    tree now=S_look(extends,S_Symbol(x->id));
    assert(now);
    if (now->finish) return ;
    if (now->vs){
        printError(x->pos,"the extends relationship has circle");
    }
    now->vs=1;
    checkExistVarList(x->vdl);
    checkExistMethodList(x->mdl);
    A_classDecl fa=S_look(classPos,now->faname);
    assert(fa);
    solveExtends(fa);
    extendsTable(x,S_look(classtable,now->name),S_look(classtable,now->faname));
    now->finish=1;
}
void extendsTable(A_classDecl x,S_table to,S_table from){
    S_symbol key=from->top;
    if (!key) return ;
    Ty_ty ty=S_look(from,key);
    addKey(x,to,key,ty);
    TAB_pop(from);
    extendsTable(x,to,from);
    S_enter(from,key,ty);
    // printf("enter %s\n",S_name(key));
}
void addKey(A_classDecl x,S_table to,S_symbol key,Ty_ty value){
    Ty_ty ty1=S_look(to,key);
    if (ty1==NULL){
        S_enter(to,key,value);
    }else{
        Ty_ty ty2=value;
        if (ty1->kind==Ty_record&&ty2->kind==Ty_record){
            compareFuctions(x,ty1,ty2,S_name(key));
        }else{
            if (ty1->kind!=Ty_record) findVarList(x->vdl,S_name(key));
            else findMethodList(x->mdl,S_name(key),"this id has been used in its father class");
        }
    }
}
void compareFuctions(A_classDecl x,Ty_ty t1,Ty_ty t2,string name){
    Ty_fieldList list1=t1->u.record,list2=t2->u.record;
    for (;list1&&list2;list1=list1->tail,list2=list2->tail){
        Ty_ty ty1=list1->head->ty,ty2=list2->head->ty;
        if (ty1->kind!=ty2->kind) findMethodList(x->mdl,name,"the signature of the fuction is different from father class");
        if (ty1->kind==Ty_name&&ty1->u.name.sym!=ty2->u.name.sym) findMethodList(x->mdl,name,"the signature of the fuction is different from father class");
    }
    if (list1||list2) findMethodList(x->mdl,name,"the signature of the fuction is different from father class");
}
void findVarList(A_varDeclList list,string name){
    for (;list;list=list->tail){
        A_varDecl x=list->head;
        if (strcmp(x->v,name)==0){
            printError(x->pos,"this id has been used in its father class");
        }
    }
}
void findMethodList(A_methodDeclList list,string name,string message){
    for (;list;list=list->tail){
        A_methodDecl x=list->head;
        if (strcmp(x->id,name)==0){
            printError(x->pos,message);
        }
    }
}
void checkTwoType(A_pos pos,string message,Ty_ty t1,Ty_ty t2){
    if (t1->kind!=t2->kind){
        printError(pos,message);
    }
    if (t1->kind==Ty_name){
        S_symbol now=t2->u.name.sym;
        while (1){
            if (t1->u.name.sym==now) return ;
            tree x=S_look(extends,now);
            if (!x) break;
            now=x->faname;
        }
        printError(pos,message);
    }
}