#include <stdio.h>
#include "util.h"
#include "table.h"
#include "graph.h"
#include "symbol.h"
#include "temp.h"
#include "assem.h"
#include "flowgraph.h"
#include "liveness.h"

//structure for in and out temps to attach to the flowgraph nodes
struct inOut_ {
    Temp_tempList in;
    Temp_tempList out;
};
typedef struct inOut_ *inOut;

//This is the (global) table for storing the in and out temps
static G_table InOutTable = NULL;

//initialize the table
static void init_INOUT() {
    if (InOutTable==NULL) {
        InOutTable = G_empty();
    }
}

//Attach the inOut info to the table
static void INOUT_enter(G_node n, inOut info) {
    G_enter(InOutTable, n, info);
}

//Lookup the inOut info
static inOut INOUT_lookup(G_node n) {
    return G_look(InOutTable, n);
}

//inOut Constructor
static inOut InOut(Temp_tempList in, Temp_tempList out) {
    inOut info = (inOut)checked_malloc(sizeof(inOut));
    info->in = in;
    info->out = out;
    return info;
}

//for printing purpose
void PrintTemp(FILE *out, Temp_temp t) {
    fprintf(out, " %s ", Temp_look(Temp_name(), t));
}

//Printing
void PrintTemps(FILE *out, Temp_tempList tl) {
    if (tl==NULL) return;
    Temp_temp h=tl->head;
    fprintf(out, "%s, ", Temp_look(Temp_name(), h));
    PrintTemps(out, tl->tail);
}


//add one to another list (if not already there)
 static Temp_tempList TempList_add(Temp_tempList tl, Temp_temp t) {
    for (Temp_tempList l1=tl; l1!=NULL; l1=l1->tail) {
        if (l1->head == t) return tl; //nothing to add
    }
    return(Temp_TempList(t, tl)); //else add to the head
}

//do a simple union (add each one at a time)
static Temp_tempList TempList_union(Temp_tempList tl1, Temp_tempList tl2) {
    for (; tl2!=NULL; tl2=tl2->tail)
        tl1=TempList_add(tl1, tl2->head);
    return(tl1);
}

//Implement a list difference tl1-tl2 (for each on in tl1, scan tl2)
static Temp_tempList TempList_diff(Temp_tempList tl1, Temp_tempList tl2)  {
    bool found;
    
    Temp_tempList scan = tl1;
    Temp_tempList result=NULL;
    while (scan!=NULL ) {
        found=FALSE;
        for (Temp_tempList l2=tl2; l2!=NULL; l2=l2->tail)
            if (scan->head==l2->head) found=TRUE;
        if (!found) { //if not found in tl2, then add to the result list
                result = Temp_TempList(scan->head, result);
        }
        scan=scan->tail;
    }
    return(result);
}

//a simple eq test using diff twice
static bool TempList_eq(Temp_tempList tl1, Temp_tempList tl2) {
    if (TempList_diff(tl1, tl2) != NULL)
        return FALSE;
    else {
        if (TempList_diff(tl2, tl1) != NULL)
            return FALSE;
        else
            return TRUE;
    }
}

Temp_tempList FG_In(G_node n) {
    inOut io;
    io=INOUT_lookup(n);
    if (io!=NULL) return io->in;
    else return NULL;
}

Temp_tempList FG_Out(G_node n) {
    inOut io;
    io=INOUT_lookup(n);
    if (io!=NULL) return io->out;
    else return NULL;
}

//initialize the INOUT info for a graph
static void init_INOUT_graph(G_nodeList l) {
    while ( l!=NULL ) {
        if (INOUT_lookup(l->head) == NULL) //If there is no io info yet, initialize one
            INOUT_enter(l->head, InOut(NULL, NULL));
        l=l->tail;
    }
}

static int gi=0;

static bool LivenessIteration(G_nodeList gl) {
    bool changed = FALSE;
    gi++;
    while ( gl!=NULL ) {
        G_node n=gl->head;

        //do in[n] = use[n] union (out[n] - def[n])
        Temp_tempList in=TempList_union(FG_use(n), TempList_diff(FG_Out(n), FG_def(n)));
    
        //Now do out[n]=union_s in succ[n] (in[s])
        G_nodeList s=G_succ(n);
        Temp_tempList out=NULL; //out is an accumulator
        for (;s!=NULL;s=s->tail) {
            out=TempList_union(out, FG_In(s->head));
        }
        //See if any in/out changed
        if (!(TempList_eq(FG_In(n), in) && TempList_eq(FG_Out(n), out)))
            changed=TRUE;
        //enter the new info
        G_enter(InOutTable, gl->head, InOut(in, out));
        gl=gl->tail;
    }
    return changed;
}

void Show_Liveness(FILE* out, G_nodeList l) {
    fprintf(out, "\n\nNumber of iterations=%d\n\n", gi);
    while ( l!=NULL ) {
        G_node n = l->head;
        fprintf(out, "----------------------\n");
        G_show(out, G_NodeList(n, NULL), NULL);
        fprintf(out, "def="); PrintTemps(out, FG_def(n)); fprintf(out, "\n");
        fprintf(out, "use="); PrintTemps(out, FG_use(n)); fprintf(out, "\n");
        fprintf(out, "In=");  PrintTemps(out, FG_In(n)); fprintf(out, "\n");
        fprintf(out, "Out="); PrintTemps(out, FG_Out(n)); fprintf(out, "\n");
        l=l->tail;
    }
}

G_nodeList Liveness(G_nodeList l) {
    init_INOUT(); //Initialize InOut table
    bool changed=TRUE;
    while (changed) changed=LivenessIteration(l);
    return l;
}
