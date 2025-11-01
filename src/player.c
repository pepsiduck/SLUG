#include <raylib.h>
#include <math.h>
#include "player.h"
#include "defines.h"
#include "collisions.h"


float gravity = -10.0f;
float ground_drag = 3.5f;

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
    player->speed = 1000.0f;
    player->hitbox.x = 236;
    player->hitbox.y = 236;
    player->hitbox.width = 128;
    player->hitbox.height = 128;
    player->velocity = (Vector2) {.x = 0.0f, .y = 0.0f};
    
    player->accel = 8.0f;
    player->airstrafe_speed = 0.7f;
    player->jmp_speed = 3.75f;
    player->bhop_speed_limit = 2500.0f;
    
    player->z_speed = 0.0f;
    player->z = 0.0f;
    
    player->sprite_box[0] = player->hitbox;
    player->sprite_box[1] = (Rectangle) {
        .x = player->sprite_box[0].x,
        .y = 348,
        .width = 128,
        .height = 16
    };

    player->airborne_shadow = LoadTexture("assets/dev_shadow.png");

    player->state = IDLE;
    player->anims[IDLE] = SLUG_AnimationLoad("assets/dev_player.png", &(player->sprite_box[0]), 1, 0);
    player->anims[WALKING_RIGHT] = SLUG_AnimationLoad("assets/dev_walking.png", &(player->sprite_box[0]), 6, 0.1);
    player->anims[WALKING_LEFT] = SLUG_AnimationHorizontalFlip(player->anims[WALKING_RIGHT], &(player->sprite_box[0]));
    player->anims[JUMPING_RIGHT] = SLUG_AnimationLoad("assets/dev_jump.png", &(player->sprite_box[0]), 1, 0);
    player->anims[FALLING_RIGHT] = SLUG_AnimationLoad("assets/dev_fall.png", &(player->sprite_box[0]), 1, 0);
    player->anims[JUMPING_LEFT] = SLUG_AnimationHorizontalFlip(player->anims[JUMPING_RIGHT], &(player->sprite_box[0]));
    player->anims[FALLING_LEFT] = SLUG_AnimationHorizontalFlip(player->anims[FALLING_RIGHT], &(player->sprite_box[0]));
    SLUG_AnimStartPlay(player->anims[player->state]);
    
    return player;
}

void SLUG_PlayerUnload(SLUG_Player *player)
{
    if(player != NULL)
    {
        SLUG_AnimationUnload(player->anims[IDLE]);
        SLUG_AnimationUnload(player->anims[WALKING_RIGHT]);
        SLUG_AnimationUnload(player->anims[WALKING_LEFT]);
        SLUG_AnimationUnload(player->anims[JUMPING_RIGHT]);
        SLUG_AnimationUnload(player->anims[FALLING_RIGHT]);
        SLUG_AnimationUnload(player->anims[JUMPING_LEFT]);
        SLUG_AnimationUnload(player->anims[FALLING_LEFT]);
        UnloadTexture(player->airborne_shadow);
        free(player);
    }
}

int8_t SLUG_PlayerChangeState(SLUG_Player *player, SLUG_PlayerState state, bool samereset)
{
	if(player == NULL)
		return -1;
	if(player->state == state && !samereset)
		return 0;
	SLUG_AnimStopPlay(player->anims[player->state]);
	player->state = state;
	SLUG_AnimStartPlay(player->anims[player->state]);
	return 0;
}

int8_t SLUG_PlayerJump(SLUG_Player *player)
{
	if(player == NULL)
		return -1;
	if(IsKeyPressed(KEY_SPACE))
	{
		if(player->z > 0.0f)
			return 0;
		player->z_speed = player->jmp_speed;
	}
	return 0;
}

int8_t SLUG_PlayerGravity(SLUG_Player *player)
{
	if(player == NULL)
		return -1;
		
	player->z += player->z_speed * dt;
	if(player->z <= 0.0f)
	{
		player->z = 0.0f;
		player->z_speed = 0.0f;
		return 0;
	}
	
	if(player->z > 0.0f)
		player->z_speed += gravity * dt;
	
	return 0;
}

int8_t SLUG_GetMove(SLUG_Player *player, Vector2 *v)
{
    if(player == NULL || v == NULL)
        return -1;
    v->x = 0;
    v->y = 0;

    if(IsKeyDown(KEY_A))
        v->x += -1; 
    if(IsKeyDown(KEY_D))
        v->x += 1;
    if(IsKeyDown(KEY_W))
        v->y += -1;
    if(IsKeyDown(KEY_S))
        v->y += 1;
        
    *v = Vector2Normalize(*v);
    return 0;
}

int8_t SLUG_PlayerGroundAccelerate(SLUG_Player *player, Vector2 *wishdir)
{
    if(player == NULL || wishdir == NULL)
        return -1;
    
    float addspeed = player->speed - Vector2Length(player->velocity);//Vector2DotProduct(player->velocity, *wishdir);   
    if(addspeed <= 0)
        return 0;
    float accelspeed = player->accel * dt * player->speed;
    if(accelspeed > addspeed)
        accelspeed = addspeed;

    player->velocity.x += accelspeed*wishdir->x;
    player->velocity.y += accelspeed*wishdir->y;

    return 0;
}

int8_t SLUG_PlayerAirAccelerate(SLUG_Player *player, Vector2 *wishdir)
{
    if(player == NULL || wishdir == NULL)
        return -1;

    if(player == NULL || wishdir == NULL)
        return -1;
    
    float addspeed;
    float speed = Vector2Length(player->velocity);
    if(speed < player->bhop_speed_limit)
        addspeed = player->speed - Vector2DotProduct(player->velocity, *wishdir);
    else
        addspeed = player->speed - speed;
    if(addspeed <= 0)
        return 0;

    float accelspeed = player->accel * dt * player->speed;
    if(accelspeed > addspeed)
        accelspeed = addspeed;

    player->velocity.x += player->airstrafe_speed*accelspeed*wishdir->x;
    player->velocity.y += player->airstrafe_speed*accelspeed*wishdir->y;

    return 0;
}

int8_t SLUG_PlayerDash(SLUG_Player *player, Vector2 *wishdir)
{
    if(player == NULL || wishdir == NULL)
        return -1;
    if(IsKeyPressed(KEY_E))
    {
    	float speed;
    	if(player->z <= 0)
        	speed = 3.5 * player->speed;
        else
        	speed = 1.75 * player->speed;
        player->velocity.x = speed * wishdir->x;
        player->velocity.y = speed * wishdir->y;
    }
    
    return 0;
}

int8_t SLUG_PlayerDrag(SLUG_Player *player)
{
	if(player == NULL)
		return -1;
	if(player->z > 0.0f)
		return 0;

	float speed = Vector2Length(player->velocity);
    float ctrl = speed < player->speed ? player->speed : speed;
    float new_speed = speed - ctrl * ground_drag * dt;
    if(new_speed < 0.0f)
	    new_speed = 0.0f;
    else
	    new_speed /= speed;
		    
    player->velocity.x *= new_speed;
    player->velocity.y *= new_speed;

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
    player->sprite_box[0].x = player->position.x - player->sprite_box[0].width/2;
    player->sprite_box[0].y = player->position.y - player->sprite_box[0].height/2 - 100*player->z;
    player->sprite_box[1].x = player->position.x - player->sprite_box[1].width/2;
    player->sprite_box[1].y = player->position.y + player->sprite_box[0].height*0.375;
    return 0;
}

int8_t SLUG_PlayerStateCheck(SLUG_Player *player, Vector2 wish_dir)
{
    if(player == NULL)
        return -1;

    if(player->z > 0.0)
    {
        SLUG_PlayerChangeState(player, JUMPING_RIGHT + (player->z_speed < 0.0) + ((wish_dir.x < 0.0) << 1), 0);
        return 0;
            
    }

    if(wish_dir.x != 0.0 || wish_dir.y != 0.0)
    {
        if(wish_dir.x >= 0.0)
    	    SLUG_PlayerChangeState(player, WALKING_RIGHT, 0);
        else
            SLUG_PlayerChangeState(player, WALKING_LEFT, 0);
        return 0;
    }

    SLUG_PlayerChangeState(player, IDLE, 0);

    return 0;
}

