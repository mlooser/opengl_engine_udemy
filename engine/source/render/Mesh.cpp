//
// Created by Marcin Lusa on 17/12/2025.
//

#include "Mesh.h"
#include "graphics/GraphicsAPI.h"

#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include "io/FileSystem.h"

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

std::shared_ptr<eng::Mesh> eng::Mesh::Load(FileSystem &fileSystem, const std::string &assetName) {
    auto contents = fileSystem.LoadAssetFileText(assetName);

    if (contents.empty()) {
        return nullptr;
    }

    auto readFloats = [](const cgltf_accessor* acc, cgltf_size i, float* out, int n)
    {
        std::fill(out, out + n, 0.0f); // zero-init
        return cgltf_accessor_read_float(acc, i, out, n) == 1;
    };

    auto readIndex = [](const cgltf_accessor* acc, cgltf_size i)
    {
        cgltf_uint out = 0;
        cgltf_bool ok = cgltf_accessor_read_uint(acc, i, &out, 1);
        return ok ? static_cast<uint32_t>(out) : 0;
    };

    cgltf_options options = {};
    cgltf_data* data = nullptr;

    cgltf_result res = cgltf_parse(&options, contents.data(), contents.size(), &data);
    if (res != cgltf_result_success) return nullptr;

    auto fullPath = fileSystem.GetAssetsFolder() / assetName;

    // Now load the .bin buffer(s)
    res = cgltf_load_buffers(&options, data, fullPath.remove_filename().string().c_str());
    if (res != cgltf_result_success) {
        cgltf_free(data);
        return nullptr;
    }

    std::shared_ptr<Mesh> result = nullptr;

    for (cgltf_size mi = 0; mi < data->meshes_count && !result; ++mi)
    {
        const cgltf_mesh& mesh = data->meshes[mi];
        for (cgltf_size pi = 0; pi < mesh.primitives_count && !result; ++pi)
        {
            const cgltf_primitive& prim = mesh.primitives[pi];
            if (prim.type != cgltf_primitive_type_triangles) continue;

            VertexLayout vertexLayout;
            const cgltf_accessor* accessors[3] = { nullptr, nullptr, nullptr };

            for (cgltf_size ai = 0; ai < prim.attributes_count; ++ai)
            {
                const cgltf_attribute& attr = prim.attributes[ai];
                const cgltf_accessor*  acc  = attr.data;
                if (!acc) continue;

                VertexElement element{};
                element.elementType = GL_FLOAT;

                switch (attr.type)
                {
                    case cgltf_attribute_type_position:
                        accessors[VertexElement::PositionIndex] = acc;
                        element.attributeLocation  = VertexElement::PositionIndex;
                        element.numberOfComponents = 3;
                        break;
                    case cgltf_attribute_type_color:
                        if (attr.index != 0) continue;
                        accessors[VertexElement::ColorIndex] = acc;
                        element.attributeLocation  = VertexElement::ColorIndex;
                        element.numberOfComponents = 3;
                        break;
                    case cgltf_attribute_type_texcoord:
                        if (attr.index != 0) continue;
                        accessors[VertexElement::UVIndex] = acc;
                        element.attributeLocation  = VertexElement::UVIndex;
                        element.numberOfComponents = 2;
                        break;
                    default:
                        continue;
                }

                if (element.numberOfComponents > 0)
                {
                    element.offset = vertexLayout.stride;
                    vertexLayout.stride += element.numberOfComponents * sizeof(float);
                    vertexLayout.elements.push_back(element);
                }
            }

            if (!accessors[VertexElement::PositionIndex])
            {
                continue;
            }
            auto vertexCount = accessors[VertexElement::PositionIndex]->count;

            std::vector<float> vertices;
            vertices.resize((vertexLayout.stride / sizeof(float)) * vertexCount);

            for (cgltf_size vi = 0; vi < vertexCount; ++vi)
            {
                for (auto& el : vertexLayout.elements)
                {
                    if (!accessors[el.attributeLocation]) continue;

                    auto index = (vi * vertexLayout.stride + el.offset) / sizeof(float);
                    float* outData = &vertices[index];
                    readFloats(accessors[index], vi, outData, el.numberOfComponents);
                }
            }

            if (prim.indices)
            {
                auto indexCount = prim.indices->count;
                std::vector<uint32_t> indices(indexCount);
                for (cgltf_size i = 0; i < indexCount; ++i)
                {
                    indices[i] = readIndex(prim.indices, i);
                }
                result = std::make_shared<Mesh>(vertexLayout, vertices, indices);
            }
            else
            {
                result = std::make_shared<Mesh>(vertexLayout, vertices);
            }

            if (result)
            {
                break;
            }
        }

        if (result)
        {
            break;
        }
    }

    cgltf_free(data);

    return result;
}
