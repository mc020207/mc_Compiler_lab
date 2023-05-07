#include <stdlib.h>
#include "../fdmjast.h"
#include "../prog1.h"
A_prog prog1() {
return
  A_Prog(A_Pos(2,1),
    A_MainMethod(A_Pos(2,1), // begin of main class
      NULL, // end of A_VarDeclList
      NULL

    ), // end of main class
    A_ClassDeclList( // begin of A_ClassDeclList
      A_ClassDecl(A_Pos(5,1),
        String("a"),
        String("b"),
        NULL, // end of A_VarDeclList
        NULL // end of A_MethodDeclList
      ), // end of ClassDecl for a 
      A_ClassDeclList(
        A_ClassDecl(A_Pos(8,1),
          String("b"),
          String("c"),
          NULL, // end of A_VarDeclList
          NULL // end of A_MethodDeclList
        ), // end of ClassDecl for b 
        A_ClassDeclList(
          A_ClassDecl(A_Pos(11,1),
            String("d"),
            String("e"),
            NULL, // end of A_VarDeclList
            NULL // end of A_MethodDeclList
          ), // end of ClassDecl for d 
          A_ClassDeclList(
            A_ClassDecl(A_Pos(14,1),
              String("c"),
              String("d"),
              NULL, // end of A_VarDeclList
              NULL // end of A_MethodDeclList
            ), // end of ClassDecl for c 
            A_ClassDeclList(
              A_ClassDecl(A_Pos(17,1),
                String("e"),
                String("f"),
                NULL, // end of A_VarDeclList
                NULL // end of A_MethodDeclList
              ), // end of ClassDecl for e 
              A_ClassDeclList(
                A_ClassDecl(A_Pos(20,1),
                  String("f"),
                  String("h"),
                  NULL, // end of A_VarDeclList
                  NULL // end of A_MethodDeclList
                ), // end of ClassDecl for f 
                A_ClassDeclList(
                  A_ClassDecl(A_Pos(23,1),
                    String("g"),
                    String("f"),
                    NULL, // end of A_VarDeclList
                    NULL // end of A_MethodDeclList
                  ), // end of ClassDecl for g 
                  A_ClassDeclList(
                    A_ClassDecl(A_Pos(26,1),
                      String("h"),
                      String("i"),
                      NULL, // end of A_VarDeclList
                      NULL // end of A_MethodDeclList
                    ), // end of ClassDecl for h 
                    A_ClassDeclList(
                      A_ClassDecl(A_Pos(29,1),
                        String("i"),
                        String("a"),
                        NULL, // end of A_VarDeclList
                        NULL // end of A_MethodDeclList
                      ), // end of ClassDecl for i 
                      NULL
                    )
                  )
                )
              )
            )
          )
        )
      )
    ) // end of A_ClassDeclList
  ); // end of Prog
}
