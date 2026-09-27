#pragma once
#include "raylib.h"
#include "PlayerState.hpp"

class Player {
    public:
        Player(
            const char* idlePath, 
            const char* walkPath,
            const char* runPath, 
            const char* walkingSound, 
            const char* runningSound
        );
        ~Player();

        void HandleInput();
        void Update(float dt);
        void Draw();
        void PlaySounds();

    private:
        Texture2D   idleTexture;
        Texture2D   walkTexture;
        Texture2D   runTexture;

        Sound walkingSound;
        Sound runningSound;

        PlayerState state;
        float posX, posY;
        float speed;
        float runSpeed;
        float width = 200.0f;
        float height = 200.0f;
        bool facingLeft = false;

        void ChangeState(PlayerState newState);
};