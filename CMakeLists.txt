cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(GameDevelopmentProject)

# Enable all warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(PROJECT_SOURCE_FILES
        source/main.cpp
        source/Game.cpp
        source/Game.h
        source/TestObject.cpp
        source/TestObject.h
)

include_directories(engine/thirdparty/glew/include)
include_directories(engine/thirdparty/glm-1.0.1)
include_directories(engine/thirdparty/stb_image)

# Add the application
include_directories(source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")
include_directories(engine/source)

target_link_libraries(${PROJECT_NAME}
        Engine
)
