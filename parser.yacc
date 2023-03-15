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
    A_exp expr; // 例：自定义的类
    A_prog prog;
    A_stm stm;
    A_stmList stmlist;
    A_mainMethod mainmethod;
}

// token的类
// %token <name in union> token_name_1 token_name_2
%token <token> OP_PLUS OP_MINUS OP_MULTIPLY OP_DIVTION
%token <expr> NUMBER
%token <key> PUTINT PUTCH MAIN INT PUBLIC
%token <expr> IDENTIFIER
// 非终结符的类
%type <expr> EXPR
%type <stm> STM
%type <stmlist> STMLIST
%type <prog> PROG
%type <mainmethod> MAINMETHOD

%left OP_PLUS OP_MINUS
%left OP_MULTIPLY OP_DIVTION
%left UMINUS

%start PROG
%%

PROG : MAINMETHOD
    {
        root=A_Prog($1->pos,$1,NULL);
        $$=root;
    }
    

MAINMETHOD : PUBLIC INT MAIN '(' ')' '{' STMLIST '}' 
    {
        $$=A_MainMethod($1,NULL,$7);
    }

STMLIST : STM  STMLIST
    {
        $$=A_StmList($1,$2);
    }
    |
    {
        $$=NULL;
    }

STM : IDENTIFIER '=' EXPR ';'
    {
        $$=A_AssignStm($1->pos,$1,NULL,$3);
    }  
    |
    PUTINT '(' EXPR ')' ';'
    {
        $$=A_Putint($1,$3);
    }
    |
    PUTCH '(' EXPR ')' ';'
    {
        $$=A_Putint($1,$3);
    }

EXPR : EXPR OP_PLUS EXPR
    {
        $$=A_OpExp($1->pos,$1,A_plus,$3);
    }
    |
    EXPR OP_MINUS EXPR
    {
        $$=A_OpExp($1->pos,$1,A_minus,$3);
    }
    |
    EXPR OP_MULTIPLY EXPR
    {
        $$=A_OpExp($1->pos,$1,A_times,$3);
    }
    |
    EXPR OP_DIVTION EXPR
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
    OP_MINUS EXPR %prec UMINUS
    {
        $$=A_MinusExp($1,$2);
    }
    |
    '(' EXPR ')'
    {
        // $$=A_EscExp($2->pos, NULL , $2);
        $$=$2;
    }
    |
    '(' '{' STMLIST '}'  EXPR ')'
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
