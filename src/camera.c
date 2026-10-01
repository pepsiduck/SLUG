#include "camera.h"

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
        display_center = (Vector2) {.x = display.x + display.width / 2.0f, .y = display.y + display.height / 2.0f};
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

