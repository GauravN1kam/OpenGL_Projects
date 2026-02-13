cmake_minimum_required(VERSION 3.20)

project(OpenGL_Projects VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(dependencies/glm)

add_executable(
    OpenGL_Projects
    dependencies/glad/src/glad.c
    helpers/stringReader.cpp
		helpers/ShaderUtil.cpp
    src/Shapes/Shapes.cpp
		src/MandelBrot/MandelBrot.cpp
		src/Going3D/Cube.cpp
    src/Shapes/RayMarching.cpp
    src/HelloWindow/HelloWindow.cpp
    src/Triangle/Triangle.cpp
    src/main.cpp
)

target_include_directories(OpenGL_Projects PRIVATE
    dependencies/glad/include
)

target_link_libraries(OpenGL_Projects PRIVATE
    glfw
    OpenGL::GL
    glm
)

