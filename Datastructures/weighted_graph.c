#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "list.h"

#include "weighted_graph.h"

struct wg {
    list ** adj;
    size_t vertices, edges;
};

weighted_graph * weighted_graph_new(size_t vertices) {
    weighted_graph * wg = malloc(sizeof(weighted_graph));
    if (wg == NULL) {
        fprintf(stderr, "weighted_graph_new(): Failed to allocate %lu bytes for weighted_graph struct.\n", sizeof(weighted_graph));
        return NULL;
    }
    wg->adj = calloc(vertices, sizeof(list *));
    if (wg->adj == NULL) {
        fprintf(stderr, "weighted_graph_new(): Failed to allocate %lu bytes for internal array.\n", vertices * sizeof(list *));
        free(wg);
        return NULL;
    }
    wg->vertices = vertices;
    wg->edges = 0;
    return wg;
}

weighted_graph * weighted_graph_copy(weighted_graph * wg) {
    if (wg == NULL) return NULL;
    weighted_graph * copy = weighted_graph_new(wg->vertices);
    if (copy == NULL) return NULL;
    copy->edges = wg->edges;
    for (size_t i = 0; i < wg->vertices; i++) {
        if (wg->adj[i] != NULL) {
            copy->adj[i] = list_copy(wg->adj[i]);
            if (copy->adj[i] == NULL) {
                weighted_graph_free(copy);
                return NULL;
            }
        }
    }
    return copy;
}

void weighted_graph_free(weighted_graph * wg) {
    if (wg == NULL) return;
    for (size_t i = 0; i < wg->vertices; i++) {
        list_free(wg->adj[i]);
    }
    free(wg->adj);
    wg->adj = NULL;
    free(wg);
}

size_t weighted_graph_vertices(weighted_graph * wg) {
    if (wg == NULL) return 0;
    return wg->vertices;
}

size_t weighted_graph_edges(weighted_graph * wg) {
    if (wg == NULL) return 0;
    return wg->edges;
}

int weighted_graph_add_edge(weighted_graph * wg, size_t from, size_t to, long weight) {
    if (wg == NULL) return -1;
    if (from >= wg->vertices || to >= wg->vertices) return -1;
    if (wg->adj[from] == NULL) {
        wg->adj[from] = list_new();
        if (wg->adj[from] == NULL) return -1;
    }
    weighted_edge * new = malloc(sizeof(weighted_edge));
    if (new == NULL) {
        fprintf(stderr, "weighted_graph_add_edge(): Failed to allocate %lu bytes for weighted_edge struct.\n", sizeof(weighted_edge));
        return -1;
    }
    wg->edges++;
    new->from = from;
    new->to = to;
    new->weight = weight;
    return list_add(wg->adj[from], new);
}

int weighted_graph_remove_edge(weighted_graph * wg, size_t from, size_t to) {
    if (wg == NULL) return -1;
    if (from >= wg->vertices || to >= wg->vertices) return -1;
    if (wg->adj[from] == NULL) return -1;
    for (size_t i = 0; i < list_size(wg->adj[from]); i++) {
        weighted_edge * e = list_get(wg->adj[from], i);
        if (e->to == to) {
            list_remove_at(wg->adj[from], i);
            free(e);
            wg->edges--;
            return 0;
        }
    }
    return 0;
}

weighted_edge * weighted_graph_get_edge(weighted_graph * wg, size_t from, size_t to) {
    if (wg == NULL) return NULL;
    if (from >= wg->vertices || to >= wg->vertices) return NULL;
    if (wg->adj[from] == NULL) return NULL;
    for (size_t i = 0; i < list_size(wg->adj[from]); i++) {
        weighted_edge * e = list_get(wg->adj[from], i);
        if (e->to == to) return e;
    }
    return NULL;
}

int weighted_graph_has_edge(weighted_graph * wg, size_t from, size_t to) {
    if (wg == NULL) return 0;
    if (from >= wg->vertices || to >= wg->vertices) return 0;
    if (wg->adj[from] == NULL) return 0;
    for (size_t i = 0; i < list_size(wg->adj[from]); i++) {
        weighted_edge * e = (weighted_edge *) list_get(wg->adj[from], i);
        if (e->to == to) return 1;
    }
    return 0;
}

long weighted_graph_edge_weight(weighted_graph * wg, size_t from, size_t to) {
    if (wg == NULL) return 0;
    if (from >= wg->vertices || to >= wg->vertices) return 0;
    if (wg->adj[from] == NULL) return 0;
    for (size_t i = 0; i < list_size(wg->adj[from]); i++) {
        weighted_edge * e = list_get(wg->adj[from], i);
        if (e->to == to) return e->weight;
    }
    return 0;
}

long weighted_graph_total_weight(weighted_graph * wg) {
    if (wg == NULL) return 0;
    long total = 0;
    for (size_t i = 0; i < wg->vertices; i++) {
        if (wg->adj[i] != NULL) {
            for (size_t j = 0; j < list_size(wg->adj[i]); j++) {
                weighted_edge * e = list_get(wg->adj[i], j);
                total += e->weight;
            }
        }
    }
    return total;
}

list * weighted_graph_outgoing_edges(weighted_graph * wg, size_t vertex) {
    if (wg == NULL) return NULL;
    if (vertex >= wg->vertices) return NULL;
    return wg->adj[vertex];
}

list * weighted_graph_edge_list(weighted_graph * wg) {
    list * edges = list_new();
    if (edges == NULL) return NULL;
    for (size_t i = 0; i < wg->vertices; i++) {
        list_concat(edges, wg->adj[i]);
    }
    return edges;
}
