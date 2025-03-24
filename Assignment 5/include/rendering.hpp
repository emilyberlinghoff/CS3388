#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

void updateBuffers(GLuint vao, GLuint vertexVBO, GLuint normalVBO, std::vector<float> vertices, std::vector<float> normals);
void renderScene(GLuint vao, GLuint programID, glm::mat4 mvp, glm::mat4 view, int vertexCount);
void setupRendering(GLuint &vao, GLuint &vertexVBO, GLuint &normalVBO, GLuint programID);
void drawBoundingBox(GLuint programID, const glm::mat4& MVP, const glm::mat4& view, float min, float max);
void drawAxes(GLuint programID, const glm::mat4& MVP, const glm::mat4& view, float min, float max);
void drawThickBox(GLuint programID, const glm::mat4& MVP, const glm::mat4& view, float min, float max, float thickness = 0.02f);