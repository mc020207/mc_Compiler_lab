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
#include "printtreep.h"
#include "ast2treep.h"
#include "canon.h"
#include "pr_linearized.h"
A_prog root;
extern int yyparse();
int main(int argc, const char * argv[]) {
    yyparse();
    typeCheckProg(root);
    T_funcDeclList fl=ast2treepprog(root);
    T_stm s;
    while (fl) {
        s=fl->head->stm;
        T_stmList sl = C_linearize(s);
        struct C_block c = C_basicBlocks(sl);
        fprintf(stdout, "%s\n",fl->head->name);
        printStmList_linearized(stdout, C_traceSchedule(c), 0);
        fprintf(stdout,"\n");
        fl=fl->tail;
    }
    fprintf(stdout, "\n");

    return 0;
}