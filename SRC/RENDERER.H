#ifndef RENDERER_H
#define RENDERER_H

void rndInit(void);

void rndExit(void);

void rndDrawRectangle(int x, int y, int width, int height, char color);

void rndClear(char color);

void rndUpdateBuffer(void);

#endif