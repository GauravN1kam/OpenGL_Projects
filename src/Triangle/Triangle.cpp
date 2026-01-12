#include "glad/glad.h"
#include <GLFW/glfw3.h>

void DrawTriangle() {
  glfwInit();

  GLFWwindow *window;

  window = glfwCreateWindow(800, 800, "DrawTriangle", NULL, NULL);
  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
