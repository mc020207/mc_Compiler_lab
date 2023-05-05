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
#include "assem.h"
#include "assemblock.h"
#include "treep2assem.h"
#include "bg.h"
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
        fprintf(stdout, "%s\n",fl->head->name);
        // printStmList_linearized(stdout,sl,0);
        struct C_block c = C_basicBlocks(sl);
        // printf("%s\n",S_name(c.label));
        // for (C_stmListList x=c.stmLists;x;x=x->tail){
        //     printf("**********\n");
        //     printStmList_linearized(stdout,x->head,0);
        // }
        // C_traceSchedule(c);
        // printStmList_linearized(stdout, C_traceSchedule(c), 0);
        // c = C_basicBlocks(sl);
        printf("------~Final traced StmList---------\n");
        AS_blockList aslist=treep2assemblcok(c);
        // for (AS_blockList x=aslist;x;x=x->tail){
        //     printf("**********\n");
        //     AS_printInstrList(stdout,x->head->instrs,Temp_name());
        // }
        // G_nodeList bg=Create_bg(aslist);
        // printf("------Basic Block Graph---------\n");

        // Show_bg(stdout, bg);
        AS_instrList il = AS_traceSchedule(aslist, NULL, NULL, FALSE);
        
        AS_printInstrList(stdout, il, Temp_name());
        // // fprintf(stdout, "%s\n",fl->head->name);
        // fprintf(stdout,"\n");
        fl=fl->tail;
    }
    fprintf(stdout, "\n");

    return 0;
}