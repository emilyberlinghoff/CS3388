#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shaders.hpp"

std::string readShaderFile(const std::string &filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void checkShaderCompilation(GLuint shaderID) {
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
    }
}

GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path) {
    std::string vertexCode = readShaderFile(vertex_file_path);
    std::string fragmentCode = readShaderFile(fragment_file_path);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexSource = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentSource = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programID;
}
