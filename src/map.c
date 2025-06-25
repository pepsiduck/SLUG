#include "map.h"

SLUG_map* SLUG_LoadMapDev()
{
    SLUG_map *map = (SLUG_map*) malloc(sizeof(SLUG_map));
    map->fixed_sprite = LoadTexture("assets/dev_map.jpg");
    map->w = 4011;
    map->h = 3330;
    return map;
}

void SLUG_MapUnload(SLUG_map *map)
{
    UnloadTexture(map->fixed_sprite);
    free(map);
}

SLUG_camera SLUG_DefaultCamera(SLUG_map *map, SLUG_Player *player)
{
    SLUG_camera camera;
    camera.map = map;
    camera.player = player;
    camera.display = &display;
    camera.camera.x = 0;
    camera.camera.y = 0;
    camera.camera.width = 1680;
    camera.camera.height = 1050;
    camera.wanted_pos.x = 1680/2;
    camera.wanted_pos.y = 1050/2;
    camera.ratio_fix_x = display.width / camera.camera.width;
    camera.ratio_fix_y = display.height / camera.camera.height;
    return camera;
}

void SLUG_CameraScrolling(SLUG_camera *cam)
{
    cam->camera.x = cam->player->position.x - cam->wanted_pos.x;
    cam->camera.y = cam->player->position.y - cam->wanted_pos.y;

    cam->camera.x = fmax(cam->camera.x, 0);
    cam->camera.x = fmin(cam->camera.x, cam->map->w - 1680);
    cam->camera.y = fmax(cam->camera.y, 0);
    cam->camera.y = fmin(cam->camera.y, cam->map->h - 1050);
}

int8_t SLUG_Display(SLUG_camera *cam) // ptet autre part après et avec d'autres arguments
{
    cam->ratio_fix_x = display.width / cam->camera.width;
    cam->ratio_fix_y = display.height / cam->camera.height;
    SLUG_CameraScrolling(cam);
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(cam->map->fixed_sprite,cam->camera,*(cam->display),Vector2_0,0,WHITE);
    if(CheckCollisionRecs(cam->camera, cam->player->bounding_box))
    {
        Rectangle p = GetCollisionRec(cam->camera, cam->player->bounding_box);
        //printf("Camera position : %f, %f\n", cam->camera.x, cam->camera.y);
        DrawTexturePro(cam->player->sprite,(Rectangle) {.x= p.x - cam->player->bounding_box.x,.y=p.y - cam->player->bounding_box.y,.width=p.width, .height=p.height},
                        (Rectangle) {.x=cam->display->x + (p.x - cam->camera.x)*cam->ratio_fix_x, 
                                     .y=cam->display->y + (p.y - cam->camera.y)*cam->ratio_fix_y, 
                                     .width=p.width * cam->ratio_fix_x, 
                                     .height=p.height * cam->ratio_fix_y} ,Vector2_0,0,WHITE);
    }
    EndDrawing();
    return 0;
}
