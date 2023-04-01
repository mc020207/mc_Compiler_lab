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
        A_AssignStm(A_Pos(5,6),
          A_IdExp(A_Pos(5,5), String("a")),
          A_NewIntArrExp(A_Pos(5,7), A_NumConst(A_Pos(5,15), 8))
        ),
        A_StmList(
          A_WhileStm(A_Pos(6,5),
            A_OpExp(A_Pos(6,32), A_EscExp(A_Pos(6,12), 
                A_StmList(
                  A_AssignStm(A_Pos(6,18),
                    A_ArrayExp(A_Pos(6,0), A_IdExp(A_Pos(6,14), String("a")), A_IdExp(A_Pos(6,16), String("i"))),
                    A_IdExp(A_Pos(6,19), String("i"))
                  ),
                  A_StmList(
                    A_AssignStm(A_Pos(6,23),
                      A_IdExp(A_Pos(6,22), String("i")),
                      A_OpExp(A_Pos(6,25), A_IdExp(A_Pos(6,24), String("i")), A_plus, A_NumConst(A_Pos(6,26), 1))
                    ),
                    NULL
                  )
                ),
                A_IdExp(A_Pos(6,30), String("i"))
              ), A_less, A_NumConst(A_Pos(6,33), 8)),
            NULL
          ),
          A_StmList(
            A_Putarray(A_Pos(7,5), 
              A_NumConst(A_Pos(7,14), 8),
              A_IdExp(A_Pos(7,16), String("a"))
            ),
            A_StmList(
              A_Return(A_Pos(8,5),
                A_CallExp(A_Pos(8,12),
                  A_NewObjExp(A_Pos(8,12), String("c1")), String("m"), A_ExpList(
                    A_NumConst(A_Pos(8,23), 0),
                    NULL
                  )
                )
              ),
              NULL
            )
          )
        )
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(11,1),
        String("c0"),
        NULL,
        NULL, // end of A_VarDeclList
        NULL // end of A_MethodDeclList
      ), // end of ClassDecl for c0 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(12,1),
          String("c1"),
          String("c0"),
          NULL, // end of A_VarDeclList
          A_MethodDeclList( // begin of A_MethodDeclList
            A_MethodDecl(A_Pos(13,5), // begin of MethodDecl for m
              A_Type(A_Pos(13,12), A_idType, String("c0")),
              String("m"),
              A_FormalList(
                A_Formal(A_Pos(13,23), A_Type(A_Pos(13,23), A_intType, NULL), String("x")),
                NULL
              ),
              NULL, // end of A_VarDeclList
              A_StmList(
                A_Return(A_Pos(14,8),
                  A_NewObjExp(A_Pos(14,15), String("c1"))
                ),
                NULL
              )
            ), // end of MethodDecl for m
            NULL
          ) // end of A_MethodDeclList
        ), // end of ClassDecl for c1 
        NULL
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
