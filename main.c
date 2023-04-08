// *****************************
// *remember to finish getarray*
// *****************************

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "fdmjast.h"
#include "y.tab.h"
#include "printast.h"
#include "typecheck.h"
#include "pr_tree_readable.h"
#include "ast2treep.h"
A_prog root;
extern int yyparse();
int main(int argc, const char * argv[]) {
    yyparse();
    classtable=S_empty();
    extends=S_empty();
    classPos=S_empty();
    typeCheckProg(root);
    printFuncDeclList(stdout,ast2treepprog(root));
    // printA_Prog(stdout, root);
    // printf("PASS!\n");
    // pr_stm(stdout,T_Seq(T_Label(Temp_newlabel()),T_Label(Temp_newlabel())),0);
    return 0;
}