#pragma once
#include <memory>

#include <chrono>
#include "input/InputManager.h"
#include "graphics/GraphicsAPI.h"

struct GLFWwindow;

namespace eng {
    class Application;

    class Engine {
    public:
        bool Initialize();

        void Shutdown();

        void Run();

        void SetApplication(Application* app);

        InputManager& GetInputManager();
        GraphicsAPI& GetGraphicsAPI();

    private:
        GLFWwindow* window;
        std::unique_ptr<Application> application;
        std::chrono::steady_clock::time_point lastTimePoint;
        InputManager inputManager;
        GraphicsAPI graphics;
    };
}
