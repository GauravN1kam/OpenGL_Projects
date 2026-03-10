#include "glad/glad.h"
#include <GLFW/glfw3.h>
#define WIDTH 800

void CallMain() {
  glfwInit();
  GLFWwindow *window;
  window = glfwCreateWindow(WIDTH, 800, "First window", NULL, NULL);

  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
