//
// Created by Marcin Lusa on 17/12/2025.
//

#include "Material.h"
#include "graphics/ShaderProgram.h"

#include <utility>
#include "graphics/Texture.h"
#include "io/FileSystem.h"
#include <nlohmann/json.hpp>

#include "graphics/GraphicsAPI.h"

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

std::shared_ptr<eng::Material> eng::Material::Load(FileSystem& fileSystem, const std::string &path) {
    auto materialJson = fileSystem.LoadAssetFileText(path);

    if (materialJson.empty()) {
        //TODO ML exception
        return nullptr;
    }

    nlohmann::json json = nlohmann::json::parse(materialJson);
    std::shared_ptr<Material> result;

    if (json.contains("shader"))
    {
        auto shaderObj = json["shader"];
        std::string vertexPath   = shaderObj.value("vertex", "");
        std::string fragmentPath = shaderObj.value("fragment", "");

        auto vertexSrc   = fileSystem.LoadAssetFileText(vertexPath);
        auto fragmentSrc = fileSystem.LoadAssetFileText(fragmentPath);

        auto shaderProgram = GraphicsAPI::CreateShaderProgram(vertexSrc, fragmentSrc);
        if (!shaderProgram) return nullptr;

        result = std::make_shared<Material>();
        result->SetShaderProgram(shaderProgram);
    }

    if (json.contains("params") && result)
    {
        auto paramsObj = json["params"];

        // Floats
        if (paramsObj.contains("float"))
        {
            for (auto& p : paramsObj["float"])
            {
                std::string name  = p.value("name", "");
                float value = p.value("value", 0.0f);
                result->SetParamValue(name, value);
            }
        }

        // Float2
        if (paramsObj.contains("float2"))
        {
            for (auto& p : paramsObj["float2"])
            {
                std::string name = p.value("name", "");
                float v0 = p.value("value0", 0.0f);
                float v1 = p.value("value1", 0.0f);
                result->SetParamValue(name, v0, v1);
            }
        }

        // Textures
        if (paramsObj.contains("textures"))
        {
            for (auto& p : paramsObj["textures"])
            {
                std::string name = p.value("name", "");
                std::string texPath = p.value("path", "");
                auto texture = Texture::LoadTexture(fileSystem, texPath);
                if (texture)
                {
                    result->SetParamValue(name, texture);
                }
            }
        }
    }

    return result;
}
