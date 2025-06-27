#include "map.h"
#include "defines.h"

SLUG_Map* SLUG_LoadMapDev(SLUG_Player *player)
{
    SLUG_Map *map = (SLUG_Map*) malloc(sizeof(SLUG_Map));
    if(map == NULL)
        return NULL;
    map->fixed_sprite = LoadTexture("assets/dev_map.jpg");
    map->w = 4011;
    map->h = 3330;
    map->player_BSP = SLUG_LoadBSPTreeDev();
    map->player = player;
    return map;
}

void SLUG_MapUnload(SLUG_Map *map)
{
    UnloadTexture(map->fixed_sprite);
    SLUG_BSTTreeUnload(map->player_BSP);
    free(map);
}


