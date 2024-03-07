#include "graph.h"

#ifndef MINIMUM_CUT_H
#define MINIMUM_CUT_H

// Find the minimum cut in a weighted graph WG with V vertices and E edges, from source S to sink T.
// The source set is represented by the SUBSET array, which is filled with the vertices in the source set.
// Returns the number of vertices in the source set.
size_t minimum_cut(weighted_graph * wg, size_t s, size_t t, size_t subset[weighted_graph_vertices(wg)]);

#endif
