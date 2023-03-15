#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "fdmjast.h"
#include "y.tab.h"
#include "printast.h"
A_prog root;

extern int yyparse();

int main(int argc, const char * argv[]) {
    yyparse();
    // printA_Prog(stdout, root);
    printf("OK!\n");
    return 0;
}