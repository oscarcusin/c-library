#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "graph.h"
#include "priority_queue.h"

#include "fastest_path.h"

size_t fastest_path(custom_graph * cg, size_t from, long time[], size_t prev[]) {
    size_t vertices = custom_graph_vertices(cg);
    size_t reachable = 0;
    for (size_t i = 0; i < vertices; i++) time[i] = LONG_MAX;
    time[from] = 0;
    priority_queue * pq = priority_queue_new();
    priority_queue_push(pq, (void *) from, time[from]);
    while (priority_queue_size(pq)) {
        size_t vertex = (size_t) priority_queue_pop(pq);
        list * edges = custom_graph_outgoing_edges(cg, vertex);
        for (size_t i = 0; i < list_size(edges); i++) {
            custom_edge * e = (custom_edge *) list_get(edges, i);
            time_data * data = e->data;
            if (data->period == 0 && time[vertex] > data->start) continue;
            long departure;
            if (time[vertex] <= data->start) departure = data->start;
            else {
                long t = (time[vertex] - data->start + data->period - 1) / data->period;
                departure = data->start + t * data->period;
            }
            if (departure + data->duration < time[e->to]) {
                if (time[e->to] == LONG_MAX) reachable++;
                time[e->to] = departure + data->duration;
                prev[e->to] = vertex;
                priority_queue_push(pq, (void *) e->to, time[e->to]);
            }
        }
    }
    priority_queue_free(pq);
    return reachable;
}
