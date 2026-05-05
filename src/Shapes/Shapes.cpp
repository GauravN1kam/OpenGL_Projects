#include "Shapes.hpp"
#include "../../helpers/ShaderUtil.hpp"
#include <iostream>
#include <vector>

bool checkShaderCompile(GLuint shader, const char *name) {
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char log[1024];
    glGetShaderInfoLog(shader, 1024, nullptr, log);
    std::cerr << "Shader compile error (" << name << "):\n" << log << std::endl;
    return false;
  }
  return true;
}

void framebuffer_size_callback_Shapes(GLFWwindow *window, int width,
                                      int height) {
  glViewport(0, 0, width, height);
}

std::vector<float> generateCircleVertices(float radius, int segments) {
  std::vector<float> vertices;

  // Center of circle
  vertices.push_back(0.0f);
  vertices.push_back(0.0f);
  vertices.push_back(0.0f);

  for (int i = 0; i <= segments; i++) {
    float angle = 2.0f * M_PI * i / segments;

    float x = radius * cos(angle);
    float y = radius * sin(angle);

    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0f);
  }

  return vertices;
}

void DrawCircle() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 800, "Circle", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_Shapes);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    return;
  }

  // ✅ Generate circle vertices
  std::vector<float> vertices = generateCircleVertices(0.5f, 100);

  // VAO & VBO
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // ✅ Use simple shaders (make sure paths are correct)
  Shader shader("../shaders/circle.vert", "../shaders/circle.frag");

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();

    // ✅ Identity matrices (no camera confusion)
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    shader.SetMat4("model", model);
    shader.SetMat4("view", view);
    shader.SetMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
}

void DrawSqaure() {
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

  std::string vertexShaderString = readShader("../shaders/Shapes.vert");
  std::string fragmentShaderString = readShader("../shaders/Shapes.frag");

  const char *vertexShaderSource = vertexShaderString.c_str();
  const char *fragmentShaderSource = fragmentShaderString.c_str();

  // Reading shaders and Compiling them

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  if (!checkShaderCompile(vertexShader, "Vertex")) {
    std::cout << "Shader failed\n";
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  if (!checkShaderCompile(fragmentShader, "Fragment")) {
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
    glfwGetFramebufferSize(window, &width, &height);
    float aspectRatio = (float)width / (float)height;

    glClearColor(0.f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);

    glUseProgram(shaderProgram);

    int aspectLoc = glGetUniformLocation(shaderProgram, "aspect");
    glUniform1f(aspectLoc, aspectRatio);

    float time = (float)glfwGetTime();
    int timeLoc = glGetUniformLocation(shaderProgram, "u_Time");
    glUniform1f(timeLoc, time);

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

void DrawShaderIWant() {
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

  std::string vertexShaderString = readShader("../shaders/Shapes.vert");
  std::string fragmentShaderString = readShader("../shaders/ShapeIWant.frag");

  const char *vertexShaderSource = vertexShaderString.c_str();
  const char *fragmentShaderSource = fragmentShaderString.c_str();

  // Reading shaders and Compiling them

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  if (!checkShaderCompile(vertexShader, "Vertex")) {
    std::cout << "Shader failed\n";
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  if (!checkShaderCompile(fragmentShader, "Fragment")) {
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
    glfwGetFramebufferSize(window, &width, &height);
    float aspectRatio = (float)width / (float)height;

    glClearColor(0.f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);

    glUseProgram(shaderProgram);

    int aspectLoc = glGetUniformLocation(shaderProgram, "aspect");
    glUniform1f(aspectLoc, aspectRatio);

    float time = (float)glfwGetTime();
    int timeLoc = glGetUniformLocation(shaderProgram, "u_Time");
    glUniform1f(timeLoc, time);

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
