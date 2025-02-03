//#pragma once
//#include <glm/glm.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//class Camera {
//public:
//    glm::vec3 position;
//    glm::quat orientation; // Camera's orientation as a quaternion
//    glm::vec3 velocity; // For smoothing camera movement
//    glm::vec3 angularVelocity; // For smoothing rotation
//
//    float yaw; // Rotation around the vertical axis (Y-axis)
//    float pitch; // Rotation around the horizontal axis (X-axis)
//    float roll; // Rotation around the forward axis (Z-axis)
//
//    float speed; // Movement speed
//    float sensitivity; // Mouse sensitivity
//    float damping; // Damping factor for smoothing
//    float distanceFromTarget; // Distance from the target (e.g., pyramid)
//
//    // Constructor
//    Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity, float dampingFactor);
//
//    // Methods
//    void move(const glm::vec3& direction, float deltaTime);
//    void rotate(float deltaX, float deltaY, float deltaRoll, float deltaTime);
//    void rotateAroundPoint(glm::vec3 target, float deltaX, float deltaY, float deltaTime);
//
//    glm::mat4 getViewMatrix() const;
//    glm::mat4 getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const;
//    glm::vec3 getPosition() const;
//
//    // Helper methods for orientation
//    glm::vec3 getForwardVector() const;
//    glm::vec3 getRightVector() const;
//    glm::vec3 getUpVector() const;
//};


#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    // Constructor for free movement (if needed)
    Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity, float dampingFactor);

    // Standard free-movement methods (if you want them)
    void move(const glm::vec3& direction, float deltaTime);
    void rotate(float deltaYaw, float deltaPitch, float deltaRoll, float deltaTime);

    // New orbit method: updates orbit angles and recalculates position based on a fixed target.
    void orbitAroundTarget(glm::vec3 target, float deltaYaw, float deltaPitch);

    // Returns the view matrix.
    glm::mat4 getViewMatrix() const;

    // Returns a perspective projection matrix.
    glm::mat4 getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const;

    // Get the current camera position.
    glm::vec3 getPosition() const;

    // Returns the camera’s forward, right, and up vectors.
    glm::vec3 getForwardVector() const;
    glm::vec3 getRightVector() const;
    glm::vec3 getUpVector() const;

    // (Optional) Set the orbit radius.
    void setOrbitRadius(float radius) { orbitRadius = radius; }

private:
    // Free-movement members:
    glm::vec3 position;
    glm::quat orientation;
    float speed;
    float sensitivity;
    float damping;
    glm::vec3 velocity;

    // For accumulated free-look (if needed)
    float accumulatedYaw;
    float accumulatedPitch;

    // Orbiting camera members:
    // These are used when you want to orbit around a target.
    float orbitYaw;    // Horizontal orbit angle (in degrees)
    float orbitPitch;  // Vertical orbit angle (in degrees)
    float orbitRadius; // Distance from the target
};

#endif // CAMERA_H

