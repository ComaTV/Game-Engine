#include "Player.hpp"

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static std::vector<Texture2D> LoadAnimationFrames(
    const std::string& folderPath
)
{
    std::vector<fs::path> imagePaths;

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath))
    {
        TraceLog(
            LOG_ERROR,
            "Animation folder not found: %s",
            folderPath.c_str()
        );

        return {};
    }

    for (const fs::directory_entry& entry : fs::directory_iterator(folderPath))
    {
        if (!entry.is_regular_file())
            continue;

        const std::string extension =
            entry.path().extension().string();

        if (extension == ".png" ||
            extension == ".jpg" ||
            extension == ".jpeg")
        {
            imagePaths.push_back(entry.path());
        }
    }

    std::sort(imagePaths.begin(), imagePaths.end());

    std::vector<Texture2D> frames;
    frames.reserve(imagePaths.size());

    for (const fs::path& imagePath : imagePaths)
    {
        Texture2D texture = LoadTexture(imagePath.string().c_str());

        if (texture.id == 0)
        {
            TraceLog(
                LOG_ERROR,
                "Failed to load animation frame: %s",
                imagePath.string().c_str()
            );

            continue;
        }

        frames.push_back(texture);
    }

    return frames;
}

Player::Player(
    const char* idleFolder,
    const char* walkFolder,
    const char* runFolder,
    const char* walkingPath,
    const char* runningPath
)
{
    idleFrames = LoadAnimationFrames(idleFolder);
    walkFrames = LoadAnimationFrames(walkFolder);
    runFrames = LoadAnimationFrames(runFolder);

    walkingSound = LoadSound(walkingPath);
    runningSound = LoadSound(runningPath);

    state = PlayerState::IDLE;
    posX = 300.0f;
    posY = 300.0f;
    speed = 150.0f;
    runSpeed = 400.0f;
}

Player::~Player()
{
    for (Texture2D texture : idleFrames)
        UnloadTexture(texture);

    for (Texture2D texture : walkFrames)
        UnloadTexture(texture);

    for (Texture2D texture : runFrames)
        UnloadTexture(texture);

    UnloadSound(walkingSound);
    UnloadSound(runningSound);
}

void Player::ChangeState(PlayerState newState)
{
    if (state != newState)
    {
        state = newState;
        ResetAnimation();
    }
}

void Player::ResetAnimation()
{
    currentFrame = 0;
    animationTimer = 0.0f;
}

void Player::HandleInput()
{
    bool isMoving = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) ||
                    IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN);
    bool isRunning = IsKeyDown(KEY_LEFT_SHIFT);

    if(isMoving && isRunning)
        ChangeState(PlayerState::RUN);
    else if(isMoving)
        ChangeState(PlayerState::WALK);
    else 
        ChangeState(PlayerState::IDLE);
}

void Player::Update(float dt)
{
    float currentSpeed =
        (state == PlayerState::RUN) ? runSpeed : speed;

    if (state != PlayerState::IDLE)
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            posX += currentSpeed * dt;
            facingLeft = false;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            posX -= currentSpeed * dt;
            facingLeft = true;
        }

        if (IsKeyDown(KEY_UP))
            posY -= currentSpeed * dt;

        if (IsKeyDown(KEY_DOWN))
            posY += currentSpeed * dt;
    }

    const std::vector<Texture2D>* frames = nullptr;

    switch (state)
    {
        case PlayerState::IDLE:
            frames = &idleFrames;
            break;

        case PlayerState::WALK:
            frames = &walkFrames;
            break;

        case PlayerState::RUN:
            frames = &runFrames;
            break;
    }

    if (frames == nullptr || frames->size() <= 1)
        return;

    animationTimer += dt;

    if (animationTimer >= frameDuration)
    {
        animationTimer -= frameDuration;
        currentFrame++;

        if (currentFrame >= static_cast<int>(frames->size()))
            currentFrame = 0;
    }
}

void Player::Draw()
{
    const std::vector<Texture2D>* frames = nullptr;

    switch (state)
    {
        case PlayerState::IDLE:
            frames = &idleFrames;
            break;

        case PlayerState::WALK:
            frames = &walkFrames;
            break;

        case PlayerState::RUN:
            frames = &runFrames;
            break;
    }

    if (frames == nullptr || frames->empty())
        return;

    Texture2D currentTexture = (*frames)[currentFrame];

    Rectangle source = {
        0.0f,
        0.0f,
        static_cast<float>(currentTexture.width),
        static_cast<float>(currentTexture.height)
    };

    if (facingLeft)
        source.width *= -1.0f;

    Rectangle dest = {
        posX,
        posY,
        width,
        height
    };

    DrawTexturePro(
        currentTexture,
        source,
        dest,
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}

void Player::PlaySounds()
{
    switch (state)
    {
        case PlayerState::WALK:
            if (IsSoundPlaying(runningSound))
                StopSound(runningSound);
            if (!IsSoundPlaying(walkingSound))
                PlaySound(walkingSound);
            break;
        case PlayerState::RUN:
            if (IsSoundPlaying(walkingSound))
                StopSound(walkingSound);
            if (!IsSoundPlaying(runningSound))
                PlaySound(runningSound);
            break;
        default:
            if (IsSoundPlaying(walkingSound))
                StopSound(walkingSound);
            if (IsSoundPlaying(runningSound))
                StopSound(runningSound);
            break;
    }
}