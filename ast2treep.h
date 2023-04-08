#pragma once
#include "fdmjast.h"
#include "printast.h"
#include "table.h"
#include "symbol.h"
#include "types.h"
#include "treep.h"
#include "typecheck.h"
T_exp rel2exp(A_exp x);
T_exp ast2treepExp(A_exp x);
T_expList ast2treepExpList(A_expList x);
T_stm ast2treepStm(A_stm x);
T_stm ast2treepStmList(A_stmList x);
T_stm ast2treepvarDeclList(A_varDeclList list);
T_funcDeclList ast2treepclassDeclList(A_classDeclList list);
T_funcDecl ast2treepMainmethod(A_mainMethod x);
T_funcDeclList ast2treepprog(A_prog x);