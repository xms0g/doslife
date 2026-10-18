#include "cell.h"
#include <stdlib.h>

void ca_init(cell_array* ca, int size) {
    ca->count = 0;
    ca->capacity = size;
    ca->data = (cell*)malloc(size * sizeof(cell));
}

void ca_pushback(cell_array* ca, cell* c) {
    if (ca->count == ca->capacity) {
        ca->capacity *= 2;
        ca->data = (cell*)realloc(ca->data, ca->capacity * sizeof(cell));
    }

    ca->data[ca->count++] = *c;
}

void ca_remove(cell_array* ca, int index) {
    int i;

    if (index < 0 || index >= ca->count) {
        return;
    }
    
    for (i = index; i < ca->count - 1; i++) {
        ca->data[i] = ca->data[i + 1];
    }
    
    ca->count--;
}

cell* ca_at(cell_array* ca, int index) {
    if (index < 0 || index >= ca->count) {
        return NULL;
    }

    return &ca->data[index];
}

void ca_clear(cell_array* ca) {
    memset(ca->data, 0, ca->count * sizeof(cell));
    ca->count = 0;
}

void caF_free(cell_array* ca) {
    free(ca->data);
    ca->data = NULL;
}

