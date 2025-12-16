#pragma once
#include <memory>

#include <chrono>

namespace eng {
    class Application;

    class Engine {
    public:
        bool Initialize();

        void Shutdown();

        void Run();

        void SetApplication(Application* app);

    private:
        std::unique_ptr<Application> application;
        std::chrono::steady_clock::time_point lastTimePoint;
    };
}
