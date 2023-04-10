#include "ast2treep.h"
#include "stdlib.h"
S_table temp_table;
struct whilenode_{
    Temp_label testLable;
    Temp_label endLable;
    Temp_label loopLable;
    struct whilenode_* nxt;
};
typedef struct whilenode_* whilenode;
whilenode head;
whilenode newnode(){
    whilenode now=checked_malloc(sizeof(*now));
    now->testLable=Temp_newlabel();
    now->endLable=Temp_newlabel();
    now->loopLable=Temp_newlabel();
    now->nxt=head->nxt;
    head->nxt=now;
    return now;
}
void popnode(){
    whilenode now=head->nxt;
    assert(now);
    head->nxt=now->nxt;
    free(now);
}
void ast2treepinit(){
    temp_table=S_empty();
    head=checked_malloc(sizeof(*head));
    head->nxt=NULL;
}
T_exp rel2exp(A_exp x){
    if (x==NULL) return NULL;
    assert(x->kind==A_opExp||x->kind==A_notExp);
    Temp_temp temp=Temp_newtemp();
    Temp_label tureLable=Temp_newlabel();
    Temp_label falseLable=Temp_newlabel();
    Temp_label endLable=Temp_newlabel();
    T_stm truestm=T_Seq(T_Label(tureLable),T_Seq(T_Move(T_Temp(temp),T_Const(1)),T_Jump(endLable)));
    T_stm falsestm=T_Seq(T_Label(falseLable),T_Seq(T_Move(T_Temp(temp),T_Const(0)),T_Jump(endLable)));
    T_stm ifstm=NULL;
    if (x->kind==A_notExp){
        ifstm=T_Cjump(T_eq,ast2treepExp(x->u.e),T_Const(0),tureLable,falseLable);
    }else{
        ifstm=T_Cjump(T_ge,ast2treepExp(x->u.op.left),ast2treepExp(x->u.op.right),tureLable,falseLable);
        switch (x->u.op.oper){
            case A_ge:{
                ifstm->u.CJUMP.op=T_ge;
                break;
            }
            case A_le:{
                ifstm->u.CJUMP.op=T_le;
                break;
            }
            case A_greater:{
                ifstm->u.CJUMP.op=T_gt;
                break;
            }
            case A_less:{
                ifstm->u.CJUMP.op=T_lt;
                break;
            }
            case A_eq:{
                ifstm->u.CJUMP.op=T_eq;
                break;
            }
            case A_ne:{
                ifstm->u.CJUMP.op=T_ne;
                break;
            }
            default:
                assert(0);
        }
    }
    return T_Eseq(T_Seq(ifstm,T_Seq(truestm,T_Seq(falsestm,T_Label(endLable)))),T_Temp(temp));
}
T_exp ast2treepExp(A_exp x){
    T_exp ans=NULL;
    switch (x->kind){
        case A_opExp:{
            if (x->u.op.oper>=A_less&&x->u.op.oper<=A_ne) ans=rel2exp(x);
            else if (x->u.op.oper>A_ne){
                ans=T_Binop(T_plus,ast2treepExp(x->u.op.left),ast2treepExp(x->u.op.right));
                switch (x->u.op.oper){
                    case A_plus:{
                        ans->u.BINOP.op=T_plus;
                        break;
                    } 
                    case A_minus:{
                        ans->u.BINOP.op=T_minus;
                        break;
                    } 
                    case A_times:{
                        ans->u.BINOP.op=T_mul;
                        break;
                    } 
                    case A_div:{
                        ans->u.BINOP.op=T_div;
                        break;
                    }
                }
            }else if(x->u.op.oper==A_and){
                Temp_temp temp=Temp_newtemp();
                Temp_label tureLable=Temp_newlabel();
                Temp_label falseLable=Temp_newlabel();
                Temp_label shortcutLable=Temp_newlabel();
                Temp_label endLable=Temp_newlabel();
                T_stm truestm=T_Seq(T_Label(tureLable),T_Seq(T_Move(T_Temp(temp),T_Const(1)),T_Jump(endLable)));
                T_stm falsestm=T_Seq(T_Label(falseLable),T_Seq(T_Move(T_Temp(temp),T_Const(0)),T_Jump(endLable)));
                T_stm ifstm=T_Cjump(T_ne,ast2treepExp(x->u.op.left),T_Const(0),shortcutLable,falseLable);
                T_stm ifstm2=T_Cjump(T_ne,ast2treepExp(x->u.op.right),T_Const(0),tureLable,falseLable);
                ans=T_Eseq(T_Seq(ifstm,T_Seq(T_Seq(T_Label(shortcutLable),ifstm2),T_Seq(truestm,T_Seq(falsestm,T_Label(endLable))))),T_Temp(temp));
            }else if (x->u.op.oper==A_or){
                Temp_temp temp=Temp_newtemp();
                Temp_label tureLable=Temp_newlabel();
                Temp_label falseLable=Temp_newlabel();
                Temp_label shortcutLable=Temp_newlabel();
                Temp_label endLable=Temp_newlabel();
                T_stm truestm=T_Seq(T_Label(tureLable),T_Seq(T_Move(T_Temp(temp),T_Const(1)),T_Jump(endLable)));
                T_stm falsestm=T_Seq(T_Label(falseLable),T_Seq(T_Move(T_Temp(temp),T_Const(0)),T_Jump(endLable)));
                T_stm ifstm=T_Cjump(T_ne,ast2treepExp(x->u.op.left),T_Const(0),tureLable,shortcutLable);
                T_stm ifstm2=T_Cjump(T_ne,ast2treepExp(x->u.op.right),T_Const(0),tureLable,falseLable);
                ans=T_Eseq(T_Seq(ifstm,T_Seq(T_Seq(T_Label(shortcutLable),ifstm2),T_Seq(truestm,T_Seq(falsestm,T_Label(endLable))))),T_Temp(temp));
            }else{
                assert(0);
            }
            break;
        }
        case A_arrayExp:{
            // fill it next time
            break;
        }
        case A_callExp:{
            // fill it next time
            break;
        }
        case A_classVarExp:{
            // fill it next time
            break;
        }
        case A_boolConst:{
            ans=T_Const(x->u.b);
            break;
        }
        case A_numConst:{
            ans=T_Const(x->u.num);
            break;
        }
        case A_idExp:{
            ans=T_Temp(S_look(temp_table,S_Symbol(x->u.v)));
            break;
        }
        case A_thisExp:{
            // fill it next time
            break;
        }
        case A_lengthExp:{
            // fill it next time
            break;
        }
        case A_newIntArrExp:{
            // fill it next time
            break;
        }
        case A_newObjExp:{
            // fill it next time
            break;
        }
        case A_notExp:{
            ans=rel2exp(x);
            break;
        }
        case A_minusExp:{
            ans=T_Binop(T_minus,T_Const(0),ast2treepExp(x->u.e));
            break;
        }
        case A_escExp:{
            ans=T_Eseq(ast2treepStmList(x->u.escExp.ns),ast2treepExp(x->u.escExp.exp));
            break;
        }
        case A_getint:{
            ans=T_ExtCall(String("getint"),NULL);
            break;
        }
        case A_getch:{
            ans=T_ExtCall(String("getch"),NULL);
            break;
        }
        case A_getarray:{
            // fill it next time
            break;
        }
    }
    return ans;
}
T_expList ast2treepExpList(A_expList x){
    if (!x) return NULL;
    return T_ExpList(ast2treepExp(x->head),ast2treepExpList(x->tail));
}
T_stm ast2treepStmList(A_stmList x){
    if (!x) return NULL;
    if (x->tail){
        return T_Seq(ast2treepStm(x->head),ast2treepStmList(x->tail));
    }else{
        return ast2treepStm(x->head);
    }
}
T_stm ast2treepStm(A_stm x){
    if (!x) return NULL;
    T_stm ans=NULL;
    switch (x->kind){
        case A_nestedStm:{
            ans=ast2treepStmList(x->u.ns);
            break;
        }
        case A_ifStm:{
            Temp_label tureLable=Temp_newlabel();
            Temp_label falseLable=Temp_newlabel();
            Temp_label endLable=Temp_newlabel();
            T_stm truestm=NULL,falsestm=NULL;
            if (x->u.if_stat.s1) truestm=T_Seq(T_Label(tureLable),T_Seq(ast2treepStm(x->u.if_stat.s1),T_Jump(endLable)));
            else truestm=T_Seq(T_Label(tureLable),T_Jump(endLable));
            if (x->u.if_stat.s2) falsestm=T_Seq(T_Label(falseLable),T_Seq(ast2treepStm(x->u.if_stat.s2),T_Jump(endLable)));
            else falsestm=T_Seq(T_Label(falseLable),T_Jump(endLable));
            T_stm ifstm=T_Cjump(T_ne,ast2treepExp(x->u.if_stat.e),T_Const(0),tureLable,falseLable);
            ans=T_Seq(ifstm,T_Seq(truestm,T_Seq(falsestm,T_Label(endLable))));
            break;
        }
        case A_whileStm:{
            whilenode now=newnode();
            T_stm ifstm=T_Cjump(T_ne,ast2treepExp(x->u.if_stat.e),T_Const(0),now->loopLable,now->endLable);
            T_stm loopstm=ast2treepStm(x->u.while_stat.s);
            if (loopstm) ans=T_Seq(T_Label(now->testLable),T_Seq(ifstm,T_Seq(T_Label(now->loopLable),T_Seq(loopstm,T_Seq(T_Jump(now->testLable),T_Label(now->endLable))))));
            else ans=T_Seq(T_Label(now->testLable),T_Seq(ifstm,T_Seq(T_Label(now->loopLable),T_Seq(T_Jump(now->testLable),T_Label(now->endLable)))));
            popnode();
            break;
        }
        case A_assignStm:{
            ans=T_Move(ast2treepExp(x->u.assign.arr),ast2treepExp(x->u.assign.value));
            break;
        }
        case A_arrayInit:{
            // fill it next time
            break;
        }
        case A_callStm:{
            // fill it next time
            break;
        }
        case A_continue:{
            whilenode now=head->nxt;
            if (!now) printError(x->pos,"can not use continue out of while");
            ans=T_Jump(now->testLable);
            break;
        }
        case A_break:{
            whilenode now=head->nxt;
            if (!now) printError(x->pos,"can not use break out of while");
            ans=T_Jump(now->endLable);
            break;
        }
        case A_return:{
            ans=T_Return(ast2treepExp(x->u.e));
            break;
        }
        case A_putint:{
            ans=T_Exp(T_ExtCall("putint",T_ExpList(ast2treepExp(x->u.e),NULL)));
            break;
        }
        case A_putarray:{
            // fill it next time
            break;
        }
        case A_putch:{
            ans=T_Exp(T_ExtCall("putch",T_ExpList(ast2treepExp(x->u.e),NULL)));
            break;
        }
        case A_starttime:{
            ans=T_Exp(T_ExtCall("starttime",NULL));
            break;
        }
        case A_stoptime:{
            ans=T_Exp(T_ExtCall("stoptime",NULL));
            break;
        }
    }
    return ans;
}
T_stm ast2treepvarDeclList(A_varDeclList list){
    T_stm ans=NULL;
    for (;list;list=list->tail){
        A_varDecl x=list->head;
        Temp_temp temp=Temp_newtemp();
        S_enter(temp_table,S_Symbol(x->v),temp);
        if (x->elist&&x->t->t==A_intType){
            if (ans==NULL) ans=T_Move(T_Temp(temp),ast2treepExp(x->elist->head));
            else ans=T_Seq(ans,T_Move(T_Temp(temp),ast2treepExp(x->elist->head)));
        }
        if (x->elist&&x->t->t==A_intType){
            // fill it next time
        }
    }
    return ans;
}
T_funcDeclList ast2treepclassDeclList(A_classDeclList list){
    // fill it next time
    return NULL;
}
T_funcDecl ast2treepMainmethod(A_mainMethod x){
    T_stm varstm=ast2treepvarDeclList(x->vdl);
    T_stm stm=ast2treepStmList(x->sl);
    T_stm ans=NULL;
    if (varstm) ans=varstm;
    if (stm){
        if (ans==NULL) ans=stm;
        else ans=T_Seq(ans,stm);
    }
    return T_FuncDecl("main",NULL,ans);
}
T_funcDeclList ast2treepprog(A_prog x){
    ast2treepinit();
    return T_FuncDeclList(ast2treepMainmethod(x->m),ast2treepclassDeclList(x->cdl));
}














