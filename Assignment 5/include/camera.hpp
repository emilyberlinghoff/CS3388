#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void updateCamera(GLFWwindow* window, glm::mat4 &V, float &r, float &theta, float &phi);

#endif
