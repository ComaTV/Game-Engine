#pragma once

#include "raylib.h"

#include <vector>

struct Obstacle
{
    Rectangle bounds;
    Color color;
};

namespace Obstacles
{
    std::vector<Obstacle> CreateDefault();
    void KeepOnFloor(std::vector<Obstacle>& obstacles);
    std::vector<Rectangle> GetBounds(const std::vector<Obstacle>& obstacles);
    void Draw(const std::vector<Obstacle>& obstacles);
}
