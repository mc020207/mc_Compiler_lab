#include <stdlib.h>
#include "../fdmjast.h"
#include "../prog1.h"
A_prog prog1() {
return
  A_Prog(A_Pos(2,1),
    A_MainMethod(A_Pos(2,1), // begin of main class
      NULL, // end of A_VarDeclList
      NULL

    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(5,1),
        String("c1"),
        NULL,
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(6,5),
            A_Type(A_Pos(6,5), A_intType, NULL),
            String("x"),
            NULL
          ), // end of VarDecl for x 
          NULL
        ), // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(7,5), // begin of MethodDecl for a
            A_Type(A_Pos(7,12), A_intType, NULL),
            String("a"),
            NULL
,
            A_VarDeclList( // begin of A_VarDeclList
              A_VarDecl(A_Pos(8,9),
                A_Type(A_Pos(8,9), A_intType, NULL),
                String("x"),
                NULL
              ), // end of VarDecl for x 
              NULL
            ), // end of A_VarDeclList
            A_StmList(
              A_Return(A_Pos(9,9),
                A_NumConst(A_Pos(9,16), 3)
              ),
              NULL
            )
          ), // end of MethodDecl for a
          NULL
        ) // end of A_MethodDeclList
      ), // end of ClassDecl for c1 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(13,1),
          String("c2"),
          NULL,
          NULL, // end of A_VarDeclList
          A_MethodDeclList( // begin of A_MethodDeclList
            A_MethodDecl(A_Pos(14,5), // begin of MethodDecl for a
              A_Type(A_Pos(14,12), A_intType, NULL),
              String("a"),
              A_FormalList(
                A_Formal(A_Pos(14,18), A_Type(A_Pos(14,18), A_intType, NULL), String("x")),
                NULL
              ),
              NULL, // end of A_VarDeclList
              A_StmList(
                A_Return(A_Pos(15,9),
                  A_IdExp(A_Pos(15,16), String("x"))
                ),
                NULL
              )
            ), // end of MethodDecl for a
            A_MethodDeclList(
              A_MethodDecl(A_Pos(17,5), // begin of MethodDecl for a
                A_Type(A_Pos(17,12), A_intType, NULL),
                String("a"),
                A_FormalList(
                  A_Formal(A_Pos(17,18), A_Type(A_Pos(17,18), A_intType, NULL), String("x")),
                  NULL
                ),
                NULL, // end of A_VarDeclList
                A_StmList(
                  A_Return(A_Pos(18,9),
                    A_NumConst(A_Pos(18,16), 4)
                  ),
                  NULL
                )
              ), // end of MethodDecl for a
              NULL
            )
          ) // end of A_MethodDeclList
        ), // end of ClassDecl for c2 
        NULL
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
