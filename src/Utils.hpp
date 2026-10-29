#pragma once

#include "raylib.h"

#include <string>
#include <vector>

namespace Utils
{
    Rectangle CreateScreenBorder(float borderSize);
    void DrawScreenBorder(float borderSize, float lineThickness, Color color);

    Texture2D LoadTextureFile(const std::string& filePath);

    std::vector<Texture2D> LoadAnimationFrames(
        const std::string& folderPath
    );

    Sound LoadSoundFile(const std::string& filePath);

    void UnloadTextures(std::vector<Texture2D>& textures);
}
