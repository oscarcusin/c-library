#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "queue.h"

#include "maximum_flow.h"

int bfs(custom_graph * fg, size_t from, size_t to, size_t prev[custom_graph_vertices(fg)]) {
    size_t vertices = custom_graph_vertices(fg);
    int * visited = (int *) calloc(vertices, sizeof(int));
    visited[from] = 1;
    queue * q = queue_new();
    queue_enqueue(q, (void *) from);
    while (queue_size(q)) {
        size_t curr = (size_t) queue_dequeue(q);
        if (curr == to) {
            free(visited);
            queue_free(q);
            return 1;
        } else {
            list * edges = custom_graph_outgoing_edges(fg, curr);
            for (size_t i = 0; i < list_size(edges); i++) {
                custom_edge * edge = (custom_edge *) list_get(edges, i);
                flow_data * fd = (flow_data *) edge->data;
                if (!visited[edge->to] && fd->capacity > fd->flow) {
                    visited[edge->to] = 1;
                    prev[edge->to] = curr;
                    queue_enqueue(q, (void *) edge->to);
                }
            }
        }
    }
    free(visited);
    queue_free(q);
    return 0;
}

long maximum_flow(custom_graph * fg, size_t s, size_t t) {
    size_t vertices = custom_graph_vertices(fg);
    size_t * prev = (size_t *) calloc(vertices, sizeof(size_t));
    long max_flow = 0;
    while (bfs(fg, s, t, prev)) {
        long min_residual = LONG_MAX;
        for (size_t v = t; v != s; v = prev[v]) {
            custom_edge * edge = (custom_edge *) custom_graph_get_edge(fg, prev[v], v);
            flow_data * fd = (flow_data *) edge->data;
            if (fd->capacity - fd->flow < min_residual) min_residual = fd->capacity - fd->flow;
        }
        for (size_t v = t; v != s; v = prev[v]) {
            size_t from = prev[v], to = v;
            custom_edge * edge = (custom_edge *) custom_graph_get_edge(fg, from, to);
            flow_data * fd = (flow_data *) edge->data;
            fd->flow += min_residual;
            if (!custom_graph_has_edge(fg, to, from)) {
                flow_data * fd2 = (flow_data *) malloc(sizeof(flow_data));
                if (fd2 == NULL) {
                    free(prev);
                    return -1;
                }
                fd2->capacity = 0;
                fd2->flow = 0;
                custom_graph_add_edge(fg, to, from, fd2);
            }
            custom_edge * edge2 = (custom_edge *) custom_graph_get_edge(fg, to, from);
            flow_data * fd2 = (flow_data *) edge2->data;
            fd2->flow -= min_residual;
        }
        max_flow += min_residual;
    }
    free(prev);
    return max_flow;
}
