#include <raylib.h>
#include <math.h>
#include "player.h"
#include "defines.h"
#include "collisions.h"

SLUG_PlayerAim *SLUG_PlayerAimLoad(Vector2 mouse_pos, const char *loadCrosshair, Rectangle sprite_rec, float radius)
{
    SLUG_PlayerAim *aim = (SLUG_PlayerAim *) malloc(sizeof(SLUG_PlayerAim));
    if(aim == NULL)
        return NULL;

    aim->mouse_pos = mouse_pos;
    aim->cos = 0.0f;
    aim->sin = 1.0f;

    aim->cross_hair = LoadTexture(loadCrosshair);
    if(aim->cross_hair.id <= 0)
    {
        printf("Error while loading crosshair.\n");
        free(aim);
        return NULL;
    }

    aim->sprite_rec = sprite_rec;
    aim->radius = radius;

    return aim;
}

void SLUG_PlayerAimUnload(SLUG_PlayerAim *aim)
{
    if(aim != NULL)
    {
        UnloadTexture(aim->cross_hair);
        free(aim);
    }
}

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
    
    player->accel = 8.0f;
    player->airstrafe_speed = 0.7f;
    player->jmp_speed = 3.75f;
    player->bhop_speed_limit = 2500.0f;
    
    player->sliding = false;
    player->slam = false;
    
    player->z_speed = 0.0f;
    player->z = 0.0f;
    
    player->wall_jump_nb = 0;
    player->max_wall_jump_nb = 5;

    player->wall_run_index = -1;
    player->wall_run_speed_boost = 1.5f;
    
    player->sprite_box[0] = player->hitbox;
    player->sprite_box[1] = (Rectangle) {
        .x = player->sprite_box[0].x,
        .y = 348,
        .width = 128,
        .height = 16
    };

    player->aim = SLUG_PlayerAimLoad((Vector2) {.x = 0, .y = 0}, "assets/dev_crosshair.png", (Rectangle) {.x = -20, .y = -20, .width = 40, .height = 40}, 200.0f);

    player->secondary = SLUG_DevShotgun();
    player->active = &(player->secondary);

    char buffer[256];

    player->airborne_shadow = LoadTexture(SLUG_GetFilePath("assets/dev_shadow.png",buffer));

    player->state = IDLE;
    player->anims[IDLE] = SLUG_AnimationLoad(SLUG_GetFilePath("assets/dev_player.png",buffer), &(player->sprite_box[0]), 1, 0);
    player->anims[TEA_BAG] = SLUG_AnimationLoad(SLUG_GetFilePath("assets/dev_player_tea_bag.png",buffer), &(player->sprite_box[0]), 1, 0);
    player->anims[WALKING_RIGHT] = SLUG_AnimationLoad(SLUG_GetFilePath("assets/dev_walking.png",buffer), &(player->sprite_box[0]), 6, 0.1);
    player->anims[WALKING_LEFT] = SLUG_AnimationHorizontalFlip(player->anims[WALKING_RIGHT], &(player->sprite_box[0]));
    player->anims[JUMPING_RIGHT] = SLUG_AnimationLoad(SLUG_GetFilePath("assets/dev_jump.png",buffer), &(player->sprite_box[0]), 1, 0);
    player->anims[FALLING_RIGHT] = SLUG_AnimationLoad(SLUG_GetFilePath("assets/dev_fall.png",buffer), &(player->sprite_box[0]), 1, 0);
    player->anims[JUMPING_LEFT] = SLUG_AnimationHorizontalFlip(player->anims[JUMPING_RIGHT], &(player->sprite_box[0]));
    player->anims[FALLING_LEFT] = SLUG_AnimationHorizontalFlip(player->anims[FALLING_RIGHT], &(player->sprite_box[0]));
    SLUG_AnimStartPlay(player->anims[player->state]);
    
    return player;
}

void SLUG_PlayerUnload(SLUG_Player *player)
{
    if(player != NULL)
    {
        SLUG_PlayerAimUnload(player->aim);

        SLUG_AnimationUnload(player->anims[IDLE]);
        SLUG_AnimationUnload(player->anims[TEA_BAG]);
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

int8_t SLUG_PlayerStateCheck(SLUG_Player *player, Vector2 wish_dir)
{
    if(player == NULL)
        return -1;

    if(player->z > 0.0)
    {
        if(player->z_speed < 0.0)
        {
            if(wish_dir.x < 0.0)
                SLUG_PlayerChangeState(player, FALLING_LEFT, 0);
            else
                SLUG_PlayerChangeState(player, FALLING_RIGHT, 0);
        }
        else
        {
            if(wish_dir.x < 0.0)
                SLUG_PlayerChangeState(player, JUMPING_LEFT, 0);
            else
                SLUG_PlayerChangeState(player, JUMPING_RIGHT, 0);
        }
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

    SLUG_PlayerChangeState(player, IsKeyDown(KEY_LEFT_CONTROL) ? TEA_BAG : IDLE, 0);

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

int8_t SLUG_PlayerWallJump(SLUG_Player *player, SLUG_Map *map, int32_t wall_index)
{
    if(player == NULL || map == NULL)
		return -1;
    if(wall_index < 0 && player->wall_run_index == -1)
        return 0;
    if(player->z > 0.0f && player->wall_jump_nb < player->max_wall_jump_nb)
    {
        if(IsKeyPressed(KEY_SPACE))
	    {
            player->z_speed = player->jmp_speed;

            Vector2 normal = wall_index >= 0 ? map->player_BSP->tab[wall_index].normal : map->player_BSP->tab[player->wall_run_index].normal;
            float player_velocity = (player->speed + fmax(abs(Vector2DotProduct(player->velocity, normal)) - player->speed, 0.0f));

            player->velocity = wall_index >= 0 ? Vector2Scale(normal, player_velocity) : Vector2Add(player->velocity, Vector2Scale(normal, player_velocity));
    
            player->wall_jump_nb++;
            player->wall_run_index = -1;

            return 1;
        }
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

        player->wall_jump_nb = 0;
        
        player->slam = false;
		return 0;
	}
	
	if(player->z > 0.0f)
		player->z_speed += gravity * dt;
	
	return 0;
}

int8_t SLUG_PlayerWallRun(SLUG_Player *player, SLUG_Map *map, int32_t wall_index)
{
    if(player == NULL || map == NULL)
		return -1;
    if(wall_index < 0 && player->wall_run_index == -1)
        return 0;

    if(player->wall_run_index == -1)
    {
        if(player->z >= 0.25f)
        {

            Vector2 normal = map->player_BSP->tab[wall_index].normal;
            if(abs(Vector2DotProduct(normal, player->velocity)) < 0.8f * Vector2Length(player->velocity))
            {
                player->wall_run_index = wall_index;

                float player_velocity = (player->speed + fmax(Vector2Length(player->velocity) * (1.0f - abs(Vector2DotProduct(player->velocity, normal))) - player->speed, 0.0f));

                Vector2 new_vel = Vector2Scale((Vector2){
                    .x = -normal.y * player_velocity,
                    .y =  normal.x * player_velocity
                }, player->wall_run_speed_boost);

                if(Vector2DotProduct(new_vel, player->velocity) >= 0.0f)
                    player->velocity = new_vel;
                else
                    player->velocity = Vector2Scale(new_vel, -1.0f);
            }    
        }
    }
    else
    {
        if(wall_index != -1 && wall_index != player->wall_run_index)
            player->wall_run_index = -1;
        else    
        {
            SLUG_SegmentExtended wall = map->player_BSP->tab[player->wall_run_index];

            if(DistanceToSegment(wall.A, wall.B, player->position) > 2.0f * DIST_EPSILON)
                player->wall_run_index = -1;
        }
    }

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
        
    if(player->sliding)
        return 0;
    
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

    if(player->sliding)
        return 0;
    
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
        	speed = 3.0 * player->speed;
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
	if(player->sliding)
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

int8_t SLUG_PlayerCrouchAction(SLUG_Player *player)
{
    if(player == NULL)
        return -1;
        
    if(player->z > 0.0f)
        return SLUG_PlayerSlam(player);
    float s = Vector2Length(player->velocity);
    if(s > player->speed)
        return SLUG_PlayerSlide(player);
    return 0;
}

int8_t SLUG_PlayerSlam(SLUG_Player *player)
{
    if(player == NULL)
        return -1;
        
    if(IsKeyPressed(KEY_LEFT_CONTROL) && !player->slam)  
    {
        player->slam = true;  
        player->z_speed = -3*player->jmp_speed;
    }    
    return 0;
}

int8_t SLUG_PlayerSlide(SLUG_Player *player)
{
    if(player == NULL)
        return -1;

    player->sliding = IsKeyDown(KEY_LEFT_CONTROL);
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

int8_t SLUG_PlayerMove(SLUG_Player *player, SLUG_Map *map, int32_t *wall_index)
{   
    if(player == NULL || map == NULL)
        return -1;

    Vector2 move = (Vector2) {
        .x = player->velocity.x * dt,
        .y = player->velocity.y * dt
    };

    if(map->player_BSP == NULL)
        return SLUG_PlayerTranslate(player, move);

    Vector2 intersection;
    Vector2 p2 = (Vector2) {
        .x = player->position.x + move.x,
        .y = player->position.y + move.y
    };
    for(uint32_t i = 0; i < (map->player_BSP->tab_size >> 3) + ((map->player_BSP->tab_size & 7) != 0); ++i)
        map->player_BSP->elements_passed[i] = 0;
    
    int8_t err = SLUG_RecursiveCollisionCheck(0, player->position, p2, map->player_BSP,&intersection);

    if(err == 1)
    {
        Vector2 v = (Vector2) {
            .x = intersection.x - player->position.x,
            .y = intersection.y - player->position.y
        };
        SLUG_PlayerTranslate(player, v);

        int32_t index = -1;
        
        for(int32_t i = 0; i < map->player_BSP->tab_size; ++i)
        {
            if(map->player_BSP->elements_passed[(i >> 3)] & (1 << (i & 7))) // check si on est passé
            {
                if(Vector2DotProduct(map->player_BSP->tab[i].normal, move) < 0) //Si je rentre dans le mur
                {
                    if(SLUG_CheckCollisionPointLine(intersection, map->player_BSP->tab[i].A, map->player_BSP->tab[i].B, 2*DIST_EPSILON)) // Si c'est le bon segment
                    {
                        index = i;
                        break;
                    }
                }
            }  
        }

        if(index == -1)
            return 0;

        if(wall_index != NULL)
            *wall_index = index;

        v = (Vector2) {
            .x =  -1* map->player_BSP->tab[index].normal.y * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y)) + player->position.x,
            .y =  map->player_BSP->tab[index].normal.x * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y)) + player->position.y
        };
        
        err = SLUG_RecursiveCollisionCheck(0, player->position, v, map->player_BSP,&intersection);
        if(err == 1)
        {
            v = (Vector2) {
                .x = intersection.x - player->position.x,
                .y = intersection.y - player->position.y
            };
        }
        else if(err == 0)
        {
            v.x -= player->position.x;
            v.y -= player->position.y;
        }
        else
            return err;

        if(SLUG_PlayerTranslate(player, v) < 0)
            return -1;
        return 1;
    }
    else if(err == 0)
        return SLUG_PlayerTranslate(player, move);
    else if(err < 0)
        return err;

    return 0;

}

int8_t SLUG_PlayerAimUpdate(SLUG_Player *player, float ratio_x, float ratio_y, Rectangle cam_view_zone)
{
    if(player == NULL)
        return -1;
        
    if(player->aim == NULL)
        return -1;
    
    Vector2 mouse = GetMousePosition();
    
    SLUG_PlayerAim *aim = player->aim;
    Vector2 *mouse_pos = &(aim->mouse_pos);
    
    *mouse_pos = NearestPointOnCircle(mouse, display_center, fmin(ratio_x, ratio_y) * aim->radius);
    SetMousePosition((int) mouse_pos->x, (int) mouse_pos->y);
    
    Vector2 player_display_pos = (Vector2) {.x = (player->position.x - cam_view_zone.x) * ratio_x, .y = (player->position.y - cam_view_zone.y) * ratio_y};
    Vector2 spr_pos =  NearestPointOnRect(Vector2Add(Vector2Subtract(*mouse_pos, display_center), player_display_pos), display);
    
    aim->sprite_rec.x = spr_pos.x - aim->sprite_rec.width / 2.f;
    aim->sprite_rec.y = spr_pos.y - aim->sprite_rec.height / 2.f;
    
    Vector2 line = Vector2Subtract(spr_pos, player_display_pos);
    float hyp = Vector2Length(line);
    aim->cos = line.x / hyp;
    aim->sin = line.y / hyp;

    return 0;
}

int8_t SLUG_PlayerFire(SLUG_Player *player, SLUG_Map *map)
{
    if(player == NULL || map == NULL)
        return -1;

    if(player->active == NULL)
        return 0;

    SLUG_Gun *gun = player->active;

    if(gun->clip > 0)
    {
        float time = (float) GetTime();
        if(time > gun->time_last_fire + gun->firing_time)
        {
            SLUG_Hitscan shot = gun->hitscan;

            for(uint8_t i = 0; i < shot.nb; ++i)
            {
                Vector2 B = (Vector2) {.x = shot.range, .y = shot.random_spread ? Rand_uniform(-shot.spread_range, shot.spread_range) : shot.spread_range*(-1.f + i * (2.f / ((float) (shot.nb - 1))))};

                Vector2 rotB;
                rotB.x = B.x * player->aim->cos - B.y * player->aim->sin;
                rotB.y = B.x * player->aim->sin + B.y * player->aim->cos;
                B = rotB;

                Vector2 A = player->position;
                B = Vector2Add(A, B);

                Vector2 intersection;
                if(SLUG_RecursiveCollisionCheck(0, A, B, map->player_BSP, &intersection))
                    B = intersection;

                //do stuff

    
            }

            gun->time_last_fire = time;
            gun->clip--;
        }
    }

    return 0;
}
