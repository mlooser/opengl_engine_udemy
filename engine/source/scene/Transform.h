#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace eng {
    struct Transform {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        glm::vec3 CalculateForwardVector() const;
        glm::vec3 CalculateRightVector() const;
    };
}