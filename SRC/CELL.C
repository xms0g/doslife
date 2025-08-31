#include "cell.h"
#include <stdlib.h>

void caInit(CellArray* ca, int size) {
    ca->count = 0;
    ca->capacity = size;
    ca->data = (Cell*)malloc(size * sizeof(Cell));
}

void caPushback(CellArray* ca, Cell* cell) {
    if (ca->count == ca->capacity) {
        ca->capacity *= 2;
        ca->data = (Cell*)realloc(ca->data, ca->capacity * sizeof(Cell));
    }

    ca->data[ca->count++] = *cell;
}

void caRemove(CellArray* ca, int index) {
    int i;

    if (index < 0 || index >= ca->count) {
        return;
    }
    
    for (i = index; i < ca->count - 1; i++) {
        ca->data[i] = ca->data[i + 1];
    }
    
    ca->count--;
}

Cell* caAt(CellArray* ca, int index) {
    if (index < 0 || index >= ca->count) {
        return NULL;
    }

    return &ca->data[index];
}

void caClear(CellArray* ca) {
    memset(ca->data, 0, ca->count * sizeof(Cell));
    ca->count = 0;
}

void caFree(CellArray* ca) {
    free(ca->data);
    ca->data = NULL;
}

