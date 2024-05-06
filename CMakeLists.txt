cmake_minimum_required(VERSION 3.10)
project(imgui_example)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add ImGui submodule
add_subdirectory(libs/third_party/imgui)

# Find GLFW
find_package(glfw3 REQUIRED)

# Add executable
add_executable(imgui_app
    src/main.cpp
)

# Link libraries
target_link_libraries(imgui_app
    imgui
    glfw
    OpenGL::GL
)
