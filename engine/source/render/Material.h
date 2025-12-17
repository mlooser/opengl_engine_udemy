#pragma once

#include <memory>
#include <string>
#include <unordered_map>


namespace eng {
    class ShaderProgram;

    class Material {
    public:
        void SetShaderProgram(std::shared_ptr<ShaderProgram>& shaderProgram);
        void SetParamValue(const std::string& name, float value);
        void Bind();

    private:
        std::shared_ptr<ShaderProgram> shader;
        std::unordered_map<std::string, float> params;
    };
}
