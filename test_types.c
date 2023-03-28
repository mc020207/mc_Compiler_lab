#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "util.h"
#include "symbol.h"
#include "types.h"

int main() {

    int i;
    //test the use of table for bindings of Symbol and Temp
    
    S_table t=S_empty(); //creating a symbold table

    char s[3];

    for (i=0; i<5; i++) {
        sprintf(s, "x%1d", i);
        S_symbol foo = S_Symbol(s); //create symbole for "x[0-9]"
        S_enter(t, foo, Ty_Int());//bind it to an int type
    }

    for (i=5; i<10; i++) {
        sprintf(s, "x%1d", i);
        S_symbol foo = S_Symbol(s); //create symbole for "x[0-9]"
        S_enter(t, foo, Ty_String());//bind it to a string type
    }

    //CHECK: how about xi, randomly?
    srand((unsigned)time(NULL));
    i=rand()%10;
    sprintf(s, "x%1d", i);
    Ty_ty ty = S_look(t, S_Symbol(s));
    if (ty != NULL) {
        printf("Random check: x%1d binds with ", i);
	Ty_print(ty);
        printf("\n");
    }
}
