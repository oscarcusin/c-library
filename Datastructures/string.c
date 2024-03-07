#include <stdlib.h>
#include <string.h>

#include "string.h"

struct str {
    char * str;
    size_t length;
    size_t capacity;
};

string * string_new(const char * str) {
    string * s = malloc(sizeof(string));
    if (s == NULL) return NULL;
    size_t len = strlen(str);
    s->capacity = INITIAL_CAPACITY;
    while (s->capacity < len) s->capacity *= 2;
    s->str = malloc(s->capacity * sizeof(char));
    if (s->str == NULL) {
        free(s);
        return NULL;
    }
    strcpy(s->str, str);
    s->length = len;
    return s;
}

string * string_copy(string * s) {
    if (s == NULL) return NULL;
    string * copy = malloc(sizeof(string));
    if (copy == NULL) return NULL;
    copy->capacity = s->capacity;
    copy->str = malloc(copy->capacity * sizeof(char));
    if (copy->str == NULL) {
        free(copy);
        return NULL;
    }
    memcpy(copy->str, s->str, s->length);
    copy->length = s->length;
    return copy;
}

void string_free(string * s) {
    if (s == NULL) return;
    free(s->str);
    s->str = NULL;
    free(s);
}

size_t string_length(string * s) {
    if (s == NULL) return 0;
    return s->length;
}
