#include "weighted_graph.h"

#ifndef MINIMUM_CUT_H
#define MINIMUM_CUT_H

// Find the minimum cut in a weighted graph G with V vertices and E edges, from source S to sink T.
// The source set is represented by the U array, which is filled with the vertices in the source set.
// Returns the number of vertices in the source set.
size_t minimum_cut(weighted_graph * G, size_t s, size_t t, size_t U[]);

#endif
