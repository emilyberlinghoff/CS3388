#include "rendering.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    GLuint viewID = glGetUniformLocation(programID, "View");

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);

    glUseProgram(0);
}

void drawBoundingBox(GLuint programID, const glm::mat4& MVP, const glm::mat4& view, float min, float max) {
    glm::vec3 corners[] = {
        {min, min, min}, {max, min, min}, {max, max, min}, {min, max, min}, // bottom face
        {min, min, max}, {max, min, max}, {max, max, max}, {min, max, max}  // top face
    };

    GLuint edges[] = {
        0, 1, 1, 2, 2, 3, 3, 0, // bottom
        4, 5, 5, 6, 6, 7, 7, 4, // top
        0, 4, 1, 5, 2, 6, 3, 7  // vertical
    };

    std::vector<float> lineVertices;
    for (int i = 0; i < 24; ++i) {
        glm::vec3 v = corners[edges[i]];
        lineVertices.push_back(v.x);
        lineVertices.push_back(v.y);
        lineVertices.push_back(v.z);
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(float), lineVertices.data(), GL_STATIC_DRAW);

    GLint posLoc = glGetAttribLocation(programID, "position");
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glUseProgram(programID);

    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniformMatrix4fv(glGetUniformLocation(programID, "View"), 1, GL_FALSE, glm::value_ptr(view));
    glUniform3f(glGetUniformLocation(programID, "modelColor"), 1.0f, 1.0f, 1.0f); // White

    glDrawArrays(GL_LINES, 0, lineVertices.size() / 3);

    // Cleanup
    glDisableVertexAttribArray(posLoc);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void drawAxes(GLuint programID, const glm::mat4& MVP, const glm::mat4& view, float min, float max) {
    float size = max - min;
    glm::vec3 origin(min, min, min);
    glm::vec3 axes[] = {
        origin, origin + glm::vec3(size, 0, 0), // X axis
        origin, origin + glm::vec3(0, size, 0), // Y axis
        origin, origin + glm::vec3(0, 0, size)  // Z axis
    };

    std::vector<float> vertices;
    std::vector<float> colors;

    // X axis - red
    vertices.insert(vertices.end(), { axes[0].x, axes[0].y, axes[0].z, axes[1].x, axes[1].y, axes[1].z });
    colors.insert(colors.end(), { 1, 0, 0, 1, 0, 0 });

    // Y axis - green
    vertices.insert(vertices.end(), { axes[2].x, axes[2].y, axes[2].z, axes[3].x, axes[3].y, axes[3].z });
    colors.insert(colors.end(), { 0, 1, 0, 0, 1, 0 });

    // Z axis - blue
    vertices.insert(vertices.end(), { axes[4].x, axes[4].y, axes[4].z, axes[5].x, axes[5].y, axes[5].z });
    colors.insert(colors.end(), { 0, 0, 1, 0, 0, 1 });

    GLuint vao, vbo, cbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cbo);

    glBindVertexArray(vao);

    // Positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    GLint posLoc = glGetAttribLocation(programID, "position");
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
    GLint colorLoc = glGetAttribLocation(programID, "color");
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glUseProgram(programID);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniformMatrix4fv(glGetUniformLocation(programID, "View"), 1, GL_FALSE, glm::value_ptr(view));
    glUniform1i(glGetUniformLocation(programID, "useLighting"), 0); // No lighting
    glLineWidth(3.0f);

    glDrawArrays(GL_LINES, 0, 6); // 3 axes, 2 points each

    glDisableVertexAttribArray(posLoc);
    glDisableVertexAttribArray(colorLoc);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cbo);
    glDeleteVertexArrays(1, &vao);
}

void drawThickBox(GLuint programID, const glm::mat4& MVP, const glm::mat4& view, float min, float max, float thickness) {
    glm::vec3 corners[] = {
        {min, min, min}, {max, min, min}, {max, max, min}, {min, max, min},
        {min, min, max}, {max, min, max}, {max, max, max}, {min, max, max}
    };

    struct Edge { int start, end; };
    Edge edges[] = {
        {0,1},{1,2},{2,3},{3,0}, // bottom
        {4,5},{5,6},{6,7},{7,4}, // top
        {0,4},{1,5},{2,6},{3,7}  // vertical
    };

    std::vector<float> vertices;

    auto push = [&](glm::vec3 pos, glm::vec3 normal) {
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        vertices.push_back(normal.x);
        vertices.push_back(normal.y);
        vertices.push_back(normal.z);
    };

    for (const Edge& edge : edges) {
        glm::vec3 a = corners[edge.start];
        glm::vec3 b = corners[edge.end];
        glm::vec3 dir = glm::normalize(b - a);

        glm::vec3 up = glm::vec3(0, 1, 0);
        if (glm::abs(glm::dot(dir, up)) > 0.99f) up = glm::vec3(1, 0, 0);

        glm::vec3 right = glm::normalize(glm::cross(dir, up)) * thickness;
        glm::vec3 offset = glm::normalize(glm::cross(dir, right)) * thickness;

        glm::vec3 v0 = a + right + offset;
        glm::vec3 v1 = a - right + offset;
        glm::vec3 v2 = a - right - offset;
        glm::vec3 v3 = a + right - offset;
        glm::vec3 v4 = b + right + offset;
        glm::vec3 v5 = b - right + offset;
        glm::vec3 v6 = b - right - offset;
        glm::vec3 v7 = b + right - offset;

        auto pushQuad = [&](glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
            glm::vec3 normal = glm::normalize(glm::cross(p1 - p0, p2 - p0));
            push(p0, normal); push(p1, normal); push(p2, normal);
            push(p2, normal); push(p3, normal); push(p0, normal);
        };

        pushQuad(v0, v1, v5, v4);
        pushQuad(v1, v2, v6, v5);
        pushQuad(v2, v3, v7, v6);
        pushQuad(v3, v0, v4, v7);
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    GLint posLoc = glGetAttribLocation(programID, "position");
    GLint normalLoc = glGetAttribLocation(programID, "normal");

    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

    glUseProgram(programID);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniformMatrix4fv(glGetUniformLocation(programID, "View"), 1, GL_FALSE, glm::value_ptr(view));
    glUniform3f(glGetUniformLocation(programID, "modelColor"), 1.0f, 1.0f, 1.0f); // White

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);

    glDisableVertexAttribArray(posLoc);
    glDisableVertexAttribArray(normalLoc);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

// 16:01
