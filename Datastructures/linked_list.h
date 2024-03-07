#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ll linked_list;
typedef struct dll doubly_linked_list;
typedef struct dll doubly_linked_list;
typedef struct ll_node {void * item; struct ll_node * next;} ll_node;
typedef struct dll_node {void * item; struct dll_node * next, * prev;} dll_node;

// Creates a new singly linked list.
// Returns pointer to the singly linked list on success, NULL on failure.
linked_list * linked_list_new();

// Creates a new doubly linked list.
// Returns pointer to the doubly linked list on success, NULL on failure.
doubly_linked_list * doubly_linked_list_new();

// Frees the singly linked list LL.
void linked_list_free(linked_list * ll);

// Frees the doubly linked list DLL.
void doubly_linked_list_free(doubly_linked_list * dll);

// Frees the items in the singly linked list LL.
// Items are assumed to be allocated with malloc.
void linked_list_free_items(linked_list * ll);

// Frees the items in the doubly linked list DLL.
// Items are assumed to be allocated with malloc.
void doubly_linked_list_free_items(doubly_linked_list * dll);

// Returns the size of the singly linked list LL.
size_t linked_list_size(linked_list * ll);

// Returns the size of the doubly linked list DLL.
size_t doubly_linked_list_size(doubly_linked_list * dll);

// Adds ITEM to the end of the singly linked list LL.
int linked_list_add(linked_list * ll, void * item);

// Adds ITEM to the end of the doubly linked list DLL.
int doubly_linked_list_add(doubly_linked_list * dll, void * item);

// Removes ITEM from the singly linked list LL.
int linked_list_remove(linked_list * ll, void * item);

// Removes ITEM from the doubly linked list DLL.
int doubly_linked_list_remove(doubly_linked_list * dll, void * item);

// Returns the head of the singly linked list LL.
ll_node * linked_list_head(linked_list * ll);

// Returns the head of the doubly linked list DLL.
dll_node * doubly_linked_list_head(doubly_linked_list * dll);

// Returns the tail of the singly linked list LL.
ll_node * linked_list_tail(linked_list * ll);

// Returns the tail of the doubly linked list DLL.
dll_node * doubly_linked_list_tail(doubly_linked_list * dll);

// Inserts ITEM before NODE in the doubly linked list DLL.
// Returns 0 on success, -1 on failure.
int doubly_linked_list_insert_before(doubly_linked_list * dll, dll_node * n, void * item);

// Inserts ITEM after NODE in the doubly linked list DLL.
// Returns 0 on success, -1 on failure.
int doubly_linked_list_insert_after(doubly_linked_list * dll, dll_node * n, void * item);

#endif
