#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>

Camera::Camera() : r(3.0f), theta(45.0f), phi(30.0f) {}

void Camera::update(GLFWwindow* window) {
    const float move_speed = 0.05f;
    const float rotate_speed = 0.5f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        r = std::max(r - move_speed, 0.1f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        r += move_speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        theta -= rotate_speed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        theta += rotate_speed;

    static bool firstClick = true;
    static double lastX = -1.0, lastY = -1.0;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (firstClick) {
            lastX = mouseX;
            lastY = mouseY;
            firstClick = false;
        } else {
            theta -= rotate_speed * float(mouseX - lastX);
            phi += rotate_speed * float(mouseY - lastY);
            phi = glm::clamp(phi, -89.0f, 89.0f);
            lastX = mouseX;
            lastY = mouseY;
        }
    } else {
        firstClick = true;
    }
}

glm::mat4 Camera::getViewMatrix() const {
    glm::vec3 pos(
        r * sin(glm::radians(theta)) * cos(glm::radians(phi)),
        r * sin(glm::radians(phi)),
        r * cos(glm::radians(theta)) * cos(glm::radians(phi))
    );
    glm::vec3 dir = glm::normalize(-pos);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    return glm::lookAt(pos, pos + dir, up);
}
