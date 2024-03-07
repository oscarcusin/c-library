#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "maximum_flow.h"

#include "minimum_cut.h"

size_t minimum_cut(weighted_graph * wg, size_t s, size_t t, size_t subset[weighted_graph_vertices(wg)]) {
    size_t vertices = weighted_graph_vertices(wg);
    custom_graph * fg = custom_graph_new(vertices);
    for (size_t i = 0; i < vertices; i++) {
        list * edges = weighted_graph_outgoing_edges(wg, i);
        for (size_t j = 0; j < list_size(edges); j++) {
            weighted_edge * we = (weighted_edge *) list_get(edges, j);
            flow_data * fd = (flow_data *) malloc(sizeof(flow_data));
            fd->capacity = we->weight;
            fd->flow = 0;
            custom_graph_add_edge(fg, i, we->to, fd);
        }
    }
    maximum_flow(fg, s, t);
    size_t index = 0;
    subset[index++] = s;
    queue * q = queue_new();
    queue_enqueue(q, (void *) s);
    int * visited = (int *) calloc(vertices, sizeof(int));
    visited[s] = 1;
    while (queue_size(q)) {
        size_t vertex = (size_t) queue_dequeue(q);
        for (size_t i = 0; i < vertices; i++) {
            custom_edge * edge = custom_graph_get_edge(fg, vertex, i);
            if (edge == NULL) continue;
            flow_data * fd = (flow_data *) edge->data;
            if (!visited[i] && fd->capacity > fd->flow) {
                subset[index++] = i;
                visited[i] = 1;
                queue_enqueue(q, (void *) i);
            }
        }
    }
    free(visited);
    queue_free(q);
    custom_graph_free(fg);
    return index;
}
