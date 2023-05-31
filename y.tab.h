/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OP_PLUS = 258,
    OP_MINUS = 259,
    OP_MULTIPLY = 260,
    OP_DIVTION = 261,
    OP_LESS = 262,
    OP_LE = 263,
    OP_GREAT = 264,
    OP_GE = 265,
    OP_EQ = 266,
    OP_NEQ = 267,
    OP_OR = 268,
    OP_AND = 269,
    PUTINT = 270,
    PUTCH = 271,
    PUTARRAY = 272,
    GETINT = 273,
    GETCH = 274,
    GETARRAY = 275,
    MAIN = 276,
    INT = 277,
    PUBLIC = 278,
    CLASS = 279,
    IF = 280,
    ELSE = 281,
    WHILE = 282,
    CONTINUE = 283,
    BREAK = 284,
    RETURN = 285,
    STARTTIME = 286,
    STOPTIME = 287,
    TTRUE = 288,
    FFALSE = 289,
    LENGTH = 290,
    THIS = 291,
    NEW = 292,
    EXTENDS = 293,
    ID = 294,
    NUM = 295,
    UMINUS = 296
  };
#endif
/* Tokens.  */
#define OP_PLUS 258
#define OP_MINUS 259
#define OP_MULTIPLY 260
#define OP_DIVTION 261
#define OP_LESS 262
#define OP_LE 263
#define OP_GREAT 264
#define OP_GE 265
#define OP_EQ 266
#define OP_NEQ 267
#define OP_OR 268
#define OP_AND 269
#define PUTINT 270
#define PUTCH 271
#define PUTARRAY 272
#define GETINT 273
#define GETCH 274
#define GETARRAY 275
#define MAIN 276
#define INT 277
#define PUBLIC 278
#define CLASS 279
#define IF 280
#define ELSE 281
#define WHILE 282
#define CONTINUE 283
#define BREAK 284
#define RETURN 285
#define STARTTIME 286
#define STOPTIME 287
#define TTRUE 288
#define FFALSE 289
#define LENGTH 290
#define THIS 291
#define NEW 292
#define EXTENDS 293
#define ID 294
#define NUM 295
#define UMINUS 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "parser.yacc"

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

#line 159 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
