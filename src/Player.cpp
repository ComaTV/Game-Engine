#include "Player.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <cmath>

Player::Player(
    const char* idleFolder,
    const char* walkFolder,
    const char* runFolder,
    const char* jumpFolder,
    const char* walkingPath,
    const char* runningPath
)
{
    idleFrames = Utils::LoadAnimationFrames(idleFolder);
    walkFrames = Utils::LoadAnimationFrames(walkFolder);
    runFrames = Utils::LoadAnimationFrames(runFolder);
    jumpFrames = Utils::LoadAnimationFrames(jumpFolder);

    walkingSound = Utils::LoadSoundFile(walkingPath);
    runningSound = Utils::LoadSoundFile(runningPath);

    state = PlayerState::IDLE;
    posX = 300.0f;
    posY = 300.0f;
    speed = 150.0f;
    runSpeed = 400.0f;
}

Player::~Player()
{
    Utils::UnloadTextures(idleFrames);
    Utils::UnloadTextures(walkFrames);
    Utils::UnloadTextures(runFrames);
    Utils::UnloadTextures(jumpFrames);

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
    bool isMoving = IsKeyDown(KEY_D) || IsKeyDown(KEY_A);
    bool isRunning = IsKeyDown(KEY_LEFT_SHIFT);

    if (IsKeyPressed(KEY_SPACE) && grounded)
    {
        verticalVelocity = -jumpStrength;
        grounded = false;
        ChangeState(PlayerState::JUMP);
    }
    else if (!grounded)
    {
        ChangeState(PlayerState::JUMP);
    }
    else if (isMoving && isRunning)
    {
        ChangeState(PlayerState::RUN);
    }
    else if (isMoving)
    {
        ChangeState(PlayerState::WALK);
    }
    else
    {
        ChangeState(PlayerState::IDLE);
    }
}

void Player::Update(float dt, const std::vector<Rectangle>& obstacles)
{
    const bool wasGrounded = grounded;
    const float previousX = posX;
    const float previousY = posY;

    float currentSpeed =
        (state == PlayerState::RUN) ? runSpeed : speed;

    if (state != PlayerState::IDLE)
    {
        if (IsKeyDown(KEY_D))
        {
            posX += currentSpeed * dt;
            facingLeft = false;
        }

        if (IsKeyDown(KEY_A))
        {
            posX -= currentSpeed * dt;
            facingLeft = true;
        }

    }

    verticalVelocity += gravity * dt;
    posY += verticalVelocity * dt;

    KeepInsideScreen();
    ResolveObstacleCollision(obstacles, previousX, previousY);

    const bool justLanded = !wasGrounded && grounded;
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

        case PlayerState::JUMP:
            frames = &jumpFrames;
            break;
    }

    if (state == PlayerState::JUMP && !jumpFrames.empty())
    {
        if (justLanded)
        {
            currentFrame =
                std::min(3, static_cast<int>(jumpFrames.size()) - 1);
            animationTimer = 0.0f;
        }
        else if (!grounded && jumpFrames.size() > 1)
        {
            animationTimer += dt;

            while (animationTimer >= frameDuration)
            {
                animationTimer -= frameDuration;
                currentFrame = std::min(currentFrame + 1, 2);
            }
        }
    }
    else if (frames != nullptr && frames->size() > 1)
    {
        animationTimer += dt;

        while (animationTimer >= frameDuration)
        {
            animationTimer -= frameDuration;
            currentFrame++;

            if (currentFrame >= static_cast<int>(frames->size()))
                currentFrame = 0;
        }
    }

}

void Player::ResolveObstacleCollision(
    const std::vector<Rectangle>& obstacles,
    float previousX,
    float previousY
)
{
    Rectangle playerBounds = { posX, posY, width, height };
    const float previousBottom = previousY + height;
    const float previousRight = previousX + width;
    const float previousLeft = previousX;

    for (const Rectangle& obstacle : obstacles)
    {
        const bool overlapsHorizontally =
            playerBounds.x < obstacle.x + obstacle.width &&
            playerBounds.x + playerBounds.width > obstacle.x;

        if (overlapsHorizontally &&
            verticalVelocity >= 0.0f &&
            previousBottom <= obstacle.y &&
            playerBounds.y + playerBounds.height >= obstacle.y)
        {
            posY = obstacle.y - height;
            verticalVelocity = 0.0f;
            grounded = true;
            return;
        }

        if (!CheckCollisionRecs(playerBounds, obstacle))
            continue;

        if (previousRight <= obstacle.x)
            posX = obstacle.x - width;
        else if (previousLeft >= obstacle.x + obstacle.width)
            posX = obstacle.x + obstacle.width;

        return;
    }
}

void Player::KeepInsideScreen()
{
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());

    posX = std::clamp(
        posX,
        borderSize,
        std::max(borderSize, screenWidth - width - borderSize)
    );
    const float floorY = std::max(borderSize, screenHeight - height - borderSize);

    if (posY >= floorY)
    {
        posY = floorY;
        verticalVelocity = 0.0f;
        grounded = true;
    }
    else
    {
        grounded = false;
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

        case PlayerState::JUMP:
            frames = &jumpFrames;
            break;
    }

    if (frames == nullptr || frames->empty())
        return;

    if (currentFrame >= static_cast<int>(frames->size()))
        currentFrame = 0;

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