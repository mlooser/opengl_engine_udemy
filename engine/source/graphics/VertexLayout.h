#pragma once

#include <vector>
#include <GL/glew.h>

namespace eng {
    struct VertexElement {
        GLuint attributeLocation = 0;
        GLuint numberOfComponents = 0;
        GLuint elementType = 0; // Like GL_FLOAT
        uint32_t offset = 0;

        static constexpr int PositionIndex = 0;
        static constexpr int ColorIndex    = 1;
        static constexpr int UVIndex       = 2;
    };

    struct VertexLayout {
        std::vector<VertexElement> elements;
        uint32_t stride = 0; //total size of a single vertex
    };
}