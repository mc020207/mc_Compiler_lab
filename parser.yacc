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
    A_exp numberRest
    A_expList expList;
}

// token的类
// %token <name in union> token_name_1 token_name_2
%token <token> OP_PLUS OP_MINUS OP_MULTIPLY OP_DIVTION
%token <key> PUTINT PUTCH PUTARRAY GETINT GETCH GETARRAY MAIN INT PUBLIC CLASS IF ELSE WHILE CONTINUE BREAK RETURN STARTTIME STOPTIME TTRUE FFALSE LENGTH THIS NEW EXTENDS
%token <exp> ID NUMBER
// 非终结符的类
%type<type> TYPE
%type<prog> PROG
%type<mainMethod> MAINMETHOD
%type<classDecl> CLASSDECL
%type<classDeclList> CLASSDECLLIST
%type<methodDecl> METHODDECL
%type<methodDeclList> METHODDECLLIST
%type<formal> FORMALREST
%type<formalList> FORMALLIST FORMALRESTLIST
%type<varDecl> VARDECL
%type<varDeclList> VARDECLLIST
%type<stmList> STMLIST
%type<stm> STM
%type<exp> EXP NUMBERREST EXPREST
%type<expList> EXPLIST EXPRESTLIST NUMBERLIST NUMBERRESTLIST


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

FORMALLIST : TYPE ID FORMALRESTLIST
    {
        
    }
    |
    {
        $$=NULL;
    }

FORMALRESTLIST : FORMALREST FORMALRESTLIST
    {
        
    }
    |
    {
        $$=NULL;
    }
    
FORMALREST : ',' TYPE ID
    {

    }

VARDECLLIST : VARDECL VARDECLLIST
    {
        $$=A_VarDeclList($1,$2);
    }
    |
    {
        $$=NULL;
    }

EXPLIST : EXP EXPRESTLIST
    {
        
    }
    |
    {
        $$=NULL;
    }

EXPRESTLIST : EXPREST EXPRESTLIST
    {
        
    }
    |
    {
        $$=NULL;
    }
    
EXPREST : ',' EXP
    {

    }

NUMBERLIST : NUMBER NUMBERRESTLIST
    {
        $$=A_ExpList($1,$2);
    }
    |
    {
        $$=NULL;
    }

NUMBERRESTLIST : NUMBERREST NUMBERRESTLIST
    {
        $$=A_ExpList($1,$2);
    }
    |
    {
        $$=NULL;
    }

NUMBERREST : ',' NUMBER
    {
        $$=$2
    }

MAINMETHOD : PUBLIC INT MAIN '(' ')' '{' STMLIST '}' 
    {
        $$=A_MainMethod($1,NULL,$7);
    }

CLASSDECL : CLASS ID EXTENDS ID '{' VARDECLLIST METHODDECLLIST '}'
    {   
        
    }
    |
    CLASS ID '{' VARDECLLIST METHODDECLLIST '}'
    {

    }

VARDECL : CLASS ID ID ';'
    {

    }
    |
    INT ID ';'
    {

    }
    |
    INT ID '=' NUMBER ';'
    {

    }
    |
    INT '[' ']' ID ';'
    {

    }
    |
    INT '[' ']' ID '=' '{' NUMBERLIST '}' ';'
    {
        
    }

METHODDECL : PUBLIC TYPE ID '(' FORMALLIST ')' '{' VARDECLLIST STMLIST '}'
    {

    }

TYPE : CLASS ID
    {

    }
    |
    INT
    {

    }
    |
    INT '[' ']'
    {
        
    }

STM : '{' STMLIST '}'
    {

    }
    |
    IF '(' EXP ')' STM ELSE STM
    {

    }
    |
    IF '(' EXP ')' STM 
    {

    }
    |
    WHILE '(' EXP ')' STM 
    {

    }
    |
    WHILE '(' EXP ')' ';'
    {

    }
    |
    EXP '=' EXP ';'
    {
        $$=A_AssignStm($1->pos,$1,NULL,$3);
    }  
    |
    EXP '[' EXP ']' '=' EXP ';'
    {

    }
    |
    EXP '[' EXP ']' '=' '{' EXPLIST '}' ';'
    {

    }
    |
    EXP '.' ID '(' EXPLIST ')' ';'
    {

    }
    |
    CONTINUE ';'
    {

    }
    |
    BREAK ';'
    {

    }
    |
    RETURN EXP ';'
    {

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
    |
    PUTARRAY '(' EXP ',' EXP ')' ';'
    {

    }
    |
    STARTTIME '(' ')' ';'
    {

    }
    |
    STOPTIME  '(' ')' ';'
    {

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
    EXP '[' EXP ']'
    {

    }
    |
    EXP '.' ID '(' EXPLIST ')'
    {

    }
    |
    EXP '.' ID
    
    {

    }
    |
    NUMBER
    {
        $$=$1;
    }
    |
    TTRUE 
    {

    }
    |
    FFALSE
    {

    }
    |
    LENGTH '(' EXP ')'
    {

    }
    |
    ID
    {
        $$=$1;
    }
    |
    THIS
    {

    }
    |
    NEW INT '[' EXP ']'
    {

    }
    |
    NEW ID '('  ')' 
    {

    }
    |
    '!' EXP 
    {

    }
    |
    OP_MINUS EXP %prec UMINUS
    {
        $$=A_MinusExp($1,$2);
    }
    |
    '(' EXP ')'
    {
        $$=$2;
    }
    |
    '(' '{' STMLIST '}'  EXP ')'
    {
        if ($3==NULL) $$=A_EscExp(NULL, $3 , $5);
        else $$=A_EscExp($3->head->pos, $3 , $5);
    }
    |
    GETINT '(' ')'
    {
        
    }
    |
    GETCH '(' ')'
    {
        
    }
    |
    GETARRAY '(' EXP ')'
    {

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
