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
            A_Type(A_Pos(3,5), A_intType, NULL),
            String("a"),
            A_ExpList(
              A_NumConst(A_Pos(3,5), 1),
              NULL
            )
          ), // end of VarDecl for a 
          NULL
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_IfStm(A_Pos(5,5),
          A_OpExp(A_Pos(5,12), A_OpExp(A_Pos(5,10), A_IdExp(A_Pos(5,9), String("i")), A_less, A_NumConst(A_Pos(5,11), 0)), A_or, A_OpExp(A_Pos(5,24), A_EscExp(A_Pos(5,14), 
                A_StmList(
                  A_AssignStm(A_Pos(5,17),
                    A_IdExp(A_Pos(5,16), String("i")),
                    A_NumConst(A_Pos(5,18), 1)
                  ),
                  NULL
                ),
                A_IdExp(A_Pos(5,22), String("a"))
              ), A_greater, A_NumConst(A_Pos(5,25), 1))),
          A_NestedStm(A_Pos(5,28),
            A_StmList(
              A_Putint(A_Pos(6,8),
                A_IdExp(A_Pos(6,15), String("i"))),
              NULL
            )
          ),
          A_NestedStm(A_Pos(7,12),
            A_StmList(
              A_IfStm(A_Pos(8,8),
                A_OpExp(A_Pos(8,17), A_OpExp(A_Pos(8,13), A_IdExp(A_Pos(8,12), String("i")), A_eq, A_NumConst(A_Pos(8,15), 0)), A_and, A_OpExp(A_Pos(8,21), A_IdExp(A_Pos(8,20), String("a")), A_eq, A_NumConst(A_Pos(8,23), 1))),
                A_Putint(A_Pos(9,11),
                  A_IdExp(A_Pos(9,18), String("a"))),
                NULL
              ),
              A_StmList(
                A_WhileStm(A_Pos(10,8),
                  A_OpExp(A_Pos(10,16), A_IdExp(A_Pos(10,15), String("i")), A_eq, A_NumConst(A_Pos(10,18), 0)),
                  A_NestedStm(A_Pos(10,21),
                    A_StmList(
                      A_AssignStm(A_Pos(11,12),
                        A_IdExp(A_Pos(11,11), String("i")),
                        A_NotExp(A_Pos(11,13),
                          A_OpExp(A_Pos(11,16), A_IdExp(A_Pos(11,15), String("a")), A_greater, A_NumConst(A_Pos(11,17), 0)))
                      ),
                      A_StmList(
                        A_Break(A_Pos(12,11)),
                        NULL
                      )
                    )
                  )
                ),
                NULL
              )
            )
          )
        ),
        A_StmList(
          A_Return(A_Pos(15,5),
            A_IdExp(A_Pos(15,12), String("a"))
          ),
          NULL
        )
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
