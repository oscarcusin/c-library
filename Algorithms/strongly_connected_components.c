#include <stdlib.h>
#include <stdint.h>
#include "graph.h"
#include "list.h"
#include "topological_sort.h"
#include "strongly_connected_components.h"

void dfs(graph * g, size_t from, size_t component[], size_t curr) {
    component[from] = curr;
    list * edges = graph_neighbours(g, from);
    for (size_t i = 0; i < list_size(edges); i++) {
        size_t to = (size_t) list_get(edges, i);
        if (component[to] == SIZE_MAX) dfs(g, to, component, curr);
    }
}

size_t strongly_connected_components(graph * g, size_t component[]) {
    for (size_t i = 0; i < graph_vertices(g); i++) component[i] = SIZE_MAX;
    size_t vertices = graph_vertices(g);
    size_t * ordering = malloc(vertices * sizeof(size_t));
    topological_sort(g, ordering);
    graph * reversed = graph_new(vertices);
    list * edges = graph_edge_list(g);
    for (size_t i = 0; i < list_size(edges); i++) {
        edge * e = list_get(edges, i);
        graph_add_edge(reversed, e->to, e->from);
    }
    size_t components = 0;
    for (size_t i = 0; i < vertices; i++) {
        size_t from = ordering[i];
        if (component[from] != SIZE_MAX) continue;
        dfs(reversed, from, component, components);
        components++;
    }
    free(ordering);
    graph_free(reversed);
    return components;
}
