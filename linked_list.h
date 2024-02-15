#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node {
    void * item;
    struct node * next;
} node;

typedef struct ll linked_list;

// Creates a new singly linked list.
// Returns pointer to the singly linked list on success, NULL on failure.
linked_list * linked_list_new();

// Frees the singly linked list L.
void linked_list_free(linked_list * l);

// Frees the items in the singly linked list L.
// Items are assumed to be allocated with malloc.
void linked_list_free_items(linked_list * l);

// Returns the size of the singly linked list L.
size_t linked_list_size(linked_list * l);

// Adds ITEM to the end of the singly linked list L.
int linked_list_add(linked_list * l, void * item);

// Removes ITEM from the singly linked list L.
int linked_list_remove(linked_list * l, void * item);

// Returns the head of the singly linked list L.
node * linked_list_head(linked_list * l);

#endif
