#pragma once
#include "fdmjast.h"
#include "printast.h"
#include "table.h"
#include "symbol.h"
#include "types.h"
#include "temp.h"
typedef struct node{
    bool location;
    Ty_ty value;
}node;
typedef struct tree_* tree;
typedef struct tree_{
    S_symbol name;
    S_symbol faname;
    bool vs;
    bool finish;
}tree_;
typedef struct TyAndInit_{
    Ty_ty ty;
    A_expList expList;
}TyAndInit_;
typedef struct TyAndInit_* TyAndInit;
void printError(A_pos pos,const char* message);
node typeCheckExp(A_exp x);
node typeCheckExpList(A_expList x,Ty_fieldList l,bool intlist,A_pos pos);
void typeCheckStmList(A_stmList x);
void typeCheckStm(A_stm x);
void typeCheckMethodDecl(A_methodDecl x);
void typeCheckMethodDeclList(A_methodDeclList list);
void typeCheckClassDecl(A_classDecl x);
void typeCheckClassDeclList(A_classDeclList list);
void typeCheckVarDecl(A_varDecl x,S_table table,bool isClassVar);
void typeCheckVarDeclList(A_varDeclList x,S_table table,bool isClassVar);
void typeCheckMainMethod(A_mainMethod x);
void typeCheckProg(A_prog root);
void fillTable(A_classDeclList list);
void solveExtendsList(A_classDeclList list);
void solveExtends(A_classDecl x);
void extendsTable(A_classDecl x,S_table to,S_table from);
void addKey(A_classDecl x,S_table to,S_symbol key,TyAndInit value);
void findMethodList(A_methodDeclList list,string name,string message);
void findVarList(A_varDeclList list,string name);
void compareFuctions(A_classDecl x,Ty_ty t1,Ty_ty t2,string name);
void checkTwoType(A_pos pos,string message,Ty_ty t1,Ty_ty t2);
void checkExistVarList(A_varDeclList list);
void checkExistMethodList(A_methodDeclList list);
Ty_fieldList getTyFieldList(A_formalList list);