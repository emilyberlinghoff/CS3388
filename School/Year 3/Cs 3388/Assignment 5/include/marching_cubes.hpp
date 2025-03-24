#ifndef MARCHING_CUBES_HPP
#define MARCHING_CUBES_HPP

#include <vector>
#include <functional>
#include <string>

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
    void writePLY(const std::string& filename);
};

#endif
