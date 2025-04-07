#include "TextureMesh.hpp"
#include "textureLoader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

// Minimal .ply loader (assumes vertices + faces only, no color)
static void loadPLY(const char* path, std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& uvs, std::vector<unsigned int>& indices) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open PLY file: " << path << std::endl;
        return;
    }

    std::string line;
    int numVertices = 0;
    int numFaces = 0;
    bool header = true;

    while (std::getline(file, line) && header) {
        std::istringstream ss(line);
        std::string word;
        ss >> word;
        if (word == "element") {
            ss >> word;
            if (word == "vertex") ss >> numVertices;
            if (word == "face") ss >> numFaces;
        } else if (word == "end_header") {
            header = false;
        }
    }

    for (int i = 0; i < numVertices; ++i) {
        float x, y, z, nx, ny, nz, u, v;
        file >> x >> y >> z >> nx >> ny >> nz >> u >> v;
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        normals.push_back(nx);
        normals.push_back(ny);
        normals.push_back(nz);
        uvs.push_back(u);
        uvs.push_back(v);
    }

    for (int i = 0; i < numFaces; ++i) {
        int count, i0, i1, i2;
        file >> count >> i0 >> i1 >> i2;
        indices.push_back(i0);
        indices.push_back(i1);
        indices.push_back(i2);
    }

    file.close();
}

TextureMesh::TextureMesh(const char* modelPath, const char* texturePath, GLuint shaderID) {
    shaderProgram = shaderID;
    std::vector<float> vertices, normals, uvs;
    std::vector<unsigned int> indices;
    loadPLY(modelPath, vertices, normals, uvs, indices);
    numIndices = indices.size();

    textureID = loadBMP_custom(texturePath);

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &nboID);
    glGenBuffers(1, &tboID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, nboID);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, tboID);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void TextureMesh::draw(glm::vec3 lightPos, glm::mat4 V, glm::mat4 P, glm::mat4 M) {
    glm::mat4 MVP = P * V * M;

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "V"), 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "P"), 1, GL_FALSE, glm::value_ptr(P));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(shaderProgram, "waterTexture"), 0);

    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
