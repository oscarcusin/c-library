#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"
#include "list.h"

#include "topological_sort.h"

void ordering_dfs(graph * g, size_t from, bool visited[], bool is_postorder, size_t ordering[], size_t * index) {
    visited[from] = 1;
    if (!is_postorder) ordering[(*index)++] = from;
    list * edges = graph_neighbours(g, from);
    for (size_t i = 0; i < list_size(edges); i++) {
        size_t to = (size_t) list_get(edges, i);
        if (!visited[to]) ordering_dfs(g, to, visited, is_postorder, ordering, index);
    }
    if (is_postorder) ordering[(*index)++] = from;
}

void preorder(graph * g, size_t from, size_t ordering[]) {
    bool * visited = (bool *) calloc(graph_vertices(g), sizeof(bool));
    if (visited == NULL) return;
    size_t index = 0;
    ordering_dfs(g, from, visited, false, ordering, &index);
    free(visited);
}

void postorder(graph * g, size_t from, size_t ordering[]) {
    bool * visited = (bool *) calloc(graph_vertices(g), sizeof(bool));
    if (visited == NULL) return;
    size_t index = 0;
    ordering_dfs(g, from, visited, true, ordering, &index);
    free(visited);
}

void topological_sort(graph * g, size_t ordering[]) {
    graph * new = graph_new(graph_vertices(g) + 1);
    size_t vertices = graph_vertices(new);
    for (size_t i = 0; i < vertices - 1; i++) {
        list * edges = graph_neighbours(g, i);
        for (size_t j = 0; j < list_size(edges); j++) {
            graph_add_edge(new, i, (size_t) list_get(edges, j));
        }
    }
    for (size_t i = 0; i < vertices - 1; i++) {
        graph_add_edge(new, vertices - 1, i);
    }
    size_t temp[vertices];
    postorder(new, vertices - 1, temp);
    for (size_t i = 0; i < vertices - 1; i++) {
        ordering[i] = temp[vertices - 2 - i];
    }
    graph_free(new);
}
