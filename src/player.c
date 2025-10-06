#include <raylib.h>
#include <math.h>
#include "player.h"
#include "defines.h"
#include "collisions.h"

float gravity = -10.0f;
float ground_drag = 4.0f;

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
    player->accel = 9.0f;
    player->airstrafe_speed = 2.35f;
    player->jmp_speed = 3.75f;
    player->z_speed = 0.0f;
    player->z = 0.0f;
    player->sprite = LoadTexture("assets/dev_player.png");
    player->bounding_box = player->hitbox;
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

    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
    {
        v->y = -0.70710678118f;
        v->x = 0.70710678118f;
    }
    else if(IsKeyDown(KEY_D) && IsKeyDown(KEY_S))
    {
        v->y = 0.70710678118f;
        v->x = 0.70710678118f;
    }
    else if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
    {
        v->y = 0.70710678118f;
        v->x = -0.70710678118f;
    }
    else if(IsKeyDown(KEY_A) && IsKeyDown(KEY_W))
    {
        v->y = -0.70710678118f;
        v->x = -0.70710678118f;
    }
    else if(IsKeyDown(KEY_A))
        v->x = -1; 
    else if(IsKeyDown(KEY_D))
        v->x = 1;
    else if(IsKeyDown(KEY_W))
        v->y = -1;
    else if(IsKeyDown(KEY_S))
        v->y = 1;
        
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

    float crossproduct = (player->velocity.x * wishdir->y) - (player->velocity.y * wishdir->x);
    if(crossproduct == 0.0)
    {
    	if(Vector2DotProduct(player->velocity, *wishdir) < 0)
    	{
    		player->velocity.x = 0;
    		player->velocity.y = 0;
    	}
    }
    else
    {
    	float angle = crossproduct > 0 ? player->airstrafe_speed * dt : -1.0f * player->airstrafe_speed * dt;
    	player->velocity = (Vector2) {
    		.x = player->velocity.x - angle * player->velocity.y,
    		.y = angle * player->velocity.x + player->velocity.y
    	};
    	if(crossproduct * ((player->velocity.x * wishdir->y) - (player->velocity.y * wishdir->x)) < 0)
			player->velocity = Vector2Scale(*wishdir, Vector2Length(player->velocity));
		else
			player->velocity = Vector2Scale(player->velocity, (1 + 0.4f * dt));
    }
    
    return 0;
}

int8_t SLUG_PlayerDash(SLUG_Player *player, Vector2 *wishdir)
{
    if(player == NULL || wishdir == NULL)
        return -1;
    if(IsKeyPressed(KEY_E))
    {
        float speed = 4 * player->speed;
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
		
	float speed = Vector2Length(player->velocity);//player->velocity.x * player->velocity.x + player->velocity.y * player->velocity.y;
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
    player->bounding_box.x += v.x;
    player->bounding_box.y += v.y;
    return 0;
}


