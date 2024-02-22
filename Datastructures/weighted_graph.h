#include "list.h"

#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

typedef struct wg weighted_graph;
typedef struct {
    size_t from, to;
    long weight;
} weighted_edge;

// Creates a new weighted graph.
// Returns pointer to the weighted graph on success, NULL on failure.
weighted_graph * weighted_graph_new(size_t vertices);

// Returns a copy of the weighted graph WG.
weighted_graph * weighted_graph_copy(weighted_graph * wg);

// Frees the weighted graph WG.
void weighted_graph_free(weighted_graph * wg);

// Returns the number of vertices in the weighted graph WG.
size_t weighted_graph_vertices(weighted_graph * wg);

// Returns the number of edges in the weighted graph WG.
size_t weighted_graph_edges(weighted_graph * wg);

// Adds an edge from FROM to TO in the weighted graph WG.
int weighted_graph_add_edge(weighted_graph * wg, size_t from, size_t to, long weight);

// Removes the edge from FROM to TO in the weighted graph WG.
// Returns 0 on success, -1 on failure.
int weighted_graph_remove_edge(weighted_graph * wg, size_t from, size_t to);

// Returns the edge from FROM to TO in the weighted graph WG.
// Returns NULL if there is no such edge.
weighted_edge * weighted_graph_get_edge(weighted_graph * wg, size_t from, size_t to);

// Returns 1 if the weighted graph WG has an edge from FROM to TO, 0 otherwise.
int weighted_graph_has_edge(weighted_graph * wg, size_t from, size_t to);

// Returns the weight of the edge from FROM to TO in the weighted graph WG.
// Returns -1 if there is no such edge.
long weighted_graph_edge_weight(weighted_graph * wg, size_t from, size_t to);

// Returns the total weight of the weighted graph WG.
long weighted_graph_total_weight(weighted_graph * wg);

// Returns a list of the outgoing edges from VERTEX in the weighted graph WG.
list * weighted_graph_outgoing_edges(weighted_graph * wg, size_t vertex);

// Returns a list of all the edges in the weighted graph WG.
list * weighted_graph_edge_list(weighted_graph * wg);

#endif
