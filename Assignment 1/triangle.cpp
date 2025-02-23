#include <GLFW/glfw3.h>
#include <iostream>

void drawTriangle() {
    glBegin(GL_TRIANGLES); // Start specifying a triangle
        glVertex2f(0.0f, 0.5f);  // Vertex 1
        glVertex2f(0.5f, -0.25f); // Vertex 2
        glVertex2f(-0.5f, -0.25f); // Vertex 3
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 1000, "Hello World", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the clear color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Set drawing color to black for the triangle
        glColor3f(0.0f, 0.0f, 0.0f);

        // Draw the triangle
        drawTriangle();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
