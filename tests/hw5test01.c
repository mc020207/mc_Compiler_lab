#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(2,5),
          A_Type(A_Pos(2,5), A_intArrType, NULL),
          String("a"),
          NULL
        ), // end of VarDecl for a 
        NULL
      ), // end of A_VarDeclList
      A_StmList(
        A_AssignStm(A_Pos(3,6),
          A_IdExp(A_Pos(3,5), String("a")),
          A_MinusExp(A_Pos(3,7),
            A_NumConst(A_Pos(3,8), 1))
        ),
        A_StmList(
          A_Putint(A_Pos(4,5),
            A_OpExp(A_Pos(4,13), A_IdExp(A_Pos(4,12), String("a")), A_plus, A_NumConst(A_Pos(4,14), 1))),
          A_StmList(
            A_Return(A_Pos(5,5),
              A_OpExp(A_Pos(5,15), A_OpExp(A_Pos(5,13), A_IdExp(A_Pos(5,12), String("a")), A_times, A_NumConst(A_Pos(5,14), 3)), A_plus, A_NumConst(A_Pos(5,16), 2))
            ),
            NULL
          )
        )
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
