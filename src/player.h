#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct SLUG_Player SLUG_Player;
struct SLUG_Player
{
    Vector2 position;
    Rectangle hitbox;
    Rectangle bounding_box; //sprite size;
    float speed;

    Texture2D sprite;
};

SLUG_Player* SLUG_DevPlayerLoad();
void SLUG_PlayerUnload(SLUG_Player *player);

Vector2 SLUG_WantedMove(SLUG_Player *player);

void SLUG_PlayerTranslate(SLUG_Player *player, Vector2 v);

#endif
