#pragma once

#include <string>

#include <GraphicsManager.h>

namespace illengine {
    class Engine {
    public:
        void Startup(int width, int height, const std::string& name, bool fullscreen);
        void Shutdown();

        void RunGameLoop();
    
    private:
        GraphicsManager graphics;
    };
}