#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "weighted_graph.h"
#include "queue.h"

#include "maximum_flow.h"

int bfs(weighted_graph * wg, size_t from, size_t to, long residual[][weighted_graph_vertices(wg)], size_t prev[]) {
    size_t V = weighted_graph_vertices(wg);
    int visited[V];
    memset(visited, 0, V * sizeof(int));
    visited[from] = 1;
    queue * q = queue_new();
    queue_enqueue(q, (void *) from);
    while (queue_size(q)) {
        size_t curr = (size_t) queue_dequeue(q);
        if (curr == to) {
            queue_free(q);
            return 1;
        } else {
            list * edges = weighted_graph_outgoing_edges(wg, curr);
            for (size_t i = 0; i < list_size(edges); i++) {
                weighted_edge * e = (weighted_edge *) list_get(edges, i);
                if (!visited[e->to] && residual[curr][e->to] > 0) {
                    visited[e->to] = 1;
                    prev[e->to] = curr;
                    queue_enqueue(q, (void *) e->to);
                }
            }
        }
    }
    queue_free(q);
    return 0;
}

long maximum_flow(weighted_graph * wg, size_t s, size_t t, long flow[][weighted_graph_vertices(wg)], long residual[][weighted_graph_vertices(wg)]) {
    weighted_graph * wg_copy = weighted_graph_copy(wg);
    size_t V = weighted_graph_vertices(wg_copy);
    memset(flow, 0, V * V * sizeof(long));
    memset(residual, 0, V * V * sizeof(long));
    long capacity[V][V];
    memset(capacity, 0, V * V * sizeof(long));
    for (size_t i = 0; i < V; i++) {
        list * edges = weighted_graph_outgoing_edges(wg_copy, i);
        for (size_t j = 0; j < list_size(edges); j++) {
            weighted_edge * e = (weighted_edge *) list_get(edges, j);
            capacity[i][e->to] = e->weight;
            residual[i][e->to] = e->weight;
        }
    }
    size_t prev[V];
    while (bfs(wg_copy, s, t, residual, prev)) {
        long min_residual = LONG_MAX;
        for (size_t v = t; v != s; v = prev[v]) {
            if (residual[prev[v]][v] < min_residual) {
                min_residual = residual[prev[v]][v];
            }
        }
        for (size_t v = t; v != s; v = prev[v]) {
            size_t from = prev[v], to = v;
            flow[from][to] += min_residual;
            residual[from][to] = capacity[from][to] - flow[from][to];
            flow[to][from] = -flow[from][to];
            residual[to][from] = capacity[to][from] - flow[to][from];
            if (!weighted_graph_has_edge(wg_copy, to, from)) {
                weighted_graph_add_edge(wg_copy, to, from, capacity[to][from]);
            }
        }
    }
    long max_flow = 0;
    list * edges = weighted_graph_outgoing_edges(wg_copy, t);
    for (size_t i = 0; i < list_size(edges); i++) {
        weighted_edge * e = (weighted_edge *) list_get(edges, i);
        max_flow -= flow[t][e->to];
    }
    weighted_graph_free(wg_copy);
    return max_flow;
}
