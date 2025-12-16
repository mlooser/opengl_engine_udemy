//
// Created by Marcin Lusa on 16/12/2025.
//

#include "InputManager.h"

#include <iostream>

void eng::InputManager::SetKeyPressed(int key, bool isPressed) {
    if (key < 0 || key >= pressed.size()) {
        return;
    }

    std::cout << key << " " << isPressed << std::endl;
    pressed[key] = isPressed;
}

bool eng::InputManager::IsKeyPressed(int key) {
    if (key < 0 || key >= pressed.size()) {
        return false;
    }

    return pressed[key];
}
