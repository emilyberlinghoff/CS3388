#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TexturedMesh.h"
#include "Camera.h"
glm::mat4 projection;

// Global variables for input handling
bool keyPressed[1024] = {false};
bool firstMouse = true;
Camera camera(glm::vec3(0.5f, 0.4f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f));

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Callback functions
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create a GLFW window (move this before using `window`)
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CS3388 Assignment 4", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Get actual framebuffer size and apply correct viewport & projection
    int winWidth, winHeight;
    glfwGetFramebufferSize(window, &winWidth, &winHeight);
    glViewport(0, 0, winWidth, winHeight);
    projection = glm::perspective(glm::radians(45.0f), (float)winWidth / (float)winHeight, 0.1f, 100.0f);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Create TexturedMesh objects for all of our models
    std::vector<TexturedMesh*> meshes;
    std::vector<bool> transparent;

    // Load models
    meshes.push_back(new TexturedMesh("LinksHouse/Walls.ply", "LinksHouse/walls.bmp"));
    transparent.push_back(false);
    
    meshes.push_back(new TexturedMesh("LinksHouse/Floor.ply", "LinksHouse/floor.bmp"));
    transparent.push_back(false);
    
    meshes.push_back(new TexturedMesh("LinksHouse/Patio.ply", "LinksHouse/patio.bmp"));
    transparent.push_back(false);
    
    meshes.push_back(new TexturedMesh("LinksHouse/WindowBG.ply", "LinksHouse/windowbg.bmp"));
    transparent.push_back(false);
    
    meshes.push_back(new TexturedMesh("LinksHouse/WoodObjects.ply", "LinksHouse/woodobjects.bmp"));
    transparent.push_back(false);
    
    meshes.push_back(new TexturedMesh("LinksHouse/Table.ply", "LinksHouse/table.bmp"));
    transparent.push_back(false);
    
    meshes.push_back(new TexturedMesh("LinksHouse/Bottles.ply", "LinksHouse/bottles.bmp"));
    transparent.push_back(false);
    
    // Transparent objects - must be rendered last
    meshes.push_back(new TexturedMesh("LinksHouse/DoorBG.ply", "LinksHouse/doorbg.bmp"));
    transparent.push_back(true);
    
    meshes.push_back(new TexturedMesh("LinksHouse/MetalObjects.ply", "LinksHouse/metalobjects.bmp"));
    transparent.push_back(true);
    
    meshes.push_back(new TexturedMesh("LinksHouse/Curtains.ply", "LinksHouse/curtains.bmp"));
    transparent.push_back(true);

    // Projection matrix
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        static float lastFrame = 0.0f;
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    
        glfwPollEvents(); // Poll input events
    
        camera.processInput(keyPressed, deltaTime);
    
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // Update view matrix
        glm::mat4 view = camera.getViewMatrix();
    
        // Render scene
        for (size_t i = 0; i < meshes.size(); i++) {
            glm::mat4 mvp = projection * view * glm::mat4(1.0f);
            meshes[i]->draw(mvp);
        }
    
        glfwSwapBuffers(window);
    }    
}

// Process keyboard input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keyPressed[key] = true;
            std::cout << "Key Pressed: " << key << std::endl;  // Debug output
        } else if (action == GLFW_RELEASE) {
            keyPressed[key] = false;
        }
    }
}

// Handle window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (width == 0 || height == 0) return;  // Prevent division by zero

    glViewport(0, 0, width, height);

    // Update the projection matrix with the new aspect ratio
    float aspectRatio = static_cast<float>(width) / (float)(height);
    projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}