#ifndef _BG
#define _BG

#include "assemblock.h"

/* Block graph */

G_nodeList Create_bg(AS_blockList); /* create bg from blocklist */
void Show_bg(FILE *, G_nodeList);
G_graph Bg_graph(); /* get the block graph */

#endif

