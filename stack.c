#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack {
    void ** items;
    size_t size;
    size_t capacity;
};

stack * stack_new() {
    stack * s = malloc(sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "stack_new(): Failed to allocate %lu bytes for stack struct.\n", sizeof(stack));
        return NULL;
    }
    s->items = malloc(INITIAL_CAPACITY * sizeof(void *));
    if (s->items == NULL) {
        fprintf(stderr, "stack_new(): Failed to allocate %lu bytes for internal array.\n", INITIAL_CAPACITY * sizeof(void *));
        free(s);
        return NULL;
    }
    s->size = 0;
    s->capacity = INITIAL_CAPACITY;
    return s;
}

void stack_free(stack * s) {
    if (s == NULL) return;
    free(s->items);
    s->items = NULL;
    free(s);
    s = NULL;
}

void stack_free_items(stack * s) {
    if (s == NULL) return;
    for (int i = 0; i < s->size; i++) {
        free(s->items[i]);
    }
}

size_t stack_size(stack * s) {
    return s->size;
}

int stack_push(stack * s, void * item) {
    if (s == NULL) return -1;
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        void ** new_items = realloc(s->items, s->capacity * sizeof(void *));
        if (new_items == NULL) {
            fprintf(stderr, "stack_push(): Failed to allocate %lu bytes for internal array.\n", s->capacity * sizeof(void *));
            return -1;
        }
        s->items = new_items;
    }
    s->items[s->size] = item;
    s->size++;
    return 0;
}

void * stack_pop(stack * s) {
    if (s == NULL || s->size == 0) return NULL;
    s->size--;
    return s->items[s->size];
}

void * stack_peek(stack * s) {
    if (s == NULL || s->size == 0) return NULL;
    return s->items[s->size - 1];
}

int stack_contains(stack * s, void * item) {
    if (s == NULL) return 0;
    for (int i = 0; i < s->size; i++) {
        if (s->items[i] == item) return 1;
    }
    return 0;
}
