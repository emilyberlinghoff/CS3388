#include "rendering.hpp"
#include "shaders.hpp"
#include <iostream>

void setupRendering(GLuint &vao, GLuint &vertexVBO, GLuint &normalVBO, GLuint &programID) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &normalVBO);

    programID = loadShaders("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
}

void updateBuffers(GLuint vao, GLuint vertexVBO, GLuint normalVBO, std::vector<float> vertices, std::vector<float> normals) {
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
}

void renderScene(GLuint vao, GLuint programID, glm::mat4 mvp, glm::mat4 view) {
    glUseProgram(programID);

    GLuint matrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

    GLuint viewID = glGetUniformLocation(programID, "V");
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);
}
