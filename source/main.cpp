
int main() {
    return 0;
}

// #include <iostream>
// #include <ostream>
// #include <vector>
// #include <string>
//
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
//
// bool initWindow(GLFWwindow *&window);
//
// void createFragmentShader(GLuint &fragmentShader);
//
// void createVertexShader(GLuint &vertexShader);
//
// void createShaderProgram(GLuint vertexShader, GLuint fragmentShader, GLuint &program);
//
// void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mode);
//
//
//
// int main() {
//     GLFWwindow *window;
//     if (!initWindow(window))
//         return 1;
//
//     GLuint vertexShader;
//     createVertexShader(vertexShader);
//
//     GLuint fragmentShader;
//     createFragmentShader(fragmentShader);
//
//     GLuint program;
//     createShaderProgram(vertexShader, fragmentShader, program);
//
//     glDetachShader(program, vertexShader);
//     glDetachShader(program, fragmentShader);
//
//
//     std::vector<float> vertexes = {
//         0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//         -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
//         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
//     };
//
//     std::vector<unsigned int> vertexIndices = {
//         0, 1, 2,
//         0, 2, 3
//     };
//
//     GLuint vbo;
//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(float), vertexes.data(), GL_STATIC_DRAW);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//     GLuint ebo;
//     glGenBuffers(1, &ebo);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), vertexIndices.data(),
//                  GL_STATIC_DRAW);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//     GLuint vertexArrayObject;
//     glGenVertexArrays(1, &vertexArrayObject);
//     glBindVertexArray(vertexArrayObject);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
//     glEnableVertexAttribArray(0);
//
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
//
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
//
//     GLint uColorLocation = glGetUniformLocation(program, "uColor");
//
//     while (!glfwWindowShouldClose(window)) {
//         glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//
//         glUseProgram(program);
//         glUniform4f(uColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
//         glBindVertexArray(vertexArrayObject);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
//     glfwTerminate();
//
//     return 0;
// }
//
//
// bool initWindow(GLFWwindow *&window) {
//     if (!glfwInit()) {
//         std::cout << "Failed to initialize GLFW" << std::endl;
//         return false;
//     }
//
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//     window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
//
//     glfwMakeContextCurrent(window);
//
//     if (glewInit() != GLEW_OK) {
//         std::cout << "Failed to initialize GLFW" << std::endl;
//         return false;
//     }
//
//     if (!window) {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return false;
//     }
//
//     glfwSetKeyCallback(window, keyCallback);
//
//     return true;
// }
//
// void createFragmentShader(GLuint &fragmentShader) {
//     std::string fragmentShaderSource = R"(
//         #version 330 core
//         out vec4 FragColor;
//
//         in vec3 vColor;
//         uniform vec4 uColor;
//
//         void main(){
//             FragColor = vec4(vColor, 1.f) * uColor;
//         }
//     )";
//
//     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     const char *fragmentShaderSourcePointer = fragmentShaderSource.c_str();
//     glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, nullptr);
//     glCompileShader(fragmentShader);
//
//     GLint success;
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (success == GL_FALSE) {
//         std::cout << "Fragment shader compilation error!" << std::endl;
//         char info[1024];
//         glGetShaderInfoLog(fragmentShader, 1024, nullptr, info);
//         std::cout << info << std::endl;
//     }
// }
//
// void createVertexShader(GLuint &vertexShader) {
//     GLint success;
//     std::string vertexShaderSource = R"(
//         #version 330 core
//         layout (location = 0) in vec3 position;
//         layout (location = 1) in vec3 color;
//
//         out vec3 vColor;
//
//         void main(){
//             vColor = color;
//             gl_Position = vec4(position.x, position.y, position.z, 1.0);
//         }
//     )";
//
//     vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     const char *vertexShaderSourcePointer = vertexShaderSource.c_str();
//     glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, nullptr);
//     glCompileShader(vertexShader);
//
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (success == GL_FALSE) {
//         std::cout << "Vertex shader compilation error!" << std::endl;
//         char info[1024];
//         glGetShaderInfoLog(vertexShader, 1024, nullptr, info);
//         std::cout << info << std::endl;
//     }
// }
//
// void createShaderProgram(GLuint vertexShader, GLuint fragmentShader, GLuint &program) {
//     program = glCreateProgram();
//     glAttachShader(program, vertexShader);
//     glAttachShader(program, fragmentShader);
//     glLinkProgram(program);
//
//     GLint success;
//     glGetShaderiv(program, GL_COMPILE_STATUS, &success);
//     if (success == GL_FALSE) {
//         std::cout << "Shader compilation error!" << std::endl;
//         char info[1024];
//         glGetShaderInfoLog(program, 1024, nullptr, info);
//         std::cout << info << std::endl;
//     }
// }
//
// void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mode) {
//     if (action == GLFW_PRESS) {
//         switch (key) {
//             case GLFW_KEY_UP:
//                 std::cout << "Up key pressed" << std::endl;
//                 break;
//             case GLFW_KEY_DOWN:
//                 std::cout << "Down key pressed" << std::endl;
//                 break;
//             case GLFW_KEY_RIGHT:
//                 std::cout << "Right key pressed" << std::endl;
//                 break;
//             case GLFW_KEY_LEFT:
//                 std::cout << "Left key pressed" << std::endl;
//                 break;
//         }
//     }
// }