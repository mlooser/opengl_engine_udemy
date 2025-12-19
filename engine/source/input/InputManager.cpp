//
// Created by Marcin Lusa on 16/12/2025.
//

#include "InputManager.h"

#include <iostream>

void eng::InputManager::SetKeyPressed(int key, bool isPressed) {
    if (key < 0 || key >= pressed.size()) {
        return;
    }

    pressed[key] = isPressed;
}

bool eng::InputManager::IsKeyPressed(int key) {
    if (key < 0 || key >= pressed.size()) {
        return false;
    }

    return pressed[key];
}

void eng::InputManager::SetMouseButtonPressed(int button, bool isPressed) {
    if (button < 0 || button >= pressed.size()) {
        return;
    }

    pressed[button] = isPressed;
}

bool eng::InputManager::IsMouseButtonPressed(int button) {
    if (button < 0 || button >= pressed.size()) {
        return false;
    }

    return pressed[button];
}

void eng::InputManager::UpdateMousePositionThisFrame(const glm::vec2 &position) {
    UpdateLastFrameMousePositionThisFrame();
    mousePositionThisFrame = position;
}

void eng::InputManager::UpdateLastFrameMousePositionThisFrame() {
    mousePositionLastFrame = mousePositionThisFrame;
}

glm::vec2 eng::InputManager::CalculateMouseDeltaSinceLastFrame() const{
    return mousePositionThisFrame - mousePositionLastFrame;
}

void eng::InputManager::SetMousePositionLastFrame(const glm::vec2 &position) {
    mousePositionLastFrame = position;
}

glm::vec2 eng::InputManager::GetMousePositionLastFrame() {
    return mousePositionLastFrame;
}

void eng::InputManager::SetMousePositionThisFrame(const glm::vec2 &position) {
    mousePositionThisFrame = position;
}

glm::vec2 eng::InputManager::GetMousePositionThisFrame() {
    return mousePositionThisFrame;
}
