//
// Created by Marcin Lusa on 17/12/2025.
//

#include "Mesh.h"
#include "graphics/GraphicsAPI.h"

void eng::Mesh::UnbindBuffers() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void eng::Mesh::SetVerticesLayout() {
    for (auto &element: vertexLayout.elements) {
        glVertexAttribPointer(
            element.attributeLocation,
            element.numberOfComponents,
            element.elementType,
            GL_FALSE,
            vertexLayout.stride,
            (void *) (uintptr_t) element.offset
        );

        glEnableVertexAttribArray(element.attributeLocation);
    }
}

void eng::Mesh::BindVAO() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void eng::Mesh::BindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void eng::Mesh::BindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void eng::Mesh::CalculateVertexCount(std::vector<float> &vertices) {
    vertexCount = (vertices.size() * sizeof(float)) / vertexLayout.stride;
}

void eng::Mesh::CalculateIndexCount(std::vector<uint32_t> &indices) {
    indexCount = indices.size();
}

eng::Mesh::Mesh(const VertexLayout &layout, std::vector<float> &vertices, std::vector<uint32_t> &indices)
    : vertexLayout(layout) {

    vbo = GraphicsAPI::CreateVertexBuffer(vertices);
    ebo = GraphicsAPI::CreateIndexBuffer(indices);

    BindVAO();
    BindVBO();
    SetVerticesLayout();
    BindEBO();
    UnbindBuffers();
    CalculateVertexCount(vertices);
    CalculateIndexCount(indices);
}

eng::Mesh::Mesh(const VertexLayout &layout, std::vector<float> &vertices)
    : vertexLayout(layout) {

    vbo = GraphicsAPI::CreateVertexBuffer(vertices);

    BindVAO();
    BindVBO();
    SetVerticesLayout();
    UnbindBuffers();
    CalculateVertexCount(vertices);
}

void eng::Mesh::Bind() {
    glBindVertexArray(vao);
}

void eng::Mesh::Draw() {
    if (indexCount > 0) {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
}
