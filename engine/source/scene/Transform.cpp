//
// Created by Marcin Lusa on 19/12/2025.
//

#include "Transform.h"

#include <glm/vec4.hpp>

using namespace glm;

vec3 eng::Transform::CalculateForwardVector() const {
    mat4 rotMatrix(1.0f);

    rotMatrix = rotate(rotMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
    rotMatrix = rotate(rotMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
    rotMatrix = rotate(rotMatrix, rotation.z, vec3(0.0f, 0.0f, 1.0f));

    vec3 forwardVector = normalize(
        vec3(rotMatrix * vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    return forwardVector;
}

vec3 eng::Transform::CalculateRightVector() const {
    mat4 rotMatrix(1.0f);

    rotMatrix = rotate(rotMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
    rotMatrix = rotate(rotMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
    rotMatrix = rotate(rotMatrix, rotation.z, vec3(0.0f, 0.0f, 1.0f));

    vec3 forwardVector = normalize(
        vec3(rotMatrix * vec4(1.0f, 0.0f, 0.0f, 0.0f)));
    return forwardVector;
}
