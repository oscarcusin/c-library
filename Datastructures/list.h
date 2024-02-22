#ifndef LIST_H
#define LIST_H

#define INITIAL_CAPACITY 16

typedef struct l list;

// Creates a new list.
// Returns pointer to the list on success, NULL on failure.
list * list_new();

// Creates a copy of the list L.
// Returns pointer to the copy on success, NULL on failure.
list * list_copy(list * l);

// Frees the list L.
void list_free(list * l);

// Frees the items in the list L.
// Items are assumed to be allocated with malloc.
void list_free_items(list * l);

// Returns the size of the list L.
size_t list_size(list * l);

// Inserts ITEM at INDEX in the list L, shifting the rest of the items to the right.
// Returns 0 on success, -1 on failure.
int list_insert(list * l, size_t index, void * item);

// Adds ITEM to the end of the list L.
// Returns 0 on success, -1 on failure.
int list_add(list * l, void * item);

// Removes ITEM from the list L, shifting the rest of the items to the left.
// Returns 0 on success, -1 on failure.
int list_remove(list * l, void * item);

// Removes the item at INDEX from the list L, shifting the rest of the items to the left.
// Returns 0 on success, -1 on failure.
int list_remove_at(list * l, size_t index);

// Sets the item at INDEX in the list L to ITEM.
// Returns 0 on success, -1 on failure.
int list_set(list * l, size_t index, void * item);

// Returns the item at INDEX in the list L.
// Returns NULL if INDEX is out of bounds.
void * list_get(list * l, size_t index);

// Sort the list L using the CMP function.
// Returns 0 on success, -1 on failure.
int list_sort(list * l, int (* cmp) (const void **, const void **));

// Returns 1 if ITEM is in the list L, 0 otherwise.
int list_contains(list * l, void * item);

// Add all the items in L2 to L1.
// Returns 0 on success, -1 on failure.
int list_concat(list * l1, list * l2);

#endif
