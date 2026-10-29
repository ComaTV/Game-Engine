#pragma once

#include "Obstacles.hpp"
#include "Player.hpp"

class World
{
public:
    World();

    void HandleInput();
    void Update(float dt);
    void Draw();

private:
    Player player;
    std::vector<Obstacle> obstacles;
};