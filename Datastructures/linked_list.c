#include <stdlib.h>

#include "linked_list.h"

struct ll {
    ll_node * head;
    ll_node * tail;
    size_t size;
};

struct dll {
    dll_node * head;
    dll_node * tail;
    size_t size;
};

linked_list * linked_list_new() {
    linked_list * l = malloc(sizeof(linked_list));
    if (l == NULL) return NULL;
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

doubly_linked_list * doubly_linked_list_new() {
    doubly_linked_list * dll = malloc(sizeof(doubly_linked_list));
    if (dll == NULL) return NULL;
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return dll;
}

void linked_list_free(linked_list * l) {
    free(l);
}

void doubly_linked_list_free(doubly_linked_list * dll) {
    free(dll);
}

void linked_list_free_items(linked_list * l) {
    if (l == NULL) return;
    ll_node * n = l->head;
    while (n != NULL) {
        free(n->item);
        n = n->next;
    }
}

void doubly_linked_list_free_items(doubly_linked_list * dll) {
    if (dll == NULL) return;
    dll_node * n = dll->head;
    while (n != NULL) {
        free(n->item);
        n = n->next;
    }
}

size_t linked_list_size(linked_list * l) {
    if (l == NULL) return 0;
    return l->size;
}

size_t doubly_linked_list_size(doubly_linked_list * dll) {
    if (dll == NULL) return 0;
    return dll->size;
}

int linked_list_add(linked_list * l, void * item) {
    if (l == NULL) return -1;
    ll_node * n = malloc(sizeof(ll_node));
    if (n == NULL) return -1;
    n->item = item;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }
    l->tail = n;
    l->size++;
    return 0;
}

int doubly_linked_list_add(doubly_linked_list * dll, void * item) {
    if (dll == NULL) return -1;
    dll_node * n = malloc(sizeof(dll_node));
    if (n == NULL) return -1;
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

int linked_list_remove(linked_list * l, void * item) {
    if (l == NULL) return -1;
    ll_node * n = l->head;
    ll_node * prev = NULL;
    while (n != NULL) {
        if (n->item == item) {
            if (prev == NULL) {
                l->head = n->next;
            } else {
                prev->next = n->next;
            }
            if (n == l->tail) {
                l->tail = prev;
            }
            free(n);
            l->size--;
            return 0;
        }
        prev = n;
        n = n->next;
    }
    return -1;
}

int doubly_linked_list_remove(doubly_linked_list * dll, void * item) {
    if (dll == NULL) return -1;
    dll_node * n = dll->head;
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

ll_node * linked_list_head(linked_list * l) {
    if (l == NULL) return NULL;
    return l->head;
}

dll_node * doubly_linked_list_head(doubly_linked_list * dll) {
    if (dll == NULL) return NULL;
    return dll->head;
}

ll_node * linked_list_tail(linked_list * l) {
    if (l == NULL) return NULL;
    return l->tail;
}

dll_node * doubly_linked_list_tail(doubly_linked_list * dll) {
    if (dll == NULL) return NULL;
    return dll->tail;
}

int doubly_linked_list_insert_before(doubly_linked_list * dll, dll_node * n, void * item) {
    if (dll == NULL) return -1;
    dll_node * new_node = malloc(sizeof(dll_node));
    if (new_node == NULL) return -1;
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

int doubly_linked_list_insert_after(doubly_linked_list * dll, dll_node * n, void * item) {
    if (dll == NULL) return -1;
    dll_node * new_node = malloc(sizeof(dll_node));
    if (new_node == NULL) return -1;
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
