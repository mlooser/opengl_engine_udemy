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
         uniform vec4 uColor;

         void main(){
             FragColor = vec4(vColor, 1.f) * uColor;
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

    std::cout << "Shader Program id =" << shaderProgram->GetShaderProgram() << std::endl;

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
