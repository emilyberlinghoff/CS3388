#include "TexturedMesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor: Load PLY file, texture, and setup OpenGL buffers
TexturedMesh::TexturedMesh(const std::string& plyPath, const std::string& bmpPath) {
    // Load mesh data from PLY file
    readPLYFile(plyPath, vertices, faces);

    // Load texture from BMP file
    loadTexture(bmpPath);

    // Setup OpenGL buffers and shaders
    setupMesh();
    setupShaders();
}

// Destructor: Clean up OpenGL resources
TexturedMesh::~TexturedMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &texCoordVBO);
    glDeleteBuffers(1, &indexVBO);
    glDeleteTextures(1, &textureID);
}

// Setup OpenGL buffers (VAO, VBO, EBO)
void TexturedMesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &texCoordVBO);
    glGenBuffers(1, &indexVBO);

    glBindVertexArray(VAO);

    // Upload vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    glEnableVertexAttribArray(0);

    // Upload texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, u)));
    glEnableVertexAttribArray(1);

    // Upload face indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(TriData), faces.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

// Load texture using BMP format
void TexturedMesh::loadTexture(const std::string& path) {
    unsigned char* data;
    unsigned int width, height;
    
    std::cout << "Loading texture: " << path << std::endl;
    loadARGB_BMP(path.c_str(), &data, &width, &height);

    if (!data) {
        std::cerr << "Error loading texture: " << path << std::endl;
        return;
    }

    std::cout << "Successfully loaded texture: " << path << " (" << width << "x" << height << ")" << std::endl;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    delete[] data;
}

// Compile and link shaders
void TexturedMesh::setupShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Render the textured mesh with transformations
void TexturedMesh::draw(glm::mat4 MVP) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    GLint mvpLocation = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(MVP));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

    glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

void readPLYFile(std::string fname, std::vector<VertexData>& vertices, std::vector<TriData>& faces) {
    std::ifstream file(fname);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open PLY file " << fname << std::endl;
        return;
    }

    std::cout << "Successfully opened PLY file: " << fname << std::endl;

    std::string line;
    bool headerEnded = false;
    int vertexCount = 0, faceCount = 0;

    while (std::getline(file, line)) {
        if (line.substr(0, 14) == "element vertex") {
            vertexCount = std::stoi(line.substr(15));
        }
        if (line.substr(0, 12) == "element face") {
            faceCount = std::stoi(line.substr(13));
        }
        if (line == "end_header") {
            headerEnded = true;
            break;
        }
    }

    if (!headerEnded) {
        std::cerr << "Error: Malformed PLY file " << fname << std::endl;
        return;
    }

    // Read vertices
    for (int i = 0; i < vertexCount; i++) {
        VertexData v;
        file >> v.x >> v.y >> v.z >> v.nx >> v.ny >> v.nz >> v.u >> v.v;
        vertices.push_back(v);
    }

    // Read faces
    for (int i = 0; i < faceCount; i++) {
        TriData tri;
        int vertexCountPerFace;
        file >> vertexCountPerFace;  // Should be 3 for triangles

        if (vertexCountPerFace == 3) {
            file >> tri.indices[0] >> tri.indices[1] >> tri.indices[2];
            faces.push_back(tri);
        } else {
            std::cerr << "Warning: Skipping non-triangle face in " << fname << std::endl;
        }
    }

    std::cout << "Loaded " << vertices.size() << " vertices and " << faces.size() << " faces from " << fname << std::endl;
    file.close();
}


