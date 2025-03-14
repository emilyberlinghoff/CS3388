#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    // Camera options
    float movementSpeed;
    float rotationSpeed;
    
    // Constructor with vectors
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 frt = glm::vec3(0.0f, 0.0f, -1.0f), 
    glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f)) :
    position(pos), front(frt), worldUp(upVec), yaw(-90.0f), pitch(0.0f),
    movementSpeed(2.5f), rotationSpeed(5000.0f)  { // More realistic rotation speed
        updateCameraVectors();
    }
    
    // Returns the view matrix calculated using position and front
    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }
    
    // Processes input received from keyboard
    void processInput(bool* keyPressed, float deltaTime) {
        float speed = movementSpeed * deltaTime;  
        float rotSpeed = glm::radians(rotationSpeed) * deltaTime;  // Convert degrees to radians
        
        // Move Forward/Backward
        if (keyPressed[GLFW_KEY_UP] || keyPressed[GLFW_KEY_W]) {
            position += speed * front;
        }
        if (keyPressed[GLFW_KEY_DOWN] || keyPressed[GLFW_KEY_S]) {
            position -= speed * front;
        }
    
        // Strafe Left/Right (Move sideways)
        if (keyPressed[GLFW_KEY_A]) {
            position -= speed * right;  // Move left
        }
        if (keyPressed[GLFW_KEY_D]) {
            position += speed * right;  // Move right
        }
    
        // Rotate Left/Right
        if (keyPressed[GLFW_KEY_LEFT]) {
            yaw -= rotSpeed;
        }
        if (keyPressed[GLFW_KEY_RIGHT]) {
            yaw += rotSpeed;
        }
    
        // Update camera direction vectors
        updateCameraVectors();
    }    
      
    
private:
    // Calculates the front, right and up vectors
    void updateCameraVectors() {
        // Calculate new front vector based on yaw and pitch
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        front = glm::normalize(newFront);
    
        // Recalculate the Right and Up vectors
        right = glm::normalize(glm::cross(front, worldUp));  
        up = glm::normalize(glm::cross(right, front));
    }    
    
    float yaw = -90.0f;   // Initial yaw (looking along -Z)
    float pitch = 0.0f;   // Initial pitch (no vertical tilt)
};
#endif // CAMERA_H
