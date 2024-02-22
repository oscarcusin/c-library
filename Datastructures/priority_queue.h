#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define INITIAL_CAPACITY 16

typedef struct pq priority_queue;

// Creates a new priority queue.
// Returns pointer to the priority queue on success, NULL on failure.
priority_queue * priority_queue_new();

// Frees the priority queue PQ.
void priority_queue_free(priority_queue * pq);

// Frees the items in the priority queue PQ.
// Items are assumed to be allocated with malloc.
void priority_queue_free_items(priority_queue * pq);

// Returns the size of the priority queue PQ.
size_t priority_queue_size(priority_queue * pq);

// Adds ITEM to the priority queue PQ with priority PRIORITY (lower value means higher priority)
// Returns 0 on success, -1 on failure.
int priority_queue_push(priority_queue * pq, void * item, long priority);

// Removes and returns the item with the highest priority (lowest value) from the priority queue PQ.
// Returns NULL on failure.
void * priority_queue_pop(priority_queue * pq);

// Returns the item with the highest priority from the priority queue PQ.
// Returns NULL on failure.
void * priority_queue_peek(priority_queue * pq);

// Returns 1 if the priority queue PQ contains ITEM, 0 otherwise.
int priority_queue_contains(priority_queue * pq, void * item);

#endif
