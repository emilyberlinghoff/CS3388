#ifndef MARCHING_CUBES_HPP
#define MARCHING_CUBES_HPP

#include <vector>
#include <functional>

class MarchingCubes {
    std::function<float(float, float, float)> generationFunction;
    float isoValue, minCoord, maxCoord, stepSize, currentIteration;
    std::vector<float> vertices;

    void generate_iterative_new();
public:
    bool finished;
    MarchingCubes(std::function<float(float, float, float)> f, float isoval, float min, float max, float step);
    void generate();
    std::vector<float> getVertices();
};

std::vector<float> compute_normals(std::vector<float> vertices);

#endif
