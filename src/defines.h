#ifndef DEFINES_H
#define DEFINES_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>

#define GAME_WIDTH 1680
#define GAME_HEIGHT 1050
#define GAME_WHRATIO 1.6

extern uint32_t screen_w;
extern uint32_t screen_h;
extern double dt;
extern bool black_stripes;
extern Rectangle display;

int8_t SLUG_GlobalVarInit();
int8_t SLUG_GraphicInit();

extern Vector2 Vector2_0;

#endif
