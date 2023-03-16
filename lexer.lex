%{
#include "util.h"
#include "fdmjast.h"
#include "y.tab.h"
int c;
int calculate(char *s, int len);
int line=1,pos=0;
%}
%start COMMENT1  COMMENT2
%%
<COMMENT1>"\n" {++line;pos=0;BEGIN INITIAL;}
<COMMENT1>. {pos+=yyleng;}

<COMMENT2>"*/" {pos+=yyleng;BEGIN INITIAL;}
<COMMENT2>"\n" {++line;pos=0;}
<COMMENT2>. {pos+=yyleng;}


<INITIAL>"\n" {++line;pos=0;}
<INITIAL>" "|"\r"|"\t" {pos+=yyleng;;}
<INITIAL>"+" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_PLUS; }
<INITIAL>"-" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_MINUS;}
<INITIAL>"*" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_MULTIPLY; }
<INITIAL>"/" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_DIVTION; }
<INITIAL>"<" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_LESS; }
<INITIAL>"<=" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_LE; }
<INITIAL>">" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_GREAT; }
<INITIAL>">=" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_GE; }
<INITIAL>"==" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_EQ; }
<INITIAL>"!=" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_NEQ; }
<INITIAL>"||" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_OR; }
<INITIAL>"&&" {yylval.token = A_Pos(line,pos); pos+=yyleng; return OP_AND; }
<INITIAL>"//" {pos+=yyleng;BEGIN COMMENT1;}
<INITIAL>"/*" {pos+=yyleng;BEGIN COMMENT2;}
<INITIAL>"putint" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return PUTINT;
}
<INITIAL>"putch" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return PUTCH;
}
<INITIAL>"putarray" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return PUTARRAY;
}
<INITIAL>"getint" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return GETINT;
}
<INITIAL>"getch" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return GETCH;
}
<INITIAL>"getarray" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return GETARRAY;
}
<INITIAL>"public" {
    // printf("public\n");
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return PUBLIC;
}
<INITIAL>"int" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return INT;
}
<INITIAL>"main" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return MAIN;
}
<INITIAL>"class" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return CLASS;
}
<INITIAL>"if" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return IF;
}
<INITIAL>"else" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return ELSE;
}
<INITIAL>"while" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return WHILE;
}
<INITIAL>"continue" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return CONTINUE;
}
<INITIAL>"break" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return BREAK;
}
<INITIAL>"return" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return RETURN;
}
<INITIAL>"starttime" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return STARTTIME;
}
<INITIAL>"stoptime" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return STOPTIME;
}
<INITIAL>"true" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return TTRUE;
}
<INITIAL>"false" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return FFALSE;
}
<INITIAL>"length" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return LENGTH;
}
<INITIAL>"this" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return THIS;
}
<INITIAL>"new" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return NEW;
}
<INITIAL>"extends" {
    yylval.key=A_Pos(line,pos);
    pos+=yyleng;
    return EXTENDS;
}
<INITIAL>"("|")"|":"|"="|","|";"|"{"|"}"|"."|"!"|"["|"]" {
    yylval.token=A_Pos(line,pos);
    pos+=yyleng;
    c = yytext[0];
    return(c);
}
<INITIAL>[a-z_A-Z][a-z_A-Z0-9]* {
    yylval.exp = A_IdExp(A_Pos(line,pos),String(yytext));
    pos+=yyleng; 
    return ID;
}
<INITIAL>[1-9][0-9]* {
    yylval.exp=A_NumConst(A_Pos(line,pos),calculate(yytext,yyleng));
    pos+=yyleng; 
    return NUM;
}
<INITIAL>0 {
    yylval.exp = A_NumConst(A_Pos(line,pos),0);
    pos+=yyleng;
    return NUM;
}
<INITIAL>. {
    pos+=yyleng;
    printf("Illegal input \"%c\"\n", yytext[0]);
}
%%


int calculate(char *s, int len) {
    int ret = 0;
    for(int i = 0; i < len; i++)
        ret = ret * 10 + (s[i] - '0');
    return ret;
}