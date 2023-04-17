#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(2,5),
          A_Type(A_Pos(2,5), A_idType, String("c2")),
          String("x"),
          NULL
        ), // end of VarDecl for x 
        NULL
      ), // end of A_VarDeclList
      A_StmList(
        A_AssignStm(A_Pos(3,6),
          A_IdExp(A_Pos(3,5), String("x")),
          A_NewObjExp(A_Pos(3,7), String("c2"))
        ),
        A_StmList(
          A_AssignStm(A_Pos(4,9),
            A_ClassVarExp(A_Pos(3,0), A_IdExp(A_Pos(4,5), String("x")), String("i2")),
            A_NumConst(A_Pos(4,10), 100)
          ),
          A_StmList(
            A_Return(A_Pos(5,5),
              A_CallExp(A_Pos(5,0),
                A_IdExp(A_Pos(5,12), String("x")), String("m2"), A_ExpList(
                  A_NewObjExp(A_Pos(5,17), String("c1")),
                  NULL
                )
              )
            ),
            NULL
          )
        )
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(8,1),
        String("c1"),
        NULL,
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(9,5),
            A_Type(A_Pos(9,5), A_intType, NULL),
            String("c1m1"),
            NULL
          ), // end of VarDecl for c1m1 
          NULL
        ), // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(10,5), // begin of MethodDecl for m1
            A_Type(A_Pos(10,12), A_idType, String("c1")),
            String("m1"),
            A_FormalList(
              A_Formal(A_Pos(10,24), A_Type(A_Pos(10,24), A_intType, NULL), String("x")),
              NULL
            ),
            NULL, // end of A_VarDeclList
            A_StmList(
              A_AssignStm(A_Pos(11,18),
                A_ClassVarExp(A_Pos(11,9), A_ThisExp(A_Pos(11,9)), String("c1m1")),
                A_IdExp(A_Pos(11,19), String("x"))
              ),
              A_StmList(
                A_Return(A_Pos(12,9),
                  A_ThisExp(A_Pos(12,16))
                ),
                NULL
              )
            )
          ), // end of MethodDecl for m1
          NULL
        ) // end of A_MethodDeclList
      ), // end of ClassDecl for c1 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(16,1),
          String("c2"),
          String("c1"),
          A_VarDeclList( // begin of A_VarDeclList
            A_VarDecl(A_Pos(17,5),
              A_Type(A_Pos(17,5), A_intType, NULL),
              String("i2"),
              NULL
            ), // end of VarDecl for i2 
            NULL
          ), // end of A_VarDeclList
          A_MethodDeclList( // begin of A_MethodDeclList
            A_MethodDecl(A_Pos(18,5), // begin of MethodDecl for m2
              A_Type(A_Pos(18,12), A_intType, NULL),
              String("m2"),
              A_FormalList(
                A_Formal(A_Pos(18,19), A_Type(A_Pos(18,19), A_idType, String("c1")), String("c")),
                NULL
              ),
              NULL, // end of A_VarDeclList
              A_StmList(
                A_Return(A_Pos(19,9),
                  A_ClassVarExp(A_Pos(19,0), A_CallExp(A_Pos(19,0),
                      A_IdExp(A_Pos(19,16), String("c")), String("m1"), A_ExpList(
                        A_ClassVarExp(A_Pos(19,21), A_ThisExp(A_Pos(19,21)), String("i2")),
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
