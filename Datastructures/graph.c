#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#include "graph.h"

struct g {
    list ** adj;
    size_t vertices, edges;
};

graph * graph_new(size_t vertices) {
    graph * g = malloc(sizeof(graph));
    if (g == NULL) {
        fprintf(stderr, "graph_new(): Failed to allocate %lu bytes for graph struct.\n", sizeof(graph));
        return NULL;
    }
    g->adj = calloc(vertices, sizeof(list *));
    if (g->adj == NULL) {
        fprintf(stderr, "graph_new(): Failed to allocate %lu bytes for internal array.\n", vertices * sizeof(list *));
        free(g);
        return NULL;
    }
    g->vertices = vertices;
    g->edges = 0;
    return g;
}

graph * graph_copy(graph * g) {
    if (g == NULL) return NULL;
    graph * copy = graph_new(g->vertices);
    if (copy == NULL) return NULL;
    copy->edges = g->edges;
    for (size_t i = 0; i < g->vertices; i++) {
        if (g->adj[i] != NULL) {
            copy->adj[i] = list_copy(g->adj[i]);
            if (copy->adj[i] == NULL) {
                graph_free(copy);
                return NULL;
            }
        }
    }
    return copy;
}

void graph_free(graph * g) {
    if (g == NULL) return;
    for (size_t i = 0; i < g->vertices; i++) {
        list_free(g->adj[i]);
    }
    free(g->adj);
    g->adj = NULL;
    free(g);
    g = NULL;
}

size_t graph_vertices(graph * g) {
    if (g == NULL) return 0;
    return g->vertices;
}

size_t graph_edges(graph * g) {
    if (g == NULL) return 0;
    return g->edges;
}

int graph_add_edge(graph * g, size_t from, size_t to) {
    if (g == NULL) return -1;
    if (from >= g->vertices || to >= g->vertices) return -1;
    if (g->adj[from] == NULL) {
        g->adj[from] = list_new();
        if (g->adj[from] == NULL) return -1;
    }
    g->edges++;
    return list_add(g->adj[from], (void *) to);
}

int graph_remove_edge(graph * g, size_t from, size_t to) {
    if (g == NULL) return -1;
    if (from >= g->vertices || to >= g->vertices) return -1;
    if (g->adj[from] == NULL) return -1;
    int result = list_remove(g->adj[from], (void *) to);
    if (result == 0) g->edges--;
    return result;
}

int graph_has_edge(graph * g, size_t from, size_t to) {
    if (g == NULL) return 0;
    if (from >= g->vertices || to >= g->vertices) return 0;
    if (g->adj[from] == NULL) return 0;
    return list_contains(g->adj[from], (void *) to);
}

list * graph_neighbours(graph * g, size_t vertex) {
    if (g == NULL) return NULL;
    if (vertex >= g->vertices) return NULL;
    return g->adj[vertex];
}

list * graph_edge_list(graph * g) {
    list * edges = list_new();
    if (edges == NULL) return NULL;
    for (size_t i = 0; i < g->vertices; i++) {
        if (g->adj[i] == NULL) continue;
        for (size_t j = 0; j < list_size(g->adj[i]); j++) {
            size_t to = (size_t) list_get(g->adj[i], j);
            edge * e = malloc(sizeof(edge));
            if (e == NULL) {
                list_free_items(edges);
                list_free(edges);
                return NULL;
            }
            e->from = i;
            e->to = to;
            list_add(edges, e);
        }
    }
    return edges;
}
