#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "player.h"
#include "collisions.h"
#include "map.h"

void SLUG_PlayerMove(SLUG_Player *player, SLUG_Map *map, Vector2 wantedMove)
{   
    Vector2 intersection;
    Vector2 p2 = (Vector2) {
        .x = player->position.x + wantedMove.x,
        .y = player->position.y + wantedMove.y
    };
    for(uint32_t i = 0; i < (map->player_BSP->tab_size >> 3) + ((map->player_BSP->tab_size & 7) != 0); ++i)
        map->player_BSP->elements_passed[i] = 0;
    
    if(SLUG_RecursiveCollisionCheck(0, player->position, p2, map->player_BSP,&intersection))
    {
        Vector2 v = (Vector2) {
            .x = intersection.x - player->position.x,
            .y = intersection.y - player->position.y
        };
        SLUG_PlayerTranslate(player, v);

        int32_t index = -1;
        
        for(int32_t i = 0; i < map->player_BSP->tab_size; ++i)
        {
            if(map->player_BSP->elements_passed[(i >> 3)] & (1 << (i & 7))) // check si on est passé
            {
                if(Vector2DotProduct(map->player_BSP->tab[i].normal, wantedMove) < 0) //Si je rentre dans le mur
                {
                    if(SLUG_CheckCollisionPointLine(intersection, map->player_BSP->tab[i].A, map->player_BSP->tab[i].B, 2*DIST_EPSILON)) // Si c'est le bon segment
                    {
                        index = i;
                        break;
                    }
                }
            }  
        }

        if(index == -1)
            return;

        v = (Vector2) {
            .x =  -1* map->player_BSP->tab[index].normal.y * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y)) + player->position.x,
            .y =  map->player_BSP->tab[index].normal.x * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y)) + player->position.y
        };

        if(SLUG_RecursiveCollisionCheck(0, player->position, v, map->player_BSP,&intersection))
        {
            v = (Vector2) {
                .x = intersection.x - player->position.x,
                .y = intersection.y - player->position.y
            };
        }
        else
        {
            v.x -= player->position.x;
            v.y -= player->position.y;
        }
        SLUG_PlayerTranslate(player, v);
    }
    else
        SLUG_PlayerTranslate(player, wantedMove);

}
