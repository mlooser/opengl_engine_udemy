//
// Created by Marcin Lusa on 16/12/2025.
//

#include "GraphicsAPI.h"

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "render/Material.h"
#include "render/Mesh.h"


std::shared_ptr<eng::ShaderProgram> eng::GraphicsAPI::CreateShaderProgram(
    const std::string &vertexSource,
    const std::string &fragmentSource) {
    GLint success;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexShaderSourcePointer = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        std::cout << "Vertex shader compilation error!" << std::endl;
        char info[1024];
        glGetShaderInfoLog(vertexShader, 1024, nullptr, info);
        std::cout << info << std::endl;
        return nullptr;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSourcePointer = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        std::cout << "Fragment shader compilation error!" << std::endl;
        char info[1024];
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, info);
        std::cout << info << std::endl;
        return nullptr;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetShaderiv(program, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        std::cout << "Shader compilation error!" << std::endl;
        char info[1024];
        glGetShaderInfoLog(program, 1024, nullptr, info);
        std::cout << info << std::endl;
        return nullptr;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return std::make_shared<ShaderProgram>(program);
}

void eng::GraphicsAPI::BindShaderProgram(ShaderProgram *program) {
    if (program) {
        program->Bind();
    }
}

void eng::GraphicsAPI::BindMaterial(Material *material) {
    if (material) {
        material->Bind();
    }
}

void eng::GraphicsAPI::BindMesh(Mesh *mesh) {
    if (mesh) {
        mesh->Bind();
    }
}

void eng::GraphicsAPI::DrawMesh(Mesh *mesh) {
    if (mesh) {
        mesh->Draw();
    }
}

void eng::GraphicsAPI::SetClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void eng::GraphicsAPI::ClearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void eng::GraphicsAPI::Init() {
    glEnable(GL_DEPTH_TEST);
}

GLuint eng::GraphicsAPI::CreateVertexBuffer(const std::vector<float> &vertices) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

GLuint eng::GraphicsAPI::CreateIndexBuffer(const std::vector<uint32_t> &indices) {
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return ebo;
}
