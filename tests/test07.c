#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      NULL, // end of A_VarDeclList
      A_StmList(
        A_Return(A_Pos(2,5),
          A_CallExp(A_Pos(2,12),
            A_CallExp(A_Pos(2,12),
              A_NewObjExp(A_Pos(2,12), String("c2")), String("m1"), A_ExpList(
                A_NumConst(A_Pos(2,24), 1),
                NULL
              )
            ), String("m2"), A_ExpList(
              A_NumConst(A_Pos(2,30), 10),
              NULL
            )
          )
        ),
        NULL
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(5,1),
        String("c1"),
        NULL,
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(6,5),
            A_Type(A_Pos(6,5), A_intType, NULL),
            String("c1m1"),
            NULL
          ), // end of VarDecl for c1m1 
          NULL
        ), // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(8,5), // begin of MethodDecl for m1
            A_Type(A_Pos(8,12), A_idType, String("c2")),
            String("m1"),
            A_FormalList(
              A_Formal(A_Pos(8,24), A_Type(A_Pos(8,24), A_intType, NULL), String("x")),
              NULL
            ),
            NULL, // end of A_VarDeclList
            A_StmList(
              A_AssignStm(A_Pos(9,18),
                A_ClassVarExp(A_Pos(9,9), A_ThisExp(A_Pos(9,9)), String("c1m1")),
                A_IdExp(A_Pos(9,19), String("x"))
              ),
              A_StmList(
                A_Return(A_Pos(10,9),
                  A_ThisExp(A_Pos(10,16))
                ),
                NULL
              )
            )
          ), // end of MethodDecl for m1
          NULL
        ) // end of A_MethodDeclList
      ), // end of ClassDecl for c1 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(14,1),
          String("c2"),
          String("c1"),
          A_VarDeclList( // begin of A_VarDeclList
            A_VarDecl(A_Pos(15,5),
              A_Type(A_Pos(15,5), A_intType, NULL),
              String("i2"),
              NULL
            ), // end of VarDecl for i2 
            NULL
          ), // end of A_VarDeclList
          A_MethodDeclList( // begin of A_MethodDeclList
            A_MethodDecl(A_Pos(16,5), // begin of MethodDecl for m2
              A_Type(A_Pos(16,12), A_intType, NULL),
              String("m2"),
              A_FormalList(
                A_Formal(A_Pos(16,19), A_Type(A_Pos(16,19), A_intType, NULL), String("x")),
                NULL
              ),
              NULL, // end of A_VarDeclList
              A_StmList(
                A_Return(A_Pos(17,9),
                  A_ClassVarExp(A_Pos(17,16), A_CallExp(A_Pos(17,17),
                      A_ThisExp(A_Pos(17,17)), String("m1"), A_ExpList(
                        A_IdExp(A_Pos(17,25), String("x")),
                        NULL
                      )
                    ), String("c1m1"))
                ),
                NULL
              )
            ), // end of MethodDecl for m2
            NULL
          ) // end of A_MethodDeclList
        ), // end of ClassDecl for c2 
        NULL
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
