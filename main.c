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
#include "treep2llvm.h"
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
int OFFSETSTEP;
extern int yyparse();
void show(AS_instr ins) {
    FG_Showinfo(stdout, ins, Temp_name());
}
int main(int argc, char * argv[]) {
    assert(argc==3);
    string filname=String(argv[1]);
    OFFSETSTEP=strcmp("llvm",argv[2])==0?8:4;
    freopen(filname,"r",stdin);
    yyparse();
    filname[strlen(filname)-strlen(".fmj")]=0;
    FILE *fast,*firp,*fstm,*fliv,*fll,*fs;
    fast=fopen(strcat(String(filname),".ast"),"w");
    firp=fopen(strcat(String(filname),".irp"),"w");
    fstm=fopen(strcat(String(filname),".stm"),"w");
    fliv=fopen(strcat(String(filname),".liv"),"w");
    if (strcmp("llvm",argv[2])==0) fll=fopen(strcat(String(filname),".ll"),"w");
    else fs=fopen(strcat(String(filname),".s"),"w");
    printA_Prog(fast,root);
    typeCheckProg(root);
    T_funcDeclList fl=ast2treepprog(root);
    printFuncDeclList(firp,fl);
    T_stm s;
    while (fl) {
        s=fl->head->stm;
        T_stmList sl = C_linearize(s);
        struct C_block c = C_basicBlocks(sl);
        sl=C_traceSchedule(c);
        printStmList_linearized(fstm,sl,0);
        c=C_basicBlocks(sl);
        AS_blockList aslist=NULL;
        if (strcmp("llvm",argv[2])==0) aslist=treep2llvmblcok(c);
        else aslist=treep2assemblcok(c);
        G_nodeList bg=Create_bg(aslist);
        fprintf(fliv,"------Basic Block Graph---------\n");
        Show_bg(fliv, bg);
        AS_instrList il=NULL;
        if (strcmp("llvm",argv[2])==0) il=treep2llvmfuction(aslist,fl->head);
        else il=treep2assemfuction(aslist,fl->head);
        fprintf(fliv,"------Interference AssemFlowGraph---------\n");
        G_graph G=FG_AssemFlowGraph(il);
        G_show(fliv, G_nodes(G), (void*)show);
        fprintf(fliv,"------Interference Liveness---------\n");
        G_nodeList lg=Liveness(G_nodes(G));
        Show_Liveness(fliv, lg);
        fprintf(fliv,"------Interference Graph---------\n");
        G_nodeList ig=Create_ig(lg);
        Show_ig(fliv, ig);
        if (fll){
            ssa(aslist,bg,lg);
            AS_printInstrList(fll, il, Temp_name());
        }
        if (fs){
            fprintf(fs,".global %s\n",fl->head->name);
            il=registerAllocation(il,ig);
            AS_printInstrList(fs,il,Temp_name());
            fprintf(fs,".section	.rodata\n");
        }
        fl=fl->tail;
    }
    if(fll){
        fprintf(fll, "declare ptr @malloc(i64)\n");
        fprintf(fll, "declare i64 @getint()\n");
        fprintf(fll, "declare i64 @getch()\n");
        fprintf(fll, "declare i64 @getarray(ptr)\n");
        fprintf(fll, "declare void @putint(i64)\n");
        fprintf(fll, "declare void @putch(i64)\n");
        fprintf(fll, "declare void @putarray(i64,ptr)\n");
        fprintf(fll, "declare void @starttime()\n");
        fprintf(fll, "declare void @stoptime()\n");
    }
    return 0;
}