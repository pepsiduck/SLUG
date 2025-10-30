#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "animation.h"

extern float gravity;
extern float ground_drag;

typedef enum {IDLE, 
              WALKING_RIGHT, 
              WALKING_LEFT, 
              JUMPING_RIGHT, 
              FALLING_RIGHT, 
              JUMPING_LEFT, 
              FALLING_LEFT} SLUG_PlayerState;

typedef struct SLUG_Player SLUG_Player;
struct SLUG_Player
{
    Vector2 position;
    Rectangle hitbox;
    
    float speed;
    Vector2 velocity; //not WASD 
    float accel;
    float airstrafe_speed;
    
    float jmp_speed;
    float z_speed;
    float z;

    SLUG_Animation* anims[7];
    Rectangle sprite_box[2]; //sprite size;
    SLUG_PlayerState state;

    Texture2D airborne_shadow;
};

SLUG_Player* SLUG_DevPlayerLoad();
void SLUG_PlayerUnload(SLUG_Player *player);

int8_t SLUG_PlayerChangeState(SLUG_Player *player, SLUG_PlayerState state, bool samereset);

int8_t SLUG_PlayerJump(SLUG_Player *player);
int8_t SLUG_PlayerGravity(SLUG_Player *player);

int8_t SLUG_GetMove(SLUG_Player *player, Vector2 *v);
int8_t SLUG_PlayerGroundAccelerate(SLUG_Player *player, Vector2 *wishdir);
int8_t SLUG_PlayerAirAccelerate(SLUG_Player *player, Vector2 *wishdir);
int8_t SLUG_PlayerDash(SLUG_Player *player, Vector2 *wishdir);
int8_t SLUG_PlayerDrag(SLUG_Player *player);

int8_t SLUG_PlayerTranslate(SLUG_Player *player, Vector2 v);

int8_t SLUG_PlayerStateCheck(SLUG_Player *player, Vector2 wish_dir);

#endif
