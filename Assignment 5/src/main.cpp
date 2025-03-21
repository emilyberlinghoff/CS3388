#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "marching_cubes.hpp"
#include "rendering.hpp"
#include "camera.hpp"

GLFWwindow* window;

// Scalar field function for Marching Cubes
float f(float x, float y, float z) {
    return x * x - y * y - z * z - z;
}

int main(int argc, char* argv[]) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    window = glfwCreateWindow(1000, 1000, "Marching Cubes", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

    // Matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view, projection;
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.001f, 1000.0f);
    
    // Initialize Marching Cubes
    MarchingCubes cubes(f, -1.5, -5.0f, 5.0f, 0.05);
    
    // Set up rendering
    GLuint vao, vertexVBO, normalVBO, programID;
    setupRendering(vao, vertexVBO, normalVBO, programID);
    
    float r = 3.0f, theta = 45.0f, phi = 45.0f;
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateCamera(window, view, r, theta, phi);
        glm::mat4 mvp = projection * view * model;

        // Generate marching cubes if not finished
        if (!cubes.finished) {
            cubes.generate();
            std::vector<float> vertices = cubes.getVertices();
            std::cout << "Generated " << vertices.size() / 3 << " vertices." << std::endl;
            std::vector<float> normals = compute_normals(vertices);
            updateBuffers(vao, vertexVBO, normalVBO, vertices, normals);
        }

        renderScene(vao, programID, mvp, view);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
