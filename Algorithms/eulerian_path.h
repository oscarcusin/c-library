#include "graph.h"

#ifndef EULERIAN_PATH_H
#define EULERIAN_PATH_H

// Finds an Eulerian cycle in the given graph, if one exists.
// Stores the cycle in the CYCLE array, which must be pre-allocated to the number of edges in the graph plus one.
// Returns 0 if an Eulerian cycle was found, -1 otherwise.
int eulerian_cycle(graph * g, size_t cycle[]);

// Finds an Eulerian path in the given graph, if one exists.
// Stores the path in the PATH array, which must be pre-allocated to the number of edges in the graph plus one.
// Returns 0 if an Eulerian path was found, -1 otherwise.
int eulerian_path(graph * g, size_t path[]);

#endif
