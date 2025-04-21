#include <raylib.h>
#include <stdio.h>

const int screenWidth = 500;
const int screenHeight = 500;


int main(int argc, char **argv) {
  

    InitWindow(screenWidth, screenHeight, "paintball client");
    InitAudioDevice();

    double dt;
  
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
    
        BeginDrawing();

        ClearBackground(PURPLE);

        dt = GetFrameTime();

    
        EndDrawing();
    //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();
    return 0;
}
