#include "Obstacles.hpp"

namespace Obstacles
{
    std::vector<Obstacle> CreateDefault()
    {
        return {
            { { 700.0f, 0.0f, 100.0f, 100.0f }, DARKGRAY },
            { { 1000.0f, 0.0f, 160.0f, 160.0f }, BROWN }
        };
    }

    void KeepOnFloor(std::vector<Obstacle>& obstacles)
    {
        const float floorY = static_cast<float>(GetScreenHeight()) - 20.0f;

        for (Obstacle& obstacle : obstacles)
            obstacle.bounds.y = floorY - obstacle.bounds.height;
    }

    std::vector<Rectangle> GetBounds(
        const std::vector<Obstacle>& obstacles
    )
    {
        std::vector<Rectangle> bounds;
        bounds.reserve(obstacles.size());

        for (const Obstacle& obstacle : obstacles)
            bounds.push_back(obstacle.bounds);

        return bounds;
    }

    void Draw(const std::vector<Obstacle>& obstacles)
    {
        for (const Obstacle& obstacle : obstacles)
        {
            DrawRectangleRec(obstacle.bounds, obstacle.color);
            DrawRectangleLinesEx(obstacle.bounds, 2.0f, BLACK);
        }
    }
}
