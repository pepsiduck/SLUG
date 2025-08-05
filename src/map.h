#ifndef MAP_H
#define MAP_H

#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "collisions.h"

typedef struct SLUG_Map SLUG_Map;
struct SLUG_Map
{
    int32_t w; 
    int32_t h;
    Texture2D fixed_sprite;
    SLUG_BSPTree* player_BSP;
    
    Vector2 player_spawn;
};

SLUG_Map* SLUG_LoadMapDev();
SLUG_Map* SLUG_LoadMap(const char *loadMap);
void SLUG_MapUnload(SLUG_Map *map);

#endif
