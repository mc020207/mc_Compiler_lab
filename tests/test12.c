#include <stdlib.h>
#include "../fdmjast.h"
#include "../prog1.h"
A_prog prog1() {
return
  A_Prog(A_Pos(2,1),
    A_MainMethod(A_Pos(2,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(3,5),
          A_Type(A_Pos(3,5), A_intType, NULL),
          String("a"),
          NULL
        ), // end of VarDecl for a 
        NULL
      ), // end of A_VarDeclList
      A_StmList(
        A_Return(A_Pos(4,5),
          A_ClassVarExp(A_Pos(4,12), A_ThisExp(A_Pos(4,12)), String("a"))
        ),
        NULL
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
