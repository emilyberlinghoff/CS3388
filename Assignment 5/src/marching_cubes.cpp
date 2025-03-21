#include <iostream>
#include <vector>
#include <functional>
#include <glm/glm.hpp>
#include "marching_cubes.hpp"

MarchingCubes::MarchingCubes(std::function<float(float, float, float)> f, float isoval, float min, float max, float step)
    : generationFunction(f), isoValue(isoval), minCoord(min), maxCoord(max), stepSize(step), currentIteration(min), finished(false) {}

void MarchingCubes::generate() {
    generate_iterative_new();
}

std::vector<float> MarchingCubes::getVertices() {
    return vertices;
}

// Compute normals
std::vector<float> compute_normals(std::vector<float> vertices) {
    std::vector<float> normals(vertices.size(), 0);
    for (size_t i = 0; i < vertices.size(); i += 9) {
        glm::vec3 p1(vertices[i], vertices[i+1], vertices[i+2]);
        glm::vec3 p2(vertices[i+3], vertices[i+4], vertices[i+5]);
        glm::vec3 p3(vertices[i+6], vertices[i+7], vertices[i+8]);

        glm::vec3 normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
        for (int j = 0; j < 3; j++) {
            normals[i + 3*j] = normal.x;
            normals[i + 3*j+1] = normal.y;
            normals[i + 3*j+2] = normal.z;
        }
    }
    return normals;
}

void MarchingCubes::generate_iterative_new() {
    // Placeholder: add actual marching cubes logic here later
    std::cout << "Running generate_iterative_new..." << std::endl;

    // Example: Just add a test triangle so you see something
    vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.0f);
    vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f);
    vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);

    finished = true;
}
