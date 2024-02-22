#include <stdlib.h>
#include <stdio.h>

#include "list.h"

struct l {
    void ** items;
    size_t size;
    size_t capacity;
};

list * list_new() {
    list * l = malloc(sizeof(list));
    if (l == NULL) {
        fprintf(stderr, "list_new(): Failed to allocate %lu bytes for list struct.\n", sizeof(list));
        return NULL;
    }
    l->items = malloc(INITIAL_CAPACITY * sizeof(void *));
    if (l->items == NULL) {
        fprintf(stderr, "list_new(): Failed to allocate %lu bytes for internal array.\n", INITIAL_CAPACITY * sizeof(void *));
        free(l);
        return NULL;
    }
    l->size = 0;
    l->capacity = INITIAL_CAPACITY;
    return l;
}

list * list_copy(list * l) {
    if (l == NULL) return NULL;
    list * copy = list_new();
    if (copy == NULL) return NULL;
    for (size_t i = 0; i < l->size; i++) {
        list_add(copy, l->items[i]);
    }
    return copy;
}

void list_free(list * l) {
    if (l == NULL) return;
    free(l->items);
    l->items = NULL;
    free(l);
    l = NULL;
}

void list_free_items(list * l) {
    if (l == NULL) return;
    for (size_t i = 0; i < l->size; i++) {
        free(l->items[i]);
        l->items[i] = NULL;
    }
}

size_t list_size(list * l) {
    if (l == NULL) return 0;
    return l->size;
}

int list_insert(list * l, size_t index, void * item) {
    if (l == NULL) return -1;
    if (index > l->size) {
        printf("Index %lu out of bounds for length %lu.\n", index, l->size);
        return -1;
    }
    if (l->size >= l->capacity) {
        l->capacity *= 2;
        void ** new_items = realloc(l->items, l->capacity * sizeof(void *));
        if (new_items == NULL) {
            fprintf(stderr, "list_insert(): Failed to allocate %lu bytes for internal array.\n", l->capacity * sizeof(void *));
            return -1;
        }
        l->items = new_items;
    }
    for (size_t i = l->size; i > index; i--) {
        l->items[i] = l->items[i - 1];
    }
    l->items[index] = item;
    l->size++;
    return 0;
}

int list_add(list * l, void * item) {
    return list_insert(l, l->size, item);
}

int list_remove(list * l, void * item) {
    if (l == NULL) return -1;
    for (size_t i = 0; i < l->size; i++) {
        if (l->items[i] == item) {
            for (size_t j = i; j < l->size - 1; j++) {
                l->items[j] = l->items[j + 1];
            }
            l->size--;
            return 0;
        }
    }
    return -1;
}

int list_remove_at(list * l, size_t index) {
    if (l == NULL) return -1;
    if (index >= l->size) {
        printf("Index %lu out of bounds for length %lu.\n", index, l->size);
        return -1;
    }
    for (size_t i = index; i < l->size - 1; i++) {
        l->items[i] = l->items[i + 1];
    }
    l->size--;
    return 0;
}

int list_set(list * l, size_t index, void * item) {
    if (l == NULL) return -1;
    if (index >= l->size) {
        printf("Index %lu out of bounds for length %lu.\n", index, l->size);
        return -1;
    }
    l->items[index] = item;
    return 0;
}

void * list_get(list * l, size_t index) {
    if (l == NULL) return NULL;
    if (index >= l->size) {
        printf("Index %lu out of bounds for length %lu.\n", index, l->size);
        return NULL;
    }
    return l->items[index];
}

int list_sort(list * l, int (* comparator) (const void **, const void **)) {
    if (l == NULL) return -1;
    qsort(l->items, l->size, sizeof(void *), (int (*) (const void *, const void *)) comparator);
    return 0;
}

int list_contains(list * l, void * item) {
    if (l == NULL) return 0;
    for (size_t i = 0; i < l->size; i++) {
        if (l->items[i] == item) return 1;
    }
    return 0;
}

int list_concat(list * l1, list * l2) {
    if (l1 == NULL || l2 == NULL) return -1;
    for (size_t i = 0; i < l2->size; i++) {
        list_add(l1, l2->items[i]);
    }
    return 0;
}
