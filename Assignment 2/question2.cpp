#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

static inline double frand() { // Function to generate a random float between -1 and 1
    double x = ((double) rand()) / (double) RAND_MAX; // Generate a random float between 0 and 1
    return (rand() % 2) ? -x : x; // Return the float with a random sign
}

void getRandomCorner(float &x, float &y, float lastX, float lastY) { // Function to get a random corner
    vector<pair<float, float>> corners = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} }; // List of corners

    for (size_t i = 0; i < corners.size(); i++) { // Iterate over the corners
        if (corners[i].first == -lastX && corners[i].second == -lastY) { // Check if the corner is the last corner
            corners.erase(corners.begin() + i); // Remove the corner
            break;
        }
    }

    int index = rand() % corners.size(); // Get a random corner
    x = corners[index].first; // Set the x coordinate
    y = corners[index].second; // Set the y coordinate
}

int main(int argc, char* argv[]) {
    if (argc != 4) { // Check if the number of arguments is correct
        cerr << "Usage: " << argv[0] << " <N> <screen_width> <screen_height>" << endl; // Print usage
        return -1;
    }

    int N = atoi(argv[1]); // Get the number of points
    int screenWidth = atoi(argv[2]);
    int screenHeight = atoi(argv[3]);

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Dot Plot Algorithm", NULL, NULL); // Create a window
    if (!window) { // Check if window was created successfully
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Set the window as the current context

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.1, 1.1, -1.1, 1.1, -1, 1); // Set the orthographic projection
    glMatrixMode(GL_MODELVIEW);

    srand(time(NULL)); // Seed the random number generator

    vector<pair<float, float>> points; // Vector to store the points

    float xmin = -1.0f, ymin = -1.0f, xmax = 1.0f, ymax = 1.0f; // Set the bounding box

    float cx, cy; // Get the first corner
    getRandomCorner(cx, cy, 0, 0); // Get the first corner

    float px = frand(); // Get the first point
    float py = frand();

    for (int i = 0; i < N; i++) { // Generate N points
        points.push_back({px, py}); // Add the point to the vector

        float newCx, newCy; // Get the new corner
        getRandomCorner(newCx, newCy, cx, cy); // Get the new corner
        cx = newCx;
        cy = newCy;

        px = (px + cx) / 2.0f; // Calculate the new point
        py = (py + cy) / 2.0f;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set the clear color to white
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    glColor3f(0, 0, 0); // Set the drawing color to black
    glPointSize(2.0f); // Set the point size

    glBegin(GL_POINTS); // Draw the points
    for (const auto& point : points) { // Iterate over the points
        glVertex2f(point.first, point.second); // Draw the point
    }
    glEnd();

    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}