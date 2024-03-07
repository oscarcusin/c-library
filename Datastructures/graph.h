#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct g graph;
typedef struct g weighted_graph;
typedef struct g custom_graph;
typedef struct {size_t from, to;} edge;
typedef struct {size_t from, to; long weight;} weighted_edge;
typedef struct {size_t from, to; void * data;} custom_edge;

// Creates a new graph.
// Returns pointer to the graph on success, NULL on failure.
graph * graph_new(size_t vertices);

// Creates a new weighted graph.
// Returns pointer to the weighted graph on success, NULL on failure.
weighted_graph * weighted_graph_new(size_t vertices);

// Creates a new custom graph.
// Returns pointer to the custom graph on success, NULL on failure.
custom_graph * custom_graph_new(size_t vertices);

// Returns a copy of the graph G.
graph * graph_copy(graph * g);

// Returns a copy of the weighted graph WG.
weighted_graph * weighted_graph_copy(weighted_graph * wg);

// Returns a copy of the custom graph CG.
custom_graph * custom_graph_copy(custom_graph * cg);

// Frees the graph G.
void graph_free(graph * g);

// Frees the weighted graph WG.
void weighted_graph_free(weighted_graph * wg);

// Frees the custom graph CG.
void custom_graph_free(custom_graph * cg);

// Returns the number of vertices in the graph G.
size_t graph_vertices(graph * g);

// Returns the number of vertices in the weighted graph WG.
size_t weighted_graph_vertices(weighted_graph * wg);

// Returns the number of vertices in the custom graph CG.
size_t custom_graph_vertices(custom_graph * cg);

// Returns the number of edges in the graph G.
size_t graph_edges(graph * g);

// Returns the number of edges in the weighted graph WG.
size_t weighted_graph_edges(weighted_graph * wg);

// Returns the number of edges in the custom graph CG.
size_t custom_graph_edges(custom_graph * cg);

// Adds an edge from FROM to TO in the graph G.
int graph_add_edge(graph * g, size_t from, size_t to);

// Adds an edge from FROM to TO in the weighted graph WG.
int weighted_graph_add_edge(weighted_graph * wg, size_t from, size_t to, long weight);

// Adds an edge from FROM to TO in the custom graph CG.
int custom_graph_add_edge(custom_graph * cg, size_t from, size_t to, void * data);

// Removes the edge from FROM to TO in the graph G.
// Returns 0 on success, -1 on failure.
int graph_remove_edge(graph * g, size_t from, size_t to);

// Removes the edge from FROM to TO in the weighted graph WG.
// Returns 0 on success, -1 on failure.
int weighted_graph_remove_edge(weighted_graph * wg, size_t from, size_t to);

// Removes the edge from FROM to TO in the custom graph CG.
// Returns 0 on success, -1 on failure.
int custom_graph_remove_edge(custom_graph * cg, size_t from, size_t to);

// Returns the edge from FROM to TO in the weighted graph WG.
// Returns NULL if there is no such edge.
weighted_edge * weighted_graph_get_edge(weighted_graph * wg, size_t from, size_t to);

// Returns the edge from FROM to TO in the custom graph CG.
// Returns NULL if there is no such edge.
custom_edge * custom_graph_get_edge(custom_graph * cg, size_t from, size_t to);

// Returns 1 if the graph G has an edge from FROM to TO, 0 otherwise.
int graph_has_edge(graph * g, size_t from, size_t to);

// Returns 1 if the weighted graph WG has an edge from FROM to TO, 0 otherwise.
int weighted_graph_has_edge(weighted_graph * wg, size_t from, size_t to);

// Returns 1 if the custom graph CG has an edge from FROM to TO, 0 otherwise.
int custom_graph_has_edge(custom_graph * cg, size_t from, size_t to);

// Returns the total weight of the weighted graph WG.
long weighted_graph_total_weight(weighted_graph * wg);

// Returns a list of the neighbours of VERTEX in the graph G.
list * graph_neighbours(graph * g, size_t vertex);

// Returns a list of the outgoing edges from VERTEX in the weighted graph WG.
list * weighted_graph_outgoing_edges(weighted_graph * wg, size_t vertex);

// Returns a list of the outgoing edges from VERTEX in the custom graph CG.
list * custom_graph_outgoing_edges(custom_graph * cg, size_t vertex);

list * custom_graph_incoming_edges(custom_graph * cg, size_t vertex);

// Returns a list of the edges in the graph G.
list * graph_edge_list(graph * g);

// Returns a list of all the edges in the weighted graph WG.
list * weighted_graph_edge_list(weighted_graph * wg);

// Returns a list of all the edges in the custom graph CG.
list * custom_graph_edge_list(custom_graph * cg);

#endif
