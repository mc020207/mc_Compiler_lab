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
AS_instrList registerAllocation(AS_instrList il,G_nodeList ig);