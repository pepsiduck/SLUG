#include "player.h"
#include "defines.h"

void SLUG_PlayerMove(SLUG_Player *player)
{
    player->position.x += dt*player->speed; 
}

