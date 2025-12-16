//
// Created by Marcin Lusa on 16/12/2025.
//

#include "Game.h"

#include <iostream>
#include <ostream>

#include "GLFW/glfw3.h"


bool Game::Initialize(eng::Engine *owner) {
    return Application::Initialize(owner);
}

void Game::Shutdown() {

}

void Game::Update(float deltaTime) {

    auto& inputManager = owner->GetInputManager();

    if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
        std::cout <<"[A]" << std::endl;
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        std::cout <<"Should be closed" << std::endl;
        SetNeedsToBeClosed(true);
    }
}
