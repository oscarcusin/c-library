#include "graph.h"

#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

// Returns the shortest path from FROM to every other vertex in the weighted graph WG, using Dijkstra's algorithm.
// The distance from FROM to a vertex is stored in DIST, and the previous vertex in the path is stored in PREV.
// Unreachable vertices have a distance of LONG_MAX.
size_t shortest_path(weighted_graph * wg, size_t from, long dist[], size_t prev[]);

// Returns the shortest path from FROM to every other vertex in the weighted graph WG, using Bellman-Ford's algorithm.
// The distance from FROM to a vertex is stored in DIST, and the previous vertex in the path is stored in PREV.
// Unreachable vertices have a distance of LONG_MAX.
// Vertices with arbitrarily short distances have a distance of LONG_MIN.
size_t shortest_path_negative_weights(weighted_graph * wg, size_t from, long dist[], size_t prev[]);

// Finds the shortest path between every pair of vertices in the weighted graph WG, using Floyd-Warshall's algorithm.
// Distances are stored in the DIST array, and the previous vertex in the path is stored in the PREV array.
// Unreachable vertices have a distance of LONG_MAX.
// Vertices with arbitrarily short distances have a distance of LONG_MIN.
void shortest_path_all(weighted_graph * wg, long dist[][weighted_graph_vertices(wg)], size_t prev[][weighted_graph_vertices(wg)]);

#endif
