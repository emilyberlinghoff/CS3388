#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <GL/glew.h>
#include <string>

std::string readShaderFile(const std::string &filePath);
void checkShaderCompilation(GLuint shaderID);
GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);

#endif
