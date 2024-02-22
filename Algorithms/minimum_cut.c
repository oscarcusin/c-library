#include <stdlib.h>
#include <string.h>
#include "weighted_graph.h"
#include "queue.h"
#include "maximum_flow.h"

#include "minimum_cut.h"

size_t minimum_cut(weighted_graph * G, size_t s, size_t t, size_t U[]) {
    size_t V = weighted_graph_vertices(G);
    long flow[V][V], residual[V][V];
    maximum_flow(G, s, t, flow, residual);
    size_t vertices = 0;
    U[vertices++] = s;
    queue * q = queue_new();
    queue_enqueue(q, (void *) s);
    int visited[V];
    memset(visited, 0, sizeof(visited));
    visited[s] = 1;
    while (queue_size(q)) {
        size_t vertex = (size_t) queue_dequeue(q);
        for (size_t i = 0; i < V; i++) {
            if (!visited[i] && residual[vertex][i] > 0) {
                U[vertices++] = i;
                visited[i] = 1;
                queue_enqueue(q, (void *) i);
            }
        }
    }
    queue_free(q);
    return vertices;
}
