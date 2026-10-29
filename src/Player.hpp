#pragma once

#include "raylib.h"
#include "PlayerState.hpp"
#include <vector>

class Player {
public:
    Player(
        const char* idleFolder,
        const char* walkFolder,
        const char* runFolder,
        const char* jumpFolder,
        const char* walkingSound,
        const char* runningSound
    );

    ~Player();

    void HandleInput();
    void Update(float dt);
    void Draw();
    void PlaySounds();

private:
    std::vector<Texture2D> idleFrames;
    std::vector<Texture2D> walkFrames;
    std::vector<Texture2D> runFrames;
    std::vector<Texture2D> jumpFrames;

    Sound walkingSound;
    Sound runningSound;

    PlayerState state;

    float posX;
    float posY;
    float speed;
    float runSpeed;
    float width = 200.0f;
    float height = 200.0f;
    float borderSize = 20.0f;
    float verticalVelocity = 0.0f;
    float gravity = 1400.0f;
    float jumpStrength = 600.0f;
    bool grounded = false;

    bool facingLeft = false;

    int currentFrame = 0;
    float animationTimer = 0.0f;
    float frameDuration = 0.15f;

    void ChangeState(PlayerState newState);
    void ResetAnimation();
    void KeepInsideScreen();
};