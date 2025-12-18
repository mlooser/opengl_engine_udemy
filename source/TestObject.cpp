//
// Created by Marcin Lusa on 18/12/2025.
//

#include "TestObject.h"

#include <GLFW/glfw3.h>
#include <iostream>

TestObject::TestObject() {
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

        uniform vec4 uModel;

        void main(){
            vColor = color;
            gl_Position = uModel * vec4(position, 1.0);
        }
    )";

    auto shaderProgram = eng::GraphicsAPI::CreateShaderProgram(
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

    mesh = std::make_shared<eng::Mesh>(vertexLayout, vertexes, vertexIndices);
}

void TestObject::Update(float deltaTime) {
    GameObject::Update(deltaTime);

    auto &inputManager = engine->GetInputManager();

    float speed = 1.0f;

    if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
        position += glm::vec3(-1.0f, 0.0f, 0.0f) * deltaTime * speed;
    }
    if (inputManager.IsKeyPressed(GLFW_KEY_D)) {
        position -= glm::vec3(1.0f, 0.0f, 0.0f) * deltaTime * speed;
    }
    if (inputManager.IsKeyPressed(GLFW_KEY_W)) {
        position += glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * speed;
    }
    if (inputManager.IsKeyPressed(GLFW_KEY_S)) {
        position -= glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * speed;
    }

    eng::RenderCommand renderCommand{
        mesh.get(),
        &material,
        GetWorldTransform()
    };

    engine->GetRenderQueue().Submit(renderCommand);
}
