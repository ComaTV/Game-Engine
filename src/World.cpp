#include "World.hpp"
#include "Utils.hpp"

World::World()
    : player(
        "assets/textures/animations/konata/idle",
        "assets/textures/animations/konata/walk",
        "assets/textures/animations/konata/run",
        "assets/textures/animations/konata/jump",
        "assets/sounds/konata/walking.wav",
        "assets/sounds/konata/running.wav"
    )
{
    obstacles = Obstacles::CreateDefault();
}

void World::HandleInput()
{
    player.HandleInput();
}

void World::Update(float dt)
{
    Obstacles::KeepOnFloor(obstacles);
    player.Update(dt, Obstacles::GetBounds(obstacles));
}

void World::Draw()
{
    Utils::DrawScreenBorder(20.0f, 2.0f, RED);

    Obstacles::Draw(obstacles);
    player.Draw();
}