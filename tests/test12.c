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
              A_Type(A_Pos(4,5), A_idType, String("c1")),
              String("cv"),
              NULL
            ), // end of VarDecl for cv 
            A_VarDeclList(
              A_VarDecl(A_Pos(5,5),
                A_Type(A_Pos(5,5), A_intType, NULL),
                String("ix"),
                NULL
              ), // end of VarDecl for ix 
              A_VarDeclList(
                A_VarDecl(A_Pos(6,5),
                  A_Type(A_Pos(6,5), A_intType, NULL),
                  String("iy"),
                  A_ExpList(
                    A_NumConst(A_Pos(6,5), 1000),
                    NULL
                  )
                ), // end of VarDecl for iy 
                NULL
              )
            )
          )
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_AssignStm(A_Pos(8,6),
          A_IdExp(A_Pos(8,5), String("a")),
          A_NewIntArrExp(A_Pos(8,7), A_OpExp(A_Pos(8,17), A_NumConst(A_Pos(8,15), 10), A_plus, A_NumConst(A_Pos(8,18), 2)))
        ),
        A_StmList(
          A_AssignStm(A_Pos(9,9),
            A_ArrayExp(A_Pos(8,0), A_IdExp(A_Pos(9,5), String("a")), A_NumConst(A_Pos(9,7), 2)),
            A_NumConst(A_Pos(9,10), 80)
          ),
          A_StmList(
            A_IfStm(A_Pos(10,5),
              A_OpExp(A_Pos(10,13), A_ArrayExp(A_Pos(10,0), A_IdExp(A_Pos(10,9), String("a")), A_NumConst(A_Pos(10,11), 0)), A_less, A_NumConst(A_Pos(10,14), 1)),
              A_CallStm(A_Pos(11,18),
                A_NewObjExp(A_Pos(11,9), String("c1")), String("m1"), NULL
              ),
              NULL
            ),
            A_StmList(
              A_Return(A_Pos(12,5),
                A_ArrayExp(A_Pos(12,0), A_IdExp(A_Pos(12,12), String("a")), A_NumConst(A_Pos(12,14), 9))
              ),
              NULL
            )
          )
        )
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(15,1),
        String("c1"),
        NULL,
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(16,5),
            A_Type(A_Pos(16,5), A_intArrType, NULL),
            String("i1"),
            A_ExpList(
              A_NumConst(A_Pos(16,5), 2),
              A_ExpList(
                A_NumConst(A_Pos(16,5), 3),
                NULL
              )
            )
          ), // end of VarDecl for i1 
          NULL
        ), // end of A_VarDeclList
        A_MethodDeclList( // begin of A_MethodDeclList
          A_MethodDecl(A_Pos(18,5), // begin of MethodDecl for m1
            A_Type(A_Pos(18,12), A_intType, NULL),
            String("m1"),
            A_FormalList(
              A_Formal(A_Pos(18,19), A_Type(A_Pos(18,19), A_intType, NULL), String("x")),
              NULL
            ),
            NULL, // end of A_VarDeclList
            A_StmList(
              A_AssignStm(A_Pos(19,14),
                A_ArrayExp(A_Pos(18,0), A_IdExp(A_Pos(19,9), String("i1")), A_NumConst(A_Pos(19,12), 1)),
                A_IdExp(A_Pos(19,15), String("x"))
              ),
              A_StmList(
                A_WhileStm(A_Pos(20,9),
                  A_OpExp(A_Pos(20,20), A_ArrayExp(A_Pos(20,0), A_IdExp(A_Pos(20,16), String("a")), A_NumConst(A_Pos(20,18), 0)), A_less, A_NumConst(A_Pos(20,21), 1)),
                  A_NestedStm(A_Pos(20,24),
                    A_StmList(
                      A_CallStm(A_Pos(21,22),
                        A_NewObjExp(A_Pos(21,13), String("c1")), String("m1"), NULL
                      ),
                      NULL
                    )
                  )
                ),
                A_StmList(
                  A_Return(A_Pos(23,9),
                    A_ArrayExp(A_Pos(23,16), A_ClassVarExp(A_Pos(23,16), A_ThisExp(A_Pos(23,16)), String("i1")), A_NumConst(A_Pos(23,24), 0))
                  ),
                  NULL
                )
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
