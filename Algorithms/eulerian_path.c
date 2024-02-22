#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stack.h"

#include "graph.h"

int eulerian_cycle(graph * g, size_t cycle[]) {
    stack * s = stack_new();
    size_t start = 0;
    for (size_t i = 0; i < graph_vertices(g); i++) {
        if (list_size(graph_neighbours(g, i))) {
            start = i;
            break;
        }
    }
    stack_push(s, (void *) start);
    size_t cycle_index = graph_edges(g) + 1;
    graph * g_copy = graph_copy(g);
    while (stack_size(s)) {
        size_t u = (size_t) stack_peek(s);
        list * neighbours = graph_neighbours(g_copy, u);
        if (list_size(neighbours)) {
            size_t v = (size_t) list_get(neighbours, list_size(neighbours) - 1);
            stack_push(s, (void *) v);
            graph_remove_edge(g_copy, u, v);
        } else {
            cycle[--cycle_index] = (size_t) stack_pop(s);
        }
    }
    stack_free(s);
    graph_free(g_copy);
    if (cycle_index) return -1;
    return 0;
}

int eulerian_path(graph * g, size_t path[]) {
    size_t V = graph_vertices(g);
    long in_out_diff[V];
    memset(in_out_diff, 0, sizeof(in_out_diff));
    for (size_t i = 0; i < V; i++) {
        list * neighbours = graph_neighbours(g, i);
        in_out_diff[i] += list_size(neighbours);
        for (size_t j = 0; j < list_size(neighbours); j++) {
            in_out_diff[(size_t) list_get(neighbours, j)]--;
        }
    }
    size_t start = SIZE_MAX, end = SIZE_MAX;
    for (size_t i = 0; i < V; i++) {
        if (in_out_diff[i] == 0) continue;
        else if (in_out_diff[i] == +1 && start == SIZE_MAX) start = i;
        else if (in_out_diff[i] == -1 && end == SIZE_MAX) end = i;
        else return -1;
    }
    if (start != SIZE_MAX && end != SIZE_MAX) {
        graph_add_edge(g, end, start);
        size_t edge_count = graph_edges(g);
        size_t cycle[edge_count + 1];
        if (eulerian_cycle(g, cycle) == -1) {
            graph_remove_edge(g, end, start);
            return -1;
        }
        size_t path_start = 0;
        for (size_t i = 0; i < edge_count + 1; i++) {
            if (cycle[i] == end && cycle[(i + 1) % (edge_count + 1)] == start) {
                path_start = (i + 1) % (edge_count + 1);
                break;
            }
        }
        size_t path_length = 0;
        for (size_t i = 0; i < edge_count + 1; i++) {
            if ((path_start + i) % (edge_count + 1) == 0 && path_start != 0) continue;
            if ((path_start + i) % (edge_count + 1) == edge_count && path_start == 0) continue;
            path[path_length++] = cycle[(path_start + i) % (edge_count + 1)];
        }
        graph_remove_edge(g, end, start);
    } else if (start == SIZE_MAX && end == SIZE_MAX) {
        return eulerian_cycle(g, path);
    } else return -1;
    return 0;
}
