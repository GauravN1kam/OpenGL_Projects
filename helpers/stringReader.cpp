#include "stringReader.hpp"

std::string readShader(const char *path) {
  std::ifstream file(path);
  std::stringstream buffer;

  buffer << file.rdbuf();

  return buffer.str();
}
