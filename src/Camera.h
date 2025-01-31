//#pragma once
//#include <array>
//#include <cmath>
//
//struct Vec3 {
//    float x, y, z;
//    Vec3 operator+(const Vec3& other) const;
//    Vec3 operator-(const Vec3& other) const;
//    Vec3 operator*(float scalar) const;
//    Vec3 normalize() const;
//};
//
//struct Quaternion {
//    float w, x, y, z;
//    Quaternion normalize() const;
//    Quaternion operator*(const Quaternion& other) const;
//    Vec3 rotate(const Vec3& v) const;
//};
//
//class Camera {
//public:
//    Camera(Vec3 position, Vec3 up);
//    std::array<std::array<float, 4>, 4> GetViewMatrix() const;
//    void ProcessRotation(float angle, Vec3 axis);
//    void ProcessMovement(Vec3 direction, float deltaTime);
//    Vec3 GetPosition() const { return position; }
//    Vec3 GetFront() const { return front; }
//private:
//    Vec3 position, front, up, right;
//    Quaternion orientation;
//    void UpdateCameraVectors();
//};


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"


//class Camera {
//public:
//    // Camera properties
//    glm::vec3 position;        // Camera position in world space
//    glm::quat orientation;     // Camera rotation as quaternion
//    float yaw, pitch;          // Camera rotation angles in degrees
//    float speed;               // Camera movement speed
//    float sensitivity;         // Mouse sensitivity for rotation
//
//    // Constructor
//    Camera(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 0.0f), float movementSpeed = 3.0f, float mouseSensitivity = 0.1f);
//
//    // Update the camera's position based on keyboard input (W, A, S, D)
//    void move(const glm::vec3& direction, float deltaTime);
//
//    // Update the camera's orientation based on mouse input
//    void rotate(float deltaX, float deltaY);
//
//    // Get the current view matrix based on the camera's position and orientation
//    glm::mat4 getViewMatrix() const;
//
//    // Get the current projection matrix (can be modified based on FOV or screen aspect ratio)
//    glm::mat4 getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const;
//
//    // Get the camera's position
//    glm::vec3 getPosition() const;
//};





//#pragma once
//#include <glm/glm.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/quaternion.hpp>
//
//
//
//#include <glm/gtc/type_ptr.hpp>     // Convert GLM types to pointers
//
//
//class Camera {
//public:
//    Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity, float dampingFactor);
//
//    void move(const glm::vec3& direction, float deltaTime);
//    void rotate(float deltaYaw, float deltaPitch, float deltaRoll, float deltaTime);
//
//    glm::mat4 getViewMatrix() const;
//    glm::mat4 getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const;
//    glm::vec3 getPosition() const;
//    void rotateAroundPoint(glm::vec3 target, float deltaX, float deltaY, float deltaTime);
//
//
//private:
//    glm::vec3 position;
//    glm::vec3 velocity;
//    glm::vec3 angularVelocity;
//    float speed;
//    float sensitivity;
//    float damping;
//    glm::quat orientation;
//
//    glm::vec3 getForwardVector() const;
//    glm::vec3 getRightVector() const;
//    glm::vec3 getUpVector() const;
//};




#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::quat orientation; // Camera's orientation as a quaternion
    glm::vec3 velocity; // For smoothing camera movement
    glm::vec3 angularVelocity; // For smoothing rotation

    float yaw; // Rotation around the vertical axis (Y-axis)
    float pitch; // Rotation around the horizontal axis (X-axis)
    float roll; // Rotation around the forward axis (Z-axis)

    float speed; // Movement speed
    float sensitivity; // Mouse sensitivity
    float damping; // Damping factor for smoothing
    float distanceFromTarget; // Distance from the target (e.g., pyramid)

    // Constructor
    Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity, float dampingFactor);

    // Methods
    void move(const glm::vec3& direction, float deltaTime);
    void rotate(float deltaX, float deltaY, float deltaRoll, float deltaTime);
    void rotateAroundPoint(glm::vec3 target, float deltaX, float deltaY, float deltaTime);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const;
    glm::vec3 getPosition() const;

    // Helper methods for orientation
    glm::vec3 getForwardVector() const;
    glm::vec3 getRightVector() const;
    glm::vec3 getUpVector() const;
};




