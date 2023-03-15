%{
#include<stdio.h>
#include "fdmjast.h"
#include "printast.h"
extern A_prog root;

extern int yylex();
extern void yyerror(char*);
extern int  yywrap();

// extern int yydebug = 1;


%}

%union
{
    A_pos token; // 例：符号
    A_pos key; // 关键字
    A_type type;
    A_prog prog;
    A_mainMethod mainMethod;
    A_classDecl classDecl;
    A_classDeclList classDeclList;
    A_methodDecl methodDecl;
    A_methodDeclList methodDeclList;
    A_formal formal;
    A_formalList formalList;
    A_varDecl varDecl;
    A_varDeclList varDeclList;
    A_stmList stmList;
    A_stm stm;
    A_exp exp;
    A_expList expList;
}

// token的类
// %token <name in union> token_name_1 token_name_2
%token <token> OP_PLUS OP_MINUS OP_MULTIPLY OP_DIVTION
%token <key> PUTINT PUTCH MAIN INT PUBLIC CLASS IF WHILE CONTINUE BREAK RETURN STARTTIME STOPTIME TTRUE FFALSE LENGTH THIS NEW
%token <exp> IDENTIFIER NUMBER
// 非终结符的类
%type<type> TYPE
%type<prog> PROG
%type<mainMethod> MAINMETHOD
%type<classDecl> CLASSDECL
%type<classDeclList> CLASSDECLLIST
%type<methodDecl> METHODDECL
%type<methodDeclList> METHODDECLLIST
%type<formal> FORMAL
%type<formalList> FORMALLIST
%type<varDecl> VARDECL
%type<varDeclList> VARDECLLIST
%type<stmList> STMLIST
%type<stm> STM
%type<exp> EXP
%type<expList> EXPLIST


%left OP_PLUS OP_MINUS
%left OP_MULTIPLY OP_DIVTION
%left UMINUS

%start PROG
%%

PROG : MAINMETHOD CLASSDECLLIST
    {
        root=A_Prog($1->pos,$1,$2);
        $$=root;
    }
    
STMLIST : STM  STMLIST
    {
        $$=A_StmList($1,$2);
    }
    |
    {
        $$=NULL;
    }

CLASSDECLLIST : CLASSDECL CLASSDECLLIST
    {
        $$=A_ClassDeclList($1,$2);
    }
    |
    {
        $$=NULL:
    }

METHODDECLLIST : METHODDECL METHODDECLLIST
    {
        $$=A_MethodDeclList($1,$2);
    }
    |
    {
        $$=NULL;
    }

FORMALLIST : FORMAL FORMALLIST
    {
        $$=A_FormalList($1,$2);
    }
    |
    {
        $$=NULL;
    }

VARDECLLIST : VARDECL VARDECLLIST
    {
        $$=A_VarDeclList($1,$2);
    }
    |
    {
        $$=NULL;
    }

EXPLIST : EXP EXPLIST
    {
        $$=A_ExpList($1,$2);
    }
    |
    {
        $$=NULL;
    }

MAINMETHOD : PUBLIC INT MAIN '(' ')' '{' STMLIST '}' 
    {
        $$=A_MainMethod($1,NULL,$7);
    }

STM : IDENTIFIER '=' EXP ';'
    {
        $$=A_AssignStm($1->pos,$1,NULL,$3);
    }  
    |
    PUTINT '(' EXP ')' ';'
    {
        $$=A_Putint($1,$3);
    }
    |
    PUTCH '(' EXP ')' ';'
    {
        $$=A_Putint($1,$3);
    }

EXP : EXP OP_PLUS EXP
    {
        $$=A_OpExp($1->pos,$1,A_plus,$3);
    }
    |
    EXP OP_MINUS EXP
    {
        $$=A_OpExp($1->pos,$1,A_minus,$3);
    }
    |
    EXP OP_MULTIPLY EXP
    {
        $$=A_OpExp($1->pos,$1,A_times,$3);
    }
    |
    EXP OP_DIVTION EXP
    {
        $$=A_OpExp($1->pos,$1,A_div,$3);
    }
    |
    NUMBER
    {
        $$=$1;
    }
    |
    IDENTIFIER
    {
        $$=$1;
    }
    |
    OP_MINUS EXP %prec UMINUS
    {
        $$=A_MinusExp($1,$2);
    }
    |
    '(' EXP ')'
    {
        // $$=A_EscExp($2->pos, NULL , $2);
        $$=$2;
    }
    |
    '(' '{' STMLIST '}'  EXP ')'
    {
        if ($3==NULL) $$=A_EscExp(NULL, $3 , $5);
        else $$=A_EscExp($3->head->pos, $3 , $5);
    }
%%

void yyerror(s)
char *s;
{
    fprintf(stderr, "%s\n",s);
}

int yywrap()
{
    return(1);
}
