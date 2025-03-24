#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera();

    void update(GLFWwindow* window);
    glm::mat4 getViewMatrix() const;

private:
    float r;
    float theta;
    float phi;

    const float angleStep = 1.5f; // degrees per frame
};
