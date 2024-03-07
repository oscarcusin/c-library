#ifndef STRING_H
#define STRING_H

#define INITIAL_CAPACITY 16

typedef struct str string;

// Create a new string from STR.
// Returns pointer to the string on success, NULL on failure.
string * string_new(const char * str);

// Create a copy of the string S.
// Returns pointer to the copy on success, NULL on failure.
string * string_copy(string * s);

// Frees the string S.
void string_free(string * s);

// Returns the length of the string S.
size_t string_length(string * s);

#endif
