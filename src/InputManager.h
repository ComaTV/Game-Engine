#pragma once

struct GLFWwindow;

namespace illengine {
    class InputManager {
    public:
        void SetWindow(GLFWwindow* window);
        void Update();
        bool KeyIsPressed(int key) const;

    private:
        struct Impl;
        Impl* pImpl = nullptr;
    };
}