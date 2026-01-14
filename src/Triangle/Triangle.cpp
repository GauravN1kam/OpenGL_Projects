#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void DrawTriangle() {
  glfwInit();

  GLFWwindow *window;

  window = glfwCreateWindow(800, 800, "DrawTriangle", NULL, NULL);

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }
  glViewport(0, 0, 800, 800);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
