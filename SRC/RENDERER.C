#include "renderer.h"
#include "vga.h"

void rndInit(void) {
    vgaInit();
}

void rndExit(void) {
    vgaExit();
}

void rndDrawRectangle(int x, int y, int width, int height, char color) {
    int i,j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            vgaPutPixel(x + i, y + j, color);
        }
    }
}

void rndClear(char color) {
    vgaClearOffscreen(color);
}

void rndUpdateBuffer(void) {
    vgaUpdateVram();
}