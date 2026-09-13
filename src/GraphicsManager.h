#pragma once

#include <string>

namespace illengine {
    class GraphicsManager {
    public:
        void Startup(int width, int height, const std::string& name, bool fullscreen);
        void Shutdown();

        bool ShouldQuit() const;
        void SetShouldQuit(bool shouldQuit);

    private:
        struct Impl;
        Impl* pImpl = nullptr;
    };
}