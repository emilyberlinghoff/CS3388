#ifndef TEXTUREDMESH_H
#define TEXTUREDMESH_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

struct VertexData {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 color;

    VertexData(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex, glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f))
        : position(pos), normal(norm), texCoords(tex), color(col) {}
};

struct TriData {
    std::vector<unsigned int> vertexIndices;

    TriData(int v1, int v2, int v3)
        : vertexIndices({static_cast<unsigned int>(v1), static_cast<unsigned int>(v2), static_cast<unsigned int>(v3)}) {}
};

class TexturedMesh {
public:
    GLuint vaoID, vboVertices, iboFaces, textureID;
    std::vector<VertexData> vertices;
    std::vector<TriData> faces;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;

    Shader shader;

    // Constructor
    TexturedMesh(const std::string& plyFilePath, const std::string& textureFilePath);

    // Destructor
    ~TexturedMesh();

    // Load PLY file and process vertices and faces
    void readPLYFile(const std::string& filename);

    // Set up mesh buffers for OpenGL
    void setupMesh();

    // Set up texture loading from BMP
    void setupTexture(unsigned char* imageData, unsigned int width, unsigned int height);

    // Render the mesh with a given shader and MVP matrix
    void draw(const glm::mat4& MVP);

    // Cleanup function to release OpenGL resources
    void cleanup();
};

#endif // TEXTUREDMESH_H