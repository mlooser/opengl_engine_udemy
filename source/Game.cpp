//
// Created by Marcin Lusa on 16/12/2025.
//

#include "Game.h"

#include <iostream>
#include <ostream>

#include "GLFW/glfw3.h"


bool Game::Initialize(eng::Engine *owner) {
    Application::Initialize(owner);

    std::string fragmentShaderSource = R"(
         #version 330 core
         out vec4 FragColor;

         in vec3 vColor;

         void main(){
             FragColor = vec4(vColor, 1.f);
         }
     )";

    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        out vec3 vColor;

        void main(){
            vColor = color;
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
        }
    )";

    auto shaderProgram = owner->GetGraphicsAPI().CreateShaderProgram(
        vertexShaderSource,
        fragmentShaderSource);

    material.SetShaderProgram(shaderProgram);

    std::cout << "Shader Program id =" << shaderProgram->GetShaderProgram() << std::endl;

    std::vector<float> vertexes = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    std::vector<unsigned int> vertexIndices = {
        0, 1, 2,
        0, 2, 3
    };

    eng::VertexLayout vertexLayout;

    //Position
    vertexLayout.elements.push_back({0, 3, GL_FLOAT, 0});

    //Color
    vertexLayout.elements.push_back({1, 3, GL_FLOAT, sizeof(float) * 3});

    vertexLayout.stride = sizeof(float) * 6;

    mesh = std::make_unique<eng::Mesh>(vertexLayout, vertexes, vertexIndices);

    return true;
}

void Game::Shutdown() {
}

void Game::Update(float deltaTime) {
    auto &inputManager = owner->GetInputManager();

    if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
        std::cout << "[A]" << std::endl;
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        std::cout << "Should be closed" << std::endl;
        SetNeedsToBeClosed(true);
    }


    eng::RenderCommand renderCommand{
        mesh.get(),
        &material
    };

    owner->GetRenderQueue().Submit(renderCommand);
}
