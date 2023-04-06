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
          A_OpExp(A_Pos(5,30), A_NotExp(A_Pos(5,12),
              A_EscExp(A_Pos(5,13), 
                A_StmList(
                  A_AssignStm(A_Pos(5,16),
                    A_IdExp(A_Pos(5,15), String("a")),
                    A_IdExp(A_Pos(5,17), String("i"))
                  ),
                  A_StmList(
                    A_AssignStm(A_Pos(5,21),
                      A_IdExp(A_Pos(5,20), String("i")),
                      A_OpExp(A_Pos(5,23), A_IdExp(A_Pos(5,22), String("i")), A_plus, A_NumConst(A_Pos(5,24), 1))
                    ),
                    NULL
                  )
                ),
                A_IdExp(A_Pos(5,28), String("i"))
              )), A_less, A_NumConst(A_Pos(5,31), 8)),
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
