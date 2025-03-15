// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

#define TOP_LEFT     8
#define TOP_RIGHT    4
#define BOTTOM_RIGHT 2
#define BOTTOM_LEFT  1

typedef float (*scalar_field_2d)(float, float);

// Lookup table for marching squares
int marching_squares_lut[16][4] = {
    {-1, -1, -1, -1}, {2, 3, -1, -1}, {1, 2, -1, -1}, {1, 3, -1, -1},
    {0, 1, -1, -1}, {0, 1, 2, 3}, {0, 2, -1, -1}, {0, 3, -1, -1},
    {0, 3, -1, -1}, {0, 2, -1, -1}, {0, 3, 1, 2}, {0, 1, -1, -1},
    {1, 3, -1, -1}, {1, 2, -1, -1}, {2, 3, -1, -1}, {-1, -1, -1, -1}
};

float g_verts[4][2] = {
    {0.5f, 1.0f}, {1.0f, 0.5f}, {0.5f, 0.0f}, {0.0f, 0.5f}
};

float f1(float x, float y) {
    return x * x + y * y;
}

std::vector<float> marching_squares(scalar_field_2d f, float isoval, float minx, float maxx, float miny, float maxy, float stepsize) {
    std::vector<float> vertices;
    for (float y = miny; y < maxy; y += stepsize) {
        for (float x = minx; x < maxx; x += stepsize) {
            float tl = f(x, y + stepsize);
            float tr = f(x + stepsize, y + stepsize);
            float br = f(x + stepsize, y);
            float bl = f(x, y);
            
            int which = (tl < isoval ? TOP_LEFT : 0) | (tr < isoval ? TOP_RIGHT : 0) |
                        (br < isoval ? BOTTOM_RIGHT : 0) | (bl < isoval ? BOTTOM_LEFT : 0);
            
            int* verts = marching_squares_lut[which];
            if (verts[0] >= 0) {
                vertices.push_back(x + stepsize * g_verts[verts[0]][0]);
                vertices.push_back(y + stepsize * g_verts[verts[0]][1]);
                vertices.push_back(x + stepsize * g_verts[verts[1]][0]);
                vertices.push_back(y + stepsize * g_verts[verts[1]][1]);
            }
            if (verts[2] >= 0) {
                vertices.push_back(x + stepsize * g_verts[verts[2]][0]);
                vertices.push_back(y + stepsize * g_verts[verts[2]][1]);
                vertices.push_back(x + stepsize * g_verts[verts[3]][0]);
                vertices.push_back(y + stepsize * g_verts[verts[3]][1]);
            }
        }
    }
    return vertices;
}

void draw_grid(float minx, float maxx, float miny, float maxy, float stepsize) {
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (float x = minx; x <= maxx; x += stepsize) {
        glVertex2f(x, miny);
        glVertex2f(x, maxy);
    }
    for (float y = miny; y <= maxy; y += stepsize) {
        glVertex2f(minx, y);
        glVertex2f(maxx, y);
    }
    glEnd();
}

// Global variables
int gridWidth = 50;   // Default grid width
int gridHeight = 50;  // Default grid height
float stepsize = 0.2f; // Step size for the grid

int main(int argc, char** argv) {
    // Read grid size from command line arguments
    if (argc == 3) {
        gridWidth = atoi(argv[1]);  // Convert argument 1 to integer
        gridHeight = atoi(argv[2]); // Convert argument 2 to integer
    }

    // Adjust world coordinates dynamically based on input grid size
    float xmin = -gridWidth * stepsize * 0.5f;
    float xmax = gridWidth * stepsize * 0.5f;
    float ymin = -gridHeight * stepsize * 0.5f;
    float ymax = gridHeight * stepsize * 0.5f;
    float isoval = 1.0f;

    // Initialize GLFW
    if (!glfwInit()) return -1;
    window = glfwCreateWindow(800, 800, "Marching Squares Grid", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glewExperimental = true; 
    glewInit();

    // Set up the OpenGL projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xmin, xmax, ymin, ymax, -1, 1);

    glClearColor(0.2f, 0.2f, 0.3f, 0.0f); // Restore original blue background

    // Generate marching squares vertices
    std::vector<float> marchingVerts = marching_squares(f1, isoval, xmin, xmax, ymin, ymax, stepsize);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        draw_grid(xmin, xmax, ymin, ymax, stepsize);

        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        for (size_t i = 0; i < marchingVerts.size(); i += 2) {
            glVertex2f(marchingVerts[i], marchingVerts[i + 1]);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
