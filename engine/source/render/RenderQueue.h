#pragma once
#include <vector>

namespace eng {
    class Mesh;
    class Material;
    class GraphicsAPI;

    struct RenderCommand {
        Mesh *mesh;
        Material *material;
    };

    class RenderQueue {
    public:
        void Submit(const RenderCommand& command);
        void Draw(GraphicsAPI& graphicsAPI);

    private:
        std::vector<RenderCommand> renderCommands;
    };
}
