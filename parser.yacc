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
%token <token> OP_PLUS OP_MINUS OP_MULTIPLY OP_DIVTION OP_LESS OP_LE OP_GREAT OP_GE OP_EQ OP_NEQ OP_OR OP_AND '(' ')' ':' '=' ',' ';' '{' '}' '.' '!' '[' ']'
%token <key> PUTINT PUTCH PUTARRAY GETINT GETCH GETARRAY MAIN INT PUBLIC CLASS IF ELSE WHILE CONTINUE BREAK RETURN STARTTIME STOPTIME TTRUE FFALSE LENGTH THIS NEW EXTENDS
%token <exp> ID NUM
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
%type<exp> EXP NUMBER NUMBERREST EXPREST
%type<expList> EXPLIST EXPRESTLIST NUMBERLIST NUMBERRESTLIST



%right '='
%left OP_OR
%left OP_AND
%left OP_EQ OP_NEQ
%left OP_LE OP_LESS OP_GREAT OP_GE
%left OP_PLUS OP_MINUS
%left OP_MULTIPLY OP_DIVTION
%right '!' UMINUS
%left '[' ']' '(' ')'
%left '.'
%right ELSE

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
        $$=NULL;
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
        $$=A_FormalList(A_Formal($1->pos,$1,$2->u.v),$3);
    }
    |
    {
        $$=NULL;
    }

FORMALRESTLIST : FORMALREST FORMALRESTLIST
    {
        $$=A_FormalList($1,$2);
    }
    |
    {
        $$=NULL;
    }
    
FORMALREST : ',' TYPE ID
    {
        $$=A_Formal($1,$2,$3->u.v);
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
        $$=A_ExpList($1, $2);
    }
    |
    {
        $$=NULL;
    }

EXPRESTLIST : EXPREST EXPRESTLIST
    {
        $$=A_ExpList($1, $2);
    }
    |
    {
        $$=NULL;
    }
    
EXPREST : ',' EXP
    {
        $$=$2;
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
        $$=$2;
    }

MAINMETHOD : PUBLIC INT MAIN '(' ')' '{' VARDECLLIST STMLIST '}' 
    {
        $$=A_MainMethod($1,$7,$8);
    }

CLASSDECL : PUBLIC CLASS ID EXTENDS ID '{' VARDECLLIST METHODDECLLIST '}'
    {   
        $$=A_ClassDecl($1, $3->u.v, $5->u.v, $7, $8);
    }
    |
    PUBLIC CLASS ID '{' VARDECLLIST METHODDECLLIST '}'
    {
        $$=A_ClassDecl($1, $3->u.v, NULL , $5 , $6);
    }

VARDECL : CLASS ID ID ';'
    {
        $$=A_VarDecl($1, A_Type($1,A_idType,$2->u.v), $3->u.v, NULL);
    }
    |
    INT ID ';'
    {
        $$=A_VarDecl($1, A_Type($1,A_intType,NULL), $2->u.v, NULL);
    }
    |
    INT ID '=' NUMBER ';'
    {
        $$=A_VarDecl($1, A_Type($1,A_intType,NULL), $2->u.v, A_ExpList($4,NULL));
    }
    |
    INT '[' ']' ID ';'
    {
        $$=A_VarDecl($1, A_Type($1,A_intArrType,NULL), $4->u.v, NULL);
    }
    |
    INT '[' ']' ID '=' '{' NUMBERLIST '}' ';'
    {
        $$=A_VarDecl($1, A_Type($1,A_intArrType,NULL), $4->u.v, $7);
    }

METHODDECL : PUBLIC TYPE ID '(' FORMALLIST ')' '{' VARDECLLIST STMLIST '}'
    {
        $$=A_MethodDecl($1, $2, $3->u.v, $5, $8, $9);
    }

TYPE : CLASS ID
    {
        $$=A_Type($1,A_idType,$2->u.v);
    }
    |
    INT
    {
        $$=A_Type($1,A_intType,NULL);
    }
    |
    INT '[' ']'
    {
        $$=A_Type($1,A_intArrType,NULL);
    }

NUMBER : NUM
    {
        $$=$1;
    }
    |
    OP_MINUS NUM
    {
        $$=A_NumConst($1,-$2->u.num);
    }

STM : '{' STMLIST '}'
    {
        $$=A_NestedStm($1,$2);
    }
    |
    IF '(' EXP ')' STM ELSE STM
    {
        $$=A_IfStm($1,$3,$5,$7);
    }
    |
    IF '(' EXP ')' STM
    {
        $$=A_IfStm($1,$3,$5,NULL);
    }
    |
    WHILE '(' EXP ')' STM 
    {
        $$=A_WhileStm($1,$3,$5);
    }
    |
    WHILE '(' EXP ')' ';'
    {
        $$=A_WhileStm($1,$3,NULL);
    }
    |
    EXP '=' EXP ';'
    {
        $$=A_AssignStm($1->pos,$1,NULL,$3);
    }  
    |
    /* EXP '[' EXP ']' '=' EXP ';'
    {

    }
    | */
    EXP '[' ']' '=' '{' EXPLIST '}' ';'
    {
        $$=A_ArrayInit($1->pos,$1, $6); 
    }
    |
    EXP '.' ID '(' EXPLIST ')' ';'
    {
        $$=A_CallStm($1->pos,$1,$3->u.v,$5);
    }
    |
    CONTINUE ';'
    {
        $$=A_Continue($1);
    }
    |
    BREAK ';'
    {
        $$=A_Break($1);
    }
    |
    RETURN EXP ';'
    {
        $$=A_Return($1,$2);
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
        $$=A_Putarray($1,$3,$5);
    }
    |
    STARTTIME '(' ')' ';'
    {
        $$=A_Starttime($1);
    }
    |
    STOPTIME  '(' ')' ';'
    {
        $$=A_Stoptime($1);
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
    EXP OP_LESS EXP
    {
        $$=A_OpExp($1->pos,$1,A_less,$3);
    }
    |
    EXP OP_LE EXP
    {
        $$=A_OpExp($1->pos,$1,A_le,$3);
    }
    |
    EXP OP_GREAT EXP
    {
        $$=A_OpExp($1->pos,$1,A_greater,$3);
    }
    |
    EXP OP_GE EXP
    {
        $$=A_OpExp($1->pos,$1,A_ge,$3);
    }
    |
    EXP OP_EQ EXP
    {
        $$=A_OpExp($1->pos,$1,A_eq,$3);
    }
    |
    EXP OP_NEQ EXP
    {
        $$=A_NotExp($1->pos,A_OpExp($1->pos,$1,A_eq,$3));
    }
    |
    EXP OP_OR EXP
    {
        $$=A_OpExp($1->pos,$1,A_or,$3);
    }
    |
    EXP OP_AND EXP
    {
        $$=A_OpExp($1->pos,$1,A_and,$3);
    }
    |
    EXP '[' EXP ']'
    {
        $$=A_ArrayExp($1->pos,$1,$3);
    }
    |
    EXP '.' ID '(' EXPLIST ')'
    {   
        $$=A_CallExp($1->pos,$1,$3->u.v,$5);
    }
    |
    EXP '.' ID
    {
        $$=A_ClassVarExp($1->pos,$1,$3->u.v,NULL);
    }
    |
    /* EXP '.' ID '[' EXP ']'
    {
        $$=A_ClassVarExp($1->pos,$1,$3->u.v,$5);
    }
    | */
    NUM
    {
        $$=$1;
    }
    |
    TTRUE 
    {
        $$=A_BoolConst($1,TRUE);
    }
    |
    FFALSE
    {
        $$=A_BoolConst($1,FALSE);
    }
    |
    LENGTH '(' EXP ')'
    {
        $$=A_LengthExp($1,$3);
    }
    |
    ID
    {
        $$=$1;
    }
    |
    THIS
    {
        $$=A_ThisExp($1);
    }
    |
    NEW INT '[' EXP ']'
    {
        $$=A_NewIntArrExp($1,$4);
    }
    |
    NEW ID '('  ')' 
    {
        $$=A_NewObjExp($1,$2->u.v);
    }
    |
    '!' EXP 
    {
        $$=A_NotExp($1,$2);
    }
    |
    OP_MINUS EXP %prec UMINUS
    {
        $$=A_MinusExp($1,$2);
    }
    |
    '(' EXP ')'
    {
        $2->pos=$1;
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
        $$=A_Getint($1);
    }
    |
    GETCH '(' ')'
    {
        $$=A_Getch($1);
    }
    |
    GETARRAY '(' EXP ')'
    {
        $$=A_Getarray($1,$3);
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
