#pragma once
#include <array>

#include "glm/vec2.hpp"

namespace eng {
    class InputManager {

    public:
        void SetKeyPressed(int key, bool isPressed);
        bool IsKeyPressed(int key);

        void SetMouseButtonPressed(int button, bool isPressed);
        bool IsMouseButtonPressed(int button);


        void UpdateMousePositionThisFrame(const glm::vec2& position);
        void UpdateLastFrameMousePositionThisFrame();
        glm::vec2 CalculateMouseDeltaSinceLastFrame() const;

        //TODO ML remove manual set
        void SetMousePositionLastFrame(const glm::vec2& position);
        glm::vec2 GetMousePositionLastFrame();

        void SetMousePositionThisFrame(const glm::vec2& position);
        glm::vec2 GetMousePositionThisFrame();



    private:
        std::array<bool, 257> pressed = {false}; //TODO ML change to bitset
        std::array<bool, 16> mouseKeys = {false};

        glm::vec2 mousePositionLastFrame = glm::vec2(0.0f);
        glm::vec2 mousePositionThisFrame = glm::vec2(0.0f);
    };
}
