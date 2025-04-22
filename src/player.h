#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <raylib.h>

typedef struct SLUG_Player SLUG_Player;
struct SLUG_Player
{
    Vector2 position;
    float speed;
};

void SLUG_PlayerMove(SLUG_Player *player);

#endif
