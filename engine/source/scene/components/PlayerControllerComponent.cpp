//
// Created by Marcin Lusa on 19/12/2025.
//

#include "PlayerControllerComponent.h"

#include "Engine.h"
#include "GLFW/glfw3.h"
#include "input/InputManager.h"
#include "scene/GameObject.h"
#include <glm/gtc/quaternion.hpp>

void eng::PlayerControllerComponent::Update(float deltaTime) {
    Component::Update(deltaTime);

    InputManager& inputManager = owner->GetEngine()->GetInputManager();

    if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        glm::vec2 mouseDelta = inputManager.CalculateMouseDeltaSinceLastFrame();
        mouseDelta *= deltaTime * mouseSensitivity;

        glm::quat& rotation = owner->GetTransform().rotation;

        float yAngle = -mouseDelta.x;
        glm::quat yRotation = glm::angleAxis(yAngle, glm::vec3(0.0f, 1.0f, 0.0f));

        float xAngle = -mouseDelta.y;
        glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
        glm::quat xRotation = glm::angleAxis(xAngle, right);

        glm::quat deltaRotation = yRotation * xRotation;

        owner->GetTransform().rotation = glm::normalize( deltaRotation * rotation);
    }

    glm::vec3 position = owner->GetTransform().position;

    glm::vec3 right = owner->GetTransform().CalculateRightVector();
    glm::vec3 forward = owner->GetTransform().CalculateForwardVector();

    if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
        position -= right  * deltaTime * movementSpeed;
    }
    if (inputManager.IsKeyPressed(GLFW_KEY_D)) {
        position += right * deltaTime * movementSpeed;
    }
    if (inputManager.IsKeyPressed(GLFW_KEY_W)) {
        position += forward * deltaTime * movementSpeed;
    }
    if (inputManager.IsKeyPressed(GLFW_KEY_S)) {
        position -= forward * deltaTime * movementSpeed;
    }
    owner->GetTransform().position = position;
}
