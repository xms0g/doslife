#include "renderer.h"
#include "keybrd.h"
#include "states.h"
#include "cell.h"

static int is_running;
static cell_array alive_cells;
static cell_array neighboring_dead_cells;
static cell_array newly_dead_cells;

static void process_neighbors(cell* cell);
static void check_neighbor(cell* current_alive, cell* neighbor);

static void process_input(void) {
    char key = kb_hit();

    if (key == ESC) {
        is_running = 0;
    }
}

static void update(void) {
    int i,j;
    cell* cell;
        
    for (i = 0; i < alive_cells.count; ++i) {
        cell = ca_at(&alive_cells, i);
        
        process_neighbors(cell);
            
        if (cell->alive_neighbors_count < 2 || cell->alive_neighbors_count > 3) {
           ca_pushback(&newly_dead_cells, cell);
        }
            
        cell->alive_neighbors_count = 0;
    } 
        
    for (i = 0; i < neighboring_dead_cells.count; ++i) {
        cell = ca_at(&neighboring_dead_cells, i);
        
        if (cell->alive_neighbors_count == 3) {
            cell->alive_neighbors_count = 0;
            ca_pushback(&alive_cells, cell);
        }
    }

    for (i = 0; i < newly_dead_cells.count; ++i) {
        cell* dead_cell = ca_at(&newly_dead_cells, i);

        for (j = 0; j < alive_cells.count; ++j) {
            cell* alive_cell = ca_at(&alive_cells, j);
            
            if (CELL_IS_SAME(dead_cell, alive_cell)) {
                ca_remove(&alive_cells, j);
            }
        }
    }

    ca_clear(&neighboring_dead_cells);
    ca_clear(&newly_dead_cells);
}

static void render(void) {
    int i;
    cell* cell;

    rnd_clear(0x0);

    for (i = 0; i < alive_cells.count; ++i) {
        cell = ca_at(&alive_cells, i);
        
        rnd_draw_rectangle(
            cell->x,
            cell->y,
            cell->width,
            cell->height,
            cell->color
        );
    }

    rnd_update_buffer();
}

static void process_neighbors(cell* cell) {
    int i;

    for (i = 0; i < NEIGHBOR_COUNT; ++i) {
        cell neighbor;
        neighbor.x = cell->x + neighbor_states[i][0];
        neighbor.y = cell->y + neighbor_states[i][1];
        neighbor.width = CELL_WIDTH;
        neighbor.height = CELL_HEIGHT;
        neighbor.color = CELL_COLOR;
        neighbor.alive_neighbors_count = 0;
        // Check grid borders
        if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= 312 || neighbor.y >= 192)
            continue;
        
        check_neighbor(cell, &neighbor);
    }
}

 static void check_neighbor(cell* current_alive, cell* neighbor) {
    int i;
    cell* cell;
    
    for (i = 0; i < alive_cells.count; i++) {
        cell = ca_at(&alive_cells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            current_alive->alive_neighbors_count++;
            return;
        }
    }

    for (i = 0; i < neighboring_dead_cells.count; i++) {
        cell = ca_at(&neighboring_dead_cells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            cell->alive_neighbors_count++;
            return;
        }
    }

    neighbor->alive_neighbors_count++;
    ca_pushback(&neighboring_dead_cells, neighbor);
}

static void initializecells(void) {
    int i;
    ca_init(&alive_cells, INITIAL_CELL_COUNT);
    ca_init(&neighboring_dead_cells, 1);
    ca_init(&newly_dead_cells, 1);
    
    for (i = 0; i < INITIAL_CELL_COUNT; i++) {
        cell cell;
        cell.x = initial_states[i][0];
        cell.y = initial_states[i][1];
        cell.width = CELL_WIDTH;
        cell.height = CELL_HEIGHT;
        cell.color = CELL_COLOR;
        cell.alive_neighbors_count = 0;

        ca_pushback(&alive_cells, &cell);
    }
}
 
void main(void) {
    is_running = 1;

    rnd_init();
    kb_init();

    initializecells();
    
    while (is_running) {
        process_input();
        update();
        render();
    }

    caF_free(&alive_cells);
    caF_free(&neighboring_dead_cells);
    caF_free(&newly_dead_cells);

    rnd_exit();
    kb_exit();
}


