#pragma once

#include <GraphicsManager.h>
#include <InputManager.h>
#include <functional>

namespace illengine {
    class Engine {
    public:
        void Startup(int width, int height, const std::string& name, bool fullscreen);
        void Shutdown();

        using UpdateCallback = std::function<void(InputManager&)>;

        void RunGameLoop();
    
    private:
        GraphicsManager graphics;
        InputManager input;
    };
}