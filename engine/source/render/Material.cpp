//
// Created by Marcin Lusa on 17/12/2025.
//

#include "Material.h"
#include "graphics/ShaderProgram.h"

#include <utility>

void eng::Material::SetShaderProgram(std::shared_ptr<ShaderProgram>& shaderProgram) {
    shader = shaderProgram;
}

void eng::Material::SetParamValue(const std::string &name, float value) {
    params[name] = value;
}

void eng::Material::SetParamValue(const std::string &name, float v0, float v1) {
    params2f[name] = std::make_pair(v0, v1);
}

void eng::Material::Bind() {
    if (!shader) {
        return;
    }

    shader->Bind();

    for (auto param : params) {
        shader->SetUniform(param.first, param.second);
    }

    for (auto param : params2f) {
        shader->SetUniform(param.first, param.second.first, param.second.second);
    }
}
