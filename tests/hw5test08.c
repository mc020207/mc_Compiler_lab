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
            A_NumConst(A_Pos(2,5), 0),
            NULL
          )
        ), // end of VarDecl for i 
        A_VarDeclList(
          A_VarDecl(A_Pos(3,5),
            A_Type(A_Pos(3,5), A_intArrType, NULL),
            String("a"),
            NULL
          ), // end of VarDecl for a 
          NULL
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_Starttime(A_Pos(5,5)),
        A_StmList(
          A_AssignStm(A_Pos(6,6),
            A_IdExp(A_Pos(6,5), String("a")),
            A_NewIntArrExp(A_Pos(6,7), A_NumConst(A_Pos(6,15), 8))
          ),
          A_StmList(
            A_WhileStm(A_Pos(7,5),
              A_NotExp(A_Pos(7,12),
                A_EscExp(A_Pos(7,13), 
                  A_StmList(
                    A_AssignStm(A_Pos(7,19),
                      A_ArrayExp(A_Pos(7,1), A_IdExp(A_Pos(7,15), String("a")), A_IdExp(A_Pos(7,17), String("i"))),
                      A_IdExp(A_Pos(7,20), String("i"))
                    ),
                    A_StmList(
                      A_AssignStm(A_Pos(7,24),
                        A_IdExp(A_Pos(7,23), String("i")),
                        A_OpExp(A_Pos(7,26), A_IdExp(A_Pos(7,25), String("i")), A_plus, A_NumConst(A_Pos(7,27), 1))
                      ),
                      NULL
                    )
                  ),
                  A_OpExp(A_Pos(7,32), A_IdExp(A_Pos(7,31), String("i")), A_less, A_NumConst(A_Pos(7,33), 8))
                )),
              A_IfStm(A_Pos(8,7),
                A_OpExp(A_Pos(8,12), A_IdExp(A_Pos(8,11), String("i")), A_ge, A_NumConst(A_Pos(8,14), 8)),
                A_Break(A_Pos(8,17)),
                NULL
              )
            ),
            A_StmList(
              A_Putarray(A_Pos(9,5), 
                A_IdExp(A_Pos(9,14), String("i")),
                A_NewIntArrExp(A_Pos(9,17), A_NumConst(A_Pos(9,25), 10))
              ),
              A_StmList(
                A_WhileStm(A_Pos(10,5),
                  A_OpExp(A_Pos(10,16), A_BoolConst(A_Pos(10,12), TRUE), A_eq, A_NumConst(A_Pos(10,18), 1)),
                  A_NestedStm(A_Pos(10,21),
                    A_StmList(
                      A_AssignStm(A_Pos(11,8),
                        A_IdExp(A_Pos(11,7), String("i")),
                        A_Getint(A_Pos(11,9))
                      ),
                      A_StmList(
                        A_IfStm(A_Pos(12,7),
                          A_IdExp(A_Pos(12,11), String("i")),
                          A_Break(A_Pos(12,14)),
                          NULL
                        ),
                        A_StmList(
                          A_IfStm(A_Pos(13,7),
                            A_NotExp(A_Pos(13,11),
                              A_IdExp(A_Pos(13,12), String("i"))),
                            A_Break(A_Pos(13,15)),
                            NULL
                          ),
                          NULL
                        )
                      )
                    )
                  )
                ),
                A_StmList(
                  A_Stoptime(A_Pos(15,5)),
                  A_StmList(
                    A_Return(A_Pos(16,5),
                      A_IdExp(A_Pos(16,12), String("a"))
                    ),
                    NULL
                  )
                )
              )
            )
          )
        )
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
