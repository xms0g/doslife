#ifndef KEYBOARD_H
#define KEYBOARD_H

#define R_ARROW     0x4D
#define L_ARROW     0x4B
#define ESC         0x01

void kb_init(void);

void kb_exit(void);

unsigned char kb_hit(void);

#endif

