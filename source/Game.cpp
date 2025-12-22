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

    auto tes1 = scene.CreateChildGameObject<TestObject>(owner, "test object");
    tes1->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));

    auto tes2 = scene.CreateChildGameObject<TestObject>(owner, "test object");
    tes2->SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));

    auto* cameraHolder = scene.CreateChildGameObject(owner, "Camera");
    cameraHolder->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    cameraHolder->AddComponent<eng::CameraComponent>();
    cameraHolder->AddComponent<eng::PlayerControllerComponent>();

    auto suzanneMesh = eng::Mesh::Load(owner->GetFileSystem(), "models/suzanne/Suzanne.gltf");
    auto suzanneMaterial = eng::Material::Load(owner->GetFileSystem(), "materials/suzanne.mat");
    
    auto suzanneObj = scene.CreateChildGameObject(owner, "Suzanne");
    suzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
    suzanneObj->AddComponent<eng::MeshComponent>(suzanneMesh, suzanneMaterial);

    scene.SetMainCamera(cameraHolder);

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
