#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct g graph;
typedef struct {
    size_t from, to;
} edge;

// Creates a new graph.
// Returns pointer to the graph on success, NULL on failure.
graph * graph_new(size_t vertices);

// Returns a copy of the graph G.
graph * graph_copy(graph * g);

// Frees the graph G.
void graph_free(graph * g);

// Returns the number of vertices in the graph G.
size_t graph_vertices(graph * g);

// Returns the number of edges in the graph G.
size_t graph_edges(graph * g);

// Adds an edge from FROM to TO in the graph G.
int graph_add_edge(graph * g, size_t from, size_t to);

// Removes the edge from FROM to TO in the graph G.
// Returns 0 on success, -1 on failure.
int graph_remove_edge(graph * g, size_t from, size_t to);

// Returns 1 if the graph G has an edge from FROM to TO, 0 otherwise.
int graph_has_edge(graph * g, size_t from, size_t to);

// Returns a list of the neighbours of VERTEX in the graph G.
list * graph_neighbours(graph * g, size_t vertex);

// Returns a list of the edges in the graph G.
list * graph_edge_list(graph * g);

#endif
