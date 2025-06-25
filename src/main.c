#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "player.h"
#include "map.h"
#include <inttypes.h>

int main(int argc, char **argv) {
  
    if(SLUG_GlobalVarInit() == -1)
    {
        printf("ERROR during global variables initialization.\n");
        return EXIT_FAILURE;
    }


    InitWindow(1680, 1050, "paintball client");
    //ToggleFullscreen();
    InitAudioDevice();
    SetWindowState(FLAG_VSYNC_HINT|FLAG_WINDOW_RESIZABLE);
    if(SLUG_GraphicInit() == -1)
    {
        printf("ERROR during graphic initialization.\n");
        return EXIT_FAILURE;
    }

    SLUG_Player *player = SLUG_DevPlayerLoad();
    SLUG_map *map = SLUG_LoadMapDev();
    SLUG_camera camera = SLUG_DefaultCamera(map, player);
    

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        SLUG_DisplayUpdate();
        SLUG_Display(&camera);

        dt = GetFrameTime();

        
    
        

        SLUG_PlayerMove(player);
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
