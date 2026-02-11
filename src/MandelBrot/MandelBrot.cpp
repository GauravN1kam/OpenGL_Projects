#include "MandelBrot.hpp"

void DrawMandelBrot() {
  if (!glfwInit()) {
    std::cout << "Failed to create a Window" << std::endl;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(800, 800, "Shapes", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }

  // Loading Shaders from file
  Shader ourShader("../shaders/MandelBrot.vert", "../shaders/MandelBrot.frag");

  float vertices[] = {
      -1.f, -1.f, 0.0, // first point
      1.f,  -1.f, 0.0, // second point
      1.f,  1.f,  0.0, // Third point
      -1.f, 1.f,  0.0  // fouth point
  };

  unsigned int points[] = {0, 1, 2, 2, 3, 0};

  unsigned int VAO, VBO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // VAO Binding VAO
  glBindVertexArray(VAO);

  // Binding VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Binding EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    int height, width;
    double mouse_x, mouse_y;
    glfwGetFramebufferSize(window, &width, &height);
    float aspectRatio = (float)width / (float)height;

    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    float mouseNormX = (float)mouse_x / (float)width * 2.f - 1.f;
    float mouseNormY = 1.0f - (float)mouse_y / (float)height * 2.f; // flip Y
    float time = (float)glfwGetTime();

    glClearColor(0.f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);
    ourShader.use();
    ourShader.setFloat("aspect", aspectRatio);
    ourShader.setFloat("u_Time", time);
    ourShader.Set2Float("u_Mouse", mouseNormX, mouseNormY);
    ourShader.setFloat("Minx", -2.0f);
    ourShader.setFloat("Maxx", 1.12f);
    ourShader.setFloat("Miny", -1.12f);
    ourShader.setFloat("Maxy", 0.47f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
