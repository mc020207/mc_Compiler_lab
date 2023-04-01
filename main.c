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
A_prog root;
extern int yyparse();
int main(int argc, const char * argv[]) {
    yyparse();
    classtable=S_empty();
    extends=S_empty();
    classPos=S_empty();
    typeCheckProg(root);
    // printA_Prog(stdout, root);
    printf("PASS!\n");
    return 0;
}