#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "Texture.h"

namespace eng {
    class Texture;

    class ShaderProgram {
    public:
        ShaderProgram(GLuint shaderProgram)
            : shaderProgram(shaderProgram) {
        }

        ~ShaderProgram();

        ShaderProgram(const ShaderProgram &) = delete;

        ShaderProgram &operator=(const ShaderProgram &) = delete;

        void Bind();

        GLint GetUniformLocation(const std::string &name);

        void SetUniform(const std::string &name, float value);

        void SetUniform(const std::string &name, float v0, float v1);

        void SetUniform(const std::string &name, const glm::mat4 &matrix);

        void SetTexture(const std::string &name, Texture *texture);

        GLuint GetShaderProgram() { return shaderProgram; }

    private:
        std::unordered_map<std::string, GLint> uniformLocationsCache;
        GLuint shaderProgram;
        int currentTextureUnit = 0;
    };
}
