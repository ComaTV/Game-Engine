#include "Player.hpp"

Player::Player(const char* idlePath, const char* walkPath, const char* runPath, const char* walkingPath, const char* runningPath)
{
    idleTexture = LoadTexture(idlePath);
    walkTexture = LoadTexture(walkPath);
    runTexture = LoadTexture(runPath);

    walkingSound = LoadSound(walkingPath);
    runningSound = LoadSound(runningPath);

    state = PlayerState::IDLE;
    posX = 300;
    posY = 300;
    speed = 150.0f;
    runSpeed = 400.0f;
}
Player::~Player()
{
    UnloadTexture(idleTexture);
    UnloadTexture(walkTexture);
    UnloadTexture(runTexture);

    UnloadSound(walkingSound);
    UnloadSound(runningSound);
}

void Player::ChangeState(PlayerState newState)
{
    if(state != newState)
        state = newState;
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
    float currentSpeed = (state == PlayerState::RUN) ? runSpeed : speed;
    
    if(state != PlayerState::IDLE)
    {
        if(IsKeyDown(KEY_RIGHT)){posX += currentSpeed * dt; facingLeft = false; }
        if(IsKeyDown(KEY_LEFT)) {posX -= currentSpeed * dt; facingLeft = true;  }
        if(IsKeyDown(KEY_UP))    posY -= currentSpeed * dt;
        if(IsKeyDown(KEY_DOWN))  posY += currentSpeed * dt;
    }
}

void Player::Draw()
{
    Texture2D currentTexture;

    switch (state)
    {
        case PlayerState::WALK: currentTexture = walkTexture; break;
        case PlayerState::RUN:  currentTexture = runTexture;  break;
        default:                currentTexture = idleTexture; break;
    }

    Rectangle source = { 0, 0, (float)currentTexture.width, (float)currentTexture.height };

    if(facingLeft) source.width *= -1;

    Rectangle dest = { posX, posY, width, height };

    DrawTexturePro(currentTexture, source, dest, {0, 0}, 0.0f, WHITE);
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