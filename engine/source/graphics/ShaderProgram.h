#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>

namespace eng {
    class ShaderProgram {

    public:
        ShaderProgram(GLuint shaderProgram)
        : shaderProgram(shaderProgram) {}

        ~ShaderProgram();

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        void Bind();
        GLint GetUniformLocation(const std::string& name);
        void SetUniform(const std::string& name, float value);

        GLuint GetShaderProgram(){return shaderProgram;}

    private:
        std::unordered_map<std::string, GLint> uniformLocationsCache;
        GLuint shaderProgram;
    };
}


