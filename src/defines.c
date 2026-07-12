#include "defines.h"

double dt;

uint32_t screen_w;
uint32_t screen_h;
bool black_stripes;
Rectangle display;

char working_dir[256];

Vector2 Vector2_0;

Texture2D missing_texture;

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

    char buffer[256];

    missing_texture = LoadTexture(SLUG_GetFilePath("assets/sprites/missing.jpg", buffer));
    if(missing_texture.id <= 0)
        return -1;

    return 0;
}

int8_t SLUG_GlobalVarFree()
{
    UnloadTexture(missing_texture);
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

int8_t RectangleEqual(Rectangle *rect1, Rectangle *rect2)
{
    if(rect1 == NULL || rect2 == NULL)
        return -1;

    return (rect1->x == rect2->x && rect1->y == rect2->y && rect1->width == rect2->width && rect1->height == rect2->height); 
}
