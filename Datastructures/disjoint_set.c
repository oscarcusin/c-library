#include <stdlib.h>

#include "disjoint_set.h"

struct ds {
    size_t * repr;
    size_t * set_size;
    size_t size;
};

disjoint_set * disjoint_set_new(size_t n) {
    disjoint_set * ds = malloc(sizeof(disjoint_set));
    if (ds == NULL) return NULL;
    ds->repr = malloc(n * sizeof(size_t));
    if (ds->repr == NULL) {
        free(ds);
        return NULL;
    }
    ds->set_size = malloc(n * sizeof(size_t));
    if (ds->set_size == NULL) {
        free(ds->repr);
        ds->repr = NULL;
        free(ds);
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        ds->repr[i] = i;
        ds->set_size[i] = 1;
    }
    ds->size = n;
    return ds;
}

void disjoint_set_free(disjoint_set * ds) {
    if (ds == NULL) return;
    if (ds->repr != NULL) {
        free(ds->repr);
        ds->repr = NULL;
    }
    if (ds->set_size != NULL) {
        free(ds->set_size);
        ds->set_size = NULL;
    }
    free(ds);
}

size_t find(disjoint_set * ds, size_t elem) {
    if (ds->repr[elem] == elem) return elem;
    size_t repr = find(ds, ds->repr[elem]);
    ds->repr[elem] = repr;
    return repr;
}

void disjoint_set_merge(disjoint_set * ds, size_t a, size_t b) {
    if (ds == NULL) return;
    if (a >= ds->size || b >= ds->size) return;
    size_t a_repr = find(ds, a);
    size_t b_repr = find(ds, b);
    if (a_repr == b_repr) return;
    if (ds->set_size[a_repr] < ds->set_size[b_repr]) {
        size_t tmp = a_repr;
        a_repr = b_repr;
        b_repr = tmp;
    }
    ds->set_size[a_repr] += ds->set_size[b_repr];
    ds->repr[b_repr] = a_repr;
}

int disjoint_set_is_same_set(disjoint_set * ds, size_t a, size_t b) {
    if (ds == NULL) return 0;
    return find(ds, a) == find(ds, b);
}

size_t disjoint_set_size(disjoint_set * ds, size_t elem) {
    if (ds == NULL) return 0;
    return ds->set_size[find(ds, elem)];
}
