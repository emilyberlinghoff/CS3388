#ifndef TEXTURED_MESH_H
#define TEXTURED_MESH_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Vertex Data structure as per assignment requirements
struct VertexData {
    float x, y, z;        // Position
    float nx, ny, nz;     // Normal
    float r, g, b;        // Color
    float u, v;           // Texture coordinates
    
    // Constructor with default values
    VertexData() : x(0), y(0), z(0), nx(0), ny(0), nz(0), r(1), g(1), b(1), u(0), v(0) {}
};

// Triangle Data structure as per assignment requirements
struct TriData {
    int indices[3];       // Indices of the three vertices making up the triangle
    
    // Constructor
    TriData() { indices[0] = 0; indices[1] = 0; indices[2] = 0; }
};

// Function declaration for reading PLY files
void readPLYFile(std::string fname, std::vector<VertexData>& vertices, std::vector<TriData>& faces);

// Function declaration for loading BMP image
void loadARGB_BMP(const char* imagepath, unsigned char** data, unsigned int* width, unsigned int* height);

class TexturedMesh {
public:
    // Constructor
    TexturedMesh(const std::string& plyPath, const std::string& bmpPath);
    
    // Destructor
    ~TexturedMesh();
    
    // Draw method
    void draw(glm::mat4 MVP);

private:
    // OpenGL objects
    GLuint vertexVBO;     // VBO for vertex positions
    GLuint texCoordVBO;   // VBO for texture coordinates
    GLuint indexVBO;      // VBO for face indices (EBO)
    GLuint VAO;           // Vertex Array Object
    GLuint textureID;     // Texture object ID
    GLuint shaderProgram; // Shader program ID
    
    // Mesh data
    std::vector<VertexData> vertices;
    std::vector<TriData> faces;
    
    // Helper methods
    void setupMesh();
    void loadTexture(const std::string& path);
    void setupShaders();
    
    // Vertex and fragment shader source code
    const char* vertexShaderSrc = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        uniform mat4 MVP;

        void main() {
            gl_Position = MVP * vec4(aPos, 1.0);
            TexCoord = aTexCoord;
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330 core
        in vec2 TexCoord;

        out vec4 FragColor;

        uniform sampler2D texture1;

        void main() {
            FragColor = texture(texture1, TexCoord);
        }
    )";
};

#endif // TEXTURED_MESH_H
