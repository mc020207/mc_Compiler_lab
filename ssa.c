# include "ssa.h"
# include <stdio.h>
S_table notDOfBlocks; // key=block.label value=S_table(block.label,bool)
S_table DFOfBlocks; // key=block.label value=S_table(block.label,bool)
S_table stackOfParams; //key=Temp_temp value=a list record temp
S_table originOfBlock; // key=block.label value=S_table(Temp_temp,bool)
S_table inOfBlock; // key=block.label value=S_table(Temp_temp,bool)
G_graph RA_bg;
int *emptyPoint;
bool isDomin(Temp_label label1,Temp_label label2){ // is label1 domin label2?
    S_table nowTabel=S_look(notDOfBlocks,label2);
    if (nowTabel==NULL) return TRUE;
    if (S_look(nowTabel,label1)) return FALSE;
    return TRUE;
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
    for (G_nodeList x=list->tail;x;x=x->tail){
        Temp_label nowLable=((AS_block)G_nodeInfo(x->head))->label;
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
void addPhiFuction(G_nodeList list,G_nodeList ig){
    Temp_label nowLabel=NULL;
    for (G_nodeList ttt=ig;ttt;ttt=ttt->tail){
        G_node x=ttt->head;
        AS_instr nowinstr=((AS_instr)G_nodeInfo(x));
        if (nowinstr->kind==I_LABEL){
            nowLabel=nowinstr->u.LABEL.label;
            for (Temp_tempList tempList=FG_In(x);tempList;tempList=tempList->tail){
                printf("%s %s\n",S_name(nowLabel),Temp_look(Temp_name(),tempList->head));
                enter_table(inOfBlock,nowLabel,tempList->head,FALSE);
            }
        }else{
            for (Temp_tempList tempList=FG_def(x);tempList;tempList=tempList->tail){
                enter_table(inOfBlock,nowLabel,tempList->head,FALSE);
            }
        }
    }
}
void ssa(AS_blockList blockList,G_nodeList bg,G_nodeList ig){
    if (blockList==NULL||bg==NULL) return ;
    notDOfBlocks=S_empty();
    DFOfBlocks=S_empty();
    stackOfParams=S_empty();
    originOfBlock=S_empty();
    inOfBlock=S_empty();
    emptyPoint=checked_malloc(sizeof(int));
    RA_bg=Bg_graph();
    getDOfBlocks(bg);
    // PRINTD(bg);
    getDFOfBlocks(bg);
    addPhiFuction(bg,ig);
    // renameParams(blockList);
}