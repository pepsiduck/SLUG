#ifndef MAP_H
#define MAP_H

#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "player.h"
#include "collisions.h"

typedef struct SLUG_Map SLUG_Map;
struct SLUG_Map
{
    uint32_t w; 
    uint32_t h;
    Texture2D fixed_sprite;
    SLUG_Player *player;
    SLUG_BSPTree* player_BSP;
    
};

SLUG_Map* SLUG_LoadMapDev(SLUG_Player *player);
void SLUG_MapUnload(SLUG_Map *map);




void SLUG_PlayerMove(SLUG_Player *player, SLUG_Map *map, Vector2 wantedMove);

#endif
