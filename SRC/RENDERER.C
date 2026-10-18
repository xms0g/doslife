#include "renderer.h"
#include "vga.h"

void rnd_init(void) {
    vga_init();
}

void rnd_exit(void) {
    vga_exit();
}

void rnd_draw_rectangle(int x, int y, int width, int height, char color) {
    int i,j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            vga_put_pixel(x + i, y + j, color);
        }
    }
}

void rnd_clear(char color) {
    vga_clr_offscreen(color);
}

void rnd_update_buffer(void) {
    vga_update_vram();
}