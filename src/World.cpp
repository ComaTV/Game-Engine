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
}

void World::HandleInput()
{
    player.HandleInput();
}

void World::Update(float dt)
{
    player.Update(dt);
}

void World::Draw()
{
    Utils::DrawScreenBorder(20.0f, 2.0f, RED);
    player.Draw();
}