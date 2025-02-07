#include <iostream>
#include <iomanip>

int main() {
    double projection_matrix[4][4] = { // Projection matrix
        {1.0723, 0.0, 0.0, 0.0},
        {0.0, 2.1445, 0.0, 0.0},
        {0.0, 0.0, -1.2222, -2.2222},
        {0.0, 0.0, -1.0, 0.0}
    };

    double point[4] = {0.0, 0.0, -5.5, 1.0}; // Input point in homogeneous coordinates (x, y, z, w)

    double transformed_point[4] = {0.0, 0.0, 0.0, 0.0}; // Result of matrix multiplication

    for (int i = 0; i < 4; ++i) { // Perform matrix multiplication
        for (int j = 0; j < 4; ++j) { // Iterate over the columns of the matrix
            transformed_point[i] += projection_matrix[i][j] * point[j]; // Multiply and add
        }
    }

    double perspective_divided_point[4] = {0.0, 0.0, 0.0, 0.0}; // Perform perspective divide
    for (int i = 0; i < 4; ++i) {
        perspective_divided_point[i] = transformed_point[i] / transformed_point[3]; // Divide by w
    }

    // Output results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Transformed Point (before perspective divide): ";
    for (int i = 0; i < 4; ++i) {
        std::cout << transformed_point[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Normalized Point (after perspective divide): ";
    for (int i = 0; i < 4; ++i) {
        std::cout << perspective_divided_point[i] << " ";
    }
    std::cout << "\n";

    return 0;
}