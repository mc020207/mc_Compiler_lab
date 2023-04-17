#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(2,5),
          A_Type(A_Pos(2,5), A_intType, NULL),
          String("i"),
          A_ExpList(
            A_NumConst(A_Pos(2,5), 3),
            NULL
          )
        ), // end of VarDecl for i 
        A_VarDeclList(
          A_VarDecl(A_Pos(3,5),
            A_Type(A_Pos(3,5), A_intArrType, NULL),
            String("a"),
            A_ExpList(
              A_NumConst(A_Pos(3,5), 9),
              A_ExpList(
                A_NumConst(A_Pos(3,5), 8),
                A_ExpList(
                  A_NumConst(A_Pos(3,5), 7),
                  A_ExpList(
                    A_NumConst(A_Pos(3,5), 6),
                    A_ExpList(
                      A_NumConst(A_Pos(3,5), 5),
                      A_ExpList(
                        A_NumConst(A_Pos(3,5), 4),
                        A_ExpList(
                          A_NumConst(A_Pos(3,5), 3),
                          A_ExpList(
                            A_NumConst(A_Pos(3,5), 2),
                            A_ExpList(
                              A_NumConst(A_Pos(3,5), 1),
                              A_ExpList(
                                A_NumConst(A_Pos(3,5), 0),
                                NULL
                              )
                            )
                          )
                        )
                      )
                    )
                  )
                )
              )
            )
          ), // end of VarDecl for a 
          NULL
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_Return(A_Pos(4,5),
          A_CallExp(A_Pos(4,12),
            A_NewObjExp(A_Pos(4,12), String("c1")), String("m1"), A_ExpList(
              A_IdExp(A_Pos(4,24), String("a")),
              A_ExpList(
                A_IdExp(A_Pos(4,26), String("i")),
                NULL
              )
            )
          )
        ),
        NULL
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(7,1),
        String("c1"),
        NULL,
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(8,5),
            A_Type(A_Pos(8,5), A_intType, NULL),
            String("max"),
            A_ExpList(
              A_NumConst(A_Pos(8,5), -100),
              NULL
            )
          ), // end of VarDecl for max 
          NULL
        ), // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(10,5), // begin of MethodDecl for m1
            A_Type(A_Pos(10,12), A_intType, NULL),
            String("m1"),
            A_FormalList(
              A_Formal(A_Pos(10,19), A_Type(A_Pos(10,19), A_intArrType, NULL), String("a")),
              A_FormalList(
              A_Formal(A_Pos(10,28), A_Type(A_Pos(10,28), A_intType, NULL), String("i")),
              NULL
            )
            ),
            NULL, // end of A_VarDeclList
            A_StmList(
              A_WhileStm(A_Pos(11,9),
                A_OpExp(A_Pos(11,25), A_LengthExp(A_Pos(11,16), A_IdExp(A_Pos(11,23), String("a"))), A_greater, A_IdExp(A_Pos(11,26), String("i"))),
                A_NestedStm(A_Pos(11,29),
                  A_StmList(
                    A_IfStm(A_Pos(12,13),
                      A_OpExp(A_Pos(12,21), A_ArrayExp(A_Pos(12,0), A_IdExp(A_Pos(12,17), String("a")), A_IdExp(A_Pos(12,19), String("i"))), A_greater, A_IdExp(A_Pos(12,22), String("max"))),
                      A_AssignStm(A_Pos(12,35),
                        A_ClassVarExp(A_Pos(12,27), A_ThisExp(A_Pos(12,27)), String("max")),
                        A_ArrayExp(A_Pos(12,0), A_IdExp(A_Pos(12,36), String("a")), A_IdExp(A_Pos(12,38), String("i")))
                      ),
                      NULL
                    ),
                    A_StmList(
                      A_AssignStm(A_Pos(13,14),
                        A_IdExp(A_Pos(13,13), String("i")),
                        A_OpExp(A_Pos(13,16), A_IdExp(A_Pos(13,15), String("i")), A_plus, A_NumConst(A_Pos(13,17), 1))
                      ),
                      NULL
                    )
                  )
                )
              ),
              A_StmList(
                A_Return(A_Pos(15,9),
                  A_ClassVarExp(A_Pos(15,16), A_ThisExp(A_Pos(15,16)), String("max"))
                ),
                NULL
              )
            )
          ), // end of MethodDecl for m1
          NULL
        ) // end of A_MethodDeclList
      ), // end of ClassDecl for c1 
      NULL
    ) // end of A_ClassDeclList
  ); // end of Prog
}
