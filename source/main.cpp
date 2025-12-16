#include <iostream>
#include <ostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (glewInit()!= GLEW_OK) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}