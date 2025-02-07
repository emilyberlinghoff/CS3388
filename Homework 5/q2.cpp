#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

void multiplyMatrices(double A[3][3], double B[3][3], double result[3][3]) { // Function to multiply two 3x3 matrices
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = 0.0;
            for (int k = 0; k < 3; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(double matrix[3][3]) { // Print a 3x3 matrix
    cout << fixed << setprecision(4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void rotationX(double alpha, double Rx[3][3]) { // Function to define rotation matrices
    Rx[0][0] = 1; Rx[0][1] = 0;                Rx[0][2] = 0;
    Rx[1][0] = 0; Rx[1][1] = cos(alpha);       Rx[1][2] = -sin(alpha);
    Rx[2][0] = 0; Rx[2][1] = sin(alpha);       Rx[2][2] = cos(alpha);
}

void rotationY(double beta, double Ry[3][3]) { // Function to define rotation matrices
    Ry[0][0] = cos(beta);  Ry[0][1] = 0;       Ry[0][2] = sin(beta);
    Ry[1][0] = 0;          Ry[1][1] = 1;       Ry[1][2] = 0;
    Ry[2][0] = -sin(beta); Ry[2][1] = 0;       Ry[2][2] = cos(beta);
}

void rotationZ(double gamma, double Rz[3][3]) { // Function to define rotation matrices
    Rz[0][0] = cos(gamma);  Rz[0][1] = -sin(gamma); Rz[0][2] = 0;
    Rz[1][0] = sin(gamma);  Rz[1][1] = cos(gamma);  Rz[1][2] = 0;
    Rz[2][0] = 0;           Rz[2][1] = 0;           Rz[2][2] = 1;
}

int main() {
    // Rotation angles in radians
    double alpha = M_PI / 6; // 30 degrees
    double beta = M_PI / 4;  // 45 degrees
    double gamma = M_PI / 3; // 60 degrees

    // Define rotation matrices
    double Rx[3][3], Ry[3][3], Rz[3][3];
    rotationX(alpha, Rx);
    rotationY(beta, Ry);
    rotationZ(gamma, Rz);

    // Compute R1 = Rx * Ry * Rz
    double temp1[3][3], R1[3][3];
    multiplyMatrices(Rx, Ry, temp1);
    multiplyMatrices(temp1, Rz, R1);

    // Compute R2 = Rz * Ry * Rx
    double temp2[3][3], R2[3][3];
    multiplyMatrices(Rz, Ry, temp2);
    multiplyMatrices(temp2, Rx, R2);

    // Output results
    cout << "R1 = Rx * Ry * Rz:" << endl;
    printMatrix(R1);

    cout << "\nR2 = Rz * Ry * Rx:" << endl;
    printMatrix(R2);

    bool areEqual = true; // Verify if R1 and R2 are equal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (abs(R1[i][j] - R2[i][j]) > 1e-4) {
                areEqual = false;
                break;
            }
        }
        if (!areEqual) break;
    }

    cout << "\nAre R1 and R2 equal? " << (areEqual ? "Yes" : "No") << endl;

    return 0;
}