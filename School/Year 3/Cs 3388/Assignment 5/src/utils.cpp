#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

std::vector<float> compute_normals(const std::vector<float>& vertices) {
    std::vector<float> normals(vertices.size(), 0.0f);
    for (size_t i = 0; i < vertices.size(); i += 9) {
        glm::vec3 v0(vertices[i], vertices[i+1], vertices[i+2]);
        glm::vec3 v1(vertices[i+3], vertices[i+4], vertices[i+5]);
        glm::vec3 v2(vertices[i+6], vertices[i+7], vertices[i+8]);

        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        for (int j = 0; j < 3; ++j) {
            normals[i + j*3 + 0] = normal.x;
            normals[i + j*3 + 1] = normal.y;
            normals[i + j*3 + 2] = normal.z;
        }
    }
    return normals;
}

void checkProgramLinking(GLuint programID) {
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cerr << "Shader linking error:\n" << infoLog << std::endl;
    }
}
