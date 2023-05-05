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
#include "flowgraph.h"
#include "liveness.h"
#include "ig.h"
#include "bg.h"
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
        c=C_basicBlocks(C_traceSchedule(c));
        AS_blockList aslist=treep2assemblcok(c);
        G_nodeList bg=Create_bg(aslist);
        printf("------Basic Block Graph---------\n");
        Show_bg(stdout, bg);
        printf("------~Final traced StmList---------\n");
        char des[1010];
        sprintf(des,"define i64 @%s() #0 {",fl->head->name);
        AS_instrList prolog=IL(OI(String(des), NULL, NULL ,NULL), NULL);
        AS_instrList epilog=I(OI("}", NULL, NULL, NULL));
        AS_instrList il = AS_traceSchedule(aslist, prolog, epilog, FALSE);
        AS_printInstrList(stdout, il, Temp_name());
        G_graph G=FG_AssemFlowGraph(il);
        G_show(stdout, G_nodes(G), (void*)show);
        G_nodeList lg=Liveness(G_nodes(G));
        Show_Liveness(stdout, lg);
        printf("------Interference Graph---------\n");
        G_nodeList ig=Create_ig(lg);
        Show_ig(stdout, ig);
        fl=fl->tail;
    }
    fprintf(stdout, "\n");

    return 0;
}