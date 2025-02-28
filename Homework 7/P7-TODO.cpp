// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include OpenGL-related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Enable experimental GLM extensions for debugging
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Error callback function for GLFW
void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << std::endl;
}

// Vertex positions for a quad
GLfloat g_vert_buffer[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};

// Vertex colors corresponding to each vertex
GLfloat g_color_buffer[] = {
    1.0f, 0.0f, 0.0f, // Red
    0.0f, 1.0f, 0.0f, // Green
    0.0f, 0.0f, 1.0f, // Blue
    0.0f, 0.5f, 0.5f, // Cyan-like
};

// Indices for drawing the quad using two triangles
GLuint indexArray[] = {
    0, 2, 1, 
    0, 3, 2
};

int main(int argc, char* argv[]) {
    // Set GLFW error callback
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    float screenW = 1400;
    float screenH = 900;
    
    // Request OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create GLFW window
    window = glfwCreateWindow(screenW, screenH, "Shader Example", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to open GLFW window! Ensure OpenGL 3.3+ is supported." << std::endl;
        glfwTerminate();
        return -1;
    } else {
        std::cout << "GLFW window successfully created!" << std::endl;
    }
    glfwMakeContextCurrent(window);

    // Ensure OpenGL context is active
    if (!glfwGetCurrentContext()) {
        std::cerr << "🚨 OpenGL context is NOT active!" << std::endl;
        glfwTerminate();
        return -1;
    } else {
        std::cout << "OpenGL context is active." << std::endl;
    }

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Generate VAO, VBO, and EBO
    GLuint VBO[2], VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and upload vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vert_buffer), g_vert_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // Bind and upload vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer), g_color_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    // Bind and upload indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Vertex shader code
    std::string VertexShaderCode = R"(
        #version 330 core
        layout(location = 0) in vec3 inPosition;
        layout(location = 1) in vec3 inColor;
        out vec3 fragColor;
        void main() {
            gl_Position = vec4(inPosition, 1.0);
            fragColor = inColor;
        }
    )";

    // Fragment shader code with conditional color modification
    std::string FragmentShaderCode = R"(
        #version 330 core
        in vec3 fragColor;
        out vec4 outColor;
        void main() {
            if (fragColor.r > 0.5) {
                outColor = vec4(0.0, 0.0, 0.0, 1.0); // Black if red component > 0.5
            } else {
                outColor = vec4(fragColor, 1.0); // Otherwise, use interpolated color
            }
        }
    )";

    // Compile shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Link shaders into a program
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    glUseProgram(ProgramID);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(ProgramID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
