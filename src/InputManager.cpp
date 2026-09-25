#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "InputManager.h"
#include <spdlog/spdlog.h>

namespace illengine {
    struct InputManager::Impl {
        GLFWwindow* window = nullptr;
    };

    void InputManager::SetWindow(GLFWwindow* window) {
        if (!pImpl) {
            pImpl = new Impl();
        }
        pImpl->window = window;
    }
    void InputManager::Update() {
        if (!pImpl || !pImpl->window) return;
        glfwPollEvents();
    }

    bool InputManager::KeyIsPressed(int key) const {
        if (!pImpl || !pImpl->window) return false;

        int state = glfwGetKey(pImpl->window, key);
        return (state == GLFW_PRESS || state == GLFW_REPEAT);
    }
}