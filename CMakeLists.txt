cmake_minimum_required(VERSION 4.0.1)
project(OpenGL_Projects VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(
		OpenGL_Projects
		src/HelloWindow/HelloWindow.cpp
    src/main.cpp
)

target_include_directories(OpenGL_Projects PRIVATE
    dependencies/glad/include
)

target_link_libraries(OpenGL_Projects PRIVATE
    glfw
    OpenGL::GL
)
