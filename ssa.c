# include "ssa.h"
# include <stdio.h>
S_table label2Block;
S_table notDOfBlocks; // key=block.label value=S_table(block.label,bool)
S_table DFOfBlocks; // key=block.label value=S_table(block.label,bool)
S_table stackOfParams; //key=Temp_temp value=a list record temp
S_table originOfBlock; // key=block.label value=S_table(Temp_temp,bool)
S_table inOfBlock; // key=block.label value=S_table(Temp_temp,bool)
S_table defsites; // key=Temp_temp value=S_table(Label,bool)
S_table phiBlock; // key=S_label value=S_table(Temp_temp,bool)
G_graph RA_bg;
int *emptyPoint;
bool isDomin(Temp_label label1,Temp_label label2){ // is label1 domin label2?
    S_table nowTabel=S_look(notDOfBlocks,label2);
    if (nowTabel==NULL) return TRUE;
    if (S_look(nowTabel,label1)) return FALSE;
    return TRUE;
}
bool inTable(S_table table,void *x,void *y){
    S_table nowTable=S_look(table,x);
    if (!nowTable) return FALSE;
    if (S_look(nowTable,y)) return 1;
    return 0;
}
bool enter_table(S_table table,void* label1,void* label2,bool cansame){
    if (!cansame&&label1==label2) return FALSE;
    S_table nowTable=S_look(table,label1);
    if (nowTable==NULL){
        nowTable=S_empty();
        S_enter(table,label1,nowTable);
    }
    void *x=S_look(nowTable,label2);
    if (x==NULL) {
        S_enter(nowTable,label2,emptyPoint);
        return TRUE;
    }
    return FALSE;
}
bool mergeTable(Temp_label labelTo,Temp_label labelFrom){
    S_table tableFrom=S_look(notDOfBlocks,labelFrom);
    if (!tableFrom) return FALSE;
    if (!tableFrom->top) return FALSE;
    bool change=0;
    Temp_label key=tableFrom->top;
    change|=enter_table(notDOfBlocks,labelTo,key,FALSE);
    TAB_pop(tableFrom);
    mergeTable(labelTo,labelFrom);
    S_enter(tableFrom,key,emptyPoint);
    return change;
}
void getDOfBlocks(G_nodeList list){
    Temp_label headLable=((AS_block)G_nodeInfo(list->head))->label;
    S_enter(label2Block,headLable,list->head);
    for (G_nodeList x=list->tail;x;x=x->tail){
        Temp_label nowLable=((AS_block)G_nodeInfo(x->head))->label;
        S_enter(label2Block,nowLable,x->head);
        enter_table(notDOfBlocks,headLable,nowLable,FALSE);
    }
    bool change=TRUE;
    while(change){
        change=FALSE;
        for (G_nodeList x=list->tail;x;x=x->tail){
            Temp_label nowLable=((AS_block)G_nodeInfo(x->head))->label;
            for (G_nodeList y=G_pred(x->head);y;y=y->tail){
                change|=mergeTable(nowLable,((AS_block)G_nodeInfo(y->head))->label);
            }
        }
    }
}
void PRINTD(G_nodeList list){
    for (G_nodeList x=list;x;x=x->tail){
        Temp_label xLabel=((AS_block)G_nodeInfo(x->head))->label;
        printf("%s : ",S_name(xLabel));
        for (G_nodeList y=list;y;y=y->tail){
            Temp_label yLabel=((AS_block)G_nodeInfo(y->head))->label;
            if (isDomin(xLabel,yLabel)) printf("%s ",S_name(yLabel));
        }
        printf("\n");
    }
}
bool isDF(G_node x,G_node w){
    Temp_label xLabel=((AS_block)G_nodeInfo(x))->label;
    Temp_label wLabel=((AS_block)G_nodeInfo(w))->label;
    for (G_nodeList predList=G_pred(w);predList;predList=predList->tail){
        G_node p=predList->head;
        Temp_label pLabel=((AS_block)G_nodeInfo(p))->label;
        // printf("    --%s--\n",S_name(pLabel));
        if (isDomin(xLabel,pLabel)&&(!(isDomin(xLabel,wLabel)&&wLabel!=xLabel)))return TRUE;
    }
    return FALSE;
}
void getDFOfBlocks(G_nodeList list){
    for (G_nodeList x=list;x;x=x->tail){
        Temp_label xLabel=((AS_block)G_nodeInfo(x->head))->label;
        // printf("----%s----\n",S_name(xLabel));
        for (G_nodeList y=list;y;y=y->tail){
            Temp_label yLabel=((AS_block)G_nodeInfo(y->head))->label;
            // printf("  ---%s---\n",S_name(yLabel));
            if(isDF(x->head,y->head)){
                enter_table(DFOfBlocks,xLabel,yLabel,TRUE);
                printf("DF(%s) -> %s\n",S_name(xLabel),S_name(yLabel));
            }
        }
    }
}
void initOriginAndIn(G_nodeList ig){
    Temp_label nowLabel=NULL;
    for (G_nodeList ttt=ig;ttt;ttt=ttt->tail){
        G_node x=ttt->head;
        AS_instr nowinstr=((AS_instr)G_nodeInfo(x));
        if (nowinstr->kind==I_LABEL){
            nowLabel=nowinstr->u.LABEL.label;
            for (Temp_tempList tempList=FG_In(x);tempList;tempList=tempList->tail){
                // printf("%s %s\n",S_name(nowLabel),Temp_look(Temp_name(),tempList->head));
                enter_table(inOfBlock,nowLabel,tempList->head,FALSE);
            }
        }else{
            for (Temp_tempList tempList=FG_def(x);tempList;tempList=tempList->tail){
                enter_table(originOfBlock,nowLabel,tempList->head,FALSE);
            }
        }
    }
}
void fillDefsitesTable(Temp_label label){
    S_table nowTable=S_look(originOfBlock,label);
    if (nowTable==NULL) return ;
    if (nowTable->top==NULL) return ;
    Temp_temp temp=(Temp_temp)nowTable->top;
    enter_table(defsites,temp,label,FALSE);
    TAB_pop(nowTable);
    fillDefsitesTable(label);
    TAB_enter(nowTable,temp,emptyPoint);
}
void solveTemp(Temp_temp nowTemp){
    S_table nowTable=TAB_look(defsites,nowTemp);
    if (nowTable==NULL) return ;
    if (nowTable->top==NULL) return ;
    Temp_label label=(S_symbol)nowTable->top;
    TAB_pop(nowTable);
    S_table dfTable=S_look(DFOfBlocks,label);
    if (dfTable){
        Temp_label y=dfTable->top;
        while (y){
            
            if (!inTable(phiBlock,y,nowTemp)&&inTable(inOfBlock,y,nowTemp)){
                enter_table(phiBlock,y,nowTemp,FALSE);
                G_node node=S_look(label2Block,y);
                AS_instrList instrList=((AS_block)G_nodeInfo(node))->instrs;
                AS_instr insertInstr=AS_Oper("phi %`s0",NULL,Temp_TempList(nowTemp,NULL),NULL);
                instrList->tail=AS_InstrList(insertInstr,instrList->tail);
                if (inTable(originOfBlock,y,nowTemp)&&!S_look(nowTable,y)){
                    S_enter(nowTable,y,emptyPoint);
                }
            }
            
            binder bin=TAB_getBinder(dfTable,y);
            printf("____%s_____\n",S_name(y));
            y=(Temp_label)bin->prevtop;
        }
    }   
    
}
void addPhiFuction(G_nodeList list){
    for (G_nodeList list2=list;list2;list2=list2->tail){
        G_node x=list2->head;
        Temp_label xLabel=((AS_block)G_nodeInfo(x))->label;
        fillDefsitesTable(xLabel);
    }
    Temp_temp nowTemp=(Temp_temp)defsites->top;
    while (nowTemp){
        printf("_____%s______\n",Temp_look(Temp_name(),nowTemp));
        solveTemp(nowTemp);
        binder bin=TAB_getBinder(defsites,nowTemp);
        nowTemp=(Temp_temp)bin->prevtop;
    }
}
void ssa(AS_blockList blockList,G_nodeList bg,G_nodeList ig){
    if (blockList==NULL||bg==NULL) return ;
    label2Block=S_empty();
    notDOfBlocks=S_empty();
    DFOfBlocks=S_empty();
    stackOfParams=S_empty();
    originOfBlock=S_empty();
    inOfBlock=S_empty();
    defsites=S_empty();
    phiBlock=S_empty();
    emptyPoint=checked_malloc(sizeof(int));
    RA_bg=Bg_graph();
    getDOfBlocks(bg);
    // PRINTD(bg);
    getDFOfBlocks(bg);
    initOriginAndIn(ig);
    printf("init\n");
    addPhiFuction(bg);
    // renameParams(blockList);
}