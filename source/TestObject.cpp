//
// Created by Marcin Lusa on 18/12/2025.
//

#include "TestObject.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include "scene/components/MeshComponent.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::shared_ptr<eng::Texture> TestObject::loadTexture() {
    eng::FileSystem& fileSystem = GetEngine()->GetFileSystem();
    auto path = fileSystem.GetAssetsFolder() / "brick.png";

    int width, height, channels;
    unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

    if (data) {
        std::cout << "Loading image " << width << "x" << height << "x" << channels << std::endl;
    }
    auto texture = std::make_shared<eng::Texture>(width, height, channels, data);
    stbi_image_free(data);
    return texture;
}

TestObject::TestObject() {
    std::string fragmentShaderSource = R"(
         #version 330 core
         out vec4 FragColor;

         in vec3 vColor;
         in vec2 vUV;

        uniform sampler2D brickTexture;

         void main(){
             vec4 texColor = texture(brickTexture, vUV);
             FragColor = texColor * vec4(vColor, 1.f);
         }
     )";

    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;
        layout (location = 2) in vec2 uv;

        out vec3 vColor;
        out vec2 vUV;

        uniform mat4 uModel;
        uniform mat4 uView;
        uniform mat4 uProjection;

        void main(){
            vColor = color;
            vUV = uv;
            gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
        }
    )";

    auto shaderProgram = eng::GraphicsAPI::CreateShaderProgram(
        vertexShaderSource,
        fragmentShaderSource);


    std::shared_ptr<eng::Texture> texture = loadTexture();

    auto material = std::make_shared<eng::Material>();
    material->SetShaderProgram(shaderProgram);
    material->SetParamValue("brickTexture", texture);

    std::cout << "Shader Program id =" << shaderProgram->GetShaderProgram() << std::endl;

    std::vector<float> vertexes = {
        // Front face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Top face
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Right face
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Left face
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Bottom face
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Back face
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f

    };

    std::vector<unsigned int> vertexIndices = {
        // front face
        0, 1, 2,
        0, 2, 3,
        // top face
        4, 5, 6,
        4, 6, 7,
        // right face
        8, 9, 10,
        8, 10, 11,
        // left face
        12, 13, 14,
        12, 14, 15,
        // bottom face
        16, 17, 18,
        16, 18, 19,
        // back face
        20, 21, 22,
        20, 22, 23
    };

    eng::VertexLayout vertexLayout;

    //Position
    vertexLayout.elements.push_back({0, 3, GL_FLOAT, 0});

    //Color
    vertexLayout.elements.push_back({1, 3, GL_FLOAT, sizeof(float) * 3});

    //UV
    vertexLayout.elements.push_back({2, 2, GL_FLOAT, sizeof(float) * 6});

    vertexLayout.stride = sizeof(float) * 8;

    auto mesh = std::make_shared<eng::Mesh>(vertexLayout, vertexes, vertexIndices);

    AddComponent<eng::MeshComponent>(mesh, material);
}

void TestObject::Update(float deltaTime) {
    GameObject::Update(deltaTime);
}
