//
// Created by Marcin Lusa on 16/12/2025.
//

#include "Engine.h"

#include <iostream>

#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene/components/CameraComponent.h"


bool initWindow(GLFWwindow *&window, eng::Engine* engine);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mode);
void mouseCallback(GLFWwindow *window, int button, int action, int mods);
void mousePositionCallback(GLFWwindow *window, double xpos, double ypos);

bool eng::Engine::Initialize() {
    std::cout << "Engine Initialized" << std::endl;

    if (!application)
        return false;

    if (!initWindow(window, this))
        return false;

    return application->Initialize(this);
}

void eng::Engine::Shutdown() {
    if (application) {
        application->Shutdown();
        application.reset();
    }

    glfwTerminate();
    window = nullptr;
}

float eng::Engine::CalculateAspectRatio() const {
    int windowWidth = 0;
    int windowHeight = 0;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    return aspectRatio;
}

eng::CameraData eng::Engine::CalculateCameraData() {
    CameraData cameraData;
    if (GameObject* cameraOwner = application->GetScene().GetMainCamera()) {
        if (CameraComponent* camera = cameraOwner->GetComponent<CameraComponent>()) {

            float aspectRatio = CalculateAspectRatio();

            cameraData.projectionMatrix = camera->GetProjectionMatrix(aspectRatio);
            cameraData.viewMatrix = camera->GetViewMatrix();
        }
    }
    return cameraData;
}

void eng::Engine::Render() {
    graphics.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    graphics.ClearBuffers();

    CameraData cameraData = CalculateCameraData();

    renderQueue.Draw(graphics, cameraData);

    glfwSwapBuffers(window);
}

void eng::Engine::Run() {
    if (!application) return;

    lastTimePoint = std::chrono::high_resolution_clock::now();

    while (
        !glfwWindowShouldClose(window)
        && !application->NeedsToBeClosed()) {

        glfwPollEvents();

        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTimePoint).count();
        lastTimePoint = now;
        application->Update(deltaTime);

        Render();

        inputManager.UpdateLastFrameMousePositionThisFrame();
    }
}

void eng::Engine::SetApplication(Application *app) {
    application.reset(app);
}

eng::InputManager & eng::Engine::GetInputManager() {
    return inputManager;
}

eng::GraphicsAPI & eng::Engine::GetGraphicsAPI() {
    return graphics;
}

eng::RenderQueue & eng::Engine::GetRenderQueue() {
    return renderQueue;
}

bool initWindow(GLFWwindow *&window, eng::Engine* engine) {
    std::cout << "Initializing window" << std::endl;
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Store the Engine pointer in the window's user pointer
    glfwSetWindowUserPointer(window, engine);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetCursorPosCallback(window, mousePositionCallback);

    std::cout << "Window initialized" << std::endl;

    return true;
}

void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mode) {
    eng::Engine* engine = static_cast<eng::Engine*>(glfwGetWindowUserPointer(window));
    if (!engine) return;

    eng::InputManager& inputManager = engine->GetInputManager();

    if (action == GLFW_PRESS) {
        inputManager.SetKeyPressed(key, true);
    }
    else if (action == GLFW_RELEASE) {
        inputManager.SetKeyPressed(key, false);
    }
}

void mouseCallback(GLFWwindow *window, int button, int action, int mods) {
    eng::Engine* engine = static_cast<eng::Engine*>(glfwGetWindowUserPointer(window));
    if (!engine) return;

    eng::InputManager& inputManager = engine->GetInputManager();

    if (action == GLFW_PRESS) {
        inputManager.SetMouseButtonPressed(button, true);
    }
    else if (action == GLFW_RELEASE) {
        inputManager.SetMouseButtonPressed(button, false);
    }
}

void mousePositionCallback(GLFWwindow *window, double xpos, double ypos) {
    eng::Engine* engine = static_cast<eng::Engine*>(glfwGetWindowUserPointer(window));
    if (!engine) return;

    eng::InputManager& inputManager = engine->GetInputManager();

    inputManager.UpdateMousePositionThisFrame(glm::vec2(xpos, ypos));
}
