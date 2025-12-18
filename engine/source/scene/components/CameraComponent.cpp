//
// Created by Marcin Lusa on 18/12/2025.
//

#include "CameraComponent.h"

#include "scene/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

void eng::CameraComponent::Update(float deltaTime) {
    Component::Update(deltaTime);
}

glm::mat4 eng::CameraComponent::GetViewMatrix() const {
    return glm::inverse(owner->GetWorldTransform());
}

glm::mat4 eng::CameraComponent::GetProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(fov),aspectRatio, nearPlane, farPlane);
}
