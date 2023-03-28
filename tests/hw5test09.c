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
          A_ExpList(
            A_NumConst(A_Pos(2,5), 1),
            A_ExpList(
              A_NumConst(A_Pos(2,5), 2),
              A_ExpList(
                A_NumConst(A_Pos(2,5), 3),
                NULL
              )
            )
          )
        ), // end of VarDecl for a 
        A_VarDeclList(
          A_VarDecl(A_Pos(3,5),
            A_Type(A_Pos(3,5), A_intType, NULL),
            String("i"),
            A_ExpList(
              A_NumConst(A_Pos(3,5), 3),
              NULL
            )
          ), // end of VarDecl for i 
          A_VarDeclList(
            A_VarDecl(A_Pos(4,5),
              A_Type(A_Pos(4,5), A_intType, NULL),
              String("a"),
              A_ExpList(
                A_NumConst(A_Pos(4,5), 1),
                NULL
              )
            ), // end of VarDecl for a 
            NULL
          )
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_ArrayInit(A_Pos(5,8),
          A_IdExp(A_Pos(5,5), String("a")),
          A_ExpList(
            A_NumConst(A_Pos(5,10), 9),
            A_ExpList(
              A_NumConst(A_Pos(5,12), 8),
              A_ExpList(
                A_NumConst(A_Pos(5,14), 7),
                A_ExpList(
                  A_NumConst(A_Pos(5,16), 6),
                  A_ExpList(
                    A_NumConst(A_Pos(5,18), 5),
                    A_ExpList(
                      A_NumConst(A_Pos(5,20), 4),
                      A_ExpList(
                        A_NumConst(A_Pos(5,22), 3),
                        A_ExpList(
                          A_NumConst(A_Pos(5,24), 2),
                          A_ExpList(
                            A_NumConst(A_Pos(5,26), 1),
                            A_ExpList(
                              A_NumConst(A_Pos(5,28), 0),
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
          A_Return(A_Pos(6,5),
            A_IdExp(A_Pos(6,12), String("i"))
          ),
          NULL
        )
      )
    ), // end of main class
    NULL // end of A_ClassDeclList
  ); // end of Prog
}
