#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void checkProgramLinking(GLuint programID) {
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cerr << "Shader linking error:\n" << infoLog << std::endl;
    }
}
