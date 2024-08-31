cmake_minimum_required(VERSION 3.30.0)
project(OpenGL)

# Dependancies
include(FetchContent)

# Set library versions coz it's good practice
set(GLFW_VERSION 3.4)

# Specify library
# Specify github url with release version/tag
FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Do not build any example code from library
set(BUILD_EXAMPLES OFF CACHE INTERNAL "examples")
FetchContent_MakeAvailable(glfw)

# Library include folders
include_directories(${glfw_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    dependencies/glad/glad.c
    dependencies/imgui/imgui_demo.cpp
    dependencies/imgui/imgui_draw.cpp
    dependencies/imgui/imgui_impl_glfw.cpp
    dependencies/imgui/imgui_impl_opengl3.cpp
    dependencies/imgui/imgui_tables.cpp
    dependencies/imgui/imgui_widgets.cpp
    dependencies/imgui/imgui.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE dependencies src)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)  