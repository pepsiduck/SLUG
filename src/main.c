#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "defines.h"
#include "player.h"
#include "map.h"
#include "display.h"
#include "game.h"

int8_t SLUG_Init(int argc, char *argv[], SLUG_Map **map, SLUG_Player **player)
{
    if(map == NULL || player == NULL)
        return -1;
    if(*map != NULL || *player != NULL)
        return -1;
    if(argc > 2)
    {
        printf("Wrong arguments");
        return -1;
    }
    else if(argc == 2)
    {
        if(strchr(argv[1], '.') != NULL)
        {
            printf("Not a folder\n");
            return -1;
        }
        
        *map = SLUG_LoadMap(argv[1]);
        if(*map == NULL)
            return -1;

        *player = SLUG_DevPlayerLoad();
        if(*player == NULL)
        {
            SLUG_MapUnload(*map);
            *map = NULL;
            return 1;
        }

        (*player)->position = (*map)->player_spawn;
        (*player)->hitbox.x = (*map)->player_spawn.x - (*player)->hitbox.width / 2;
        (*player)->hitbox.y = (*map)->player_spawn.y - (*player)->hitbox.height / 2;
        (*player)->bounding_box = (*player)->hitbox;

    }
    else if(argc == 1)
    {
        *player = SLUG_DevPlayerLoad();
        if(*player == NULL)
            return 1;
        *map = SLUG_LoadMapDev();
        if(*map == NULL)
        {
            SLUG_PlayerUnload(*player);
            return 1;
        }
    }
    else
        return -1;
    return 0;
}

int main(int argc, char **argv) 
{
  
    if(SLUG_GlobalVarInit() == -1)
    {
        printf("ERROR during global variables initialization.\n");
        return EXIT_FAILURE;
    }


    InitWindow(GAME_WIDTH, GAME_HEIGHT, "SLUG");
    //ToggleFullscreen();
    InitAudioDevice();
    SetWindowState(FLAG_VSYNC_HINT|FLAG_WINDOW_RESIZABLE);
    if(SLUG_GraphicInit() == -1)
    {
        printf("ERROR during graphic initialization.\n");
        return EXIT_FAILURE;
    }

    SLUG_Map *map = NULL;
    SLUG_Player *player = NULL;
    int8_t err = SLUG_Init(argc, argv, &map, &player);
    if(err != 0)
        return err;    

    SLUG_Camera camera;
    SLUG_DefaultCamera(map, player, &camera);
    

    SetTargetFPS(60);
    Vector2 playermove;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        SLUG_DisplayUpdate();
        SLUG_Display(&camera);

        dt = GetFrameTime();
        
        SLUG_PlayerJump(player);
		SLUG_PlayerGravity(player);

		SLUG_PlayerDrag(player);
    
        SLUG_GetMove(player, &playermove);

        err = SLUG_PlayerMove(player, map, playermove);
        if(err < 0)
        {
            printf("Error");
            SLUG_PlayerUnload(player); 
            player = NULL;   
            SLUG_MapUnload(map);
            map = NULL;
            CloseWindow(); // Close window and OpenGL context
            CloseAudioDevice();
            return err;
        }

        printf("%f ; %f ; %f ; %f\n", player->position.x, player->position.y, player->velocity.x, player->velocity.y);
    //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    SLUG_PlayerUnload(player);   
    player = NULL; 
    SLUG_MapUnload(map);
    map = NULL;
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();
    return 0;
}
