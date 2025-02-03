#define GL_SILENCE_DEPRECATION // Suppress macOS OpenGL deprecation warnings cause idk how to fix them
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <glm/glm.hpp> // Modern OpenGL Math Library
#include <glm/gtc/matrix_transform.hpp> // Transformation functions
#define PI 3.14159265

struct Point { // A simple struct to store 2D points
    float x, y;
};

std::vector<Point> dogPoints;  // Stores the poly-line vertices

void readDogFile(const char* filename) { // Function to read the dog file
    std::ifstream file(filename);
    if (!file) { // Check if file opened successfully
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    float x, y; // Temporary variables to store the x and y coordinates
    while (file >> x >> y) { // Read the x and y coordinates from the file
        dogPoints.push_back(Point{x, y}); // Add the point to the vector
    }
}

void drawDog(float centerX, float centerY, float angle) { // Function to draw the dog at a given position and angle
    glm::mat4 model = glm::mat4(1.0f); // Identity matrix
    model = glm::translate(model, glm::vec3(centerX, centerY, 0.0f)); // Translate to the center of the circle
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 0, 1)); // Rotate the dog by the given angle
    glLoadMatrixf(&model[0][0]); // Load the model matrix
    glBegin(GL_LINE_STRIP); // Draw the dog
    for (const auto& p : dogPoints) { // Iterate over the vertices of the dog
        glVertex2f(p.x, p.y); // Draw the vertex
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1; // Initialize GLFW
    GLFWwindow* window = glfwCreateWindow(600, 600, "Rotating Dogs", NULL, NULL); // Create a window
    if (!window) { // Check if window was created successfully
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Set the window as the current context
    glMatrixMode(GL_PROJECTION); // Set the projection matrix
    glLoadIdentity();
    glOrtho(0, 60, 0, 60, -1, 1); // Set the orthographic projection
    glMatrixMode(GL_MODELVIEW);

    readDogFile("dog.txt");

    float angle = 0.0f; // Initialize the angle to 0

    while (!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set the clear color to white
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glColor3f(0, 0, 0); // Set the drawing color to black

    float radius = 25;
    float centerX = 30, centerY = 30;

    for (int i = 0; i < 8; i++) { // Draw 8 dogs in a circle
        float theta = i * 45 * PI / 180; // Calculate the angle of the dog
        float x = centerX + radius * cos(theta); // Calculate the x coordinate of the dog
        float y = centerY + radius * sin(theta); // Calculate the y coordinate of the dog
        drawDog(x, y, angle); // Draw the dog at the calculated position
    }

    angle += 1.0f; 

    glfwSwapBuffers(window);
    glfwPollEvents();
}

    glfwTerminate();
    return 0;
}