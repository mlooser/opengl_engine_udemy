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
    glm::mat4 viewMatrix = glm::mat4_cast(owner->GetTransform().rotation);
    viewMatrix = glm::translate(viewMatrix, owner->GetTransform().position);

    if (owner->GetParent()) {
        viewMatrix = owner->GetParent()->GetWorldTransform() * viewMatrix;
    }
    return glm::inverse(viewMatrix);
}

glm::mat4 eng::CameraComponent::GetProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(fov),aspectRatio, nearPlane, farPlane);
}
