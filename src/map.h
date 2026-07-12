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

#define MAX_PLACED_SPRITES 1024
#define MAX_SPRITES 128

#define MAX_MAP_CHAR 256

typedef struct SLUG_PlacableSprite SLUG_PlacableSprite; //same as in SLUGmaker
struct SLUG_PlacableSprite
{
	int16_t sprite_index;
	Rectangle zone;
};

typedef struct SLUG_Map SLUG_Map;
struct SLUG_Map
{
    uint32_t w; 
    uint32_t h;

    int16_t loaded_sprites_nb;
    Texture2D *fixed_sprites;
    int16_t sprite_nb;
    SLUG_PlacableSprite *sprites;
    
    SLUG_BSPTree* player_BSP;
    
    Vector2 player_spawn;
};

SLUG_Map* SLUG_LoadMapDev();
SLUG_Map* SLUG_LoadMap(const char *loadMap);
void SLUG_MapUnload(SLUG_Map *map);

#endif
