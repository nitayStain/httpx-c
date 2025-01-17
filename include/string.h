#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MIN_CAPACITY 16

typedef struct string {
    char* buffer;
    size_t size;
    size_t capacity;
} string;

string* string_new(const char* buffer) {
    size_t size = strlen(buffer);
    size_t capacity = (size > MIN_CAPACITY) ? size + 1 : MIN_CAPACITY;

    string* s = (string*) malloc(sizeof(string));
 
    if(!s)
    {
        return NULL;
    }

    s->buffer = (char*) malloc(capacity);
    if(!s->buffer) {
        free(s);
        return NULL;
    }

    strcpy(s->buffer, buffer);

    s->size = size;
    s->capacity = capacity;

    return s;
}

void string_concat_c(string* self, char* src) {
    size_t new_size = self->size + strlen(src);
    if(new_size >= self->size + 1) {
        self->buffer = (char*) realloc(self->buffer, new_size);
    }

    strcat(self->buffer, src);
}

void string_concat(const string* self, const string* src) {
    string_concat_c(self, src->buffer);
}
