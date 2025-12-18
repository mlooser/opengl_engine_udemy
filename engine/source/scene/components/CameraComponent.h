#pragma once

#include <glm/mat4x4.hpp>

#include "scene/Component.h"

namespace eng {
    class CameraComponent : public Component {
        COMPONENT(CameraComponent)

    public:
        void Update(float deltaTime) override;

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    private:
        float fov = 60.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;
    };
}
