#pragma once
#include "scene/Component.h"

namespace eng {
    class PlayerControllerComponent: public Component {
        COMPONENT(PlayerControllerComponent)

    public:
        void Update(float deltaTime) override;

    private:
        float mouseSensitivity = 0.1f;
        float movementSpeed = 1.0f;
    };
}
