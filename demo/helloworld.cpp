#include <Engine.h>
#include <spdlog/spdlog.h>
#include "GLFW/glfw3.h"

int main() {
    spdlog::set_level(spdlog::level::debug);

    illengine::Engine engine;

    int width = 1024;
    int height = 768;
    std::string name = "A game and sh";
    bool fullscreen = false;

    engine.Startup(width, height, name, fullscreen);

    engine.RunGameLoop([](illengine::InputManager& input) {
        if (input.KeyIsPressed(GLFW_KEY_ESCAPE)) 
            spdlog::info("Escape key pressed, quitting...");
        if (input.KeyIsPressed(GLFW_KEY_SPACE)) 
            spdlog::info("Space key pressed");
        if (input.KeyIsPressed(GLFW_KEY_W)) 
            spdlog::info("W key pressed");
    });
    engine.Shutdown();
    return 0;
}
