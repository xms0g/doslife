#ifndef RENDERER_H
#define RENDERER_H

void rnd_init(void);

void rnd_exit(void);

void rnd_draw_rectangle(int x, int y, int width, int height, char color);

void rnd_clear(char color);

void rnd_update_buffer(void);

#endif