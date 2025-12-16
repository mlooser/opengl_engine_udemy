//
// Created by Marcin Lusa on 16/12/2025.
//

#include "GraphicsAPI.h"

#include <GL/glew.h>
#include <iostream>

#include "ShaderProgram.h"


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
    program->Bind();
}
