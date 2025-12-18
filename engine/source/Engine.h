#pragma once
#include <memory>

#include <chrono>
#include "input/InputManager.h"
#include "graphics/GraphicsAPI.h"
#include "render/RenderQueue.h"

struct GLFWwindow;

namespace eng {
    class Application;

    class Engine {
    public:
        bool Initialize();

        void Shutdown();

        float CalculateAspectRatio() const;

        eng::CameraData CalculateCameraData();

        void Render();

        void Run();

        void SetApplication(Application* app);

        InputManager& GetInputManager();
        GraphicsAPI& GetGraphicsAPI();
        RenderQueue& GetRenderQueue();

    private:
        GLFWwindow* window;
        std::unique_ptr<Application> application;
        std::chrono::steady_clock::time_point lastTimePoint;

        InputManager inputManager;
        GraphicsAPI graphics;
        RenderQueue renderQueue;
    };
}
