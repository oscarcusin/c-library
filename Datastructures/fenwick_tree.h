#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

typedef struct ft fenwick_tree;

// Creates a new fenwick tree of the given SIZE, with all values initialized to 0.
// Returns a pointer to the fenwick tree on success, NULL on failure.
fenwick_tree * fenwick_tree_new(size_t size);

// Frees the memory associated with FT.
void fenwick_tree_free(fenwick_tree * ft);

// Adds DELTA to the value at INDEX in FT.
void fenwick_tree_add(fenwick_tree * ft, size_t index, long delta);

// Returns the sum of the values in FT from 0 to INDEX, exclusive.
long fenwick_tree_prefix_sum(fenwick_tree * ft, size_t index);

// Returns the sum of the values in FT from INDEX to the end.
long fenwick_tree_suffix_sum(fenwick_tree * ft, size_t index);

#endif
