#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct node {
    void * item;
    struct node * next, * prev;
} node;

typedef struct dll doubly_linked_list;

// Creates a new doubly linked list.
// Returns pointer to the doubly linked list on success, NULL on failure.
doubly_linked_list * doubly_linked_list_new();

// Frees the doubly linked list L.
void doubly_linked_list_free(doubly_linked_list * l);

// Frees the items in the doubly linked list L.
// Items are assumed to be allocated with malloc.
void doubly_linked_list_free_items(doubly_linked_list * l);

// Returns the size of the doubly linked list L.
size_t doubly_linked_list_size(doubly_linked_list * l);

// Adds ITEM to the end of the doubly linked list L.
int doubly_linked_list_add(doubly_linked_list * l, void * item);

// Removes ITEM from the doubly linked list L.
int doubly_linked_list_remove(doubly_linked_list * l, void * item);

// Returns the head of the doubly linked list L.
node * doubly_linked_list_head(doubly_linked_list * l);

// Returns the tail of the doubly linked list L.
node * doubly_linked_list_tail(doubly_linked_list * l);

// Inserts ITEM before NODE in the doubly linked list L.
// Returns 0 on success, -1 on failure.
int doubly_linked_list_insert_before(doubly_linked_list * l, node * n, void * item);

// Inserts ITEM after NODE in the doubly linked list L.
// Returns 0 on success, -1 on failure.
int doubly_linked_list_insert_after(doubly_linked_list * l, node * n, void * item);

#endif
