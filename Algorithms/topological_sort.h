#include "graph.h"

#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

// Finds the pre-order traversal of the graph G starting from vertex FROM.
// Saves the ordering in ORDERING.
void preorder(graph * g, size_t from, size_t ordering[]);

// Finds the post-order traversal of the graph G starting from vertex FROM.
// Saves the ordering in ORDERING.
void postorder(graph * g, size_t from, size_t ordering[]);

// Finds a topological ordering of the vertices in the graph G.
// Saves the ordering in ORDERING.
void topological_sort(graph * g, size_t ordering[]);

#endif
