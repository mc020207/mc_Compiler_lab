#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      NULL, // end of A_VarDeclList
      A_StmList(
        A_Return(A_Pos(2,5),
          A_ArrayExp(A_Pos(2,12), A_NewIntArrExp(A_Pos(2,13), A_NumConst(A_Pos(2,21), 10)), A_NumConst(A_Pos(2,26), 1))
        ),
        NULL
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
