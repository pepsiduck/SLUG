#include "defines.h"

double dt;

uint32_t screen_w;
uint32_t screen_h;
bool black_stripes;
Rectangle display;

Vector2 Vector2_0;

char working_dir[256];

int8_t SLUG_GlobalVarInit(int argc, char *argv[])
{
    Vector2_0.x = 0;
    Vector2_0.y = 0;
    black_stripes = true;

    if(strlen(argv[0]) > 255)
    {
        printf("Error : working directory string too long.\n");
        return -1;
    }

    char tmp_str[strlen(argv[0])];
    strcpy(tmp_str,argv[0]);

    size_t p = strlen(tmp_str);
    while(p >= 0 && tmp_str[p-1] != '/')
        p--;
    tmp_str[p] = '\0';

    if(strcmp(tmp_str,"./") == 0)
        strcpy(working_dir,"");
    else
        strcpy(working_dir,tmp_str);

    printf("%s\n",working_dir);
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

char* SLUG_GetFilePath(char path[], char buffer[])
{
    strcpy(buffer,working_dir);
    strcat(buffer, path);
    return buffer;
}
