#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      NULL, // end of A_VarDeclList
      NULL

    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(3,1),
        String("C2"),
        String("C1"),
        NULL, // end of A_VarDeclList
        NULL // end of A_MethodDeclList
      ), // end of ClassDecl for C2 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(4,1),
          String("C3"),
          String("C2"),
          NULL, // end of A_VarDeclList
          NULL // end of A_MethodDeclList
        ), // end of ClassDecl for C3 
        A_ClassDeclList(
          A_ClassDecl(A_Pos(5,1),
            String("C1"),
            String("C0"),
            NULL, // end of A_VarDeclList
            NULL // end of A_MethodDeclList
          ), // end of ClassDecl for C1 
          A_ClassDeclList(
            A_ClassDecl(A_Pos(6,1),
              String("C0"),
              String("C3"),
              NULL, // end of A_VarDeclList
              NULL // end of A_MethodDeclList
            ), // end of ClassDecl for C0 
            NULL
          )
        )
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
