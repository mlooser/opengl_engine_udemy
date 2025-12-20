//
// Created by Marcin Lusa on 16/12/2025.
//

#include "ShaderProgram.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/Texture.h"


eng::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(shaderProgram);
}

void eng::ShaderProgram::Bind() {
    glUseProgram(shaderProgram);
    currentTextureUnit = 0;
}

GLint eng::ShaderProgram::GetUniformLocation(const std::string &name) {
    auto it = uniformLocationsCache.find(name);
    if (it != uniformLocationsCache.end()) {
        return it->second;
    }

    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    uniformLocationsCache[name] = location;
    return location;

}

void eng::ShaderProgram::SetUniform(const std::string &name, float value) {
    auto location = GetUniformLocation(name);
    glUniform1f(location, value);
}

void eng::ShaderProgram::SetUniform(const std::string &name, float v0, float v1) {
    auto location = GetUniformLocation(name);
    glUniform2f(location, v0, v1);
}

void eng::ShaderProgram::SetUniform(const std::string &name, const glm::mat4& matrix) {
    auto location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void eng::ShaderProgram::SetTexture(const std::string &name, Texture *texture) {
    auto location = GetUniformLocation(name);

    glActiveTexture(GL_TEXTURE0 + currentTextureUnit);
    glBindTexture(GL_TEXTURE_2D, texture->GetId());
    glUniform1i(location, currentTextureUnit);
    currentTextureUnit++;
}
