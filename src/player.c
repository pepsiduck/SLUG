#include <raylib.h>
#include <math.h>
#include "player.h"
#include "defines.h"

void SLUG_PlayerMove(SLUG_Player *player)
{   
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        player->position.y -= dt*player->speed * 0.70710678118f;
        player->position.x += dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_D) && IsKeyDown(KEY_S))
    {
        player->position.y += dt*player->speed * 0.70710678118f;
        player->position.x += dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
    {
        player->position.y += dt*player->speed * 0.70710678118f;
        player->position.x -= dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_A) && IsKeyDown(KEY_W))
    {
        player->position.y -= dt*player->speed * 0.70710678118f;
        player->position.x -= dt*player->speed * 0.70710678118f;
    }
    else if(IsKeyDown(KEY_A))
        player->position.x -= dt*player->speed; 
    else if(IsKeyDown(KEY_D))
        player->position.x += dt*player->speed;
    else if(IsKeyDown(KEY_W))
        player->position.y -= dt*player->speed;
    else if(IsKeyDown(KEY_S))
        player->position.y += dt*player->speed;
}

