//
// Created by Marcin Lusa on 16/12/2025.
//

#include "Game.h"

#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>

#include "TestObject.h"

bool Game::Initialize(eng::Engine *owner) {
    Application::Initialize(owner);

    scene.CreateChildGameObject<TestObject>(owner, "test object");

    return true;
}

void Game::Shutdown() {
}

void Game::Update(float deltaTime) {
    auto &inputManager = owner->GetInputManager();

    scene.Update(deltaTime);

    if (inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        std::cout << "Should be closed" << std::endl;
        SetNeedsToBeClosed(true);
    }
}
