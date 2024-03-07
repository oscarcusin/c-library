#include <stdlib.h>
#include "list.h"

#include "graph.h"

struct g {
    list ** adj;
    size_t vertices, edges;
};

graph * graph_new(size_t vertices) {
    graph * g = malloc(sizeof(graph));
    if (g == NULL) return NULL;
    g->adj = calloc(vertices, sizeof(list *));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }
    g->vertices = vertices;
    g->edges = 0;
    return g;
}

custom_graph * custom_graph_new(size_t vertices) {
    return (custom_graph *) graph_new(vertices);
}

weighted_graph * weighted_graph_new(size_t vertices) {
    return (weighted_graph *) graph_new(vertices);
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

weighted_graph * weighted_graph_copy(weighted_graph * wg) {
    if (wg == NULL) return NULL;
    weighted_graph * copy = weighted_graph_new(wg->vertices);
    if (copy == NULL) return NULL;
    copy->edges = wg->edges;
    for (size_t i = 0; i < wg->vertices; i++) {
        if (wg->adj[i] != NULL) {
            copy->adj[i] = list_new_with_capacity(list_size(wg->adj[i]));
            if (copy->adj[i] == NULL) {
                weighted_graph_free(copy);
                return NULL;
            }
            for (size_t j = 0; j < list_size(wg->adj[i]); j++) {
                weighted_edge * e = list_get(wg->adj[i], j);
                weighted_edge * new = malloc(sizeof(weighted_edge));
                if (new == NULL) {
                    weighted_graph_free(copy);
                    return NULL;
                }
                new->from = e->from;
                new->to = e->to;
                new->weight = e->weight;
                list_add(copy->adj[i], new);
            }
        }
    }
    return copy;
}

custom_graph * custom_graph_copy(custom_graph * cg) {
    if (cg == NULL) return NULL;
    custom_graph * copy = custom_graph_new(cg->vertices);
    if (copy == NULL) return NULL;
    copy->edges = cg->edges;
    for (size_t i = 0; i < cg->vertices; i++) {
        if (cg->adj[i] != NULL) {
            copy->adj[i] = list_new_with_capacity(list_size(cg->adj[i]));
            if (copy->adj[i] == NULL) {
                custom_graph_free(copy);
                return NULL;
            }
            for (size_t j = 0; j < list_size(cg->adj[i]); j++) {
                custom_edge * e = list_get(cg->adj[i], j);
                custom_edge * new = malloc(sizeof(custom_edge));
                if (new == NULL) {
                    custom_graph_free(copy);
                    return NULL;
                }
                new->from = e->from;
                new->to = e->to;
                new->data = e->data;
                list_add(copy->adj[i], new);
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
}

void weighted_graph_free(weighted_graph * wg) {
    if (wg == NULL) return;
    for (size_t i = 0; i < wg->vertices; i++) {
        list_free_items(wg->adj[i]);
        list_free(wg->adj[i]);
    }
    free(wg->adj);
    wg->adj = NULL;
    free(wg);
}

void custom_graph_free(custom_graph * cg) {
    if (cg == NULL) return;
    for (size_t i = 0; i < cg->vertices; i++) {
        for (size_t j = 0; j < list_size(cg->adj[i]); j++) {
            custom_edge * e = list_get(cg->adj[i], j);
            free(e->data);
        }
        list_free_items(cg->adj[i]);
        list_free(cg->adj[i]);
    }
    free(cg->adj);
    cg->adj = NULL;
    free(cg);
}

size_t graph_vertices(graph * g) {
    if (g == NULL) return 0;
    return g->vertices;
}

size_t weighted_graph_vertices(weighted_graph * wg) {
    if (wg == NULL) return 0;
    return wg->vertices;
}

size_t custom_graph_vertices(custom_graph * cg) {
    if (cg == NULL) return 0;
    return cg->vertices;
}

size_t graph_edges(graph * g) {
    if (g == NULL) return 0;
    return g->edges;
}

size_t weighted_graph_edges(weighted_graph * wg) {
    if (wg == NULL) return 0;
    return wg->edges;
}

size_t custom_graph_edges(custom_graph * cg) {
    if (cg == NULL) return 0;
    return cg->edges;
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

int weighted_graph_add_edge(weighted_graph * wg, size_t from, size_t to, long weight) {
    if (wg == NULL) return -1;
    if (from >= wg->vertices || to >= wg->vertices) return -1;
    if (wg->adj[from] == NULL) {
        wg->adj[from] = list_new();
        if (wg->adj[from] == NULL) return -1;
    }
    weighted_edge * new = malloc(sizeof(weighted_edge));
    if (new == NULL) return -1;
    wg->edges++;
    new->from = from;
    new->to = to;
    new->weight = weight;
    return list_add(wg->adj[from], new);
}

int custom_graph_add_edge(custom_graph * cg, size_t from, size_t to, void * data) {
    if (cg == NULL) return -1;
    if (from >= cg->vertices || to >= cg->vertices) return -1;
    if (cg->adj[from] == NULL) {
        cg->adj[from] = list_new();
        if (cg->adj[from] == NULL) return -1;
    }
    custom_edge * new = malloc(sizeof(custom_edge));
    if (new == NULL) return -1;
    cg->edges++;
    new->from = from;
    new->to = to;
    new->data = data;
    return list_add(cg->adj[from], new);
}

int graph_remove_edge(graph * g, size_t from, size_t to) {
    if (g == NULL) return -1;
    if (from >= g->vertices || to >= g->vertices) return -1;
    if (g->adj[from] == NULL) return -1;
    int result = list_remove(g->adj[from], (void *) to);
    if (result == 0) g->edges--;
    return result;
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

int custom_graph_remove_edge(custom_graph * cg, size_t from, size_t to) {
    if (cg == NULL) return -1;
    if (from >= cg->vertices || to >= cg->vertices) return -1;
    if (cg->adj[from] == NULL) return -1;
    for (size_t i = 0; i < list_size(cg->adj[from]); i++) {
        custom_edge * e = list_get(cg->adj[from], i);
        if (e->to == to) {
            list_remove_at(cg->adj[from], i);
            free(e->data);
            free(e);
            cg->edges--;
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

custom_edge * custom_graph_get_edge(custom_graph * cg, size_t from, size_t to) {
    if (cg == NULL) return NULL;
    if (from >= cg->vertices || to >= cg->vertices) return NULL;
    if (cg->adj[from] == NULL) return NULL;
    for (size_t i = 0; i < list_size(cg->adj[from]); i++) {
        custom_edge * e = list_get(cg->adj[from], i);
        if (e->to == to) return e;
    }
    return NULL;
}

int graph_has_edge(graph * g, size_t from, size_t to) {
    if (g == NULL) return 0;
    if (from >= g->vertices || to >= g->vertices) return 0;
    if (g->adj[from] == NULL) return 0;
    return list_contains(g->adj[from], (void *) to);
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

int custom_graph_has_edge(custom_graph * cg, size_t from, size_t to) {
    if (cg == NULL) return 0;
    if (from >= cg->vertices || to >= cg->vertices) return 0;
    if (cg->adj[from] == NULL) return 0;
    for (size_t i = 0; i < list_size(cg->adj[from]); i++) {
        custom_edge * e = (custom_edge *) list_get(cg->adj[from], i);
        if (e->to == to) return 1;
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

list * graph_neighbours(graph * g, size_t vertex) {
    if (g == NULL) return NULL;
    if (vertex >= g->vertices) return NULL;
    return g->adj[vertex];
}

list * weighted_graph_outgoing_edges(weighted_graph * wg, size_t vertex) {
    if (wg == NULL) return NULL;
    if (vertex >= wg->vertices) return NULL;
    return wg->adj[vertex];
}

list * custom_graph_outgoing_edges(custom_graph * cg, size_t vertex) {
    if (cg == NULL) return NULL;
    if (vertex >= cg->vertices) return NULL;
    return cg->adj[vertex];
}

list * custom_graph_incoming_edges(custom_graph *cg, size_t vertex) {
    if (cg == NULL) return NULL;
    list * incoming = list_new();
    if (incoming == NULL) return NULL;
    for (size_t i = 0; i < cg->vertices; i++) {
        if (cg->adj[i] == NULL) continue;
        for (size_t j = 0; j < list_size(cg->adj[i]); j++) {
            custom_edge * e = list_get(cg->adj[i], j);
            if (e->to == vertex) {
                custom_edge * new = malloc(sizeof(custom_edge));
                if (new == NULL) {
                    list_free(incoming);
                    return NULL;
                }
                new->from = i;
                new->to = vertex;
                new->data = e->data;
                list_add(incoming, new);
            }
        }
    }
    return incoming;
}

list * graph_edge_list(graph * g) {
    list * edges = list_new_with_capacity(g->edges);
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

list * weighted_graph_edge_list(weighted_graph * wg) {
    list * edges = list_new_with_capacity(wg->edges);
    if (edges == NULL) return NULL;
    for (size_t i = 0; i < wg->vertices; i++) {
        list_concat(edges, wg->adj[i]);
    }
    return edges;
}

list * custom_graph_edge_list(custom_graph * cg) {
    list * edges = list_new_with_capacity(cg->edges);
    if (edges == NULL) return NULL;
    for (size_t i = 0; i < cg->vertices; i++) {
        list_concat(edges, cg->adj[i]);
    }
    return edges;
}
