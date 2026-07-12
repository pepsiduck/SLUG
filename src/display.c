#include "display.h"
#include "defines.h"

void SLUG_DisplayUpdate()
{
    if(screen_w != GetScreenWidth() || screen_h != GetScreenHeight())
    {
        screen_w = GetScreenWidth();
        screen_h = GetScreenHeight();
        if(black_stripes)
        {
            if(((float) screen_w) / ((float) screen_h) > GAME_WHRATIO)
            {
                display.width = GAME_WHRATIO*screen_h;
                display.height = screen_h;
                display.x = (screen_w - display.width) / 2;
                display.y = 0;
            }
            else
            {
                display.width = screen_w;
                display.height = screen_w / GAME_WHRATIO;
                display.y = (screen_h - display.height) / 2;
                display.x = 0;
            }
        }
        else
        {
            display.x = 0;
            display.y = 0;
            display.width = screen_w;
            display.height = screen_h;
        }
    }
}

int8_t SLUG_DefaultCamera(SLUG_Map *map, SLUG_Player *player, SLUG_Camera *camera)
{
    if(map == NULL || player == NULL || camera == NULL)
    {
        if(map == NULL)
            printf("map\n");
        if(player == NULL)
            printf("player\n");
        if(camera == NULL)
            printf("camera\n");
        printf("kek\n");
        return -1;
    }

    camera->map = map;
    camera->player = player;
    camera->display = &display;
    camera->view_zone.x = 0;
    camera->view_zone.y = 0;
    camera->view_zone.width = GAME_WIDTH;
    camera->view_zone.height = GAME_HEIGHT;
    camera->wanted_pos.x = GAME_WIDTH/2;
    camera->wanted_pos.y = GAME_HEIGHT/2;
    camera->ratio_fix_x = camera->display->width / camera->view_zone.width;
    camera->ratio_fix_y = camera->display->height / camera->view_zone.height;
    return 0;
}

int8_t SLUG_CameraScrolling(SLUG_Camera *cam)
{
    if(cam == NULL)
        return -1;
    cam->view_zone.x = cam->player->position.x - cam->wanted_pos.x;
    cam->view_zone.y = cam->player->position.y - cam->wanted_pos.y;

    cam->view_zone.x = fmin(cam->view_zone.x,cam->map->w - GAME_WIDTH);
    cam->view_zone.x = fmax(cam->view_zone.x, 0.0);
    cam->view_zone.y = fmin(cam->view_zone.y,cam->map->h - GAME_HEIGHT);   
    cam->view_zone.y = fmax(cam->view_zone.y, 0.0);
    
    return 0;
}

int8_t SLUG_DisplaySprite(SLUG_Camera *cam, Texture2D *sprite, Rectangle *sprite_box)
{
	if(cam == NULL || sprite == NULL)
		return -1;
		
    if(CheckCollisionRecs(cam->view_zone, *sprite_box))
    {
        Rectangle p = GetCollisionRec(cam->view_zone, *sprite_box);
        
        Rectangle source = (Rectangle) {.x = 0, .y = 0, .width = (float) sprite->width, .height = (float) sprite->height};
        
		if(p.x - sprite_box->x != 0)
        	source.x += (p.x - sprite_box->x) * (source.width / sprite_box->width);
		if(p.y - sprite_box->y != 0)
        	source.y += (p.y - sprite_box->y) * (source.height / sprite_box->height);
		if(p.width != sprite_box->width)
			source.width *= (p.width/sprite_box->width);
		if(p.height != sprite_box->height)
			source.height *= (p.height/sprite_box->height);

        DrawTexturePro(*sprite,source,
                        (Rectangle) {.x=cam->display->x + (p.x - cam->view_zone.x)*cam->ratio_fix_x, 
                                     .y=cam->display->y + (p.y - cam->view_zone.y)*cam->ratio_fix_y, 
                                     .width=p.width * cam->ratio_fix_x, 
                                     .height=p.height * cam->ratio_fix_y} ,Vector2_0,0,WHITE);
    }
		
	return 0;
}

int8_t SLUG_DisplayAnim(SLUG_Camera *cam, SLUG_Animation *anim)
{
	if(cam == NULL || anim == NULL)
		return -1;
	if(!anim->playing)
		return 0;	
		
    if(CheckCollisionRecs(cam->view_zone, *(anim->bounding_box)))
    {
        Rectangle p = GetCollisionRec(cam->view_zone, *(anim->bounding_box));
        
        Rectangle source = anim->curr_sprite;
        
		if(p.x - anim->bounding_box->x != 0)
        	source.x += (p.x - anim->bounding_box->x) * (anim->curr_sprite.width / anim->bounding_box->width);
		if(p.y - anim->bounding_box->y != 0)
        	source.y += (p.y - anim->bounding_box->y) * (anim->curr_sprite.height / anim->bounding_box->height);
		if(p.width != anim->bounding_box->width)
			source.width *= (p.width/anim->bounding_box->width);
		if(p.height != anim->bounding_box->height)
			source.height *= (p.height/anim->bounding_box->height);

        DrawTexturePro(anim->sprite_sheet,source,
                        (Rectangle) {.x=cam->display->x + (p.x - cam->view_zone.x)*cam->ratio_fix_x, 
                                     .y=cam->display->y + (p.y - cam->view_zone.y)*cam->ratio_fix_y, 
                                     .width=p.width * cam->ratio_fix_x, 
                                     .height=p.height * cam->ratio_fix_y} ,Vector2_0,0,WHITE);
    }
		
	return 0;
}

int8_t SLUG_DisplayPlayer(SLUG_Camera *cam, SLUG_Player *player)
{
    if(cam == NULL || player == NULL)
        return -1;

    int8_t err;
    err = SLUG_DisplayAnim(cam, cam->player->anims[player->state]);
    if(err < 0)
        return err;

    if(player->z > 0.0)
    {
        err = SLUG_DisplaySprite(cam, &(player->airborne_shadow), &(player->sprite_box[1]));
        if(err < 0)
            return err;
    }

    return 0;
}

int8_t SLUG_Display(SLUG_Camera *cam) // ptet autre part après et avec d'autres arguments
{
    if(cam == NULL)
        return -1;
    
    if(cam->display->width != cam->ratio_fix_x * cam->view_zone.width)
        cam->ratio_fix_x = cam->display->width / cam->view_zone.width;  
    if(cam->display->height != cam->ratio_fix_y * cam->view_zone.height)   
        cam->ratio_fix_y = display.height / cam->view_zone.height;

    SLUG_CameraScrolling(cam);
    ClearBackground(BLACK);

    Texture2D *img_buf;
    float w, h;
    
    SLUG_PlacableSprite *spr_buffer;
    Rectangle *rec_buffer;
    int16_t index_buffer;

    Rectangle *view_zone = &(cam->view_zone);
    Rectangle *display = cam->display;
    float ratio_fix_x = cam->ratio_fix_x;
    float ratio_fix_y = cam->ratio_fix_y;

    Texture2D *fixed_sprites = cam->map->fixed_sprites;

    if(cam->map->fixed_sprites != NULL && cam->map->sprites != NULL)
    {
        for(int16_t i = 0; i < cam->map->sprite_nb; ++i)
        {
            spr_buffer = &(cam->map->sprites[i]);

            rec_buffer = &(spr_buffer->zone);

            index_buffer = spr_buffer->sprite_index;

            if(CheckCollisionRecs(*view_zone, *rec_buffer))
            {
                if(index_buffer < cam->map->loaded_sprites_nb)
                {
                    Rectangle visible_rect = GetCollisionRec(*view_zone, *rec_buffer);

                    if(index_buffer < 0)
                    {
                        img_buf = &missing_texture;

                        w = (float) missing_texture.width;
                        h = (float) missing_texture.height;
                    }
                    else
                    {
                        img_buf = fixed_sprites + index_buffer;

                        w = (float) img_buf->width;
                        h = (float) img_buf->height;
                    }

                    Rectangle dest = (Rectangle) {
                        .x = display->x + (visible_rect.x - view_zone->x) * ratio_fix_x,
                        .y = display->y + (visible_rect.y - view_zone->y) * ratio_fix_y,
                        .width = visible_rect.width * ratio_fix_x,
                        .height = visible_rect.height * ratio_fix_y
                    };

                    Rectangle src = RectangleEqual(&visible_rect, rec_buffer) == 0 ?
                        (Rectangle) {
                            .x = ((visible_rect.x - rec_buffer->x) * w)/rec_buffer->width,
                            .y = ((visible_rect.y - rec_buffer->y) * h)/rec_buffer->height,
                            .width = ((float) visible_rect.width * w)/rec_buffer->width,
                            .height = ((float) visible_rect.height * h)/rec_buffer->height
                        } :
                        (Rectangle) {
                            .x = 0.0,
                            .y = 0.0,
                            .width = w,
                            .height = h
                        };

                    DrawTexturePro(*img_buf, src, dest, Vector2_0, 0, WHITE);
                    
                }
            }
        }
    }

    //DrawTexturePro(cam->map->fixed_sprite,cam->view_zone,*(cam->display),Vector2_0,0,WHITE);
    SLUG_DisplayPlayer(cam, cam->player);
    return 0;
}
