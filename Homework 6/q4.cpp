// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include OpenGL Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Using GLM for transformations
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

GLFWwindow* window;

// Callback for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//////////////////////////////////////////////////////////////////////////////
// Vertex Data: Positions + Colors (18 floats total)
//////////////////////////////////////////////////////////////////////////////
static const GLfloat vertexData[] = {
    // Position (x, y, z)   // Color (r, g, b)
    0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // v1 (Red)
    1.0f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  // v2 (Green)
   -1.0f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f   // v3 (Blue)
};

// Index Data (for `glDrawElements`)
static const GLuint indices[] = { 0, 1, 2 };

//////////////////////////////////////////////////////////////////////////////
// Shader Source Code (OpenGL 2.1 - #version 120)
//////////////////////////////////////////////////////////////////////////////

const char* vertexShaderSource = R"(
    #version 120
    attribute vec3 vertexPosition;
    attribute vec3 vertexColor;
    varying vec3 fragColor;
    void main() {
        gl_Position = vec4(vertexPosition, 1.0);
        fragColor = vertexColor;  // Pass color to fragment shader
    }
)";

const char* fragmentShaderSource = R"(
    #version 120
    varying vec3 fragColor;
    void main() {
        gl_FragColor = vec4(fragColor, 1.0);  // Use interpolated color
    }
)";

//////////////////////////////////////////////////////////////////////////////
// Helper Function: Compile Shader
//////////////////////////////////////////////////////////////////////////////
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader Compilation Failed\n" << infoLog << std::endl;
    }

    return shader;
}

//////////////////////////////////////////////////////////////////////////////
// Main Program
//////////////////////////////////////////////////////////////////////////////

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Create a GLFW window
    glfwWindowHint(GLFW_SAMPLES, 4);
    window = glfwCreateWindow(800, 600, "OpenGL Triangle", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    // Print OpenGL Version (Debugging)
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Compile shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader Program Linking Failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create VAO, VBO, and EBO (Index Buffer)
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    // Load vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // Load index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Get attribute locations manually (since OpenGL 2.1 does not support `layout(location = X)`)
    GLuint positionAttrib = glGetAttribLocation(shaderProgram, "vertexPosition");
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(positionAttrib);

    GLuint colorAttrib = glGetAttribLocation(shaderProgram, "vertexColor");
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the Triangle using `glDrawElements`
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // Uses indices
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}