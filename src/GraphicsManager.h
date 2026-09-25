#pragma once

#include <string>

struct GLFWwindow;

namespace illengine {
    class GraphicsManager {
    public:
        void Startup(int width, int height, const std::string& name, bool fullscreen);
        void Shutdown();

        bool ShouldQuit() const;
        void SetShouldQuit(bool shouldQuit);

        GLFWwindow* GetWindow();

    private:
        struct Impl;
        Impl* pImpl = nullptr;
    };
}