#include "defines.h"

uint32_t screen_w;
uint32_t screen_h;
double dt;
Vector2 Vector2_0;
bool black_stripes;
Rectangle display;

int8_t SLUG_GlobalVarInit()
{
    Vector2_0.x = 0;
    Vector2_0.y = 0;
    black_stripes = true;
    return 0;
}

int8_t SLUG_GraphicInit()
{
    screen_w = GetScreenWidth();
    screen_h = GetScreenHeight();

    if(black_stripes)
    {
        if(((float) screen_w) / ((float) screen_h) > GAME_WHRATIO)
        {
            display.width = GAME_WHRATIO*screen_h;
            display.height = screen_h;
            display.x = (screen_w - display.width) / 2;
            display.y = 0;
        }
        else
        {
            display.width = screen_w;
            display.height = screen_w / GAME_WHRATIO;
            display.y = (screen_h - display.height) / 2;
            display.x = 0;
        }
    }
    else
    {
        display.x = 0;
        display.y = 0;
        display.width = screen_w;
        display.height = screen_h;
    }
    return 0;
}


