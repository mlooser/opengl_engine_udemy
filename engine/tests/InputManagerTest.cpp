#include <gtest/gtest.h>
#include "input/InputManager.h"
#include <glm/vec2.hpp>

TEST(InputManagerTest, UpdateMousePositionThisFrame) {
    eng::InputManager inputManager;

    inputManager.SetMousePositionThisFrame(glm::vec2(100.0f, 200.0f));
    inputManager.UpdateMousePositionThisFrame(glm::vec2(150.0f, 250.0f));

    EXPECT_EQ(inputManager.GetMousePositionThisFrame(), glm::vec2(150.0f, 250.0f));
    EXPECT_EQ(inputManager.GetMousePositionLastFrame(), glm::vec2(100.0f, 200.0f));
}

TEST(InputManagerTest, UpdateLastFrameMousePositionThisFrame) {
    eng::InputManager inputManager;

    inputManager.SetMousePositionThisFrame(glm::vec2(300.0f, 400.0f));
    inputManager.UpdateLastFrameMousePositionThisFrame();

    EXPECT_EQ(inputManager.GetMousePositionLastFrame(), glm::vec2(300.0f, 400.0f));
    EXPECT_EQ(inputManager.GetMousePositionThisFrame(), glm::vec2(300.0f, 400.0f));
}

TEST(InputManagerTest, CalculateMouseDeltaSinceLastFrame) {
    eng::InputManager inputManager;

    inputManager.SetMousePositionLastFrame(glm::vec2(100.0f, 200.0f));
    inputManager.SetMousePositionThisFrame(glm::vec2(150.0f, 250.0f));

    glm::vec2 delta = inputManager.CalculateMouseDeltaSinceLastFrame();

    EXPECT_EQ(delta, glm::vec2(50.0f, 50.0f));
}
