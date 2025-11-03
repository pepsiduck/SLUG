#ifndef DEFINES_H
#define DEFINES_H

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#define GAME_WIDTH 1680
#define GAME_HEIGHT 1050
#define GAME_WHRATIO 1.6

extern double dt;

extern uint32_t screen_w;
extern uint32_t screen_h;
extern bool black_stripes;
extern Rectangle display;

extern char working_dir[256];

extern Vector2 Vector2_0;

int8_t SLUG_GlobalVarInit(int argc, char *argv[]);
int8_t SLUG_GraphicInit();

char* SLUG_GetFilePath(char path[], char buffer[]);

#endif
