#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

struct node {
    int priority;
    void * item;
};

struct pq {
    struct node * heap;
    size_t size;
    size_t capacity;
};

priority_queue * priority_queue_new() {
    priority_queue * q = malloc(sizeof(priority_queue));
    if (q == NULL) {
        fprintf(stderr, "priority_queue_new(): Failed to allocate %lu bytes for priority_queue struct.\n", sizeof(priority_queue));
        return NULL;
    }
    q->heap = malloc(INITIAL_CAPACITY * sizeof(struct node));
    if (q->heap == NULL) {
        fprintf(stderr, "priority_queue_new(): Failed to allocate %lu bytes for internal array.\n", INITIAL_CAPACITY * sizeof(struct node));
        free(q);
        return NULL;
    }
    q->size = 0;
    q->capacity = INITIAL_CAPACITY;
    return q;
}

void priority_queue_free(priority_queue * q) {
    if (q == NULL) return;
    free(q->heap);
    q->heap = NULL;
    free(q);
    q = NULL;
}

void priority_queue_free_items(priority_queue * q) {
    if (q == NULL) return;
    for (int i = 0; i < q->size; i++) {
        free(q->heap[i].item);
    }
}

size_t priority_queue_size(priority_queue * q) {
    return q->size;
}

int priority_queue_push(priority_queue * q, void * item, int priority) {
    if (q == NULL) return -1;
    if (q->size >= q->capacity) {
        q->capacity *= 2;
        struct node * new_heap = malloc(q->capacity * sizeof(struct node));
        if (new_heap == NULL) {
            fprintf(stderr, "priority_queue_push): Failed to allocate %lu bytes for internal array.\n", q->capacity * sizeof(struct node));
            return -1;
        }
        memcpy(new_heap, q->heap, q->size * sizeof(struct node));
        free(q->heap);
        q->heap = new_heap;
    }
    size_t i = q->size;
    q->size++;
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (q->heap[parent].priority <= priority) break;
        q->heap[i] = q->heap[parent];
        i = parent;
    }
    q->heap[i].priority = priority;
    q->heap[i].item = item;
    return 0;
}

void * priority_queue_pop(priority_queue * q) {
    if (q == NULL || q->size == 0) return NULL;
    void * item = q->heap[0].item;
    q->size--;
    if (q->size > 0) {
        struct node last = q->heap[q->size];
        size_t i = 0;
        while (i * 2 + 1 < q->size) {
            size_t left = i * 2 + 1;
            size_t right = i * 2 + 2;
            if (right < q->size && q->heap[right].priority < q->heap[left].priority) left = right;
            if (last.priority <= q->heap[left].priority) break;
            q->heap[i] = q->heap[left];
            i = left;
        }
        q->heap[i] = last;
    }
    return item;
}

void * priority_queue_peek(priority_queue * q) {
    if (q == NULL || q->size == 0) return NULL;
    return q->heap[0].item;
}

int priority_queue_contains(priority_queue * q, void * item) {
    if (q == NULL) return 0;
    for (int i = 0; i < q->size; i++) {
        if (q->heap[i].item == item) return 1;
    }
    return 0;
}
