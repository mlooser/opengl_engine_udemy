#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

#include "graphics/Texture.h"


namespace eng {
    class ShaderProgram;
    class Texture;
    class FileSystem;

    class Material {
    public:
        void SetShaderProgram(std::shared_ptr<ShaderProgram>& shaderProgram);
        ShaderProgram* GetShaderProgram();
        void SetParamValue(const std::string& name, float value);
        void SetParamValue(const std::string& name, float v0, float v1);
        void SetParamValue(const std::string& name, std::shared_ptr<Texture>& texture);

        void Bind();

        static std::shared_ptr<Material> Load(FileSystem& fileSystem, const std::string& path);

    private:
        std::shared_ptr<ShaderProgram> shader;
        std::unordered_map<std::string, float> params;
        std::unordered_map<std::string, std::pair<float, float>> params2f;
        std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    };
}
