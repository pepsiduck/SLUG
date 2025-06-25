#ifndef DEFINES_H
#define DEFINES_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>

extern uint32_t screen_w;
extern uint32_t screen_h;
extern double dt;
extern bool black_stripes;
extern Rectangle display;


int8_t SLUG_GlobalVarInit();
int8_t SLUG_GraphicInit();

void SLUG_DisplayUpdate();

extern Vector2 Vector2_0;

#endif
