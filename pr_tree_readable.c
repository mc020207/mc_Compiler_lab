/*
 * printtree.c - functions to print out intermediate representation (IR) trees.
 *
 */
#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "treep.h"
#include "pr_tree_readable.h"

/* local function prototype */
static void pr_tree_exp(FILE *out, T_exp exp, int d);

int inst=1;
int eseqlevel=0;

static void indent(FILE *out, int d) {
 int i;
 for (i = 0; i <= d; i++) fprintf(out, " ");
}

static void indent_dash(FILE *out, int d) {
 int i;
 for (i = 0; i <= d; i++) fprintf(out, "-");
}

static char bin_oper[][12] = {
   "PLUS", "MINUS", "TIMES", "DIVIDE", 
   "AND", "OR", "LSHIFT", "RSHIFT", "ARSHIFT", "XOR"};

static char rel_oper[][12] = {
  "EQ", "NE", "LT", "GT", "LE", "GE", "ULT", "ULE", "UGT", "UGE"};
 
static void pr_stm(FILE *out, T_stm stm, int d)
{
  switch (stm->kind) {
  case T_SEQ:
    if (stm->u.SEQ.left->kind!=T_SEQ) {
      indent_dash(out,eseqlevel);
      fprintf(out, "[Stm#%d]", inst++); d=1; 
    } 
    else indent(out, d);
    fprintf(out, "SEQ(\n"); pr_stm(out, stm->u.SEQ.left,d+1);  fprintf(out, ",\n"); 
    if (stm->u.SEQ.right && stm->u.SEQ.right->kind!=T_SEQ) 
          {indent_dash(out, eseqlevel); fprintf(out, "[Stm#%d]", inst++); d=1;}
    pr_stm(out, stm->u.SEQ.right,d+1); fprintf(out, ")");
    break;
  case T_LABEL:
    indent(out,d); fprintf(out, "LABEL %s", S_name(stm->u.LABEL));
    break;
  case T_JUMP:
    indent(out,d); fprintf(out, "JUMP("); 
    fprintf(out, " %s)", Temp_labelstring(stm->u.JUMP.jump));
    break;
  case T_CJUMP:
    indent(out,d); fprintf(out, "CJUMP(%s,\n", rel_oper[stm->u.CJUMP.op]);
    pr_tree_exp(out, stm->u.CJUMP.left,d+1); fprintf(out, ",\n"); 
    pr_tree_exp(out, stm->u.CJUMP.right,d+1); fprintf(out, ",\n");
    indent(out,d+1); fprintf(out, "%s,", S_name(stm->u.CJUMP.true));
    fprintf(out, "%s", S_name(stm->u.CJUMP.false)); fprintf(out, ")");
    break;
  case T_MOVE:
    indent(out,d); fprintf(out, "MOVE(\n"); pr_tree_exp(out, stm->u.MOVE.dst,d+1); 
    fprintf(out, ",\n");
    pr_tree_exp(out, stm->u.MOVE.src,d+1); fprintf(out, ")");
    break;
  case T_EXP:
    indent(out,d); fprintf(out, "T_EXP(\n"); pr_tree_exp(out, stm->u.EXP,d+1); 
    fprintf(out, ")");
    break;
  case T_RETURN: 
    indent(out,d); fprintf(out, "T_Return(\n"); pr_tree_exp(out, stm->u.EXP,d+1); 
    fprintf(out, ")");
    break;
  }
}

static void pr_tree_exp(FILE *out, T_exp exp, int d)
{
  switch (exp->kind) {
  case T_BINOP:
    indent(out,d); fprintf(out, "BINOP(%s,\n", bin_oper[exp->u.BINOP.op]); 
    pr_tree_exp(out, exp->u.BINOP.left,d+1); fprintf(out, ",\n"); 
    pr_tree_exp(out, exp->u.BINOP.right,d+1); fprintf(out, ")");
    break;
  case T_MEM:
    indent(out,d); fprintf(out, "MEM");
    fprintf(out, "(\n"); pr_tree_exp(out, exp->u.MEM,d+1); fprintf(out, ")");
    break;
  case T_TEMP:
    indent(out,d); fprintf(out, "T_TEMP(t%s)", 
			   Temp_look(Temp_name(), exp->u.TEMP));
    break;
  case T_ESEQ:
    eseqlevel++;
    indent(out,d); fprintf(out, "ESEQ(\n"); 
    if (exp->u.ESEQ.stm->kind!=T_SEQ) {
      indent_dash(out, eseqlevel); fprintf(out, "[Stm#%d]", inst++); d=eseqlevel;
    }
    pr_stm(out, exp->u.ESEQ.stm,d+1); 
    fprintf(out, "\n"); pr_tree_exp(out, exp->u.ESEQ.exp,d+1); fprintf(out, ")");
    eseqlevel--;
    break;
  case T_NAME:
    indent(out,d); fprintf(out, "NAME %s", S_name(exp->u.NAME));
    break;
  case T_CONST:
    indent(out,d); fprintf(out, "CONST %d", exp->u.CONST);
    break;
  case T_CALL:
    {
    T_expList args = exp->u.CALL.args;
    indent(out,d); 
    fprintf(out, "CALL(%s,\n", exp->u.CALL.id); 
    pr_tree_exp(out, exp->u.CALL.obj,d+1);
    for (;args; args=args->tail) {
     fprintf(out, ",\n"); pr_tree_exp(out, args->head,d+2);
    }
    fprintf(out, ")");
    }
    break;
   case T_ExtCALL:
    {
    T_expList args = exp->u.ExtCALL.args;
    indent(out,d); 
     if (args) fprintf(out, "T_ExtCALL(%s,\n", exp->u.ExtCALL.extfun); 
     else fprintf(out, "T_ExtCALL(%s", exp->u.ExtCALL.extfun); 
    if (args)
      for (;args; args=args->tail) {
        pr_tree_exp(out, args->head,d+2);
        if (args->tail) fprintf(out, ",\n");
      }
//    indent(out, d+2); fprintf(out, "NULL)");
      fprintf(out, ")");
    }
    break;
  } /* end of switch */
}

void printStmList (FILE *out, T_stmList stmList, int d) 
{
  T_stmList l=stmList;
  if (l) {
    //indent(out, d);
    //fprintf(out, "T_StmList(\n");
    fprintf(out, "[Stm #%d:] ", d);
    pr_stm(out, l->head, 0);
    fprintf(out, ",\n"); 
    printStmList(out, l->tail, d+1);
    //printStmList(out, l->tail, d+1); //don't indent stm any further
    //indent(out, d);
    //fprintf(out, ")");
  }
/*
  else {
    indent(out, d);
    fprintf(out, "NULL");
  }
*/
  return ;
}

void printFuncDecl(FILE *out, T_funcDecl funcDecl) 
{
  Temp_tempList t=funcDecl->args;
  T_stm sl=funcDecl->stm;

  fprintf(out, "--A Function---\nFuncDecl(%s,\n", funcDecl->name);
  fprintf(out, "[ARGS:]\n");
  if (!t) 
     fprintf(out, "NULL");
  else {
    if (t)
      for (;t; t=t->tail) {
        fprintf(out, " t%s", Temp_look(Temp_name(), t->head));
        if (t->tail) fprintf(out, ", \n");
      }
  }

  fprintf(out, "\n[STMS:]\n");
  if (sl) {
   if (sl->kind != T_SEQ) { 
    indent_dash(out, eseqlevel); fprintf(out, "[Stm#%d]", inst++);
   }
    pr_stm(out, sl, 1);
  }
  else 
    fprintf(out, "NULL");
  fprintf(out, "\n--End Func-----\n");
  return;
}

void printFuncDeclList(FILE *out, T_funcDeclList funcDeclList) 
{
   T_funcDeclList l=funcDeclList;
   while (l) { 
     //fprintf(out, "[FuncDeclList:]\n");
     printFuncDecl(out, l->head); 
     //fprintf(out, "),\n");
     l=l->tail;
   }
   //fprintf(out, "NULL)\n");
   return;
}
