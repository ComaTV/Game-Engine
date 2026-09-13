#include <Engine.h>

int main() {
    illengine::Engine engine;

    int width = 1024;
    int height = 768;
    std::string name = "A game and sh";
    bool fullscreen = false;

    engine.Startup(width, height, name, fullscreen);
    engine.RunGameLoop();
    engine.Shutdown();
    return 0;
}
