#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "player.h"

int main(int argc, char **argv) {
  
    if(SLUG_GlobalVarInit() == -1)
    {
        printf("ERROR during global variables initialization.\n");
        return EXIT_FAILURE;
    }

    InitWindow(screen_w, screen_h, "paintball client");
    ToggleFullscreen();
    InitAudioDevice();
  
    SLUG_Player player;
    player.position.x = 500.0f;
    player.position.y = 500.0f;
    player.speed = 100.0f;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
    
        BeginDrawing();

        ClearBackground(PURPLE);

        dt = GetFrameTime();

        if(IsKeyDown(KEY_Q))
            SLUG_PlayerMove(&player);

        Rectangle playerRect = { player.position.x - 20, player.position.y - 20, 40.0f, 40.0f };
        DrawRectangleRec(playerRect, RED);
    
        EndDrawing();
    //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();
    return 0;
}
