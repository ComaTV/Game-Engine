#include "raylib.h"
#include "World.hpp"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Konata Adventure");
    InitAudioDevice();
    SetTargetFPS(60);

    {
        World world;

        while (!WindowShouldClose())
        {
            if (IsKeyPressed(KEY_F11))
                ToggleFullscreen();

            float dt = GetFrameTime();
            world.HandleInput();
            world.Update(dt);

            BeginDrawing();
            ClearBackground({ 135, 206, 235, 255 });
            world.Draw();
            EndDrawing();
        }
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
