cmake_minimum_required(VERSION 3.10)

project(Engine)

set(PROJECT_SOURCE_FILES
        source/Engine.h
        source/Engine.cpp
        source/Application.h
        source/Application.cpp
        source/eng.h
        source/input/InputManager.cpp
        source/input/InputManager.h
        source/graphics/ShaderProgram.cpp
        source/graphics/ShaderProgram.h
        source/graphics/GraphicsAPI.cpp
        source/graphics/GraphicsAPI.h
        source/render/Material.cpp
        source/render/Material.h
        source/render/Mesh.cpp
        source/render/Mesh.h
        source/graphics/VertexLayout.h
        source/render/RenderQueue.cpp
        source/render/RenderQueue.h
        source/scene/GameObject.cpp
        source/scene/GameObject.h
        source/scene/Scene.cpp
        source/scene/Scene.h
)

include_directories(source)
add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add GLFW library
add_subdirectory(thirdparty/glfw-3.4 "${CMAKE_CURRENT_BINARY_DIR}/glfw_build")
include_directories(thirdparty/glfw-3.4/include)

# Add GLM
add_subdirectory(thirdparty/glm-1.0.1/glm)
include_directories(thirdparty/glm-1.0.1)

# Add Glew library
add_compile_definitions(GLEW_NO_GLU)
set(BUILD_UTILS OFF CACHE BOOL "utilities" FORCE)
add_subdirectory(thirdparty/glew/build/cmake "${CMAKE_CURRENT_BINARY_DIR}/glew_build")
include_directories(thirdparty/glew/include)
set_property(TARGET glew_s PROPERTY FOLDER GLEW)
set_property(TARGET glew PROPERTY FOLDER GLEW)

# Link all thirdparty libraries
target_link_libraries(${PROJECT_NAME}
        glfw
        glew_s
        glm
)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add tests subdirectory
add_subdirectory(tests)