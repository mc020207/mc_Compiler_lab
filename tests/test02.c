#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(2,5),
          A_Type(A_Pos(2,5), A_intType, NULL),
          String("r"),
          NULL
        ), // end of VarDecl for r 
        NULL
      ), // end of A_VarDeclList
      A_StmList(
        A_Return(A_Pos(3,5),
          A_EscExp(A_Pos(3,12), 
            A_StmList(
              A_AssignStm(A_Pos(3,15),
                A_IdExp(A_Pos(3,14), String("r")),
                A_CallExp(A_Pos(3,16),
                  A_NewObjExp(A_Pos(3,16), String("c2")), String("m1"), A_ExpList(
                    A_NumConst(A_Pos(3,28), 10),
                    NULL
                  )
                )
              ),
              A_StmList(
                A_Putint(A_Pos(3,33),
                  A_IdExp(A_Pos(3,40), String("r"))),
                NULL
              )
            ),
            A_IdExp(A_Pos(3,45), String("r"))
          )
        ),
        NULL
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(6,1),
        String("c1"),
        NULL,
        NULL, // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(7,5), // begin of MethodDecl for m1
            A_Type(A_Pos(7,12), A_intType, NULL),
            String("m1"),
            A_FormalList(
              A_Formal(A_Pos(7,19), A_Type(A_Pos(7,19), A_intType, NULL), String("x")),
              NULL
            ),
            NULL, // end of A_VarDeclList
            A_StmList(
              A_IfStm(A_Pos(8,9),
                A_OpExp(A_Pos(8,14), A_IdExp(A_Pos(8,13), String("x")), A_greater, A_NumConst(A_Pos(8,15), 2)),
                A_Return(A_Pos(9,12),
                  A_OpExp(A_Pos(9,31), A_CallExp(A_Pos(9,19),
                      A_ThisExp(A_Pos(9,19)), String("m1"), A_ExpList(
                        A_OpExp(A_Pos(9,28), A_IdExp(A_Pos(9,27), String("x")), A_minus, A_NumConst(A_Pos(9,29), 1)),
                        NULL
                      )
                    ), A_plus, A_CallExp(A_Pos(9,32),
                      A_ThisExp(A_Pos(9,32)), String("m1"), A_ExpList(
                        A_OpExp(A_Pos(9,41), A_IdExp(A_Pos(9,40), String("x")), A_minus, A_NumConst(A_Pos(9,42), 2)),
                        NULL
                      )
                    ))
                ),
                NULL
              ),
              A_StmList(
                A_Return(A_Pos(10,9),
                  A_IdExp(A_Pos(10,16), String("x"))
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
          NULL,
          NULL, // end of A_VarDeclList
          A_MethodDeclList( // begin of A_MethodDeclList
            A_MethodDecl(A_Pos(15,5), // begin of MethodDecl for m1
              A_Type(A_Pos(15,12), A_intType, NULL),
              String("m1"),
              A_FormalList(
                A_Formal(A_Pos(15,19), A_Type(A_Pos(15,19), A_intType, NULL), String("x")),
                NULL
              ),
              NULL, // end of A_VarDeclList
              A_StmList(
                A_Return(A_Pos(16,9),
                  A_NumConst(A_Pos(16,16), 0)
                ),
                NULL
              )
            ), // end of MethodDecl for m1
            NULL
          ) // end of A_MethodDeclList
        ), // end of ClassDecl for c2 
        NULL
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
