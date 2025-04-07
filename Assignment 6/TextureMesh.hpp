#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class TextureMesh {
private:
    GLuint vaoID, vboID, nboID, tboID, eboID;
    GLuint textureID;
    GLuint shaderProgram;
    int numIndices;

public:
    TextureMesh(const char* modelPath, const char* texturePath, GLuint shaderID);
    void draw(glm::vec3 lightPos, glm::mat4 V, glm::mat4 P, glm::mat4 M);
};