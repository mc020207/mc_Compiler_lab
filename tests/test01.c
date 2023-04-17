#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(2,5),
          A_Type(A_Pos(2,5), A_idType, String("c1")),
          String("c"),
          NULL
        ), // end of VarDecl for c 
        NULL
      ), // end of A_VarDeclList
      A_StmList(
        A_AssignStm(A_Pos(3,6),
          A_IdExp(A_Pos(3,5), String("c")),
          A_NewObjExp(A_Pos(3,7), String("c1"))
        ),
        A_StmList(
          A_Return(A_Pos(4,5),
            A_ClassVarExp(A_Pos(4,0), A_IdExp(A_Pos(4,12), String("c")), String("x"))
          ),
          NULL
        )
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(7,1),
        String("c5"),
        String("c2"),
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(7,29),
            A_Type(A_Pos(7,29), A_intType, NULL),
            String("x"),
            NULL
          ), // end of VarDecl for x 
          NULL
        ), // end of A_VarDeclList
        NULL // end of A_MethodDeclList
      ), // end of ClassDecl for c5 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(8,1),
          String("c1"),
          NULL,
          A_VarDeclList( // begin of A_VarDeclList
            A_VarDecl(A_Pos(8,18),
              A_Type(A_Pos(8,18), A_intType, NULL),
              String("x"),
              A_ExpList(
                A_NumConst(A_Pos(8,18), 2),
                NULL
              )
            ), // end of VarDecl for x 
            NULL
          ), // end of A_VarDeclList
          NULL // end of A_MethodDeclList
        ), // end of ClassDecl for c1 
        A_ClassDeclList(
          A_ClassDecl(A_Pos(9,1),
            String("c3"),
            NULL,
            NULL, // end of A_VarDeclList
            NULL // end of A_MethodDeclList
          ), // end of ClassDecl for c3 
          A_ClassDeclList(
            A_ClassDecl(A_Pos(10,1),
              String("c4"),
              String("c3"),
              NULL, // end of A_VarDeclList
              NULL // end of A_MethodDeclList
            ), // end of ClassDecl for c4 
            A_ClassDeclList(
              A_ClassDecl(A_Pos(11,1),
                String("c2"),
                String("c1"),
                NULL, // end of A_VarDeclList
                NULL // end of A_MethodDeclList
              ), // end of ClassDecl for c2 
              NULL
            )
          )
        )
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
