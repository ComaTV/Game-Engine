#include <Engine.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <thread>

#if defined(_WIN32)
#include <Windows.h>
#endif

namespace illengine {
    void Engine::Startup(int width, int height, const std::string& name, bool fullscreen) {
        #if defined(_WIN32)
            timeBeginPeriod(1);
        #endif
        graphics.Startup(width, height, name, fullscreen);
        spdlog::info("No way that engine started 0_0");
    }

    void Engine::Shutdown() {
        graphics.Shutdown();
        spdlog::info("Bye bye engine");
        #if defined(_WIN32)
        timeEndPeriod(1);
        #endif
    }
    
    void Engine::RunGameLoop() {
        using namespace std::chrono;
        using real = double;

        const real targetFPS = 60.0;
        const duration<real> frameDuration{1.0 / targetFPS};

        auto lastTime = steady_clock::now();

        while (!graphics.ShouldQuit()) {
            auto currentTime = steady_clock::now();
            lastTime = currentTime;

            auto frameTime = duration<real>(0);
            while(frameTime < frameDuration && !graphics.ShouldQuit()) {
                auto now = steady_clock::now();
                frameTime = now - currentTime;
                if(frameTime < frameDuration) {
                    std::this_thread::sleep_for(frameDuration - frameTime);
                }
            }
        }
    }
}