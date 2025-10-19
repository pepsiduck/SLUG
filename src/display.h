#ifndef DISPLAY_H
#define DISPLAY_H

#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "player.h"
#include "animation.h"
#include "map.h"

typedef struct SLUG_Camera SLUG_Camera;
struct SLUG_Camera
{
    SLUG_Map *map;
    SLUG_Player *player;
    Rectangle view_zone; //1680 et 1050
    Rectangle *display; //zone de l'écran ou c'est affiché
    float ratio_fix_x;
    float ratio_fix_y;
    Vector2 wanted_pos;
};

void SLUG_DisplayUpdate();

int8_t SLUG_DefaultCamera(SLUG_Map *map, SLUG_Player *player, SLUG_Camera *camera);

int8_t SLUG_CameraScrolling(SLUG_Camera *cam);

int8_t SLUG_DisplaySprite(SLUG_Camera *cam, Texture2D *sprite, Rectangle *sprite_box);
int8_t SLUG_DisplayAnim(SLUG_Camera *cam, SLUG_Animation *anim);

int8_t SLUG_Display(SLUG_Camera *cam); // ptet autre part après et avec d'autres arguments

#endif
