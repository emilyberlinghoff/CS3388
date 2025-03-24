#ifndef UTILS_HPP
#define UTILS_HPP

#include <GL/glew.h>
#include <vector>
#include <string>

#pragma once
#include <vector>

std::vector<float> compute_normals(const std::vector<float>& vertices);

std::string readShaderFile(const std::string &filePath);
void checkShaderCompilation(GLuint shaderID);
void checkProgramLinking(GLuint programID);

#endif
