# include "ssa.h"
# include <stdio.h>
# include <string.h>
S_table label2Block;
S_table notDOfBlocks; // key=block.label value=S_table(block.label,bool)
S_table DFOfBlocks; // key=block.label value=S_table(block.label,bool)
S_table stackOfParams; //key=Temp_temp value=Temp_tempList
S_table originOfBlock; // key=block.label value=S_table(Temp_temp,bool)
S_table inOfBlock; // key=block.label value=S_table(Temp_temp,bool)
S_table defsites; // key=Temp_temp value=S_table(Label,bool)
S_table phiBlock; // key=S_label value=S_table(Temp_temp,bool)
S_table visBlock; // key=S_label value=bool(isvis)
G_graph RA_bg;
int *emptyPoint;
char des[1000];
char des2[1010];
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
bool isPhi(string s){
    string t="%`d0=phi i64 ";
    for (int i=0;i<strlen(t);i++){
        if (s[i]!=t[i]) return 0;
    }
    return 1;
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
bool isDF(G_node x,G_node w){
    Temp_label xLabel=((AS_block)G_nodeInfo(x))->label;
    Temp_label wLabel=((AS_block)G_nodeInfo(w))->label;
    for (G_nodeList predList=G_pred(w);predList;predList=predList->tail){
        G_node p=predList->head;
        Temp_label pLabel=((AS_block)G_nodeInfo(p))->label;
        if (isDomin(xLabel,pLabel)&&(!(isDomin(xLabel,wLabel)&&wLabel!=xLabel)))return TRUE;
    }
    return FALSE;
}
void getDFOfBlocks(G_nodeList list){
    for (G_nodeList x=list;x;x=x->tail){
        Temp_label xLabel=((AS_block)G_nodeInfo(x->head))->label;
        for (G_nodeList y=list;y;y=y->tail){
            Temp_label yLabel=((AS_block)G_nodeInfo(y->head))->label;
            if(isDF(x->head,y->head)){
                enter_table(DFOfBlocks,xLabel,yLabel,TRUE);
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
AS_instr getPhiFuction(G_node node,Temp_temp temp){
    Temp_tempList tempList=NULL;
    sprintf(des,"%%`d0=phi i64 ");
    bool first=1;
    G_nodeList list=G_pred(node);
    int idx=0;
    for (;list;list=list->tail){
        G_node x=list->head;
        if (!first) strcat(des,",");
        first=0;
        sprintf(des2,"[%%`s%d,%%%s]",idx,S_name(((AS_block)G_nodeInfo(x))->label));
        strcat(des,des2);
        tempList=Temp_TempList(temp,tempList);
        idx++;
    }
    return AS_Oper(String(des),Temp_TempList(temp,NULL),tempList,NULL);
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
                AS_instr insertInstr=getPhiFuction(node,nowTemp);
                instrList->tail=AS_InstrList(insertInstr,instrList->tail);
                if (!inTable(originOfBlock,y,nowTemp)&&!S_look(nowTable,y)){
                    S_enter(nowTable,y,emptyPoint);
                }
            }
            binder bin=TAB_getBinder(dfTable,y);
            y=(Temp_label)bin->prevtop;
        }
    }   
    solveTemp(nowTemp);
}
void addPhiFuction(G_nodeList list){
    for (G_nodeList list2=list;list2;list2=list2->tail){
        G_node x=list2->head;
        Temp_label xLabel=((AS_block)G_nodeInfo(x))->label;
        fillDefsitesTable(xLabel);
    }
    Temp_temp nowTemp=(Temp_temp)defsites->top;
    while (nowTemp){
        solveTemp(nowTemp);
        binder bin=TAB_getBinder(defsites,nowTemp);
        nowTemp=(Temp_temp)bin->prevtop;
    }
}
void renamePhi(G_node x,Temp_label faLabel){
    AS_instrList xlist=((AS_block)G_nodeInfo(x))->instrs;
    for (xlist=xlist->tail;xlist;xlist=xlist->tail){
        AS_instr now=xlist->head;
        if (now->kind==I_LABEL) break;
        if (isPhi(now->u.OPER.assem)){
            G_nodeList pred=G_pred(x);
            Temp_tempList tempList=now->u.OPER.src;
            for (;pred;pred=pred->tail,tempList=tempList->tail){
                Temp_label predLabel=((AS_block)G_nodeInfo(pred->head))->label;
                if (predLabel==faLabel){
                    Temp_temp src=tempList->head;
                    if (TAB_look(stackOfParams,src)==NULL) TAB_enter(stackOfParams,src,Temp_TempList(src,Temp_TempList(src,NULL)));
                    tempList->head=((Temp_tempList)TAB_look(stackOfParams,src))->tail->head;
                    break;
                }
            }
        }
    }
}
void renameDst(AS_instrList list){
    if (!list) return ;
    if (list->head->kind==I_LABEL) return ;
    renameDst(list->tail);
    
    AS_instr x=list->head;
    Temp_tempList dstList=x->u.OPER.dst;
    if (dstList){
        Temp_temp dst=dstList->head;
        Temp_tempList stackList=TAB_look(stackOfParams,dst);
        assert(stackList->tail);
        if (dst!=stackList->tail->head){
            x->u.OPER.dst->head=stackList->tail->head;
            stackList->tail=stackList->tail->tail;
        }
    }
}
void renameBlock(G_node x){
    Temp_label xLabel=((AS_block)G_nodeInfo(x))->label;
    if (S_look(visBlock,xLabel)) return ;
    S_enter(visBlock,xLabel,emptyPoint);
    AS_instrList xlist=((AS_block)G_nodeInfo(x))->instrs;
    xlist=xlist->tail;
    for (;xlist;xlist=xlist->tail){
        AS_instr now=xlist->head;
        if (now->kind==I_LABEL) break;
        if (!isPhi(now->u.OPER.assem)){
            Temp_tempList srcList=now->u.OPER.src;
            for (;srcList;srcList=srcList->tail){
                Temp_temp src=srcList->head;
                if (TAB_look(stackOfParams,src)==NULL) TAB_enter(stackOfParams,src,Temp_TempList(src,Temp_TempList(src,NULL)));
                srcList->head=((Temp_tempList)TAB_look(stackOfParams,src))->tail->head;
            }
        }
        Temp_tempList dstList=now->u.OPER.dst;
        if (dstList){
            Temp_temp dst=dstList->head;
            Temp_tempList stackList=TAB_look(stackOfParams,dst);
            if (stackList==NULL){
                stackList=Temp_TempList(dst,Temp_TempList(dst,NULL));
                TAB_enter(stackOfParams,dst,stackList);
            }
            else stackList->tail=Temp_TempList(Temp_newtemp(),stackList->tail);
        }
    }
    G_nodeList succ=G_succ(x);
    for (;succ;succ=succ->tail){
        renamePhi(succ->head,xLabel);
    }
    succ=G_succ(x);
    for (;succ;succ=succ->tail){
        renameBlock(succ->head);
    }
    xlist=((AS_block)G_nodeInfo(x))->instrs;
    xlist=xlist->tail;
    renameDst(xlist);
}
void renameParams(G_nodeList bg){
    for (;bg;bg=bg->tail) renameBlock(bg->head);
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
    visBlock=S_empty();
    emptyPoint=checked_malloc(sizeof(int));
    RA_bg=Bg_graph();
    getDOfBlocks(bg);
    getDFOfBlocks(bg);
    initOriginAndIn(ig);
    addPhiFuction(bg);
    renameParams(bg);
}