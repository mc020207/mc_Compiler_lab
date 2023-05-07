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
          String("x"),
          NULL
        ), // end of VarDecl for x 
        NULL
      ), // end of A_VarDeclList
      NULL

    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(6,1),
        String("c1"),
        NULL,
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(7,5),
            A_Type(A_Pos(7,5), A_intType, NULL),
            String("x"),
            NULL
          ), // end of VarDecl for x 
          NULL
        ), // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(8,5), // begin of MethodDecl for a
            A_Type(A_Pos(8,12), A_intType, NULL),
            String("a"),
            A_FormalList(
              A_Formal(A_Pos(8,18), A_Type(A_Pos(8,18), A_intType, NULL), String("x")),
              NULL
            ),
            NULL, // end of A_VarDeclList
            A_StmList(
              A_Return(A_Pos(9,9),
                A_ClassVarExp(A_Pos(9,16), A_ThisExp(A_Pos(9,16)), String("y"))
              ),
              NULL
            )
          ), // end of MethodDecl for a
          NULL
        ) // end of A_MethodDeclList
      ), // end of ClassDecl for c1 
      NULL
    ) // end of A_ClassDeclList
  ); // end of Prog
}
