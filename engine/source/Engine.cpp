//
// Created by Marcin Lusa on 16/12/2025.
//

#include "Engine.h"

#include "Application.h"

bool eng::Engine::Initialize() {
    if (!application)
        return false;

    return application->Initialize();
}

void eng::Engine::Shutdown() {
    if (application) {
        application->Shutdown();
        application.reset();
    }
}

void eng::Engine::Run() {
    if (!application) return;

    lastTimePoint = std::chrono::high_resolution_clock::now();

    while (!application->NeedsToBeClosed()) {
        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTimePoint).count();
        application->Update(deltaTime);
    }
}

void eng::Engine::SetApplication(Application *app) {
    application.reset(app);
}
