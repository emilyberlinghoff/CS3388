
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // DEBUG: Wireframe mode

    GLuint programID = loadShaders("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    GLint linkStatus = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        char log[512];
        glGetProgramInfoLog(programID, 512, nullptr, log);
        std::cerr << "Shader link error: " << log << std::endl;
    }

    auto func = [](float x, float y, float z) {
        return x * x + y * y + z * z - 4.0f;
    };

    MarchingCubes cubes(func, 0.0f, -3.0f, 3.0f, 0.1f);
    cubes.generate();

    std::cout << "Generated " << cubes.getVertices().size() / 9 << " triangles.\n";
    std::cout << "Vertices: " << cubes.getVertices().size() << "\n";

    GLuint vao, vertexVBO, normalVBO;
    setupRendering(vao, vertexVBO, normalVBO, programID);
    updateBuffers(vao, vertexVBO, normalVBO, cubes.getVertices(), compute_normals(cubes.getVertices()));

    const auto& verts = cubes.getVertices();
    std::cout << "First few vertices: ";
    for (int i = 0; i < std::min(9, static_cast<int>(verts.size())); ++i)
        std::cout << verts[i] << " ";
    std::cout << std::endl;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    Camera camera;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // red background for visibility
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update(window);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 mvp = projection * view;

        glUseProgram(programID);
        GLuint mvpID = glGetUniformLocation(programID, "MVP");
        glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

        glBindVertexArray(vao);

        std::cout << "Drawing " << verts.size() / 3 << " vertices...\n";
        glDrawArrays(GL_TRIANGLES, 0, verts.size() / 3);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
            std::cerr << "OpenGL Error: " << err << std::endl;

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &normalVBO);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(programID);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
