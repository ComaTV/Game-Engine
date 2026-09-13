#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <GraphicsManager.h>
#include <spdlog/spdlog.h>

namespace illengine {
    struct GraphicsManager::Impl {
        GLFWwindow* window = nullptr;
        bool shouldQuit = false;
    };

    void GraphicsManager::Startup(int width, int height, const std::string& name, bool fullscreen) {
        pImpl = new Impl();

        if (!glfwInit()) {
            spdlog::error("Failed to initialize GLFW");
            return;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        pImpl->window = glfwCreateWindow(width, height, name.c_str(), monitor, nullptr);
        if (!pImpl->window) {
            spdlog::error("Failed to create GLFW window");
            glfwTerminate();
            delete pImpl;
            pImpl = nullptr;
            return;
        }
        glfwSetWindowAspectRatio(pImpl->window, width, height);
        spdlog::info("Window created with size {}x{} and title '{}'", width, height, name, fullscreen);
    }
    
    void GraphicsManager::Shutdown() {
        if (pImpl) {
            if (pImpl->window) {
                glfwDestroyWindow(pImpl->window);
                pImpl->window = nullptr;
            }
            glfwTerminate();
            delete pImpl;
            pImpl = nullptr;
        }
    }

    bool GraphicsManager::ShouldQuit() const {
        if (!pImpl || !pImpl->window) return true;
        return pImpl->shouldQuit || glfwWindowShouldClose(pImpl->window);
    }

    void GraphicsManager::SetShouldQuit(bool shouldQuit) {
        if (!pImpl) return;
        pImpl->shouldQuit = shouldQuit;
        if (pImpl->window && shouldQuit) {
            glfwSetWindowShouldClose(pImpl->window, GLFW_TRUE);
        }
    }
}