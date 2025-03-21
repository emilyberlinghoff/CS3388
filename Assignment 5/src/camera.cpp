#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

void updateCamera(GLFWwindow* window, glm::mat4 &V, float &r, float &theta, float &phi) {
    static const float move_speed = 0.05f;
    static const float rotate_speed = 0.5f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        r = std::max(r - move_speed, 0.1f);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        r += move_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        theta += rotate_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        theta -= rotate_speed;
    }

    static bool firstClick = true;
    static double last_xpos = -1, last_ypos = -1;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (firstClick) {
            last_xpos = xpos;
            last_ypos = ypos;
            firstClick = false;
        } else {
            theta -= rotate_speed * float(xpos - last_xpos);
            phi += rotate_speed * float(ypos - last_ypos);
            phi = glm::clamp(phi, -89.0f, 89.0f);
        }
    } else {
        firstClick = true;
    }

    glm::vec3 camera_position(
        r * sin(glm::radians(theta)) * cos(glm::radians(phi)),
        r * sin(glm::radians(phi)),
        r * cos(glm::radians(theta)) * cos(glm::radians(phi))
    );

    glm::vec3 camera_direction = glm::normalize(-camera_position);
    glm::vec3 camera_up(0.0f, 1.0f, 0.0f);

    V = glm::lookAt(camera_position, camera_position + camera_direction, camera_up);
}
