#include "TexturedMesh.h"
#include "ImageLoader.h"

TexturedMesh::TexturedMesh(const std::string& plyFilePath, const std::string& textureFilePath)
    : shader("vertexShaderPath.glsl", "fragmentShaderPath.glsl") // Explicitly initialize Shader
{
    // Load mesh data
    readPLYFile(plyFilePath);

    // Load texture data
    unsigned char* imageData;
    unsigned int width, height;
    loadARGB_BMP(textureFilePath.c_str(), &imageData, &width, &height);

    // Setup OpenGL resources
    setupMesh();
    setupTexture(imageData, width, height);

    // Free image data after uploading it to GPU
    delete[] imageData;
}

TexturedMesh::~TexturedMesh() {
    cleanup();
}

void TexturedMesh::setupMesh() {
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboVertices);
    glGenBuffers(1, &iboFaces);

    glBindVertexArray(vaoID);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, texCoords));

    // Upload index data
    std::vector<unsigned int> indices;
    for (const auto& face : faces) {
        indices.insert(indices.end(), face.vertexIndices.begin(), face.vertexIndices.end());
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboFaces);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0); // Unbind VAO
}

void TexturedMesh::setupTexture(unsigned char* imageData, unsigned int width, unsigned int height) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
}

void TexturedMesh::draw(const glm::mat4& MVP) {
    shader.use();

    glBindVertexArray(vaoID);
    glUniformMatrix4fv(shader.getUniformLocation("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

    glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void TexturedMesh::cleanup() {
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &iboFaces);
    glDeleteTextures(1, &textureID);
}

void TexturedMesh::readPLYFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open PLY file: " << filename << std::endl;
        return;
    }

    std::string line;
    bool headerEnded = false;
    int vertexCount = 0, faceCount = 0;
    int vertexIndex = 0, faceIndex = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);

        if (!headerEnded) {
            // Read header
            if (line.find("element vertex") != std::string::npos) {
                ss.ignore(14); // Ignore "element vertex"
                ss >> vertexCount;
            } else if (line.find("element face") != std::string::npos) {
                ss.ignore(12); // Ignore "element face"
                ss >> faceCount;
            } else if (line.find("end_header") != std::string::npos) {
                headerEnded = true;
            }
            continue;
        }

        if (vertexIndex < vertexCount) {
            // Read vertex properties
            glm::vec3 position, normal;
            glm::vec2 texCoords;

            ss >> position.x >> position.y >> position.z; // Position
            ss >> normal.x >> normal.y >> normal.z;       // Normal
            ss >> texCoords.x >> texCoords.y;             // Texture coordinates

            positions.push_back(position);
            normals.push_back(normal);
            glm::vec2 texCoord(texCoords.x, texCoords.y);
            this->texCoords.push_back(texCoord);

            vertexIndex++;
        } else if (faceIndex < faceCount) {
            // Read face indices
            int numVertices, v0, v1, v2;
            ss >> numVertices; // Expect 3 for a triangle

            if (numVertices == 3) {
                ss >> v0 >> v1 >> v2;
                indices.push_back(v0);
                indices.push_back(v1);
                indices.push_back(v2);
            } else {
                std::cerr << "Only triangular faces are supported!" << std::endl;
            }

            faceIndex++;
        }
    }

    file.close();

    std::cout << "Loaded PLY file: " << filename << " with " 
              << vertexCount << " vertices and " << faceCount << " faces." << std::endl;
}