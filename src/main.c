#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "defines.h"
#include "player.h"
#include "map.h"
#include "display.h"

int main(int argc, char **argv) {
  
    if(SLUG_GlobalVarInit() == -1)
    {
        printf("ERROR during global variables initialization.\n");
        return EXIT_FAILURE;
    }


    InitWindow(GAME_WIDTH, GAME_HEIGHT, "paintball client");
    //ToggleFullscreen();
    InitAudioDevice();
    SetWindowState(FLAG_VSYNC_HINT|FLAG_WINDOW_RESIZABLE);
    if(SLUG_GraphicInit() == -1)
    {
        printf("ERROR during graphic initialization.\n");
        return EXIT_FAILURE;
    }

    SLUG_Player *player = SLUG_DevPlayerLoad();
    SLUG_Map *map = SLUG_LoadMapDev(player);
    SLUG_Camera camera = SLUG_DefaultCamera(map, player);
    

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        SLUG_DisplayUpdate();
        SLUG_Display(&camera);

        dt = GetFrameTime();

    
        

        SLUG_PlayerMove(player, map, SLUG_WantedMove(player));
    //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    SLUG_PlayerUnload(player);    
    SLUG_MapUnload(map);
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();
    return 0;
}
