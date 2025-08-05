#include <raylib.h>
#include <math.h>
#include "player.h"
#include "defines.h"
#include "collisions.h"

SLUG_Player* SLUG_DevPlayerLoad()
{
    SLUG_Player *player = (SLUG_Player *) malloc(sizeof(SLUG_Player));
    if(player == NULL)
    {
        printf("Malloc error\n");
        return NULL;
    }
    player->position.x = 300.0f;
    player->position.y = 300.0f;
    player->speed = 500.0f;
    player->hitbox.x = 236;
    player->hitbox.y = 236;
    player->hitbox.width = 128;
    player->hitbox.height = 128;
    player->bounding_box = player->hitbox;
    player->sprite = LoadTexture("assets/dev_player.png");
    return player;
}

void SLUG_PlayerUnload(SLUG_Player *player)
{
    if(player != NULL)
    {
        UnloadTexture(player->sprite);
        free(player);
    }
}

int8_t SLUG_WantedMove(SLUG_Player *player, Vector2 *v)
{
    if(player == NULL || v == NULL)
        return -1;
    v->x = 0;
    v->y = 0;
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        v->y = -dt*player->speed * 0.70710678118f;
        v->x = dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_D) && IsKeyDown(KEY_S))
    {
        v->y = dt*player->speed * 0.70710678118f;
        v->x = dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
    {
        v->y = dt*player->speed * 0.70710678118f;
        v->x = -dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_A) && IsKeyDown(KEY_W))
    {
        v->y = -dt*player->speed * 0.70710678118f;
        v->x = -dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_A))
        v->x = -dt*player->speed; 
    else if(IsKeyDown(KEY_D))
        v->x = dt*player->speed;
    else if(IsKeyDown(KEY_W))
        v->y = -dt*player->speed;
    else if(IsKeyDown(KEY_S))
        v->y = dt*player->speed;
    return 0;
}

int8_t SLUG_PlayerTranslate(SLUG_Player *player, Vector2 v)
{
    if(player == NULL)
        return -1;
    player->position.x += v.x;
    player->position.y += v.y;
    player->hitbox.x += v.x;
    player->hitbox.y += v.y;
    player->bounding_box.x += v.x;
    player->bounding_box.y += v.y;
    return 0;
}


