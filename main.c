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
#include "flowgraph.h"
#include "liveness.h"
#include "ig.h"
#include "bg.h"
#include "ssa.h"
#include "registerAllocation.h"
#define I(a) AS_InstrList(a, NULL)
#define IL(a, b) AS_InstrList(a, b)
#define MI(a, b, c) AS_Move(a, b, c)
#define LI(a, b) AS_Label(a, b)
#define OI(a, b, c, d) AS_Oper(a, b, c, d)
#define T(a) Temp_TempList(a, NULL)
#define TL(a, b) Temp_TempList(a, b)
#define LL(a, b) Temp_LabelList(a, b)
#define L(a) Temp_LabelList(a, NULL)
#define Targets(a) AS_Targets(a)
A_prog root;
extern int yyparse();
void show(AS_instr ins) {
    FG_Showinfo(stdout, ins, Temp_name());
}
int main(int argc, const char * argv[]) {
    yyparse();
    typeCheckProg(root);
    T_funcDeclList fl=ast2treepprog(root);
    T_stm s;
    while (fl) {
        s=fl->head->stm;
        T_stmList sl = C_linearize(s);
        struct C_block c = C_basicBlocks(sl);
        sl=C_traceSchedule(c);
        // printf("------~Final traced StmList1---------\n");
        // printStmList_linearized(stdout,sl,0);
        c=C_basicBlocks(sl);
        AS_blockList aslist=treep2assemblcok(c);
        // printf("222\n");
        G_nodeList bg=Create_bg(aslist);
        // printf("------Basic Block Graph---------\n");
        // Show_bg(stdout, bg);
        AS_instrList il=treep2assemfuction(aslist,fl->head);
        // printf("------Interference AssemFlowGraph---------\n");
        G_graph G=FG_AssemFlowGraph(il);
        // G_show(stdout, G_nodes(G), (void*)show);
        // printf("------Interference Liveness---------\n");
        G_nodeList lg=Liveness(G_nodes(G));
        // Show_Liveness(stdout, lg);
        // printf("------Interference Graph---------\n");
        G_nodeList ig=Create_ig(lg);
        // Show_ig(stdout, ig);
        // printf("------~Final traced StmList2---------\n");
        // ssa(aslist,bg,lg);
        // AS_printInstrList(stdout, il, Temp_name());
        // printf("------~Final traced StmList3---------\n");
        printf(".global %s\n",fl->head->name);
        il=registerAllocation(il,ig);
        AS_printInstrList(stdout,il,Temp_name());
        fl=fl->tail;
    }
    // fprintf(stdout, "declare ptr @malloc(i64)\n");
    // fprintf(stdout, "declare i64 @getint()\n");
    // fprintf(stdout, "declare i64 @getch()\n");
    // fprintf(stdout, "declare i64 @getarray(ptr)\n");
    // fprintf(stdout, "declare void @putint(i64)\n");
    // fprintf(stdout, "declare void @putch(i64)\n");
    // fprintf(stdout, "declare void @putarray(i64,ptr)\n");
    // fprintf(stdout, "declare void @starttime()\n");
    // fprintf(stdout, "declare void @stoptime()\n");
    return 0;
}