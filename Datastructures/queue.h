#ifndef QUEUE_H
#define QUEUE_H

#define INITIAL_CAPACITY 16

typedef struct q queue;

// Creates a new queue.
// Returns pointer to the queue on success, NULL on failure.
queue * queue_new();

// Creates a new queue with a capacity of CAPACITY.
// Returns pointer to the queue on success, NULL on failure.
queue * queue_new_with_capacity(size_t capacity);

// Frees the queue Q.
void queue_free(queue * q);

// Frees the items in the queue Q.
// Items are assumed to be allocated with malloc.
void queue_free_items(queue * q);

// Returns the size of the queue Q.
size_t queue_size(queue * q);

// Adds ITEM to the end of the queue Q.
// Returns 0 on success, -1 on failure.
int queue_enqueue(queue * q, void * item);

// Removes and returns the first item from the queue Q.
// Returns NULL on failure.
void * queue_dequeue(queue * q);

// Returns the first item in the queue Q.
// Returns NULL on failure.
void * queue_peek(queue * q);

// Returns 1 if ITEM is in the queue Q, 0 otherwise.
int queue_contains(queue * q, void * item);

#endif
