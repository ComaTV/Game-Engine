#include "raylib.h"
#include "Player.hpp"

int main()
{
    InitWindow(800, 600, "Konata Adventure");
    InitAudioDevice();
    SetTargetFPS(60);

    {
        Player player(
            "assets/textures/animations/konata/idle",
            "assets/textures/animations/konata/walk",
            "assets/textures/animations/konata/run",
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
            ClearBackground({ 135, 206, 235, 255 });
            player.Draw();
            EndDrawing();
        }
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}