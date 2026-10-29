#pragma once

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
};