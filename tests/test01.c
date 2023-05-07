#include <stdlib.h>
#include "../fdmjast.h"
#include "../prog1.h"
A_prog prog1() {
return
  A_Prog(A_Pos(2,1),
    A_MainMethod(A_Pos(2,1), // begin of main class
      NULL, // end of A_VarDeclList
      A_StmList(
        A_Return(A_Pos(3,5),
          A_ClassVarExp(A_Pos(3,12), A_NewObjExp(A_Pos(3,12), String("c2")), String("a"))
        ),
        NULL
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(6,1),
        String("c1"),
        NULL,
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(7,5),
            A_Type(A_Pos(7,5), A_intType, NULL),
            String("a"),
            NULL
          ), // end of VarDecl for a 
          NULL
        ), // end of A_VarDeclList
        NULL // end of A_MethodDeclList
      ), // end of ClassDecl for c1 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(10,1),
          String("c2"),
          String("c1"),
          A_VarDeclList( // begin of A_VarDeclList
            A_VarDecl(A_Pos(11,5),
              A_Type(A_Pos(11,5), A_intArrType, NULL),
              String("a"),
              NULL
            ), // end of VarDecl for a 
            NULL
          ), // end of A_VarDeclList
          NULL // end of A_MethodDeclList
        ), // end of ClassDecl for c2 
        NULL
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
