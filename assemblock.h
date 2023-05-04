#ifndef _AS_BLOCK
#define _AS_BLOCK

#include "assem.h"
#include "temp.h"

typedef struct AS_block_ *AS_block;
typedef struct AS_blockList_ *AS_blockList;
struct AS_block_ {AS_instrList instrs; Temp_label label; Temp_labelList succs;};
struct AS_blockList_ { AS_block head; AS_blockList tail;};

AS_blockList AS_BlockList(AS_block head, AS_blockList tail);
AS_block AS_Block(AS_instrList instrs);

AS_instrList AS_traceSchedule(AS_blockList bl,
        AS_instrList prolog, AS_instrList epilog, bool optimize);

#endif
