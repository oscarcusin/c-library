#include "graph.h"
#include "topological_sort.h"

#ifndef STRONGLY_CONNECTED_COMPONENTS_H
#define STRONGLY_CONNECTED_COMPONENTS_H

// Finds the strongly connected components of the graph G.
// The component of each vertex is stored in the COMPONENT array, as a number from 0 to the number of components - 1.
// Returns the number of components.
size_t strongly_connected_components(graph * g, size_t component[]);

#endif
