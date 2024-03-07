#include "graph.h"

#ifndef FASTEST_PATH_H
#define FASTEST_PATH_H

typedef struct {long start, period, duration;} time_data;

// Returns the fastest path from FROM to TO in the custom graph CG, using modified Dijkstra's algorithm.
// Data field of the custom graph edges must be of type time_data.
// The minimum time from FROM to TO is stored in TIME, and the previous vertex in the path is stored in PREV.
// Unreachable vertices have a TIME of LONG_MAX.
size_t fastest_path(custom_graph * wg, size_t from, long time[], size_t prev[]);

#endif
