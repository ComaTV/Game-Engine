#include "raylib.h"
#include "Player.hpp"

int main()
{
    InitWindow(800, 600, "Lil Buddy");
    SetTargetFPS(60);

    Player player(
        "assets/textures/animations/konata/idle.png", 
        "assets/textures/animations/konata/walk.png", 
        "assets/textures/animations/konata/run.png", 
        "assets/sounds/konata/walking.mp3", 
        "assets/sounds/konata/running.mp3"
    );

    while(!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_D))
        {
            ToggleFullscreen();
        }

        float dt = GetFrameTime();

        player.HandleInput();
        player.Update(dt);

        BeginDrawing();
        ClearBackground(MAROON);
        player.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}