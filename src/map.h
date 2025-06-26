#ifndef MAP_H
#define MAP_H

#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "player.h"
#include "defines.h"
#include "collisions.h"

#define WALL_HARD 1

typedef struct SLUG_unbreakable_wall SLUG_unbreakable_wall;
struct SLUG_unbreakable_wall
{
    uint32_t flags; //up to 32
    Rectangle hitbox;
};

typedef struct SLUG_map SLUG_map;
struct SLUG_map
{
    uint32_t w; 
    uint32_t h;
    Texture2D fixed_sprite;
    SLUG_BSPTree* player_BSP;
    
};

SLUG_BSPTree* SLUG_LoadBSPTreeDev();

SLUG_map* SLUG_LoadMapDev();
void SLUG_MapUnload(SLUG_map *map);

typedef struct SLUG_camera SLUG_camera;
struct SLUG_camera
{
    SLUG_map *map;
    SLUG_Player *player;
    Rectangle camera; //1680 et 1050
    Rectangle *display; //zone de l'écran ou c'est affiché
    float ratio_fix_x;
    float ratio_fix_y;
    Vector2 wanted_pos;
};

SLUG_camera SLUG_DefaultCamera(SLUG_map *map, SLUG_Player *player);

void SLUG_CameraScrolling(SLUG_camera *cam);

int8_t SLUG_Display(SLUG_camera *cam); // ptet autre part après et avec d'autres arguments


void SLUG_PlayerMove(SLUG_Player *player, SLUG_map *map, Vector2 wantedMove, uint32_t count);

#endif
