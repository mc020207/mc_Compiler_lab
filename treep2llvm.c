#include "treep2llvm.h"
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
AS_instrList treep2llvmExp(T_exp x,Temp_temp* rettemp,bool canMiss);
AS_instr AS_Label2(Temp_label lable){
    return AS_Label(String(strcat(String(S_name(lable)),":")),lable);
}
AS_instrList getargs(T_expList list,string demand,Temp_tempList* templist,int d,bool first){
    if (!list) {
        strcpy(demand,"");
        *templist=NULL;
        return NULL;
    }
    AS_instrList ans;
    if (list->head->kind==T_CONST){
        if (first) sprintf(demand,"i64 %d",list->head->u.CONST);
        else sprintf(demand,",i64 %d",list->head->u.CONST);
        string tempstring=checked_malloc(sizeof(char)*1000);// careful
        ans=getargs(list->tail,tempstring,templist,d,0);
        strcat(demand,tempstring);
        *templist=*templist;
    }
    else{
        if (first) sprintf(demand,"i64 %%`s%d",d);
        else sprintf(demand,",i64 %%`s%d",d);
        string tempstring=checked_malloc(sizeof(char)*1000);// careful
        ans=getargs(list->tail,tempstring,templist,d+1,0);
        strcat(demand,tempstring);
        Temp_temp temp=NULL;
        ans=AS_splice(treep2llvmExp(list->head,&temp,TRUE),ans);
        *templist=Temp_TempList(temp,*templist);
    }
    return ans;
}
AS_instrList treep2llvmExp(T_exp x,Temp_temp* rettemp,bool canMiss){
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
            if (x->u.BINOP.left->kind==T_CONST&&x->u.BINOP.right->kind==T_CONST){
                switch (x->u.BINOP.op){
                    case T_plus:{
                        sprintf(des,"%%`d0 = add i64 %d, %d",x->u.BINOP.left->u.CONST,x->u.BINOP.right->u.CONST);
                        break;
                    }
                    case T_minus:{
                        sprintf(des,"%%`d0 = sub i64 %d, %d",x->u.BINOP.left->u.CONST,x->u.BINOP.right->u.CONST);
                        break;
                    }
                    case T_mul:{
                        sprintf(des,"%%`d0 = mul i64 %d, %d",x->u.BINOP.left->u.CONST,x->u.BINOP.right->u.CONST);
                        break;
                    }
                    case T_div:{
                        sprintf(des,"%%`d0 = sdiv i64 %d, %d",x->u.BINOP.left->u.CONST,x->u.BINOP.right->u.CONST);
                        break;
                    }
                }
                ans=I(OI(String(des), T(ret),NULL, NULL));
            }else if (x->u.BINOP.left->kind==T_CONST){
                ans=treep2llvmExp(x->u.BINOP.right,&temp2,TRUE);
                switch (x->u.BINOP.op){
                    case T_plus:{
                        sprintf(des,"%%`d0 = add i64 %d, %%`s0",x->u.BINOP.left->u.CONST);
                        break;
                    }
                    case T_minus:{
                        sprintf(des,"%%`d0 = sub i64 %d, %%`s0",x->u.BINOP.left->u.CONST);
                        break;
                    }
                    case T_mul:{
                        sprintf(des,"%%`d0 = mul i64 %d, %%`s0",x->u.BINOP.left->u.CONST);
                        break;
                    }
                    case T_div:{
                        sprintf(des,"%%`d0 = sdiv i64 %d, %%`s0",x->u.BINOP.left->u.CONST);
                        break;
                    }
                }
                ans=AS_splice(ans,I(OI(String(des), T(ret), T(temp2), NULL)));
            }else if (x->u.BINOP.right->kind==T_CONST){
                ans=treep2llvmExp(x->u.BINOP.left,&temp1,TRUE);
                switch (x->u.BINOP.op){
                    case T_plus:{
                        sprintf(des,"%%`d0 = add i64 %%`s0, %d",x->u.BINOP.right->u.CONST);
                        break;
                    }
                    case T_minus:{
                        sprintf(des,"%%`d0 = sub i64 %%`s0, %d",x->u.BINOP.right->u.CONST);
                        break;
                    }
                    case T_mul:{
                        sprintf(des,"%%`d0 = mul i64 %%`s0, %d",x->u.BINOP.right->u.CONST);
                        break;
                    }
                    case T_div:{
                        sprintf(des,"%%`d0 = sdiv i64 %%`s0, %d",x->u.BINOP.right->u.CONST);
                        break;
                    }
                }
                ans=AS_splice(ans,I(OI(String(des), T(ret), T(temp1), NULL)));
            }else{
                ans=AS_splice(treep2llvmExp(x->u.BINOP.left,&temp1,TRUE),treep2llvmExp(x->u.BINOP.right,&temp2,TRUE));
                switch (x->u.BINOP.op){
                    case T_plus:{
                        strcpy(des,"%`d0 = add i64 %`s0, %`s1");
                        break;
                    }
                    case T_minus:{
                        strcpy(des,"%`d0 = sub i64 %`s0, %`s1");
                        break;
                    }
                    case T_mul:{
                        strcpy(des,"%`d0 = mul i64 %`s0, %`s1");
                        break;
                    }
                    case T_div:{
                        strcpy(des,"%`d0 = sdiv i64 %`s0, %`s1");
                        break;
                    }
                }
                ans=AS_splice(ans,I(OI(String(des), T(ret), TL(temp1, T(temp2)), NULL)));
            }
            break;
        }
        case T_MEM:{
            free(ans);
            Temp_temp tempsrci64=NULL,tempsrcptr=NULL;
            tempsrcptr=Temp_newtemp();
            ans=treep2llvmExp(x->u.MEM,&tempsrci64,TRUE);
            ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 %`s0 to ptr",T(tempsrcptr),T(tempsrci64),NULL)));
            ans=AS_splice(ans,I(OI("%`d0 = load i64, ptr %`s0",T(ret),T(tempsrcptr),NULL)));
            break;
        }
        case T_TEMP:{
            if(canMiss&&*rettemp==NULL) ret=x->u.TEMP;
            else ans->head=OI("%`d0 = add i64 %`s0, 0", T(ret), T(x->u.TEMP), NULL);
            break;
        }
        case T_ESEQ:{
            assert(0);
            break;
        }
        case T_NAME:{
            sprintf(des,"%%`d0 = ptrtoint ptr @%s to i64",S_name(x->u.NAME));
            ans->head=OI(String(des),T(ret),NULL,NULL);
            break;
        }
        case T_CONST:{
            sprintf(des,"%%`d0 = add i64 %d, 0",x->u.CONST);
            ans->head=OI(String(des),T(ret),NULL,NULL);
            break;
        }
        case T_CALL:{
            free(ans);
            Temp_temp tempfuci64=NULL,tempfucptr=Temp_newtemp();
            ans=treep2llvmExp(x->u.CALL.obj,&tempfuci64,TRUE);
            ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 %`s0 to ptr",T(tempfucptr),T(tempfuci64),NULL)));
            string des2=checked_malloc(1000);
            sprintf(des2,"%%`d0 = call i64 %%`s0(");
            string tempstring=checked_malloc(1000);
            Temp_tempList args;
            ans=AS_splice(ans,getargs(x->u.CALL.args,tempstring,&args,1,1));
            strcat(des2,tempstring);
            strcat(des2,")");
            args=Temp_TempList(tempfucptr,args);
            ans=AS_splice(ans,I(OI(String(des2),T(ret),args,NULL)));
            break;
        }
        case T_ExtCALL:{
            if (strcmp(x->u.ExtCALL.extfun,"malloc")==0){
                Temp_temp temp1=NULL,temp2=NULL,temp3=NULL;
                temp2=Temp_newtemp();
                free(ans);
                if (x->u.ExtCALL.args->head->kind==T_CONST){
                    sprintf(des,"%%`d0 = call ptr @malloc(i64 %d)",x->u.ExtCALL.args->head->u.CONST);
                    ans=I(OI(String(des),T(temp2),NULL,NULL));
                    ans=AS_splice(ans,I(OI("%`d0 = ptrtoint ptr %`s0 to i64",T(ret),T(temp2),NULL)));
                }
                else{
                    ans=treep2llvmExp(x->u.ExtCALL.args->head,&temp1,TRUE);
                    ans=AS_splice(ans,I(OI("%`d0 = call ptr @malloc(i64 %`s0)",T(temp2),T(temp1),NULL)));
                    ans=AS_splice(ans,I(OI("%`d0 = ptrtoint ptr %`s0 to i64",T(ret),T(temp2),NULL)));
                }
            }else if (strcmp(x->u.ExtCALL.extfun,"putint")==0||strcmp(x->u.ExtCALL.extfun,"putch")==0){
                Temp_temp temp1=NULL;
                assert(x->u.ExtCALL.args);
                ans=treep2llvmExp(x->u.ExtCALL.args->head,&temp1,TRUE);
                sprintf(des,"call void @%s(i64 %%`s0)",x->u.ExtCALL.extfun);
                ans=AS_splice(ans,I(OI(String(des),NULL,T(temp1),NULL)));
            }else if (strcmp(x->u.ExtCALL.extfun,"starttime")==0||strcmp(x->u.ExtCALL.extfun,"stoptime")==0){
                sprintf(des,"call void @%s()",x->u.ExtCALL.extfun);
                ans->head=OI(String(des),NULL,NULL,NULL);
            }else if (strcmp(x->u.ExtCALL.extfun,"putarray")==0){
                Temp_temp temp1=NULL,temp2=NULL,temp3=NULL;
                temp3=Temp_newtemp();
                ans=treep2llvmExp(x->u.ExtCALL.args->head,&temp1,TRUE);
                ans=AS_splice(ans,treep2llvmExp(x->u.ExtCALL.args->tail->head,&temp2,TRUE));
                ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 %`s0 to ptr",T(temp3),T(temp2),NULL)));
                ans=AS_splice(ans,I(OI("call void @putarray(i64 %`s0,ptr %`s1)",NULL,TL(temp1,T(temp3)),NULL)));
            }else if (strcmp(x->u.ExtCALL.extfun,"getint")==0||strcmp(x->u.ExtCALL.extfun,"getch")==0){
                sprintf(des,"%%`d0=call i64 @%s()",x->u.ExtCALL.extfun);
                ans->head=OI(String(des),T(ret),NULL,NULL);
            }else if (strcmp(x->u.ExtCALL.extfun,"getarray")==0){
                Temp_temp temp2=NULL,temp3=NULL;
                temp3=Temp_newtemp();
                ans=treep2llvmExp(x->u.ExtCALL.args->head,&temp2,TRUE);
                ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 %`s0 to ptr",T(temp3),T(temp2),NULL)));
                ans=AS_splice(ans,I(OI("%`d0 = call i64 @getarray(ptr %`s0)",T(ret),T(temp3),NULL)));
            }
            break;
        }
    }
    if (ans->head==NULL) ans=NULL;
    *rettemp=ret;
    return ans;
}
AS_instrList treep2llvmStm(T_stm x){
    if (x==NULL) return NULL;
    AS_instrList ans=checked_malloc(sizeof(*ans));
    ans->head=NULL;ans->tail=NULL;
    switch (x->kind){
         case T_SEQ:{
            ans=AS_splice(treep2llvmStm(x->u.SEQ.left),treep2llvmStm(x->u.SEQ.right));
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
            Temp_temp temp1=NULL,temp2=NULL,tempcond=NULL;
            tempcond=Temp_newtemp();
            if (x->u.CJUMP.left->kind==T_CONST&&x->u.CJUMP.right->kind==T_CONST){
                ans=NULL;
                switch (x->u.CJUMP.op){
                    case T_eq:{
                        sprintf(des,"%%`d0 = icmp eq i64 %d, %d",x->u.CJUMP.left->u.CONST,x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_ne:{
                        sprintf(des,"%%`d0 = icmp ne i64 %d, %d",x->u.CJUMP.left->u.CONST,x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_lt:{
                        sprintf(des,"%%`d0 = icmp slt i64 %d, %d",x->u.CJUMP.left->u.CONST,x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_gt:{
                        sprintf(des,"%%`d0 = icmp sgt i64 %d, %d",x->u.CJUMP.left->u.CONST,x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_le:{
                        sprintf(des,"%%`d0 = icmp sle i64 %d, %d",x->u.CJUMP.left->u.CONST,x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_ge:{
                        sprintf(des,"%%`d0 = icmp sge i64 %d, %d",x->u.CJUMP.left->u.CONST,x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    default:{
                        assert(0);
                        break;
                    }
                }
                ans=AS_splice(ans,I(OI(String(des),T(tempcond),NULL,NULL)));
            }else if (x->u.CJUMP.left->kind==T_CONST){
                ans=treep2llvmExp(x->u.CJUMP.right,&temp2,TRUE);
                switch (x->u.CJUMP.op){
                    case T_eq:{
                        sprintf(des,"%%`d0 = icmp eq i64 %d, %%`s0",x->u.CJUMP.left->u.CONST);
                        break;
                    }
                    case T_ne:{
                        sprintf(des,"%%`d0 = icmp ne i64 %d, %%`s0",x->u.CJUMP.left->u.CONST);
                        break;
                    }
                    case T_lt:{
                        sprintf(des,"%%`d0 = icmp slt i64 %d, %%`s0",x->u.CJUMP.left->u.CONST);
                        break;
                    }
                    case T_gt:{
                        sprintf(des,"%%`d0 = icmp sgt i64 %d, %%`s0",x->u.CJUMP.left->u.CONST);
                        break;
                    }
                    case T_le:{
                        sprintf(des,"%%`d0 = icmp sle i64 %d, %%`s0",x->u.CJUMP.left->u.CONST);
                        break;
                    }
                    case T_ge:{
                        sprintf(des,"%%`d0 = icmp sge i64 %d, %%`s0",x->u.CJUMP.left->u.CONST);
                        break;
                    }
                    default:{
                        assert(0);
                        break;
                    }
                }
                ans=AS_splice(ans,I(OI(String(des),T(tempcond),T(temp2),NULL)));
            }else if (x->u.CJUMP.right->kind==T_CONST){
                ans=treep2llvmExp(x->u.CJUMP.left,&temp1,TRUE);
                switch (x->u.CJUMP.op){
                    case T_eq:{
                        sprintf(des,"%%`d0 = icmp eq i64 %%`s0, %d",x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_ne:{
                        sprintf(des,"%%`d0 = icmp ne i64 %%`s0, %d",x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_lt:{
                        sprintf(des,"%%`d0 = icmp slt i64 %%`s0, %d",x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_gt:{
                        sprintf(des,"%%`d0 = icmp sgt i64 %%`s0, %d",x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_le:{
                        sprintf(des,"%%`d0 = icmp sle i64 %%`s0, %d",x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    case T_ge:{
                        sprintf(des,"%%`d0 = icmp sge i64 %%`s0, %d",x->u.CJUMP.right->u.CONST);
                        break;
                    }
                    default:{
                        assert(0);
                        break;
                    }
                }
                ans=AS_splice(ans,I(OI(String(des),T(tempcond),T(temp1),NULL)));
            }else{
                ans=treep2llvmExp(x->u.CJUMP.left,&temp1,TRUE);
                ans=AS_splice(ans,treep2llvmExp(x->u.CJUMP.right,&temp2,TRUE));
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
            }
            sprintf(des,"br i1 %%`s0, label %%%s, label %%%s",S_name(x->u.CJUMP.true),S_name(x->u.CJUMP.false));
            ans=AS_splice(ans,I(OI(String(des),NULL,T(tempcond),AS_Targets(LL(x->u.CJUMP.true,L(x->u.CJUMP.false))))));
            break;
         }
         case T_MOVE:{
            free(ans);
            if (x->u.MOVE.dst->kind==T_TEMP){
                if(x->u.MOVE.src->kind==T_TEMP){
                    ans=I(AS_Move("%`d0 = add i64 %`s0, 0",T(x->u.MOVE.dst->u.TEMP),T(x->u.MOVE.src->u.TEMP)));
                }else{
                    Temp_temp temp1=x->u.MOVE.dst->u.TEMP;
                    ans=treep2llvmExp(x->u.MOVE.src,&temp1,FALSE);
                }
            }else if (x->u.MOVE.dst->kind==T_MEM){
                Temp_temp tempsrc=NULL,tempdsti64=NULL,tempdst=NULL;
                tempdst=Temp_newtemp();
                ans=treep2llvmExp(x->u.MOVE.dst->u.MEM,&tempdsti64,TRUE);
                ans=AS_splice(ans,I(OI("%`d0 = inttoptr i64 %`s0 to ptr",T(tempdst),T(tempdsti64),NULL)));
                if (x->u.MOVE.src->kind==T_CONST){
                    sprintf(des,"store i64 %d, ptr %%`s0",x->u.MOVE.src->u.CONST);
                    ans=AS_splice(ans,I(OI(String(des),NULL,T(tempdst),NULL)));
                }
                else{
                    ans=AS_splice(ans,treep2llvmExp(x->u.MOVE.src,&tempsrc,TRUE));
                    ans=AS_splice(ans,I(OI("store i64 %`s0, ptr %`s1",NULL,TL(tempsrc,T(tempdst)),NULL)));
                }
            }else{
                assert(0);
            }
            break;
         }
         case T_EXP:{
            free(ans);
            Temp_temp temp=NULL;
            ans=treep2llvmExp(x->u.EXP,&temp,FALSE);
            break;
         }
         case T_RETURN:{
            free(ans);
            Temp_temp temp=NULL;
            if (x->u.EXP->kind==T_CONST){
                sprintf(des,"ret i64 %d",x->u.EXP->u.CONST);
                ans=I(OI(String(des),NULL,NULL,NULL));
            }else{
                ans=treep2llvmExp(x->u.EXP,&temp,TRUE);
                ans=AS_splice(ans,I(OI("ret i64 %`s0", NULL, T(temp), NULL)));
            }
            break;
         }
    }
    return ans;
}
AS_instrList treep2llvmStmList(T_stmList list){
    if (list==NULL) return NULL;
    AS_instrList now = treep2llvmStm(list->head);
    return AS_splice(now,treep2llvmStmList(list->tail));
}
AS_blockList treep2llvmblcok(struct C_block block){
    if (!block.stmLists) return NULL;
    AS_instrList now1 = treep2llvmStmList(block.stmLists->head);
    AS_block now=AS_Block(now1);
    block.stmLists=block.stmLists->tail;
    return AS_BlockList(now,treep2llvmblcok(block));
}
AS_instrList treep2llvmfuction(AS_blockList aslist,T_funcDecl x){
    string des2=checked_malloc(1000);
    sprintf(des2,"define i64 @%s(",x->name);
    Temp_tempList list=x->args;
    for (int i=0;;i++){
        if (!list) break;
        if (i==0) sprintf(des,"i64 %%`s%d",i);
        else sprintf(des,", i64 %%`s%d",i);
        strcat(des2,des);
        list=list->tail;
    }
    strcat(des2,") #0 {");
    AS_instrList prolog=IL(OI(String(des2), NULL, x->args ,NULL), NULL);
    AS_instrList epilog=I(OI("}", NULL, NULL, NULL));
    AS_instrList il = AS_traceSchedule(aslist, prolog, epilog, FALSE);
    return il;
}