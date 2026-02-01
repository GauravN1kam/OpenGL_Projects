#include "Shapes.hpp"
#include <iostream>

bool checkShaderCompileRayMarching(GLuint shader, const char *name) {
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char log[1024];
    glGetShaderInfoLog(shader, 1024, nullptr, log);
    std::cerr << "❌ Shader compile error (" << name << "):\n"
              << log << std::endl;
    return false;
  }
  return true;
}
void framebuffer_size_callback_Shape(GLFWwindow *window, int width,
                                     int height) {
  glViewport(0, 0, width, height);
}
void DrawRayMarchingSpace() {
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

  std::string vertexShaderString = readShader("../shaders/RayMarching.vert");
  std::string fragmentShaderString = readShader("../shaders/RayMarching.frag");

  const char *vertexShaderSource = vertexShaderString.c_str();
  const char *fragmentShaderSource = fragmentShaderString.c_str();

  // Reading shaders and Compiling them

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  if (!checkShaderCompileRayMarching(vertexShader, "Vertex")) {
    std::cout << "Shader failed\n";
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  if (!checkShaderCompileRayMarching(fragmentShader, "Fragment")) {
    std::cout << "Fragement shader failed\n";
  }

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "PROGRAM LINK ERROR:\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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

    glClearColor(0.f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);

    glUseProgram(shaderProgram);

    int aspectLoc = glGetUniformLocation(shaderProgram, "aspect");
    glUniform1f(aspectLoc, aspectRatio);

    float time = (float)glfwGetTime();
    int timeLoc = glGetUniformLocation(shaderProgram, "u_Time");
    glUniform1f(timeLoc, time);

    int mouseLoc = glGetUniformLocation(shaderProgram, "u_Mouse");
    glUniform2f(mouseLoc, mouseNormX, mouseNormY);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
}
