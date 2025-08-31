#include "renderer.h"
#include "keybrd.h"
#include "states.h"
#include "cell.h"

static int isRunning;
static CellArray aliveCells;
static CellArray neighboringDeadCells;
static CellArray newlyDeadCells;

static void processNeighbors(Cell* cell);
static void checkNeighbor(Cell* currentAlive, Cell* neighbor);

static void processInput(void) {
    char key = kbHit();

    if (key == ESC) {
        isRunning = 0;
    }
}

static void update(void) {
    int i,j;
    Cell* cell;
        
    for (i = 0; i < aliveCells.count; i++) {
        cell = caAt(&aliveCells, i);
        
        processNeighbors(cell);
            
        if (cell->aliveNeighborsCount < 2 || cell->aliveNeighborsCount > 3) {
           caPushback(&newlyDeadCells, cell);
        }
            
        cell->aliveNeighborsCount = 0;
    } 
        
    for (i = 0; i < neighboringDeadCells.count; i++) {
        cell = caAt(&neighboringDeadCells, i);
        
        if (cell->aliveNeighborsCount == 3) {
            cell->aliveNeighborsCount = 0;
            caPushback(&aliveCells, cell);
        }
    }

    for (i = 0; i < newlyDeadCells.count; i++) {
        Cell* deadCell = caAt(&newlyDeadCells, i);

        for (j = 0; j < aliveCells.count; j++) {
            Cell* aliveCell = caAt(&aliveCells, j);
            
            if (CELL_IS_SAME(deadCell, aliveCell)) {
                caRemove(&aliveCells, j);
            }
        }
    }

    caClear(&neighboringDeadCells);
    caClear(&newlyDeadCells);
}

static void render(void) {
    int i;
    Cell* cell;

    rndClear(0x0);

    for (i = 0; i < aliveCells.count; i++) {
        cell = caAt(&aliveCells, i);
        
        rndDrawRectangle(
            cell->x,
            cell->y,
            cell->width,
            cell->height,
            cell->color
        );
    }

    rndUpdateBuffer();
}

static void processNeighbors(Cell* cell) {
    int i;

    for (i = 0; i < NEIGHBOR_COUNT; i++) {
        Cell neighbor;
        neighbor.x = cell->x + neighborStates[i][0];
        neighbor.y = cell->y + neighborStates[i][1];
        neighbor.width = CELL_WIDTH;
        neighbor.height = CELL_HEIGHT;
        neighbor.color = CELL_COLOR;
        neighbor.aliveNeighborsCount = 0;
        // Check grid borders
        if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= 312 || neighbor.y >= 192)
            continue;
        
        checkNeighbor(cell, &neighbor);
    }
}

 static void checkNeighbor(Cell* currentAlive, Cell* neighbor) {
    int i;
    Cell* cell;
    
    for (i = 0; i < aliveCells.count; i++) {
        cell = caAt(&aliveCells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            currentAlive->aliveNeighborsCount++;
            return;
        }
    }

    for (i = 0; i < neighboringDeadCells.count; i++) {
        cell = caAt(&neighboringDeadCells, i);
        
        if (CELL_IS_SAME(cell, neighbor)) {
            cell->aliveNeighborsCount++;
            return;
        }
    }

    neighbor->aliveNeighborsCount++;
    caPushback(&neighboringDeadCells, neighbor);
}

static void initializeCells(void) {
    int i;
    caInit(&aliveCells, INITIAL_CELL_COUNT);
    caInit(&neighboringDeadCells, 1);
    caInit(&newlyDeadCells, 1);
    
    for (i = 0; i < INITIAL_CELL_COUNT; i++) {
        Cell cell;
        cell.x = initialStates[i][0];
        cell.y = initialStates[i][1];
        cell.width = CELL_WIDTH;
        cell.height = CELL_HEIGHT;
        cell.color = CELL_COLOR;
        cell.aliveNeighborsCount = 0;

        caPushback(&aliveCells, &cell);
    }
}
 
void main(void) {
    isRunning = 1;

    rndInit();
    kbInit();

    initializeCells();
    
    while (isRunning) {
        processInput();
        update();
        render();
    }

    caFree(&aliveCells);
    caFree(&neighboringDeadCells);
    caFree(&newlyDeadCells);

    rndExit();
    kbExit();
}


