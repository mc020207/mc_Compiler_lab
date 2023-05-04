/*
 * printtree.c - functions to print out intermediate representation (IR) trees.
 *
 */
#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "treep.h"
#include "printtreep.h"

/* local function prototype */
static void pr_tree_exp(FILE *out, T_exp exp, int d);

static void indent(FILE *out, int d) {
 int i;
 for (i = 0; i <= d; i++) fprintf(out, " ");
}

static char bin_oper[][12] = {
   "T_plus", "T_minus", "T_mul", "T_div", "T_and", "T_or"};

static char rel_oper[][12] = {
  "T_eq", "T_ne", "T_lt", "T_gt", "T_le", "T_ge"};
 
static void pr_stm(FILE *out, T_stm stm, int d)
{
  switch (stm->kind) {
  case T_SEQ:
    indent(out,d);
    fprintf(out, "T_Seq(\n"); pr_stm(out, stm->u.SEQ.left,d+1);  fprintf(out, ",\n"); 
    pr_stm(out, stm->u.SEQ.right,d+1); fprintf(out, ")");
    break;
  case T_LABEL:
    indent(out,d); fprintf(out, "T_Label(Temp_namedlabel(String(\"%s\")))", S_name(stm->u.LABEL));
    break;
  case T_JUMP:
    indent(out,d); fprintf(out, "T_Jump(");
    fprintf(out, "Temp_namedlabel(String(\"%s\"))", S_name(stm->u.JUMP.jump));
    fprintf(out, ")");
    break;
  case T_CJUMP:
    indent(out,d); fprintf(out, "T_Cjump(%s,\n", rel_oper[stm->u.CJUMP.op]);
    pr_tree_exp(out, stm->u.CJUMP.left,d+1); fprintf(out, ",\n"); 
    pr_tree_exp(out, stm->u.CJUMP.right,d+1); fprintf(out, ",\n");
    indent(out,d+1); fprintf(out, "Temp_namedlabel(String(\"%s\")),", S_name(stm->u.CJUMP.true));
    fprintf(out, "Temp_namedlabel(String(\"%s\"))", S_name(stm->u.CJUMP.false)); fprintf(out, ")");
    break;
  case T_MOVE:
    indent(out,d); fprintf(out, "T_Move(\n"); pr_tree_exp(out, stm->u.MOVE.dst,d+1); 
    fprintf(out, ",\n");
    pr_tree_exp(out, stm->u.MOVE.src,d+1); fprintf(out, ")");
    break;
  case T_EXP:
    indent(out,d); fprintf(out, "T_Exp(\n"); pr_tree_exp(out, stm->u.EXP,d+1); 
    fprintf(out, ")");
    break;
  case T_RETURN: 
    indent(out,d); fprintf(out, "T_Return(\n"); pr_tree_exp(out, stm->u.EXP,d+1); 
    fprintf(out, ")");
    break;
  }
}

static void pr_templist(FILE *out, Temp_tempList tl, int d) 
{
  indent(out, d);
  if (!tl) {
    fprintf(out, "NULL");
    return ;
  }
  fprintf(out, "Temp_TempList(");
  fprintf(out, "TC(String(\"t%s\"))", Temp_look(Temp_name(), tl->head));
  tl = tl->tail;
  if (tl)
     fprintf(out, ",\n");
  else 
     fprintf(out, ", ");
  pr_templist(out, tl, d);
  fprintf(out, ")");
  return ;
}

static void pr_explist(FILE *out, T_expList el, int d)
{
  if (!el) {
    fprintf(out, "NULL");
    return ;
  }
  indent(out, d);
  fprintf(out, "T_ExpList(");
  pr_tree_exp(out, el->head, -1);
  el=el->tail;
  if (el)
    fprintf(out, ",\n");
  else
    fprintf(out, ", ");
  pr_explist(out, el, d);
  fprintf(out , ")");
  return;
}

static void pr_tree_exp(FILE *out, T_exp exp, int d)
{
  switch (exp->kind) {
  case T_BINOP:
    indent(out,d); fprintf(out, "T_Binop(%s,\n", bin_oper[exp->u.BINOP.op]); 
    pr_tree_exp(out, exp->u.BINOP.left,d+1); fprintf(out, ",\n"); 
    pr_tree_exp(out, exp->u.BINOP.right,d+1); fprintf(out, ")");
    break;
  case T_MEM:
    indent(out,d); fprintf(out, "T_Mem");
    fprintf(out, "(\n"); pr_tree_exp(out, exp->u.MEM,d+1); fprintf(out, ")");
    break;
  case T_TEMP:
    indent(out,d); fprintf(out, "T_Temp(TC(String(\"t%s\")))", 
			   Temp_look(Temp_name(), exp->u.TEMP));
    break;
  case T_ESEQ:
    indent(out,d); fprintf(out, "T_Eseq(\n"); pr_stm(out, exp->u.ESEQ.stm,d+1); 
    fprintf(out, ",\n");
    pr_tree_exp(out, exp->u.ESEQ.exp,d+1); fprintf(out, ")");
    break;
  case T_NAME:
    indent(out,d); fprintf(out, "T_Name(Temp_namedlabel(String(\"%s\")))", S_name(exp->u.NAME));
    break;
  case T_CONST:
    indent(out,d); fprintf(out, "T_Const(%d)", exp->u.CONST);
    break;
  case T_CALL:
    {
    T_expList args = exp->u.CALL.args;
    indent(out,d); 
    fprintf(out, "T_Call(String(\"%s\"),\n", exp->u.CALL.id); 
    pr_tree_exp(out, exp->u.CALL.obj,0);
    fprintf(out, ",\n");
    if (args) 
      pr_explist(out, args, d);
    else
      fprintf(out, "NULL)");
    fprintf(out, ")");
    }
    break;
   case T_ExtCALL:
    {
    T_expList args = exp->u.ExtCALL.args;
    indent(out,d); 
    fprintf(out, "T_ExtCall(String(\"%s\"),", exp->u.ExtCALL.extfun); 
    if (args) {
      fprintf(out, "\n");
      pr_explist(out, args, d);
    }
    else {
      indent(out, d);
      fprintf(out, "NULL");
    }
    fprintf(out, ")");
    }
    break;
  } /* end of switch */
}

void printStmList (FILE *out, T_stmList stmList, int d) 
{
  T_stmList l=stmList;
  if (l) {
    indent(out, d);
    fprintf(out, "T_StmList(\n");
    pr_stm(out, l->head, d);
    l=l->tail;
    if (l) 
      fprintf(out, ",\n"); 
    printStmList(out, l, d);
    fprintf(out, ")");
  }
  else {
    indent(out, d);
    fprintf(out, ", NULL");
  }
  return ;
}

void printFuncDecl(FILE *out, T_funcDecl funcDecl) 
{
  Temp_tempList t=funcDecl->args;
  T_stm sl=funcDecl->stm;

  fprintf(out, "T_FuncDecl(String(\"%s\"),\n", funcDecl->name);

  if (t) 
    pr_templist(out, t, 0);
  else {
    fprintf(out, "NULL");
  }

  fprintf(out, ",\n");

  if (sl) {
    pr_stm(out, sl, 0);
  }
  else 
    fprintf(out, " NULL");

  fprintf(out, ")");
  return;
}

void printFuncDeclList(FILE *out, T_funcDeclList funcDeclList) 
{
   T_funcDeclList l=funcDeclList;
   if (l) { 
     fprintf(out, "T_FuncDeclList\(\n");
     printFuncDecl(out, l->head); 
     l=l->tail;
     fprintf(out, ",\n");
     printFuncDeclList(out, l);
     fprintf(out, ")");
   }
   else {
     fprintf(out, "NULL\n");
   }
   return;
}
