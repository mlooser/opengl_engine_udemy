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
        void Init();
        static GLuint CreateVertexBuffer(const std::vector<float> &vertices);

        static GLuint CreateIndexBuffer(const std::vector<uint32_t> &indices);

        static std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string &vertexSource,
                                                                  const std::string &fragmentSource);

    public:
        void BindShaderProgram(ShaderProgram *program);

        void BindMaterial(Material *material);

        void BindMesh(Mesh *mesh);

        void DrawMesh(Mesh *mesh);

        void SetClearColor(float r, float g, float b, float a);

        void ClearBuffers();
    };
}
