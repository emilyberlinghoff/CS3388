#ifndef UTILS_HPP
#define UTILS_HPP

#include <GL/glew.h>
#include <vector>
#include <string>

std::string readShaderFile(const std::string &filePath);
void checkShaderCompilation(GLuint shaderID);
void checkProgramLinking(GLuint programID);

#endif
