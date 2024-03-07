#include <stdlib.h>
#include "fenwick_tree.h"

struct ft {
    long * tree;
    size_t size;
};

fenwick_tree * fenwick_tree_new(size_t size) {
    fenwick_tree * ft = malloc(sizeof(fenwick_tree));
    if (ft == NULL) return NULL;
    ft->tree = calloc(size + 1, sizeof(long));
    if (ft->tree == NULL) {
        free(ft);
        return NULL;
    }
    ft->size = size + 1;
    return ft;
}

void fenwick_tree_free(fenwick_tree * ft) {
    if (ft == NULL) return;
    if (ft->tree != NULL) {
        free(ft->tree);
        ft->tree = NULL;
    }
    free(ft);
}

void fenwick_tree_add(fenwick_tree * ft, size_t index, long delta) {
    while (index < ft->size) {
        ft->tree[index] += delta;
        index += index & -index;
    }
}

long fenwick_tree_prefix_sum(fenwick_tree * ft, size_t index) {
    long sum = 0;
    while (index > 0) {
        sum += ft->tree[index];
        index -= index & -index;
    }
    return sum;
}

long fenwick_tree_suffix_sum(fenwick_tree * ft, size_t index) {
    return fenwick_tree_prefix_sum(ft, ft->size - 1) - fenwick_tree_prefix_sum(ft, index);
}
