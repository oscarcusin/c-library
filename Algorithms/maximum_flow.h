#include "graph.h"

#ifndef MAXIMUM_FLOW_H
#define MAXIMUM_FLOW_H

typedef struct {long capacity, flow;} flow_data;

// Finds the maximum flow in a flow graph FG from source FROM to sink TO.
// The flow graph FG is represented as a custom_graph, with the data field being of type flow_data.
// Warning: the flow graph FG will be modified by this function.
// Returns the maximum flow from source S to sink T, or -1 if an error occurs.
long maximum_flow(custom_graph * fg, size_t from, size_t to);

#endif
