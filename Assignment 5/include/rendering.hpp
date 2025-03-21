#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

void setupRendering(GLuint &vao, GLuint &vertexVBO, GLuint &normalVBO, GLuint &programID);
void updateBuffers(GLuint vao, GLuint vertexVBO, GLuint normalVBO, std::vector<float> vertices, std::vector<float> normals);
void renderScene(GLuint vao, GLuint programID, glm::mat4 mvp, glm::mat4 view);

#endif
