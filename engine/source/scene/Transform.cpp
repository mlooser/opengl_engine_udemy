//
// Created by Marcin Lusa on 19/12/2025.
//

#include "Transform.h"

#include <glm/vec4.hpp>

using namespace glm;

vec3 eng::Transform::CalculateForwardVector() const {
    return rotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

vec3 eng::Transform::CalculateRightVector() const {
    return rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}
