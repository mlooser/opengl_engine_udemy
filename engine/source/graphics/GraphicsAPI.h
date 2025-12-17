#pragma once
#include <memory>

#include "GL/glew.h"
#include "render/Mesh.h"

namespace eng {
    class ShaderProgram;
    class Material;
    class Mesh;

    class GraphicsAPI {
    public:
        static GLuint CreateVertexBuffer(const std::vector<float> & vertices);
        static GLuint CreateIndexBuffer(const std::vector<uint32_t> & indices);

    public:
        std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);

        void BindShaderProgram(ShaderProgram* program);
        void BindMaterial(Material* material);
        void BindMesh(Mesh* mesh);
        void DrawMesh(Mesh* mesh);

        void SetClearColor(float r, float g, float b, float a);
        void ClearBuffers();

    };
}


