#pragma once
#include <vector>

#include "glm/mat4x4.hpp"

namespace eng {
    class Mesh;
    class Material;
    class GraphicsAPI;

    struct RenderCommand {
        Mesh *mesh;
        Material *material;
        glm::mat4 modelMatrix;
    };

    class RenderQueue {
    public:
        void Submit(const RenderCommand& command);
        void Draw(GraphicsAPI& graphicsAPI);

    private:
        std::vector<RenderCommand> renderCommands;
    };
}
