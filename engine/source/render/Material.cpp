//
// Created by Marcin Lusa on 17/12/2025.
//

#include "Material.h"
#include "graphics/ShaderProgram.h"

#include <utility>
#include "graphics/Texture.h"

void eng::Material::SetShaderProgram(std::shared_ptr<ShaderProgram>& shaderProgram) {
    shader = shaderProgram;
}

eng::ShaderProgram * eng::Material::GetShaderProgram() {
    return shader.get();
}

void eng::Material::SetParamValue(const std::string &name, float value) {
    params[name] = value;
}

void eng::Material::SetParamValue(const std::string &name, float v0, float v1) {
    params2f[name] = std::make_pair(v0, v1);
}

void eng::Material::SetParamValue(const std::string &name, std::shared_ptr<Texture>& texture) {
    textures[name] = texture;
}

void eng::Material::Bind() {
    if (!shader) {
        return;
    }

    shader->Bind();

    for (auto& param : params) {
        shader->SetUniform(param.first, param.second);
    }

    for (auto& param : params2f) {
        shader->SetUniform(param.first, param.second.first, param.second.second);
    }

    for (auto& param : textures) {
        shader->SetTexture(param.first, param.second.get());
    }
}
