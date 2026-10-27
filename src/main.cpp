#include "raylib.h"
#include "Player.hpp"

int main()
{
    InitWindow(800, 600, "Lil Buddy");
    InitAudioDevice();
    SetTargetFPS(60);

    {
        Player player(
            "assets/textures/animations/konata/idle.png",
            "assets/textures/animations/konata/walk.png",
            "assets/textures/animations/konata/run.png",
            "assets/sounds/konata/walking.wav",
            "assets/sounds/konata/running.wav"
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
            player.PlaySounds();

            BeginDrawing();
            ClearBackground(MAROON);
            player.Draw();
            EndDrawing();
        }
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}