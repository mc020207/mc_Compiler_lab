#include "treep2assem.h"
#include "stdlib.h"
#include "string.h"
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
#define lbegin Temp_namedlabel(String("lbegin"))
#define lend Temp_namedlabel(String("lend"))

// Temp_temp return_temp=NULL;
Temp_label return_label=NULL;
char des[1000];
static char strbinop[][5]={"add","sub","mul","sdiv"};
static char stricomp[][5]={"beq", "bne", "blt", "bgt", "ble", "bge"};
AS_instrList treep2assemExp(T_exp x,Temp_temp* rettemp,bool canMiss);
AS_instr AS_Label2(Temp_label lable){
    return AS_Label(String(strcat(String(S_name(lable)),":")),lable);
}
static Temp_temp r(int i){
    char des2[1000];
    sprintf(des2, "t%d", i);
    return TC(String(des2));
}
AS_instrList getargs(T_expList list){
    AS_instrList ans=NULL;
    Temp_tempList arglist=NULL;
    int i=-1;
    for (T_expList now=list;now;now=now->tail,i++){
        Temp_temp temp=NULL;
        ans=AS_splice(ans,treep2assemExp(now->head,&temp,TRUE));
        arglist=TL(temp,arglist);
    }
    for (int j=i;arglist;arglist=arglist->tail,j--){
        if (j>=4){
            ans=AS_splice(ans,I(OI("push {`s0}",NULL,T(arglist->head),NULL)));
        }else{
            ans=AS_splice(ans,I(OI("mov `d0, `s0",T(r(j)),T(arglist->head),NULL)));
        }
    }
    // if (i!=-1){
    //     sprintf(des,"sub `d0,`s0,#%d",4*(i>=3?4:(i+1)));
    //     ans=AS_splice(ans,I(OI(String(des),T(sp),T(sp),NULL)));
    // }
    return ans;
}
AS_instrList treep2assemExp(T_exp x,Temp_temp* rettemp,bool canMiss){
    if (x==NULL) return NULL;
    AS_instrList ans=checked_malloc(sizeof(*ans));
    ans->head=NULL;ans->tail=NULL;
    Temp_temp ret;
    if (*rettemp) ret=*rettemp;
    else ret=Temp_newtemp();
    switch (x->kind){
        case T_BINOP:{
            Temp_temp temp1=NULL,temp2=NULL;
            free(ans);
            bool canconst=!(x->u.BINOP.op==T_mul||x->u.BINOP.op==T_div);
            if (x->u.BINOP.left->kind==T_CONST&&x->u.BINOP.op!=T_div&&canconst){
                Temp_temp temp1=NULL;
                ans=treep2assemExp(x->u.BINOP.right,&temp1,TRUE);
                if (x->u.BINOP.op==T_minus) sprintf(des,"rsb `d0, `s0,#%d",x->u.BINOP.left->u.CONST);
                else sprintf(des,"%s `d0, `s0,#%d",strbinop[x->u.BINOP.op],x->u.BINOP.left->u.CONST);
                ans=AS_splice(ans,I(OI(String(des),T(ret),T(temp1),NULL)));
            }else if (x->u.BINOP.right->kind==T_CONST&&canconst){
                Temp_temp temp1=NULL;
                ans=treep2assemExp(x->u.BINOP.left,&temp1,TRUE);
                sprintf(des,"%s `d0, `s0,#%d",strbinop[x->u.BINOP.op],x->u.BINOP.right->u.CONST);
                ans=AS_splice(ans,I(OI(String(des),T(ret),T(temp1),NULL)));
            }else{
                Temp_temp temp1=NULL,temp2=NULL;
                ans=treep2assemExp(x->u.BINOP.left,&temp1,TRUE);
                ans=AS_splice(ans,treep2assemExp(x->u.BINOP.right,&temp2,TRUE));
                sprintf(des,"%s `d0, `s0, `s1",strbinop[x->u.BINOP.op]);
                ans=AS_splice(ans,I(OI(String(des), T(ret), TL(temp1, T(temp2)), NULL)));
            }
            break;
        }
        case T_MEM:{
            free(ans);
            Temp_temp tempsrcptr=NULL;
            ans=treep2assemExp(x->u.MEM,&tempsrcptr,TRUE);
            ans=AS_splice(ans,I(OI("ldr `d0, [`s0]",T(ret),T(tempsrcptr),NULL)));
            break;
        }
        case T_TEMP:{
            if(canMiss&&*rettemp==NULL) ret=x->u.TEMP;
            else ans->head=MI("mov `d0, `s0",T(ret),T(x->u.TEMP));
            break;
        }
        case T_ESEQ:{
            assert(0);
            break;
        }
        case T_NAME:{
            sprintf(des,"ldr `d0 , = %s",S_name(x->u.NAME));
            ans->head=OI(String(des),T(ret),NULL,NULL);
            break;
        }
        case T_CONST:{
            sprintf(des,"mov `d0, #%d", x->u.CONST);
            ans->head=OI(String(des),T(ret),NULL,NULL);
            break;
        }
        case T_CALL:{
            free(ans);
            Temp_temp tempfucptr=NULL;
            ans=treep2assemExp(x->u.CALL.obj,&tempfucptr,TRUE);
            ans=AS_splice(ans,getargs(x->u.CALL.args));
            ans=AS_splice(ans,I(OI("blx `s0",TL(lr,TL(r0,TL(r1,TL(r2,T(r3))))),T(tempfucptr),NULL)));
            ans=AS_splice(ans,I(OI("mov `d0, `s0",T(ret),T(r(0)),NULL)));
            break;
        }
        case T_ExtCALL:{
            ans=getargs(x->u.ExtCALL.args);
            sprintf(des,"bl %s",x->u.ExtCALL.extfun);
            ans=AS_splice(ans,I(OI(String(des),TL(lr,TL(r0,TL(r1,TL(r2,T(r3))))),NULL,NULL)));
            ans=AS_splice(ans,I(OI("mov `d0, `s0",T(ret),T(r(0)),NULL)));
        }
    }
    if (ans->head==NULL) ans=NULL;
    *rettemp=ret;
    return ans;
}
AS_instrList treep2assemStm(T_stm x){
    if (x==NULL) return NULL;
    AS_instrList ans=checked_malloc(sizeof(*ans));
    ans->head=NULL;ans->tail=NULL;
    switch (x->kind){
         case T_SEQ:{
            ans=AS_splice(treep2assemStm(x->u.SEQ.left),treep2assemStm(x->u.SEQ.right));
            break;
         }
         case T_LABEL:{
            ans->head=AS_Label2(x->u.LABEL);
            break;
         }
         case T_JUMP:{
            sprintf(des,"b %s",S_name(x->u.JUMP.jump));
            ans->head=OI(String(des),NULL,NULL,AS_Targets(L(x->u.JUMP.jump)));
            break;
         }
         case T_CJUMP:{
            free(ans);
            if (x->u.CJUMP.right->kind==T_CONST){
                Temp_temp temp1=NULL;
                ans=treep2assemExp(x->u.CJUMP.left,&temp1,TRUE);
                sprintf(des,"cmp `s0,#%d",x->u.CJUMP.right->u.CONST);
                ans=AS_splice(ans,I(OI(String(des),NULL,T(temp1),NULL)));
            }else{
                Temp_temp temp1=NULL,temp2=NULL;
                ans=treep2assemExp(x->u.CJUMP.left,&temp1,TRUE);
                ans=AS_splice(ans,treep2assemExp(x->u.CJUMP.right,&temp2,TRUE));
                ans=AS_splice(ans,I(OI("cmp `s0,`s1",NULL,TL(temp1,T(temp2)),NULL)));
            }
            sprintf(des,"%s `j0",stricomp[x->u.CJUMP.op]);
            ans=AS_splice(ans,I(OI(String(des),NULL,NULL,AS_Targets(LL(x->u.CJUMP.true,L(x->u.CJUMP.false))))));
            break;
         }
         case T_MOVE:{
            free(ans);
            if (x->u.MOVE.dst->kind==T_TEMP){
                if(x->u.MOVE.src->kind==T_TEMP){
                    ans=I(AS_Move("mov `d0,`s0",T(x->u.MOVE.dst->u.TEMP),T(x->u.MOVE.src->u.TEMP)));
                }else{
                    Temp_temp temp1=x->u.MOVE.dst->u.TEMP;
                    ans=treep2assemExp(x->u.MOVE.src,&temp1,FALSE);
                }
            }else if (x->u.MOVE.dst->kind==T_MEM){
                Temp_temp tempsrc=NULL,tempdst=NULL;
                ans=treep2assemExp(x->u.MOVE.dst->u.MEM,&tempdst,TRUE);
                ans=AS_splice(ans,treep2assemExp(x->u.MOVE.src,&tempsrc,TRUE));
                ans=AS_splice(ans,I(OI("str `s0, [`s1]",NULL,TL(tempsrc,T(tempdst)),NULL)));
            }else{
                assert(0);
            }
            break;
         }
         case T_EXP:{
            free(ans);
            Temp_temp temp=NULL;
            ans=treep2assemExp(x->u.EXP,&temp,FALSE);
            break;
         }
         case T_RETURN:{
            free(ans);
            Temp_temp temp=r(0);
            ans=treep2assemExp(x->u.EXP,&temp,TRUE);
            // ans=AS_splice(ans,I(OI(String("mov `d0, `s0"),T(sp) , T(fp), NULL)));
            // ans=AS_splice(ans,I(OI(String("pop {`s0}"),NULL , T(fp), NULL)));
            ans=AS_splice(ans,I(OI(String("b `j0"),NULL , NULL, AS_Targets(L(return_label)))));
            break;
         }
    }
    return ans;
}
AS_instrList treep2assemStmList(T_stmList list){
    if (list==NULL) return NULL;
    AS_instrList now = treep2assemStm(list->head);
    return AS_splice(now,treep2assemStmList(list->tail));
}
AS_blockList treep2assemblcok(struct C_block block){
    if (!block.stmLists) return NULL;
    // if (!return_temp) return_temp=Temp_newtemp();
    if (!return_label) return_label=Temp_newlabel();
    AS_instrList now1 = treep2assemStmList(block.stmLists->head);
    AS_block now=AS_Block(now1);
    block.stmLists=block.stmLists->tail;
    return AS_BlockList(now,treep2assemblcok(block));
}
AS_instrList treep2assemfuction(AS_blockList aslist,T_funcDecl x){
    sprintf(des,"%s: ",x->name);
    AS_instrList prolog=I(LI(String(des),Temp_namedlabel(String(x->name))));
    // prolog=AS_splice(prolog,I(OI("push {`s0}", NULL, T(fp), NULL)));
    // prolog=AS_splice(prolog,I(MI("mov `d0, `s0", T(fp), T(sp))));
    // prolog=AS_splice(prolog,I(MI("mov `d0, `s0", T(return_temp), T(lr))));
    // prolog=AS_splice(prolog,I(OI("push {`s0}", NULL, T(fp), NULL)));
    Temp_tempList list=x->args;
    for (int i=0;list;list=list->tail,i++){
        if (i<4){
            prolog=AS_splice(prolog,I(MI("mov `d0, `s0",T(list->head),T(r(i)))));
        }else{
            sprintf(des,"ldr `d0, [fp, #%d]",4*(i-3));
            prolog=AS_splice(prolog,I(OI(String(des),T(list->head),NULL,NULL)));
        }
    }
    AS_instrList epilog=I(AS_Label2(return_label));
    /* I(LI("lend:", lend));
    epilog=AS_splice(epilog,I(OI("mov `d0, #-2", T(r0), NULL, NULL)));
    epilog=AS_splice(epilog,I(MI("mov `d0, `s0", T(sp), T(fp))));
    epilog=AS_splice(epilog,I(OI("pop {`d0}", T(fp), NULL, NULL)));
    epilog=AS_splice(epilog,I(OI("bx `s0", NULL, T(return_temp), NULL))); */
    AS_instrList il = AS_traceSchedule(aslist, prolog, epilog, FALSE);
    // return_temp=NULL;
    return_label=NULL;
    return il;
}