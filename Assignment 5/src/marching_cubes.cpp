#include "marching_cubes.hpp"
#include "TriTable.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream> 
#include <vector>
#include <glm/glm.hpp>

// Constructor
MarchingCubes::MarchingCubes(std::function<float(float, float, float)> f,
                             float isoval, float min, float max, float step)
    : generationFunction(f), isoValue(isoval),
      minCoord(min), maxCoord(max), stepSize(step),
      currentIteration(min), finished(false) {}

// // Compute face normals for each triangle
// std::vector<float> compute_normals(const std::vector<float>& vertices) {
//     std::vector<float> normals(vertices.size(), 0.0f);
//     for (size_t i = 0; i < vertices.size(); i += 9) {
//         glm::vec3 v0(vertices[i], vertices[i+1], vertices[i+2]);
//         glm::vec3 v1(vertices[i+3], vertices[i+4], vertices[i+5]);
//         glm::vec3 v2(vertices[i+6], vertices[i+7], vertices[i+8]);

//         glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

//         for (int j = 0; j < 3; ++j) {
//             normals[i + j*3 + 0] = normal.x;
//             normals[i + j*3 + 1] = normal.y;
//             normals[i + j*3 + 2] = normal.z;
//         }
//     }
//     return normals;
// }

// Main public entry point
void MarchingCubes::generate() {
    generate_iterative_new();
    writePLY("output.ply"); // Write the mesh to a PLY file
}

// Return the vertices of the mesh
std::vector<float> MarchingCubes::getVertices() {
    return vertices;
}

// Core marching cubes logic
void MarchingCubes::generate_iterative_new() {
    vertices.clear();

    for (float x = minCoord; x < maxCoord; x += stepSize) {
        for (float y = minCoord; y < maxCoord; y += stepSize) {
            for (float z = minCoord; z < maxCoord; z += stepSize) {
                glm::vec3 grid[8] = {
                    {x, y, z},
                    {x + stepSize, y, z},
                    {x + stepSize, y + stepSize, z},
                    {x, y + stepSize, z},
                    {x, y, z + stepSize},
                    {x + stepSize, y, z + stepSize},
                    {x + stepSize, y + stepSize, z + stepSize},
                    {x, y + stepSize, z + stepSize}
                };

                float values[8];
                for (int i = 0; i < 8; ++i)
                    values[i] = generationFunction(grid[i].x, grid[i].y, grid[i].z);

                int cubeIndex = 0;
                for (int i = 0; i < 8; ++i)
                    if (values[i] < isoValue)
                        cubeIndex |= (1 << i);

                if (cubeIndex == 0 || cubeIndex == 255)
                    continue;

                glm::vec3 vertList[12];
                for (int i = 0; i < 12; ++i) {
                    int v1 = edge_to_vertex[i][0];
                    int v2 = edge_to_vertex[i][1];

                    float val1 = values[v1];
                    float val2 = values[v2];
                    glm::vec3 p1 = grid[v1];
                    glm::vec3 p2 = grid[v2];

                    float t = (isoValue - val1) / (val2 - val1 + 1e-6f);
                    vertList[i] = p1 + t * (p2 - p1);
                }

                for (int i = 0; marching_cubes_lut[cubeIndex][i] != -1; i += 3) {
                    glm::vec3 v0 = vertList[marching_cubes_lut[cubeIndex][i]];
                    glm::vec3 v1 = vertList[marching_cubes_lut[cubeIndex][i + 1]];
                    glm::vec3 v2 = vertList[marching_cubes_lut[cubeIndex][i + 2]];

                    for (glm::vec3 v : {v0, v1, v2}) {
                        vertices.push_back(v.x);
                        vertices.push_back(v.y);
                        vertices.push_back(v.z);
                    }
                }
            }
        }
    }

    finished = true;
    std::cout << "Generated " << vertices.size() / 9 << " triangles.\n";
}

void MarchingCubes::writePLY(const std::string& filename) {
    std::vector<float> normals = compute_normals(vertices);
    std::ofstream plyFile(filename);

    plyFile << "ply\nformat ascii 1.0\nelement vertex " << vertices.size() / 3 << "\n";
    plyFile << "property float x\nproperty float y\nproperty float z\n";
    plyFile << "property float nx\nproperty float ny\nproperty float nz\n";
    plyFile << "element face " << vertices.size() / 9 << "\n";
    plyFile << "property list uchar int vertex_indices\nend_header\n";

    for (size_t i = 0; i < vertices.size(); i += 3) {
        plyFile << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << " ";
        plyFile << normals[i] << " " << normals[i+1] << " " << normals[i+2] << "\n";
    }

    for (size_t i = 0; i < vertices.size() / 3; i += 3)
        plyFile << "3 " << i << " " << i+1 << " " << i+2 << "\n";

    plyFile.close();
}
