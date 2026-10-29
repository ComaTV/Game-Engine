#include "Utils.hpp"

#include <algorithm>
#include <cctype>
#include <filesystem>

namespace fs = std::filesystem;

namespace
{
    bool IsImageFile(const fs::path& path)
    {
        std::string extension = path.extension().string();
        std::transform(
            extension.begin(),
            extension.end(),
            extension.begin(),
            [](unsigned char character)
            {
                return static_cast<char>(std::tolower(character));
            }
        );

        return extension == ".png" ||
               extension == ".jpg" ||
               extension == ".jpeg";
    }
}

namespace Utils
{
    Rectangle CreateScreenBorder(float borderSize)
    {
        const float screenWidth = static_cast<float>(GetScreenWidth());
        const float screenHeight = static_cast<float>(GetScreenHeight());

        return {
            borderSize,
            borderSize,
            std::max(0.0f, screenWidth - 2.0f * borderSize),
            std::max(0.0f, screenHeight - 2.0f * borderSize)
        };
    }

    void DrawScreenBorder(float borderSize, float lineThickness, Color color)
    {
        DrawRectangleLinesEx(
            CreateScreenBorder(borderSize),
            lineThickness,
            color
        );
    }

    Texture2D LoadTextureFile(const std::string& filePath)
    {
        Texture2D texture = LoadTexture(filePath.c_str());

        if (texture.id == 0)
        {
            TraceLog(
                LOG_ERROR,
                "Failed to load texture: %s",
                filePath.c_str()
            );
        }

        return texture;
    }

    std::vector<Texture2D> LoadAnimationFrames(
        const std::string& folderPath
    )
    {
        std::vector<fs::path> imagePaths;
        std::error_code error;

        if (!fs::is_directory(folderPath, error))
        {
            TraceLog(
                LOG_ERROR,
                "Animation folder not found: %s",
                folderPath.c_str()
            );

            return {};
        }

        for (const fs::directory_entry& entry :
             fs::directory_iterator(folderPath, error))
        {
            if (error)
                break;

            if (entry.is_regular_file(error) && IsImageFile(entry.path()))
                imagePaths.push_back(entry.path());
        }

        if (error)
        {
            TraceLog(
                LOG_ERROR,
                "Failed to read animation folder: %s",
                folderPath.c_str()
            );

            return {};
        }

        std::sort(imagePaths.begin(), imagePaths.end());

        std::vector<Texture2D> frames;
        frames.reserve(imagePaths.size());

        for (const fs::path& imagePath : imagePaths)
        {
            Texture2D texture = LoadTextureFile(imagePath.string());

            if (texture.id != 0)
                frames.push_back(texture);
        }

        return frames;
    }

    Sound LoadSoundFile(const std::string& filePath)
    {
        Sound sound = LoadSound(filePath.c_str());

        if (sound.frameCount == 0)
        {
            TraceLog(
                LOG_ERROR,
                "Failed to load sound: %s",
                filePath.c_str()
            );
        }

        return sound;
    }

    void UnloadTextures(std::vector<Texture2D>& textures)
    {
        for (Texture2D texture : textures)
            UnloadTexture(texture);

        textures.clear();
    }
}
