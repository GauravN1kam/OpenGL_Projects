#include "glad/glad.h"
#include <GLFW/glfw3.h>

void CallMain() {
  glfwInit();
  GLFWwindow *window;
  window = glfwCreateWindow(800, 800, "First window", NULL, NULL);

  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
