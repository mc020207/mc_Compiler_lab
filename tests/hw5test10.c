#include <stdlib.h>
#include "fdmjast.h"
A_prog prog1() {
return
  A_Prog(A_Pos(1,1),
    A_MainMethod(A_Pos(1,1), // begin of main class
      A_VarDeclList( // begin of A_VarDeclList
        A_VarDecl(A_Pos(2,5),
          A_Type(A_Pos(2,5), A_intArrType, NULL),
          String("a"),
          NULL
        ), // end of VarDecl for a 
        A_VarDeclList(
          A_VarDecl(A_Pos(3,5),
            A_Type(A_Pos(3,5), A_intArrType, NULL),
            String("aa"),
            A_ExpList(
              A_NumConst(A_Pos(3,5), 3),
              A_ExpList(
                A_NumConst(A_Pos(3,5), 4),
                A_ExpList(
                  A_NumConst(A_Pos(3,5), 5),
                  NULL
                )
              )
            )
          ), // end of VarDecl for aa 
          A_VarDeclList(
            A_VarDecl(A_Pos(4,5),
              A_Type(A_Pos(4,5), A_intType, NULL),
              String("ix"),
              NULL
            ), // end of VarDecl for ix 
            A_VarDeclList(
              A_VarDecl(A_Pos(5,5),
                A_Type(A_Pos(5,5), A_intType, NULL),
                String("iy"),
                A_ExpList(
                  A_NumConst(A_Pos(5,5), 1000),
                  NULL
                )
              ), // end of VarDecl for iy 
              NULL
            )
          )
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_ArrayInit(A_Pos(7,8),
          A_IdExp(A_Pos(7,5), String("a")),
          A_ExpList(
            A_NumConst(A_Pos(7,10), 1),
            A_ExpList(
              A_NumConst(A_Pos(7,12), 2),
              A_ExpList(
                A_NumConst(A_Pos(7,14), 3),
                A_ExpList(
                  A_NumConst(A_Pos(7,16), 4),
                  A_ExpList(
                    A_NumConst(A_Pos(7,18), 5),
                    A_ExpList(
                      A_NumConst(A_Pos(7,20), 6),
                      A_ExpList(
                        A_NumConst(A_Pos(7,22), 7),
                        A_ExpList(
                          A_NumConst(A_Pos(7,24), 8),
                          A_ExpList(
                            A_NumConst(A_Pos(7,26), 9),
                            A_ExpList(
                              A_NumConst(A_Pos(7,28), 10),
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
        ),
        A_StmList(
          A_AssignStm(A_Pos(8,9),
            A_ArrayExp(A_Pos(7,1), A_IdExp(A_Pos(8,5), String("a")), A_NumConst(A_Pos(8,7), 2)),
            A_NumConst(A_Pos(8,10), 80)
          ),
          A_StmList(
            A_IfStm(A_Pos(9,5),
              A_OpExp(A_Pos(9,38), A_ArrayExp(A_Pos(9,1), A_IdExp(A_Pos(9,9), String("a")), A_ArrayExp(A_Pos(9,11), A_NewIntArrExp(A_Pos(9,11), A_NumConst(A_Pos(9,19), 10)), A_ArrayExp(A_Pos(9,23), A_NewIntArrExp(A_Pos(9,23), A_NumConst(A_Pos(9,31), 9)), A_NumConst(A_Pos(9,34), 0)))), A_less, A_NumConst(A_Pos(9,39), 1)),
              A_AssignStm(A_Pos(10,11),
                A_IdExp(A_Pos(10,9), String("aa")),
                A_NewIntArrExp(A_Pos(10,12), A_BoolConst(A_Pos(10,20), TRUE))
              ),
              NULL
            ),
            A_StmList(
              A_Return(A_Pos(11,5),
                A_ArrayExp(A_Pos(11,1), A_IdExp(A_Pos(11,12), String("ix")), A_OpExp(A_Pos(11,16), A_NumConst(A_Pos(11,15), 9), A_greater, A_NumConst(A_Pos(11,17), 10)))
              ),
              NULL
            )
          )
        )
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
