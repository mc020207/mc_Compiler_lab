#include <stdlib.h>
#include "../fdmjast.h"
#include "../prog1.h"
A_prog prog1() {
return
  A_Prog(A_Pos(2,1),
    A_MainMethod(A_Pos(2,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(3,5),
          A_Type(A_Pos(3,5), A_idType, String("c1")),
          String("my_class"),
          NULL
        ), // end of VarDecl for my_class 
        NULL
      ), // end of A_VarDeclList
      A_StmList(
        A_AssignStm(A_Pos(4,14),
          A_IdExp(A_Pos(4,5), String("my_class")),
          A_NewObjExp(A_Pos(4,16), String("c1"))
        ),
        A_StmList(
          A_Return(A_Pos(5,5),
            A_CallExp(A_Pos(5,1),
              A_IdExp(A_Pos(5,12), String("my_class")), String("b"), NULL
            )
          ),
          NULL
        )
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(8,1),
        String("c1"),
        NULL,
        NULL, // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(9,5), // begin of MethodDecl for a
            A_Type(A_Pos(9,12), A_intType, NULL),
            String("a"),
            NULL
,
            NULL, // end of A_VarDeclList
            A_StmList(
              A_Return(A_Pos(10,9),
                A_NumConst(A_Pos(10,16), 2)
              ),
              NULL
            )
          ), // end of MethodDecl for a
          NULL
        ) // end of A_MethodDeclList
      ), // end of ClassDecl for c1 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(14,1),
          String("c2"),
          String("c1"),
          NULL, // end of A_VarDeclList
          A_MethodDeclList( // begin of A_MethodDeclList
            A_MethodDecl(A_Pos(15,5), // begin of MethodDecl for a
              A_Type(A_Pos(15,12), A_intType, NULL),
              String("a"),
              NULL
,
              NULL, // end of A_VarDeclList
              A_StmList(
                A_Return(A_Pos(16,9),
                  A_NumConst(A_Pos(16,16), 3)
                ),
                NULL
              )
            ), // end of MethodDecl for a
            A_MethodDeclList(
              A_MethodDecl(A_Pos(18,5), // begin of MethodDecl for b
                A_Type(A_Pos(18,12), A_intType, NULL),
                String("b"),
                NULL
,
                NULL, // end of A_VarDeclList
                A_StmList(
                  A_Return(A_Pos(19,9),
                    A_NumConst(A_Pos(19,16), 3)
                  ),
                  NULL
                )
              ), // end of MethodDecl for b
              NULL
            )
          ) // end of A_MethodDeclList
        ), // end of ClassDecl for c2 
        NULL
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
