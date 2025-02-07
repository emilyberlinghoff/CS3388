#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double magnitude(double x, double y, double z) { // Function to calculate the magnitude of a vector
    return sqrt(x * x + y * y + z * z);
}

void normalize(double& x, double& y, double& z) { // Function to normalize a vector
    double mag = magnitude(x, y, z);
    x /= mag;
    y /= mag;
    z /= mag;
}

void crossProduct(double ax, double ay, double az, double bx, double by, double bz, double& rx, double& ry, double& rz) { // Function to compute the cross product of two vectors
    rx = ay * bz - az * by;
    ry = az * bx - ax * bz;
    rz = ax * by - ay * bx;
}

int main() { // Main function to compute the view matrix

    double Cx = 5.0, Cy = 3.0, Cz = 5.0; // Camera position

    double Tx = 2.0, Ty = 0.0, Tz = -1.0; // Look-at point

    double Ux = 0.0, Uy = 1.0, Uz = 0.0; // World up vector

    double Fx = Tx - Cx, Fy = Ty - Cy, Fz = Tz - Cz; // Compute the forward vector F = (T - C)
    normalize(Fx, Fy, Fz);  // Normalize F

    double Rx, Ry, Rz; // Compute the right vector R = F x U
    crossProduct(Fx, Fy, Fz, Ux, Uy, Uz, Rx, Ry, Rz);
    normalize(Rx, Ry, Rz);  // Normalize R

    double Ux_prime, Uy_prime, Uz_prime; // Compute the recalculated up vector U' = R x F
    crossProduct(Rx, Ry, Rz, Fx, Fy, Fz, Ux_prime, Uy_prime, Uz_prime);

    double viewMatrix[4][4] = { // Compute the view matrix
        {Rx, Ry, Rz, -(Rx * Cx + Ry * Cy + Rz * Cz)},
        {Ux_prime, Uy_prime, Uz_prime, -(Ux_prime * Cx + Uy_prime * Cy + Uz_prime * Cz)},
        {-Fx, -Fy, -Fz, Fx * Cx + Fy * Cy + Fz * Cz},
        {0.0, 0.0, 0.0, 1.0}
    };

    cout << fixed << setprecision(4); // Output the view matrix
    cout << "View Matrix:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << viewMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}