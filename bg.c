#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "table.h"
#include "graph.h"
#include "symbol.h"
#include "temp.h"
#include "assem.h"
#include "bg.h"

/* graph on AS_ basic blocks. This is useful to find dominance 
   relations, etc. */

static G_graph RA_bg;
static S_table block_env;

static void Bg_empty() {
    RA_bg=G_Graph();
}

G_graph Bg_graph() {
    return RA_bg;
}

static G_node Look_bg(AS_block b) {
    G_node n1=NULL;
    for (G_nodeList n=G_nodes(RA_bg); n!=NULL; n=n->tail) {
        if ((AS_block)G_nodeInfo(n->head) == b) {
            n1=n->head;
            break;
        }
    }
    if (n1==NULL) return(G_Node(RA_bg, b));
    else return n1;
}

static void Enter_bg(AS_block b1, AS_block b2) {
    G_node n1=Look_bg(b1);
    G_node n2=Look_bg(b2);
    G_addEdge(n1, n2);
    return;
}

/* input AS_blockList after instruction selection for each block 
   in the C_Block, generate a graph on the basic blocks */


G_nodeList Create_bg(AS_blockList bl) {
    AS_blockList list=bl;

    RA_bg=G_Graph(); // prepare the empty graph
    block_env = S_empty(); //build a table of label -> block

    for (AS_blockList l=bl; l; l=l->tail) {
      S_enter(block_env, l->head->label, l->head);
      Look_bg(l->head); /* enter the block into graph as a node */
    }

    for (AS_blockList l=bl; l; l=l->tail) {
      Temp_labelList tl = l->head->succs;
      while (tl) {
        Enter_bg(l->head, S_look(block_env, tl->head));
        tl=tl->tail;
      }
    }
    return G_nodes(RA_bg);
}

static void show_AS_Block(AS_block b) {
    fprintf(stdout, "%s, ", Temp_labelstring(b->label));
}

void Show_bg(FILE* out, G_nodeList l) {
        G_show(out, l, (void*)show_AS_Block);
}

