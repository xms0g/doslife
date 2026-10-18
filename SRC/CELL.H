#ifndef cell_H
#define cell_H

#define CELL_WIDTH  8
#define CELL_HEIGHT 8
#define CELL_COLOR  0x02

#define CELL_IS_SAME(c1, c2) ((c1)->x == (c2)->x && (c1)->y == (c2)->y)

typedef struct {
    int x, y;
    char color;
    int width
    int height;
    int alive_neighbors_count;
} cell;

typedef struct {    
    int count;      
    int capacity;   
    cell* data;     
} cell_array;   

void ca_init(cell_array* ca, int size);
void ca_pushback(cell_array* ca, cell* cell);
void ca_remove(cell_array* ca, int index);
cell* ca_at(cell_array* ca, int index);
void ca_clear(cell_array* ca);
void caF_free(cell_array* ca);

#endif