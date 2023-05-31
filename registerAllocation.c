#include "registerAllocation.h"
#include <string.h>
#define OFFSETSTEP 4
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
#define r0 TC(String("t0"))
#define r1 TC(String("t1"))
#define r2 TC(String("t2"))
#define r3 TC(String("t3"))
#define r4 TC(String("t4"))
#define r5 TC(String("t5"))
#define r6 TC(String("t6"))
#define r7 TC(String("t7"))
#define r8 TC(String("t8"))
#define r9 TC(String("t9"))
#define r10 TC(String("t10"))
#define r11 TC(String("t11"))
#define fp TC(String("t11"))
#define sp TC(String("t13"))
#define lr TC(String("t14"))
TAB_table tempToNode; // key=temp value=Gnode
TAB_table colorTable; // key=temp value=colorNode
TAB_table inCanInStack; // key=temp value=empty_pointer
TAB_table fanout; // key=temp value=int
typedef struct node{
    bool isSpill;
    int renum;
}colorNode_;
typedef colorNode_* colorNode;
int mxrenum=0;
int spillOffset=0;
const int canUserRegister=9;
Temp_tempList colorstack=NULL;
Temp_tempList canInStack=NULL;
char *emptyPoint=NULL;
char des[1000];
static int sx[]={0,1,2,3,14,4,5,6,7};
static Temp_temp r(int i){
    char des2[1000];
    sprintf(des2, "t%d", i);
    return TC(String(des2));
}
AS_instrList renameColor(AS_instrList il){
    AS_instrList pre=NULL;
    for (AS_instrList list=il;list;list=list->tail){
        AS_instr x=list->head;
        if (x->kind==I_LABEL){
            pre=list;
            continue;
        }
        Temp_tempList desList=x->u.OPER.dst,srcList=x->u.OPER.src;
        int ptrnum=8;
        for (;srcList;srcList=srcList->tail){
            colorNode nowcNode=(colorNode)TAB_look(colorTable,srcList->head);
            if (nowcNode->isSpill){
                sprintf(des,"ldr `d0 , [`s0 , #%d]",nowcNode->renum);
                AS_instr y=OI(String(des),T(r(ptrnum)),T(sp),NULL);
                if (pre==NULL){
                    pre=il=AS_InstrList(y,list);
                    pre->tail=list;
                }else{
                    pre->tail=AS_InstrList(y,list);
                    pre=pre->tail;
                }
                srcList->head=r(ptrnum);
                mxrenum=mxrenum>ptrnum?mxrenum:ptrnum;
                ptrnum++;
            }else{
                srcList->head=r(nowcNode->renum);
            }
        }
        for (;desList;desList=desList->tail){
            colorNode nowcNode=(colorNode)TAB_look(colorTable,desList->head);
            if (nowcNode->isSpill){
                sprintf(des,"str `s0 , [`s1 , #%d]",nowcNode->renum);
                // printf("%s\n",des);
                AS_instr y=OI(String(des),NULL,TL(r(ptrnum),T(sp)),NULL);
                // AS_printInstrList(stdout,I(y),Temp_name());
                list->tail=AS_InstrList(y,list->tail);
                list=list->tail;
                desList->head=r(ptrnum);
                mxrenum=mxrenum>ptrnum?mxrenum:ptrnum;
                ptrnum++;
            }else{
                desList->head=r(nowcNode->renum);
            }
        }
        pre=list;
    }
    return il;
}
void selectColor(){
    while (colorstack){
        Temp_temp xTemp=colorstack->head;
        G_node xnode=TAB_look(tempToNode,xTemp);
        colorstack=colorstack->tail;
        int vis=0;
        G_nodeList adj=G_succ(xnode);
        colorNode nowcNode=checked_malloc(sizeof(*nowcNode));
        for (;adj;adj=adj->tail){
            Temp_temp nowTemp=(Temp_temp)G_nodeInfo(adj->head);
            colorNode cNode=TAB_look(colorTable,nowTemp);
            if (cNode==NULL) continue;
            if (cNode->isSpill) continue;
            vis|=1<<cNode->renum;
        }
        nowcNode->isSpill=1;
        for (int i=0;i<canUserRegister;i++){
            if ((vis&(1<<sx[i]))==0){
                nowcNode->isSpill=0;
                nowcNode->renum=sx[i];
                mxrenum=mxrenum>i?mxrenum:i;
                break;
            }   
        }
        if (nowcNode->isSpill){
            nowcNode->renum=spillOffset;
            spillOffset+=OFFSETSTEP;
        }
        TAB_enter(colorTable,xTemp,nowcNode);
        // printf("%s -> %d %d\n",Temp_look(Temp_name(),xTemp),nowcNode->isSpill,nowcNode->renum);
    }
}
void simplify(G_nodeList ig){
    bool finish=0;
    while (!finish){
        while (canInStack){
            Temp_temp x=canInStack->head;
            G_node xnode=(G_node)TAB_look(tempToNode,x);
            canInStack=canInStack->tail;
            colorstack=Temp_TempList(x,colorstack);
            G_nodeList adj=G_succ(xnode);
            for (;adj;adj=adj->tail){
                Temp_temp nowTemp=(Temp_temp)G_nodeInfo(adj->head);
                if (TAB_look(inCanInStack,nowTemp)) continue;
                int *num=TAB_look(fanout,nowTemp);
                assert(num);
                *num--;
                if (*num<canUserRegister){
                    canInStack=Temp_TempList(nowTemp,canInStack);
                    TAB_enter(inCanInStack,nowTemp,emptyPoint);
                }
            }
        }
        finish=1;
        for (G_nodeList list=ig;list;list=list->tail){
            Temp_temp nowTemp=(Temp_temp)G_nodeInfo(list->head);
            if (!TAB_look(inCanInStack,nowTemp)){
                finish=0;
                canInStack=Temp_TempList(nowTemp,canInStack);
                TAB_enter(inCanInStack,nowTemp,emptyPoint);
                break;
            }
        }
    }
}
AS_instrList registerAllocation(AS_instrList il,G_nodeList ig){
    tempToNode=TAB_empty();
    colorTable=TAB_empty();
    inCanInStack=TAB_empty();
    fanout=TAB_empty();
    emptyPoint=malloc(sizeof(1));
    assert(colorstack==NULL);
    assert(canInStack==NULL);
    spillOffset=0;
    mxrenum=0;
    for (int i=0;i<=14;i++){
        Temp_temp xTemp=r(i);
        TAB_enter(inCanInStack,xTemp,emptyPoint);
        colorNode nowcNode=checked_malloc(sizeof(*nowcNode));
        nowcNode->isSpill=0;nowcNode->renum=i;
        TAB_enter(colorTable,xTemp,nowcNode);
    }
    for (G_nodeList list=ig;list;list=list->tail){
        G_node x=list->head;
        Temp_temp xTemp=G_nodeInfo(x);
        TAB_enter(tempToNode,xTemp,x);
        G_nodeList adj=G_succ(x);
        int *num=checked_malloc(sizeof(int));
        *num=0;
        for (;adj;adj=adj->tail,*num++);
        TAB_enter(fanout,xTemp,num);
        if (strlen(Temp_look(Temp_name(),xTemp))<=2) continue;
        else if (*num<canUserRegister){
            canInStack=Temp_TempList(xTemp,canInStack);
            TAB_enter(inCanInStack,xTemp,emptyPoint);
        }
    }
    simplify(ig);
    selectColor();
    mxrenum=mxrenum<=4?0:mxrenum-1;
    il=renameColor(il);
    AS_instrList prolog=I(OI("push {`s0,`s1}",NULL,TL(fp,T(lr)),NULL));
    prolog=AS_splice(prolog,I(OI("add `d0, `s0, #4",T(fp),T(sp),NULL)));
    for (int i=4;i<=mxrenum;i++){
        prolog=AS_splice(prolog,I(OI("push {`s0}",NULL,T(r(i)),NULL)));
    }
    sprintf(des,"sub `d0, `s0, #%d",spillOffset);
    prolog=AS_splice(prolog,I(OI(String(des),T(sp),T(sp),NULL)));
    sprintf(des,"add `d0, `s0, #%d",spillOffset);
    AS_instrList epilog=I(OI(String(des),T(sp),T(sp),NULL));
    for (int i=mxrenum;i>=4;i--){
        epilog=AS_splice(epilog,I(OI("pop {`d0}",T(r(i)),NULL,NULL)));
    }
    epilog=AS_splice(epilog,I(OI("pop {`d0,`d1}",TL(fp,T(lr)),NULL,NULL)));
    epilog=AS_splice(epilog,I(OI("bx `s0",NULL,T(lr),NULL)));
    il->tail=AS_splice(prolog,il->tail);
    il=AS_splice(il,epilog);
    return il;
}