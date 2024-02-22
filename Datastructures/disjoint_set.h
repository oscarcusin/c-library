#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

typedef struct ds disjoint_set;

// Creates a new disjoint set with N elements, each in their own set, numbered 0 to N-1.
// Returns pointer to the disjoint set on success, NULL on failure.
disjoint_set * disjoint_set_new(size_t n);

// Free the disjoint set DS.
void disjoint_set_free(disjoint_set * ds);

// Declares that A and B are in the same set.
void disjoint_set_merge(disjoint_set * ds, size_t a, size_t b);

// Returns 1 if A and B are in the same set, 0 otherwise.
int disjoint_set_is_same_set(disjoint_set * ds, size_t a, size_t b);

// Returns the number of elements in the set containing ELEM.
size_t disjoint_set_size(disjoint_set * ds, size_t elem);

#endif
