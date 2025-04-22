#include "defines.h"

uint32_t screen_w;
uint32_t screen_h;
double dt;

int8_t SLUG_GlobalVarInit()
{
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();

    return 0;
}
