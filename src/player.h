#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "animation.h"
#include "map.h"
#include "gun.h"

//!Mouse
typedef struct SLUG_PlayerAim SLUG_PlayerAim;
struct SLUG_PlayerAim
{
    Vector2 mouse_pos;
    float cos;
    float sin;
    Texture2D cross_hair;
    Rectangle sprite_rec;
    float radius;
};

SLUG_PlayerAim *SLUG_PlayerAimLoad(Vector2 mouse_pos, const char *loadCrosshair, Rectangle sprite_rec, float radius);
void SLUG_PlayerAimUnload(SLUG_PlayerAim *aim);

//!Player
extern float gravity;
extern float ground_drag;

typedef enum {IDLE, 
              TEA_BAG,
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
    float bhop_speed_limit;
    
    bool sliding;
    bool slam;
    
    float jmp_speed;
    float z_speed;
    float z;
    uint8_t wall_jump_nb;
    uint8_t max_wall_jump_nb;

    int32_t wall_run_index;
    float wall_run_speed_boost;

    SLUG_Animation* anims[8];
    Rectangle sprite_box[2]; //sprite size;
    SLUG_PlayerState state;

    SLUG_PlayerAim *aim;

    SLUG_HitscanGun secondary;
    SLUG_HitscanGun *active; //not malloced

    Texture2D airborne_shadow;
};

SLUG_Player* SLUG_DevPlayerLoad();
void SLUG_PlayerUnload(SLUG_Player *player);

int8_t SLUG_PlayerChangeState(SLUG_Player *player, SLUG_PlayerState state, bool samereset);
int8_t SLUG_PlayerStateCheck(SLUG_Player *player, Vector2 wish_dir);

int8_t SLUG_PlayerJump(SLUG_Player *player);
int8_t SLUG_PlayerWallJump(SLUG_Player *player, SLUG_Map *map, int32_t wall_index);
int8_t SLUG_PlayerGravity(SLUG_Player *player);

int8_t SLUG_PlayerWallRun(SLUG_Player *player, SLUG_Map *map, int32_t wall_index);

int8_t SLUG_GetMove(SLUG_Player *player, Vector2 *v);
int8_t SLUG_PlayerGroundAccelerate(SLUG_Player *player, Vector2 *wishdir);
int8_t SLUG_PlayerAirAccelerate(SLUG_Player *player, Vector2 *wishdir);
int8_t SLUG_PlayerDash(SLUG_Player *player, Vector2 *wishdir);
int8_t SLUG_PlayerDrag(SLUG_Player *player);

int8_t SLUG_PlayerCrouchAction(SLUG_Player *player);
int8_t SLUG_PlayerSlam(SLUG_Player *player);
int8_t SLUG_PlayerSlide(SLUG_Player *player);

int8_t SLUG_PlayerTranslate(SLUG_Player *player, Vector2 v);
int8_t SLUG_PlayerMove(SLUG_Player *player, SLUG_Map *map, int32_t *wall_index);

int8_t SLUG_PlayerAimUpdate(SLUG_Player *player, float ratio_x, float ratio_y, Rectangle cam_view_zone);

int8_t SLUG_PlayerFire(SLUG_Player *player, SLUG_Map *map);

#endif
