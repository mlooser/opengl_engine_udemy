#pragma once

#include <GL/glew.h>
#include "graphics/VertexLayout.h"

namespace eng {

    class GraphicsAPI;
    class FileSystem;

    class Mesh {

    public:
        void UnbindBuffers();

        void SetVerticesLayout();

        void BindVAO();

        void BindEBO();

        void BindVBO();

        void CalculateVertexCount(std::vector<float> &vertices);

        void CalculateIndexCount(std::vector<uint32_t> &indices);

        Mesh(const VertexLayout& layout, std::vector<float>& vertices, std::vector<uint32_t>& indices);
        Mesh(const VertexLayout& layout, std::vector<float>& vertices);
        Mesh(const Mesh& mesh) = delete;
        Mesh& operator=(const Mesh& mesh) = delete;

        void Bind();
        void Draw();

        static std::shared_ptr<Mesh> Load(FileSystem& fileSystem, const std::string& assetName);
    private:
        GLuint vbo = 0;
        GLuint ebo = 0;
        GLuint vao = 0;

        VertexLayout vertexLayout;
        size_t vertexCount = 0;
        size_t indexCount = 0;
    };

}