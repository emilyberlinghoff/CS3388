#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include "camera.hpp"
#include "shaders.hpp"
#include "rendering.hpp"
#include "marching_cubes.hpp"
#include "utils.hpp"
#include <glm/gtc/type_ptr.hpp>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Marching Cubes", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLuint programID = loadShaders("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    glUseProgram(programID);
    GLint colorLoc = glGetUniformLocation(programID, "modelColor");
    glUniform3f(colorLoc, 0.0f, 1.0f, 1.0f); // Cyan

    // Set uniform for light direction
    GLint lightDirLoc = glGetUniformLocation(programID, "LightDir");
    glUniform3f(lightDirLoc, 0.0f, 0.0f, -1.0f); // Light coming from +z view direction

    // Implicit functions for the two surfaces
    auto funcTop = [](float x, float y, float z) {
        return y - (sin(x) * cos(z));
    };

    auto funcBottom = [](float x, float y, float z) {
        return (x*x) - (y*y) - (z*z) - z - 1.5f;
    };

    // Marching Cubes for the top surface
    MarchingCubes cubesTop(funcTop, 0.0f, -3.0f, 3.0f, 0.1f);
    cubesTop.generate();

    // Marching Cubes for the bottom surface
    MarchingCubes cubesBottom(funcBottom, 0.0f, -3.0f, 3.0f, 0.1f);
    cubesBottom.generate();

    // Setup rendering for both surfaces
    GLuint vaoTop, vertexVBOTop, normalVBOTop;
    setupRendering(vaoTop, vertexVBOTop, normalVBOTop, programID);
    updateBuffers(vaoTop, vertexVBOTop, normalVBOTop, cubesTop.getVertices(), compute_normals(cubesTop.getVertices()));

    GLuint vaoBottom, vertexVBOBottom, normalVBOBottom;
    setupRendering(vaoBottom, vertexVBOBottom, normalVBOBottom, programID);
    updateBuffers(vaoBottom, vertexVBOBottom, normalVBOBottom, cubesBottom.getVertices(), compute_normals(cubesBottom.getVertices()));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    Camera camera;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.3f, 0.0f); // Dark grey background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        camera.update(window);
    
        glm::mat4 model = glm::mat4(1.0f); // Identity matrix
    
        int winWidth, winHeight;
        glfwGetFramebufferSize(window, &winWidth, &winHeight);
    
        // ===== TOP VIEWPORT =====
        glm::mat4 viewTop = camera.getViewMatrix();
        glm::mat4 MVPTop = projection * viewTop * model;
    
        glViewport(0, (winHeight / 2) + 1, winWidth, winHeight / 2); // Top half
    
        glUseProgram(programID);
        glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVPTop));
        glUniformMatrix4fv(glGetUniformLocation(programID, "View"), 1, GL_FALSE, glm::value_ptr(viewTop));
        glUniform3f(glGetUniformLocation(programID, "LightDir"), -1.0f, -1.0f, -1.0f);
        glUniform1i(glGetUniformLocation(programID, "useLighting"), 1);
        glUniform3f(glGetUniformLocation(programID, "modelColor"), 0.0f, 1.0f, 1.0f); // Cyan
    
        // Draw top mesh
        glBindVertexArray(vaoTop);
        glDrawArrays(GL_TRIANGLES, 0, cubesTop.getVertices().size() / 3);
    
        // Draw top box and axes
        glUniform1i(glGetUniformLocation(programID, "useLighting"), 0);
        glUniform3f(glGetUniformLocation(programID, "modelColor"), 1.0f, 1.0f, 1.0f); // White
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glLineWidth(3.0f);
        drawThickBox(programID, MVPTop, viewTop, -3.0f, 3.0f, 0.01f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(programID);
        glUniform1i(glGetUniformLocation(programID, "useLighting"), 0);
        drawAxes(programID, MVPTop, viewTop, -3.0f, 3.0f);
    
        // ===== BOTTOM VIEWPORT =====
        glm::mat4 viewBottom = camera.getViewMatrix();
        glm::mat4 MVPBottom = projection * viewBottom * model;
    
        glViewport(0, 0, winWidth, (winHeight / 2) - 1); // Bottom half
    
        glUseProgram(programID);
        glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVPBottom));
        glUniformMatrix4fv(glGetUniformLocation(programID, "View"), 1, GL_FALSE, glm::value_ptr(viewBottom));
        glUniform3f(glGetUniformLocation(programID, "LightDir"), -1.0f, -1.0f, -1.0f);
        glUniform1i(glGetUniformLocation(programID, "useLighting"), 1);
        glUniform3f(glGetUniformLocation(programID, "modelColor"), 0.0f, 1.0f, 1.0f); // Cyan
    
        // Draw bottom mesh
        glBindVertexArray(vaoBottom);
        glDrawArrays(GL_TRIANGLES, 0, cubesBottom.getVertices().size() / 3);
    
        // Draw bottom box and axes
        glUniform1i(glGetUniformLocation(programID, "useLighting"), 0);
        glUniform3f(glGetUniformLocation(programID, "modelColor"), 1.0f, 1.0f, 1.0f); // White
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glLineWidth(3.0f);
        drawThickBox(programID, MVPBottom, viewBottom, -3.0f, 3.0f, 0.03f);
        drawAxes(programID, MVPBottom, viewBottom, -3.0f, 3.0f);
    
        glBindVertexArray(0);
        glUseProgram(0);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }    

    // Cleanup
    glDeleteBuffers(1, &vertexVBOTop);
    glDeleteBuffers(1, &normalVBOTop);
    glDeleteVertexArrays(1, &vaoTop);

    glDeleteBuffers(1, &vertexVBOBottom);
    glDeleteBuffers(1, &normalVBOBottom);
    glDeleteVertexArrays(1, &vaoBottom);

    glDeleteProgram(programID);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// 16:06