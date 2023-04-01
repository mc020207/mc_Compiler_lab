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
          A_VarDeclList(
            A_VarDecl(A_Pos(4,5),
              A_Type(A_Pos(4,5), A_idType, String("c1")),
              String("o1"),
              NULL
            ), // end of VarDecl for o1 
            A_VarDeclList(
              A_VarDecl(A_Pos(5,5),
                A_Type(A_Pos(5,5), A_idType, String("c2")),
                String("o2"),
                NULL
              ), // end of VarDecl for o2 
              A_VarDeclList(
                A_VarDecl(A_Pos(6,5),
                  A_Type(A_Pos(6,5), A_idType, String("c3")),
                  String("o3"),
                  NULL
                ), // end of VarDecl for o3 
                A_VarDeclList(
                  A_VarDecl(A_Pos(7,5),
                    A_Type(A_Pos(7,5), A_idType, String("c4")),
                    String("o4"),
                    NULL
                  ), // end of VarDecl for o4 
                  NULL
                )
              )
            )
          )
        )
      ), // end of A_VarDeclList
      A_StmList(
        A_Starttime(A_Pos(9,5)),
        A_StmList(
          A_AssignStm(A_Pos(10,6),
            A_IdExp(A_Pos(10,5), String("a")),
            A_NewIntArrExp(A_Pos(10,7), A_NumConst(A_Pos(10,15), 8))
          ),
          A_StmList(
            A_WhileStm(A_Pos(11,5),
              A_NotExp(A_Pos(11,12),
                A_EscExp(A_Pos(11,13), 
                  A_StmList(
                    A_AssignStm(A_Pos(11,19),
                      A_ArrayExp(A_Pos(11,0), A_IdExp(A_Pos(11,15), String("a")), A_IdExp(A_Pos(11,17), String("i"))),
                      A_IdExp(A_Pos(11,20), String("i"))
                    ),
                    A_StmList(
                      A_AssignStm(A_Pos(11,24),
                        A_IdExp(A_Pos(11,23), String("i")),
                        A_OpExp(A_Pos(11,26), A_IdExp(A_Pos(11,25), String("i")), A_plus, A_NumConst(A_Pos(11,27), 1))
                      ),
                      NULL
                    )
                  ),
                  A_NumConst(A_Pos(11,31), 0)
                )),
              A_IfStm(A_Pos(12,7),
                A_OpExp(A_Pos(12,12), A_IdExp(A_Pos(12,11), String("i")), A_ge, A_NumConst(A_Pos(12,14), 8)),
                A_Break(A_Pos(12,17)),
                NULL
              )
            ),
            A_StmList(
              A_Putarray(A_Pos(13,5), 
                A_NumConst(A_Pos(13,14), 8),
                A_IdExp(A_Pos(13,16), String("a"))
              ),
              A_StmList(
                A_WhileStm(A_Pos(14,5),
                  A_BoolConst(A_Pos(14,12), TRUE),
                  A_NestedStm(A_Pos(14,18),
                    A_StmList(
                      A_AssignStm(A_Pos(15,8),
                        A_IdExp(A_Pos(15,7), String("i")),
                        A_Getint(A_Pos(15,9))
                      ),
                      A_StmList(
                        A_IfStm(A_Pos(16,7),
                          A_IdExp(A_Pos(16,11), String("i")),
                          A_Break(A_Pos(16,14)),
                          NULL
                        ),
                        A_StmList(
                          A_IfStm(A_Pos(17,7),
                            A_NotExp(A_Pos(17,11),
                              A_IdExp(A_Pos(17,12), String("i"))),
                            A_Break(A_Pos(17,15)),
                            NULL
                          ),
                          NULL
                        )
                      )
                    )
                  )
                ),
                A_StmList(
                  A_Stoptime(A_Pos(19,5)),
                  A_StmList(
                    A_AssignStm(A_Pos(21,7),
                      A_IdExp(A_Pos(21,5), String("o1")),
                      A_NewObjExp(A_Pos(21,8), String("c4"))
                    ),
                    A_StmList(
                      A_AssignStm(A_Pos(22,7),
                        A_IdExp(A_Pos(22,5), String("o2")),
                        A_NewObjExp(A_Pos(22,8), String("c4"))
                      ),
                      A_StmList(
                        A_AssignStm(A_Pos(23,7),
                          A_IdExp(A_Pos(23,5), String("o3")),
                          A_NewObjExp(A_Pos(23,8), String("c4"))
                        ),
                        A_StmList(
                          A_AssignStm(A_Pos(24,7),
                            A_IdExp(A_Pos(24,5), String("o4")),
                            A_NewObjExp(A_Pos(24,8), String("c4"))
                          ),
                          A_StmList(
                            A_AssignStm(A_Pos(26,10),
                              A_ClassVarExp(A_Pos(24,0), A_IdExp(A_Pos(26,5), String("o1")), String("x1")),
                              A_NumConst(A_Pos(26,11), 1)
                            ),
                            A_StmList(
                              A_AssignStm(A_Pos(27,10),
                                A_ClassVarExp(A_Pos(26,0), A_IdExp(A_Pos(27,5), String("o2")), String("x1")),
                                A_NumConst(A_Pos(27,11), 2)
                              ),
                              A_StmList(
                                A_AssignStm(A_Pos(28,10),
                                  A_ClassVarExp(A_Pos(27,0), A_IdExp(A_Pos(28,5), String("o3")), String("x1")),
                                  A_NumConst(A_Pos(28,11), 3)
                                ),
                                A_StmList(
                                  A_AssignStm(A_Pos(29,10),
                                    A_ClassVarExp(A_Pos(28,0), A_IdExp(A_Pos(29,5), String("o4")), String("x1")),
                                    A_NumConst(A_Pos(29,11), 4)
                                  ),
                                  A_StmList(
                                    A_AssignStm(A_Pos(31,10),
                                      A_ClassVarExp(A_Pos(29,0), A_IdExp(A_Pos(31,5), String("o1")), String("x4")),
                                      A_NumConst(A_Pos(31,11), 1)
                                    ),
                                    A_StmList(
                                      A_AssignStm(A_Pos(32,10),
                                        A_ClassVarExp(A_Pos(31,0), A_IdExp(A_Pos(32,5), String("o2")), String("x4")),
                                        A_NumConst(A_Pos(32,11), 2)
                                      ),
                                      A_StmList(
                                        A_AssignStm(A_Pos(33,10),
                                          A_ClassVarExp(A_Pos(32,0), A_IdExp(A_Pos(33,5), String("o3")), String("x4")),
                                          A_NumConst(A_Pos(33,11), 3)
                                        ),
                                        A_StmList(
                                          A_AssignStm(A_Pos(34,10),
                                            A_ClassVarExp(A_Pos(33,0), A_IdExp(A_Pos(34,5), String("o4")), String("x4")),
                                            A_NumConst(A_Pos(34,11), 4)
                                          ),
                                          A_StmList(
                                            A_Return(A_Pos(35,5),
                                              A_ArrayExp(A_Pos(35,0), A_IdExp(A_Pos(35,12), String("a")), A_NumConst(A_Pos(35,14), 7))
                                            ),
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
                      )
                    )
                  )
                )
              )
            )
          )
        )
      )
    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(38,1),
        String("c4"),
        String("c3"),
        A_VarDeclList( // begin of A_VarDeclList
          A_VarDecl(A_Pos(39,5),
            A_Type(A_Pos(39,5), A_intType, NULL),
            String("x4"),
            NULL
          ), // end of VarDecl for x4 
          NULL
        ), // end of A_VarDeclList
        NULL // end of A_MethodDeclList
      ), // end of ClassDecl for c4 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(42,1),
          String("c3"),
          NULL,
          A_VarDeclList( // begin of A_VarDeclList
            A_VarDecl(A_Pos(43,5),
              A_Type(A_Pos(43,5), A_intType, NULL),
              String("x3"),
              NULL
            ), // end of VarDecl for x3 
            NULL
          ), // end of A_VarDeclList
          NULL // end of A_MethodDeclList
        ), // end of ClassDecl for c3 
        A_ClassDeclList(
          A_ClassDecl(A_Pos(46,1),
            String("c2"),
            String("c1"),
            A_VarDeclList( // begin of A_VarDeclList
              A_VarDecl(A_Pos(47,5),
                A_Type(A_Pos(47,5), A_intType, NULL),
                String("x2"),
                NULL
              ), // end of VarDecl for x2 
              NULL
            ), // end of A_VarDeclList
            NULL // end of A_MethodDeclList
          ), // end of ClassDecl for c2 
          A_ClassDeclList(
            A_ClassDecl(A_Pos(50,1),
              String("c1"),
              NULL,
              A_VarDeclList( // begin of A_VarDeclList
                A_VarDecl(A_Pos(51,5),
                  A_Type(A_Pos(51,5), A_intType, NULL),
                  String("x1"),
                  NULL
                ), // end of VarDecl for x1 
                NULL
              ), // end of A_VarDeclList
              NULL // end of A_MethodDeclList
            ), // end of ClassDecl for c1 
            NULL
          )
        )
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
