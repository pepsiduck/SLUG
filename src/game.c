#include "game.h"
#include "collisions.h"

int8_t SLUG_PlayerMove(SLUG_Player *player, SLUG_Map *map)
{   
    if(player == NULL || map == NULL)
        return -1;

    Vector2 move = (Vector2) {
        .x = player->velocity.x * dt,
        .y = player->velocity.y * dt
    };

    if(map->player_BSP == NULL)
        return SLUG_PlayerTranslate(player, move);

    Vector2 intersection;
    Vector2 p2 = (Vector2) {
        .x = player->position.x + move.x,
        .y = player->position.y + move.y
    };
    for(uint32_t i = 0; i < (map->player_BSP->tab_size >> 3) + ((map->player_BSP->tab_size & 7) != 0); ++i)
        map->player_BSP->elements_passed[i] = 0;
    
    int8_t err = SLUG_RecursiveCollisionCheck(0, player->position, p2, map->player_BSP,&intersection);

    if(err == 1)
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
                if(Vector2DotProduct(map->player_BSP->tab[i].normal, move) < 0) //Si je rentre dans le mur
                {
                    if(SLUG_CheckCollisionPointLine(intersection, map->player_BSP->tab[i].A, map->player_BSP->tab[i].B, 2*DIST_EPSILON)) // Si c'est le bon segment
                    {
                        printf("%d\n",i);
                        index = i;
                        break;
                    }
                }
            }  
        }

        if(index == -1)
            return 0;

        v = (Vector2) {
            .x =  -1* map->player_BSP->tab[index].normal.y * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y)) + player->position.x,
            .y =  map->player_BSP->tab[index].normal.x * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y)) + player->position.y
        };
        
        err = SLUG_RecursiveCollisionCheck(0, player->position, v, map->player_BSP,&intersection);
        if(err == 1)
        {
            v = (Vector2) {
                .x = intersection.x - player->position.x,
                .y = intersection.y - player->position.y
            };
        }
        else if(err == 0)
        {
            v.x -= player->position.x;
            v.y -= player->position.y;
        }
        else
            return err;
        return SLUG_PlayerTranslate(player, v);
    }
    else if(err == 0)
        return SLUG_PlayerTranslate(player, move);
    else if(err < 0)
        return err;

    return 0;

}
