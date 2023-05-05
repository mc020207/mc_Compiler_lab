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
char des[1000];
AS_instrList treep2assemExp(T_exp x,Temp_temp* rettemp);
AS_instr AS_Label2(Temp_label lable){
    return AS_Label(S_name(lable),lable);
}
AS_instrList getargs(T_expList list,string demand,Temp_tempList* templist,int d){
    if (!list) {
        strcpy(demand,"");
        *templist=NULL;
        return NULL;
    }
    if (d==1) sprintf(demand,"i64 %%`s%d",d);
    else sprintf(demand,",i64 %%`s%d",d);
    string tempstring=checked_malloc(sizeof(char)*100);// careful
    AS_instrList ans=getargs(list->tail,tempstring,templist,d+1);
    strcat(demand,tempstring);
    Temp_temp temp;
    ans=AS_splice(treep2assemExp(list->head,&temp),ans);
    *templist=Temp_TempList(temp,*templist);
    return ans;
}
AS_instrList treep2assemExp(T_exp x,Temp_temp* rettemp){
    if (x==NULL) return NULL;
    AS_instrList ans=checked_malloc(sizeof(*ans));
    // printf("%d\n",x->kind);
    ans->head=NULL;ans->tail=NULL;
    Temp_temp ret=Temp_newtemp();
    switch (x->kind){
        case T_BINOP:{
            Temp_temp temp1,temp2;
            free(ans);
            ans=AS_splice(treep2assemExp(x->u.BINOP.left,&temp1),treep2assemExp(x->u.BINOP.right,&temp2));
            switch (x->u.BINOP.op){
                case T_plus:{
                    strcpy(des,"%`d0 = add i32 %`s0, %`s1");
                    break;
                }
                case T_minus:{
                    strcpy(des,"%`d0 = sub i32 %`s0, %`s1");
                    break;
                }
                case T_mul:{
                    strcpy(des,"%`d0 = mul i32 %`s0, %`s1");
                    break;
                }
                case T_div:{
                    strcpy(des,"%`d0 = sdiv i32 %`s0, %`s1");
                    break;
                }
            }
            ans=AS_splice(ans,I(OI(String(des), T(ret), TL(temp1, T(temp2)), NULL)));
            break;
        }
        case T_MEM:{
            free(ans);
            Temp_temp tempsrci64,tempsrcptr;
            tempsrcptr=Temp_newtemp();
            ans=treep2assemExp(x->u.MEM,&tempsrci64);
            ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 `s0 to ptr",T(tempsrcptr),T(tempsrci64),NULL)));
            ans=AS_splice(ans,I(OI("%`d0 = load i64, ptr %`s0",T(ret),T(tempsrcptr),NULL)));
            break;
        }
        case T_TEMP:{
            ans->head=OI("%`d0 = add i32 %`s0, 0", T(ret), T(x->u.TEMP), NULL);
            break;
        }
        case T_ESEQ:{
            assert(0);
            break;
        }
        case T_NAME:{
            sprintf(des,"%`d0 = ptrtoint ptr @%s to i64",S_name(x->u.NAME));
            ans->head=OI(String(des),T(ret),NULL,NULL);
            break;
        }
        case T_CONST:{
            sprintf(des,"%`d0 = add i32 %d, 0",x->u.CONST);
            // printf("%s\n",des);
            ans->head=OI(String(des),T(ret),NULL,NULL);
            break;
        }
        case T_CALL:{
            free(ans);
            
            Temp_temp tempfuci64,tempfucptr=Temp_newtemp();
            ans=treep2assemExp(x->u.CALL.obj,&tempfuci64);
            ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 `s0 to ptr",T(tempfucptr),T(tempfuci64),NULL)));
            string des2=String("%`d0 = call i64 `s0(");
            string tempstring=checked_malloc(100);
            Temp_tempList args;
            ans=AS_splice(ans,getargs(x->u.CALL.args,tempstring,&args,1));
            strcat(des2,tempstring);
            strcat(des2,")");
            // printf("%s\n",des2);
            args=Temp_TempList(tempfucptr,args);
            // for (Temp_tempList list=args;list;list=list->tail) printf("1\n");
            ans=AS_splice(ans,I(OI(des2,T(ret),args,NULL)));
            break;
        }
        case T_ExtCALL:{
            if (strcmp(x->u.ExtCALL.extfun,"malloc")==0){
                Temp_temp temp1,temp2,temp3;
                temp2=Temp_newtemp();
                free(ans);
                ans=treep2assemExp(x->u.ExtCALL.args->head,&temp1);
                ans=AS_splice(ans,I(OI("%`d0 = call i64 @malloc(i64 %`s0)",T(temp2),T(temp1),NULL)));
                ans=AS_splice(ans,I(OI("%`d0 = ptrtoint ptr %`s0 to i64",T(ret),T(temp2),NULL)));
            }else{
                assert(0);
            }
            break;
        }
    }
    *rettemp=ret;
    return ans;
}
AS_instrList treep2assemStm(T_stm x){
    if (x==NULL) return NULL;
    AS_instrList ans=checked_malloc(sizeof(*ans));
    ans->head=NULL;ans->tail=NULL;
    switch (x->kind){
         case T_SEQ:{
            assert(0);
            ans=AS_splice(treep2assemStm(x->u.SEQ.left),treep2assemStm(x->u.SEQ.right));
            break;
         }
         case T_LABEL:{
            ans->head=AS_Label2(x->u.LABEL);
            break;
         }
         case T_JUMP:{
            sprintf(des,"br label %%%s",S_name(x->u.JUMP.jump));
            ans->head=AS_Oper(String(des),NULL,NULL,AS_Targets(L(x->u.JUMP.jump)));
            break;
         }
         case T_CJUMP:{
            free(ans);
            Temp_temp temp1,temp2,tempcond;
            tempcond=Temp_newtemp();
            ans=treep2assemExp(x->u.CJUMP.left,&temp1);
            ans=AS_splice(ans,treep2assemExp(x->u.CJUMP.right,&temp2));
            switch (x->u.CJUMP.op){
                case T_eq:{
                    strcpy(des,"%`d0 = icmp eq i64 %`s0, %`s1");
                    break;
                }
                case T_ne:{
                    strcpy(des,"%`d0 = icmp ne i64 %`s0, %`s1");
                    break;
                }
                case T_lt:{
                    strcpy(des,"%`d0 = icmp slt i64 %`s0, %`s1");
                    break;
                }
                case T_gt:{
                    strcpy(des,"%`d0 = icmp sgt i64 %`s0, %`s1");
                    break;
                }
                case T_le:{
                    strcpy(des,"%`d0 = icmp sle i64 %`s0, %`s1");
                    break;
                }
                case T_ge:{
                    strcpy(des,"%`d0 = icmp sge i64 %`s0, %`s1");
                    break;
                }
                default:{
                    assert(0);
                    break;
                }
            }
            ans=AS_splice(ans,I(OI(String(des),T(tempcond),TL(temp1,T(temp2)),NULL)));
            sprintf(des,"br i1 %`s0, label %%%s, label %%%s",S_name(x->u.CJUMP.true),S_name(x->u.CJUMP.false));
            ans=AS_splice(ans,I(OI(String(des),NULL,T(tempcond),AS_Targets(LL(x->u.CJUMP.true,L(x->u.CJUMP.false))))));
            break;
         }
         case T_MOVE:{
            free(ans);
            if (x->u.MOVE.dst->kind==T_TEMP){
                Temp_temp temp1;
                ans=treep2assemExp(x->u.MOVE.src,&temp1);
                ans=AS_splice(ans,I(OI("%`d0 = add i32 %`s0, 0",T(x->u.MOVE.dst->u.TEMP),T(temp1),NULL)));
            }else if (x->u.MOVE.dst->kind==T_MEM){
                Temp_temp tempsrc,tempdsti64,tempdst;
                tempdst=Temp_newtemp();
                ans=treep2assemExp(x->u.MOVE.dst->u.MEM,&tempdsti64);
                ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 %`s0 to ptr",T(tempdst),T(tempdsti64),NULL)));
                ans=AS_splice(ans,treep2assemExp(x->u.MOVE.src,&tempsrc));
                ans=AS_splice(ans,I(OI("store i64 %`s0, ptr %`s1",NULL,TL(tempsrc,T(tempdst)),NULL)));
            }else{
                assert(0);
            }
            break;
         }
         case T_EXP:{
            free(ans);
            Temp_temp temp;
            ans=treep2assemExp(x->u.EXP,&temp);
            break;
         }
         case T_RETURN:{
            free(ans);
            Temp_temp temp=NULL;
            ans=treep2assemExp(x->u.EXP,&temp);
            ans=AS_splice(ans,I(OI("ret i32 %`s0", NULL, T(temp), NULL)));
            break;
         }
    }
    // printf("%p: return\n",x);
    return ans;
}
AS_instrList treep2assemStmList(T_stmList list){
    if (list==NULL) return NULL;
    // printf("************%d**************\n",list->head->kind);
    // printf("asd head:%p tail:%p\n",list->head,list->tail);
    AS_instrList now = treep2assemStm(list->head);
    // AS_printInstrList(stdout,now,Temp_name());
    return AS_splice(now,treep2assemStmList(list->tail));
}
AS_blockList treep2assemblcok(struct C_block block){
    
    if (!block.stmLists) return NULL;
    AS_instrList now1 = treep2assemStmList(block.stmLists->head);
    
    AS_block now=AS_Block(now1);
    
    block.stmLists=block.stmLists->tail;
    
    return AS_BlockList(now,treep2assemblcok(block));
}