#include "rendering.hpp"
#include <GL/glew.h>
#include <iostream>

void setupRendering(GLuint &vao, GLuint &vertexVBO, GLuint &normalVBO, GLuint programID) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &normalVBO);
}

void updateBuffers(GLuint vao, GLuint vertexVBO, GLuint normalVBO, std::vector<float> vertices, std::vector<float> normals) {
    glBindVertexArray(vao);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}

void renderScene(GLuint vao, GLuint programID, glm::mat4 mvp, glm::mat4 view, int vertexCount) {
    glUseProgram(programID);

    GLuint mvpID = glGetUniformLocation(programID, "MVP");
    GLuint viewID = glGetUniformLocation(programID, "V");

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);

    glUseProgram(0);
}
