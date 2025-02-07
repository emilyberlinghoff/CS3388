#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    // Given parameters
    double fov = 50.0;          // Field of view in degrees
    double aspect_ratio = 2.0;  // Aspect ratio
    double near_plane = 1.0;    // Near clipping plane
    double far_plane = 10.0;    // Far clipping plane

    double t = near_plane * std::tan((fov / 2.0) * M_PI / 180.0); // Calculate t (top)

    double r = t * aspect_ratio; // Calculate r (right)

    double projection_matrix[4][4] = { // Construct the projection matrix
        {near_plane / r, 0.0, 0.0, 0.0},
        {0.0, near_plane / t, 0.0, 0.0},
        {0.0, 0.0, -(far_plane + near_plane) / (far_plane - near_plane), -2.0 * far_plane * near_plane / (far_plane - near_plane)},
        {0.0, 0.0, -1.0, 0.0}
    };

    // Output the results
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "t (top): " << t << std::endl;
    std::cout << "r (right): " << r << std::endl;
    std::cout << "Projection Matrix:" << std::endl;

    for (int i = 0; i < 4; ++i) { // Output the projection matrix
        for (int j = 0; j < 4; ++j) {
            std::cout << projection_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
