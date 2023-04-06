#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(2,5),
          A_Type(A_Pos(2,5), A_intType, NULL),
          String("i"),
          A_ExpList(
            A_NumConst(A_Pos(2,5), 0),
            NULL
          )
        ), // end of VarDecl for i 
        A_VarDeclList(
          A_VarDecl(A_Pos(3,5),
            A_Type(A_Pos(3,5), A_intType, NULL),
            String("a"),
            NULL
          ), // end of VarDecl for a 
          NULL
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_WhileStm(A_Pos(5,5),
          A_OpExp(A_Pos(5,38), A_EscExp(A_Pos(5,12), 
              A_StmList(
                A_AssignStm(A_Pos(5,15),
                  A_IdExp(A_Pos(5,14), String("a")),
                  A_IdExp(A_Pos(5,16), String("i"))
                ),
                A_StmList(
                  A_AssignStm(A_Pos(5,20),
                    A_IdExp(A_Pos(5,19), String("i")),
                    A_OpExp(A_Pos(5,22), A_IdExp(A_Pos(5,21), String("i")), A_plus, A_NumConst(A_Pos(5,23), 1))
                  ),
                  NULL
                )
              ),
              A_EscExp(A_Pos(5,27), 
                A_StmList(
                  A_AssignStm(A_Pos(5,30),
                    A_IdExp(A_Pos(5,29), String("a")),
                    A_NumConst(A_Pos(5,31), 0)
                  ),
                  NULL
                ),
                A_IdExp(A_Pos(5,35), String("i"))
              )
            ), A_less, A_NumConst(A_Pos(5,39), 8)),
          NULL
        ),
        A_StmList(
          A_Putint(A_Pos(6,5),
            A_IdExp(A_Pos(6,12), String("a"))),
          A_StmList(
            A_Return(A_Pos(7,5),
              A_IdExp(A_Pos(7,12), String("a"))
            ),
            NULL
          )
        )
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
