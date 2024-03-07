#ifndef STACK_H
#define STACK_H

#define INITIAL_CAPACITY 16

typedef struct stack stack;

// Creates a new stack.
// Returns pointer to the stack on success, NULL on failure.
stack * stack_new();

// Creates a new stack with a capacity of CAPACITY.
// Returns pointer to the stack on success, NULL on failure.
stack * stack_new_with_capacity(size_t capacity);

// Frees the stack S.
void stack_free(stack * s);

// Frees the items in the stack S.
// Items are assumed to be allocated with malloc.
void stack_free_items(stack * s);

// Returns the size of the stack S.
size_t stack_size(stack * s);

// Adds ITEM to the end of the stack S.
// Returns 0 on success, -1 on failure.
int stack_push(stack * s, void * item);

// Removes and returns the last item from the stack S.
// Returns NULL on failure.
void * stack_pop(stack * s);

// Returns the last item in the stack S.
// Returns NULL on failure.
void * stack_peek(stack * s);

// Returns 1 if ITEM is in the stack S, 0 otherwise.
int stack_contains(stack * s, void * item);

#endif
