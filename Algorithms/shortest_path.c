#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "priority_queue.h"

#include "shortest_path.h"

size_t shortest_path(weighted_graph * wg, size_t from, long dist[], size_t prev[]) {
    size_t vertices = weighted_graph_vertices(wg);
    size_t reachable = 0;
    for (size_t i = 0; i < vertices; i++) dist[i] = LONG_MAX;
    dist[from] = 0;
    priority_queue * pq = priority_queue_new();
    priority_queue_push(pq, (void *) from, dist[from]);
    while (priority_queue_size(pq)) {
        size_t vertex = (size_t) priority_queue_pop(pq);
        list * edges = weighted_graph_outgoing_edges(wg, vertex);
        for (size_t i = 0; i < list_size(edges); i++) {
            weighted_edge * e = (weighted_edge *) list_get(edges, i);
            if (dist[vertex] + e->weight < dist[e->to]) {
                if (dist[e->to] == LONG_MAX) reachable++;
                dist[e->to] = dist[vertex] + e->weight;
                prev[e->to] = vertex;
                priority_queue_push(pq, (void *) e->to, dist[e->to]);
            }
        }
    }
    priority_queue_free(pq);
    return reachable;
}

size_t shortest_path_negative_weights(weighted_graph * wg, size_t from, long dist[], size_t prev[]) {
    size_t vertices = weighted_graph_vertices(wg);
    size_t reachable = 0;
    for (size_t i = 0; i < vertices; i++) dist[i] = LONG_MAX;
    dist[from] = 0;
    list * edges = weighted_graph_edge_list(wg);
    for (size_t i = 0; i < vertices - 1; i++) {
        for (size_t j = 0; j < list_size(edges); j++) {
            weighted_edge * e = (weighted_edge *) list_get(edges, j);
            if (dist[e->from] == LONG_MAX) continue;
            if (dist[e->from] + e->weight < dist[e->to]) {
                if (dist[e->to] == LONG_MAX) reachable++;
                dist[e->to] = dist[e->from] + e->weight;
                prev[e->to] = e->from;
            }
        }
    }
    for (size_t i = 0; i < vertices - 1; i++) {
        int changed = 0;
        for (size_t j = 0; j < list_size(edges); j++) {
            weighted_edge * e = (weighted_edge *) list_get(edges, j);
            if (dist[e->from] == LONG_MAX) continue;
            if ((dist[e->from] == LONG_MIN && e->weight < 0)
            || dist[e->from] + e->weight < dist[e->to]) {
                dist[e->to] = LONG_MIN;
                changed = 1;
            }
        }
        if (!changed) break;
    }
    list_free(edges);
    return reachable;
}

void shortest_path_all(weighted_graph * wg, long dist[][weighted_graph_vertices(wg)], size_t prev[][weighted_graph_vertices(wg)]) {
    size_t vertices = weighted_graph_vertices(wg);
    for (size_t i = 0; i < vertices; i++) {
        for (size_t j = 0; j < vertices; j++) {
            if (i == j) {
                dist[i][j] = 0;
                prev[i][j] = i;
            } else dist[i][j] = LONG_MAX;
        }
    }
    for (size_t i = 0; i < vertices; i++) {
        list * edges = weighted_graph_outgoing_edges(wg, i);
        for (size_t j = 0; j < list_size(edges); j++) {
            weighted_edge * e = (weighted_edge *) list_get(edges, j);
            dist[i][e->to] = e->weight < dist[i][e->to] ? e->weight : dist[i][e->to];
            prev[i][e->to] = i;
        }
    }
    for (size_t i = 0; i < vertices; i++) {
        for (size_t j = 0; j < vertices; j++) {
            for (size_t k = 0; k < vertices; k++) {
                if (dist[j][i] != LONG_MAX && dist[i][k] != LONG_MAX && dist[j][i] + dist[i][k] < dist[j][k]) {
                    dist[j][k] = dist[j][i] + dist[i][k];
                    prev[j][k] = prev[i][k];
                }
            }
        }
    }
    for (size_t i = 0; i < vertices; i++) {
        if (dist[i][i] == 0) continue;
        for (size_t j = 0; j < vertices; j++) {
            for (size_t k = 0; k < vertices; k++) {
                if (dist[j][i] != LONG_MAX && dist[i][k] != LONG_MAX) {
                    dist[j][k] = LONG_MIN;
                }
            }
        }
    }
}
