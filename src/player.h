#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

extern float gravity;
extern float ground_drag;

typedef struct SLUG_Player SLUG_Player;
struct SLUG_Player
{
    Vector2 position;
    Rectangle hitbox;
    
    float speed;
    
    Vector2 velocity; //not WASD 
    float jmp_speed;
    float z_speed;
    float z;

    Texture2D sprite;
    Rectangle bounding_box; //sprite size;
};

SLUG_Player* SLUG_DevPlayerLoad();
void SLUG_PlayerUnload(SLUG_Player *player);

int8_t SLUG_GetMove(SLUG_Player *player, Vector2 *v);

int8_t SLUG_PlayerJump(SLUG_Player *player);
int8_t SLUG_PlayerGravity(SLUG_Player *player);

int8_t SLUG_PlayerDrag(SLUG_Player *player);

int8_t SLUG_PlayerTranslate(SLUG_Player *player, Vector2 v);

#endif
