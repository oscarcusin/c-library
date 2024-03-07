#include <stdlib.h>
#include "graph.h"
#include "disjoint_set.h"

#include "minimum_spanning_tree.h"

int weighted_edge_cmp(const void ** a, const void ** b) {
    weighted_edge * e1 = *(weighted_edge **) a;
    weighted_edge * e2 = *(weighted_edge **) b;
    if (e1->weight < e2->weight) return -1;
    if (e1->weight > e2->weight) return 1;
    return 0;
}

weighted_graph * kruskal(weighted_graph * wg) {
    if (wg == NULL) return NULL;
    size_t vertices = weighted_graph_vertices(wg);
    weighted_graph * mst = weighted_graph_new(vertices);
    disjoint_set * ds = disjoint_set_new(vertices);
    list * edges = weighted_graph_edge_list(wg);
    list_sort(edges, weighted_edge_cmp);
    for (size_t i = 0; i < list_size(edges); i++) {
        weighted_edge * e = (weighted_edge *) list_get(edges, i);
        if (!disjoint_set_is_same_set(ds, e->from, e->to)) {
            weighted_graph_add_edge(mst, e->from, e->to, e->weight);
            disjoint_set_merge(ds, e->from, e->to);
        }
    }
    list_free(edges);
    disjoint_set_free(ds);
    return mst;
}

// todo
weighted_graph * prim(weighted_graph * wg) {
    return NULL;
}

weighted_graph * minimum_spanning_tree(weighted_graph * wg) {
    if (wg == NULL) return NULL;
    return kruskal(wg);
}
