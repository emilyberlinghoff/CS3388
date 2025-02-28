// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Enable experimental GLM features
#define GLM_ENABLE_EXPERIMENTAL

// Include OpenGL-related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM for transformations and vector operations
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Vertex positions for a quad
GLfloat g_vert_buffer[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};

// Swapped UV texture coordinates to match correct gradient orientation
GLfloat g_uv_buffer[] = {
    1.0f, 0.0f,  // Bottom-left
    1.0f, 1.0f,  // Top-left
    0.0f, 1.0f,  // Top-right
    0.0f, 0.0f   // Bottom-right
};

// Indices for drawing the quad using two triangles
GLuint indexArray[] = {
    0, 2, 1,
    0, 3, 2
};

GLuint VAO, VBO, UVBO, EBO;

// Function to check shader compilation errors
void checkShaderCompilation(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "ERROR: Shader Compilation (" << type << ")\n" << infoLog << std::endl;
    } else {
        std::cout << type << " Shader Compiled Successfully!\n";
    }
}

// Function to check program linking errors
void checkProgramLinking(GLuint program) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cerr << "ERROR: Shader Program Linking\n" << infoLog << std::endl;
    } else {
        std::cout << "Shader Program Linked Successfully!\n";
    }
}

int main(int argc, char* argv[]) {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    float screenW = 1400;
    float screenH = 900;
    window = glfwCreateWindow(screenW, screenH, "An Example", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    // Vertex Shader Code
    std::string VertexShaderCode = R"(
        #version 120
        attribute vec3 inPosition;
        attribute vec2 inTexCoord;
        varying vec2 texCoord;
        void main() {
            gl_Position = vec4(inPosition, 1.0);
            texCoord = inTexCoord;
        }
    )";

    // Fragment Shader Code
    std::string FragmentShaderCode = R"(
        #version 120
        varying vec2 texCoord;
        void main() {
            gl_FragColor = vec4(texCoord.x, texCoord.y, 0.0, 1.0);
        }
    )";

    // Compile Shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    const char* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);
    checkShaderCompilation(VertexShaderID, "Vertex");

    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);
    checkShaderCompilation(FragmentShaderID, "Fragment");

    // Link Shader Program
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    checkProgramLinking(ProgramID);
    glUseProgram(ProgramID);

    // Generate and bind VAO and VBOs
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UVBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vert_buffer), g_vert_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer), g_uv_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);

    glBindVertexArray(0);

    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(ProgramID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();
    return 0;
}