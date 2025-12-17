#pragma once
#include <array>

namespace eng {
    class InputManager {

    public:
        void SetKeyPressed(int key, bool isPressed);
        bool IsKeyPressed(int key);

    private:
        std::array<bool, 257> pressed = {false}; //TODO change to bitset
    };
}
