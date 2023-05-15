#pragma once
#include "util.h"
#include "table.h"
#include "symbol.h"
#include "temp.h"
#include "assemblock.h"
#include "graph.h"
#include "bg.h"
#include "flowgraph.h"
#include "liveness.h"
void ssa(AS_blockList blockList,G_nodeList b,G_nodeList ig);