#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

struct ll {
    node * head;
    node * tail;
    size_t size;
};

linked_list * linked_list_new() {
    linked_list * l = malloc(sizeof(linked_list));
    if (l == NULL) {
        fprintf(stderr, "linked_list_new(): Failed to allocate %lu bytes for singly linked list struct.\n", sizeof(linked_list));
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void linked_list_free(linked_list * l) {
    free(l);
}

void linked_list_free_items(linked_list * l) {
    if (l == NULL) return;
    node * n = l->head;
    while (n != NULL) {
        free(n->item);
        n = n->next;
    }
}

size_t linked_list_size(linked_list * l) {
    if (l == NULL) return 0;
    return l->size;
}

int linked_list_add(linked_list * l, void * item) {
    if (l == NULL) return -1;
    node * n = malloc(sizeof(node));
    if (n == NULL) {
        fprintf(stderr, "linked_list_add(): Failed to allocate %lu bytes for node struct.\n", sizeof(node));
        return -1;
    }
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

int linked_list_remove(linked_list * l, void * item) {
    if (l == NULL) return -1;
    node * n = l->head;
    node * prev = NULL;
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

node * linked_list_head(linked_list * l) {
    if (l == NULL) return NULL;
    return l->head;
}
