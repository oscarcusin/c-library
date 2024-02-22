#include "weighted_graph.h"

#ifndef MAXIMUM_FLOW_H
#define MAXIMUM_FLOW_H

// Returns the maximum flow from FROM to TO in the weighted graph WG.
long maximum_flow(weighted_graph * wg, size_t from, size_t to, long flow[][weighted_graph_vertices(wg)], long residual[][weighted_graph_vertices(wg)]);

#endif
