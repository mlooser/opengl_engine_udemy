cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

# Create test executable
add_executable(EngineTests
    GameObjectTest.cpp
    SceneTest.cpp
)

# Link against gtest, Engine library
target_link_libraries(EngineTests
    GTest::gtest_main
    Engine
)

# Discover tests
gtest_discover_tests(EngineTests)
