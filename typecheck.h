#include "fdmjast.h"
#include "printast.h"
#include "table.h"
#include "symbol.h"
#include "types.h"
S_table t;          // save local VAR and its type in it , key:name value:type
S_table classtable; // save class type in it , key:className Value:S_table{Var/method's name,Ty_Ty} 
                    // when save fuction use a Ty_record.
                    // in Ty_fildlist ,the first Ty in the list is the returnType
S_table extends;    // save className and its treenode pointer key:calssName value:tree
S_table classPos;   // save className and their struct
Ty_ty returnType;
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
node typeCheckExp(A_exp x);
node typeCheckExpList(A_expList x,A_formalList l,bool intlist);
void typeCheckStmList(A_stmList x);
void typeCheckStm(A_stm x);
void typeCheckClassDecl(A_classDeclList list);
void typeCheckVarDecl(A_varDecl x,S_table table);
void typeCheckVarDeclList(A_varDeclList x,S_table table);
void typeCheckMainMethod(A_mainMethod x);
void typeCheckProg(A_prog root);
void fillTable(A_classDeclList list);
void solveExtendsList(A_classDeclList list);
void solveExtends(A_classDecl x);
void extendsTable(A_classDecl x,S_table to,S_table from);
void addKey(A_classDecl x,S_table to,S_symbol key,Ty_ty value);
void findMethodList(A_methodDeclList list,string name,string message);
void findVarList(A_varDeclList list,string name);
void compareFuctions(A_classDecl x,Ty_ty t1,Ty_ty t2,string name);