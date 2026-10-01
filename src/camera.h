#ifndef CAMERA_H
#define CAMERA_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include "defines.h"
#include "player.h"
#include "map.h"

//!Camera
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

#endif
