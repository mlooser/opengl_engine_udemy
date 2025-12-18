#pragma once

#include <memory>

#include "scene/Component.h"

namespace eng {
    class Mesh;
    class Material;

    class MeshComponent : public Component {
        COMPONENT(MeshComponent)

    public:
        MeshComponent(const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Material> &material);
        void Update(float deltaTime) override;

    private:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
    };
}
