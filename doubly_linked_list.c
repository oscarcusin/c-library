#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

struct dll {
    node * head;
    node * tail;
    size_t size;
};

doubly_linked_list * doubly_linked_list_new() {
    doubly_linked_list * dll = malloc(sizeof(doubly_linked_list));
    if (dll == NULL) {
        fprintf(stderr, "doubly_linked_list_new(): Failed to allocate %lu bytes for doubly linked list struct.\n", sizeof(doubly_linked_list));
        return NULL;
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return dll;
}

void doubly_linked_list_free(doubly_linked_list * dll) {
    free(dll);
}

void doubly_linked_list_free_items(doubly_linked_list * dll) {
    if (dll == NULL) return;
    node * n = dll->head;
    while (n != NULL) {
        free(n->item);
        n = n->next;
    }
}

size_t doubly_linked_list_size(doubly_linked_list * dll) {
    if (dll == NULL) return 0;
    return dll->size;
}

int doubly_linked_list_add(doubly_linked_list * dll, void * item) {
    if (dll == NULL) return -1;
    node * n = malloc(sizeof(node));
    if (n == NULL) {
        fprintf(stderr, "doubly_linked_list_add(): Failed to allocate %lu bytes for node struct.\n", sizeof(node));
        return -1;
    }
    n->item = item;
    n->prev = dll->tail;
    n->next = NULL;
    if (dll->head == NULL) {
        dll->head = n;
    } else {
        dll->tail->next = n;
    }
    dll->tail = n;
    dll->size++;
    return 0;
}

int doubly_linked_list_remove(doubly_linked_list * dll, void * item) {
    if (dll == NULL) return -1;
    node * n = dll->head;
    while (n != NULL) {
        if (n->item == item) {
            if (n->prev != NULL) {
                n->prev->next = n->next;
            } else {
                dll->head = n->next;
            }
            if (n->next != NULL) {
                n->next->prev = n->prev;
            } else {
                dll->tail = n->prev;
            }
            free(n);
            dll->size--;
            return 0;
        }
        n = n->next;
    }
    return -1;
}

node * doubly_linked_list_head(doubly_linked_list * dll) {
    if (dll == NULL) return NULL;
    return dll->head;
}

node * doubly_linked_list_tail(doubly_linked_list * dll) {
    if (dll == NULL) return NULL;
    return dll->tail;
}

int doubly_linked_list_insert_before(doubly_linked_list * dll, node * n, void * item) {
    if (dll == NULL) return -1;
    node * new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "doubly_linked_list_insert_before(): Failed to allocate %lu bytes for node struct.\n", sizeof(node));
        return -1;
    }
    new_node->item = item;
    new_node->prev = n->prev;
    new_node->next = n;
    if (n->prev != NULL) {
        n->prev->next = new_node;
    } else {
        dll->head = new_node;
    }
    n->prev = new_node;
    dll->size++;
    return 0;
}

int doubly_linked_list_insert_after(doubly_linked_list * dll, node * n, void * item) {
    if (dll == NULL) return -1;
    node * new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "doubly_linked_list_insert_after(): Failed to allocate %lu bytes for node struct.\n", sizeof(node));
        return -1;
    }
    new_node->item = item;
    new_node->prev = n;
    new_node->next = n->next;
    if (n->next != NULL) {
        n->next->prev = new_node;
    } else {
        dll->tail = new_node;
    }
    n->next = new_node;
    dll->size++;
    return 0;
}
