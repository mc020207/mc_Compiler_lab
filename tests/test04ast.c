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
        A_AssignStm(A_Pos(5,6),
          A_IdExp(A_Pos(5,5), String("a")),
          A_NotExp(A_Pos(5,7),
            A_OpExp(A_Pos(5,10), A_IdExp(A_Pos(5,9), String("i")), A_greater, A_NumConst(A_Pos(5,11), 0)))
        ),
        A_StmList(
          A_Return(A_Pos(6,5),
            A_IdExp(A_Pos(6,12), String("a"))
          ),
          NULL
        )
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
