#pragma once
#include "canon.h"
#include "assemblock.h"
#include "assem.h"
AS_blockList treep2assemblcok(struct C_block block);
AS_instrList treep2assemfuction(AS_blockList aslist,T_funcDecl x);