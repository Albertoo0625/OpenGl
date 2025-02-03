//#include "Camera.h"
//
//Camera::Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity, float dampingFactor)
//    : position(startPos), speed(movementSpeed), sensitivity(mouseSensitivity), damping(dampingFactor),
//    velocity(0.0f), angularVelocity(0.0f),
//    orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}  // Identity quaternion
//
////void Camera::move(const glm::vec3& direction, float deltaTime) {
////    glm::vec3 forward = getForwardVector();
////    glm::vec3 right = getRightVector();
////    glm::vec3 up = getUpVector();
////
////    // Compute desired velocity
////    glm::vec3 desiredVelocity = forward * direction.z + right * direction.x + up * direction.y;
////    desiredVelocity *= speed;
////
////    // Apply smoothing (lerp velocity towards target)
////    velocity = glm::mix(velocity, desiredVelocity, 1.0f - glm::exp(-damping * deltaTime));
////
////    // Update position
////    position += velocity * deltaTime;
////}
//
//
//void Camera::move(const glm::vec3& direction, float deltaTime) {
//    // Get the camera's forward, right, and up vectors based on the current orientation.
//    glm::vec3 forward = getForwardVector();
//    glm::vec3 right = getRightVector();
//    glm::vec3 up = getUpVector();
//
//    // We want movement based on the camera’s local coordinate system, so:
//    //   X: right (+), left (-)
//    //   Y: up (+), down (-)
//    //   Z: forward (-), backward (+)
//    glm::vec3 movementDirection = forward * direction.z + right * direction.x + up * direction.y;
//
//    // Apply the movement speed.
//    movementDirection *= speed;
//
//    // Apply smoothing using damping.
//    velocity = glm::mix(velocity, movementDirection, 1.0f - glm::exp(-damping * deltaTime));
//
//    // Update position with the smoothed velocity.
//    position += velocity * deltaTime;
//}
//
//
//
//void Camera::rotate(float deltaYaw, float deltaPitch, float deltaRoll, float deltaTime) {
//    // Convert input angles to radians
//    float yawRad = glm::radians(deltaYaw * sensitivity);
//    float pitchRad = glm::radians(deltaPitch * sensitivity);
//    float rollRad = glm::radians(deltaRoll * sensitivity);
//
//    // Compute desired angular velocity
//    glm::vec3 desiredAngularVelocity = glm::vec3(pitchRad, yawRad, rollRad);
//
//    // Apply smoothing (lerp angular velocity towards target)
//    angularVelocity = glm::mix(angularVelocity, desiredAngularVelocity, 1.0f - glm::exp(-damping * deltaTime));
//
//    // Get the rotation axis for each component (yaw, pitch, roll)
//    glm::quat yawQuat = glm::angleAxis(angularVelocity.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis (world-space yaw)
//    glm::quat pitchQuat = glm::angleAxis(angularVelocity.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis (world-space pitch)
//    glm::quat rollQuat = glm::angleAxis(angularVelocity.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis (world-space roll)
//
//    // Combine the rotations: yaw ? pitch ? roll
//    // Apply to the existing orientation in the right order: yaw ? pitch ? roll
//    orientation = glm::normalize(yawQuat * pitchQuat * rollQuat * orientation);
//}
//
//
//
//
//
//glm::mat4 Camera::getViewMatrix() const {
//    return glm::lookAt(position, position + getForwardVector(), getUpVector());
//}
//
//glm::mat4 Camera::getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const {
//    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
//}
//
//glm::vec3 Camera::getPosition() const {
//    return position;
//}
//
//// Get camera forward vector
//glm::vec3 Camera::getForwardVector() const {
//    return glm::normalize(orientation * glm::vec3(0.0f, 0.0f, -1.0f));
//}
//
//// Get camera right vector
//glm::vec3 Camera::getRightVector() const {
//    return glm::normalize(orientation * glm::vec3(1.0f, 0.0f, 0.0f));
//}
//
//// Get camera up vector
//glm::vec3 Camera::getUpVector() const {
//    return glm::normalize(orientation * glm::vec3(0.0f, 1.0f, 0.0f));
//}
//



#include "Camera.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

// Constructor for free movement
Camera::Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity, float dampingFactor)
    : position(startPos), speed(movementSpeed), sensitivity(mouseSensitivity), damping(dampingFactor),
    velocity(0.0f),
    orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
    accumulatedYaw(0.0f), accumulatedPitch(0.0f),
    orbitYaw(0.0f), orbitPitch(0.0f), orbitRadius(glm::length(startPos))
{
}

// Free movement: move() remains unchanged.
void Camera::move(const glm::vec3& direction, float deltaTime) {
    glm::vec3 forward = getForwardVector();
    glm::vec3 right = getRightVector();
    glm::vec3 up = getUpVector();

    glm::vec3 desiredVelocity = forward * direction.z + right * direction.x + up * direction.y;
    desiredVelocity *= speed;

    velocity = glm::mix(velocity, desiredVelocity, 1.0f - glm::exp(-damping * deltaTime));
    position += velocity * deltaTime;
}

// Free look rotation (accumulated method).
void Camera::rotate(float deltaYaw, float deltaPitch, float deltaRoll, float deltaTime) {
    accumulatedYaw += deltaYaw * sensitivity;
    accumulatedPitch += deltaPitch * sensitivity;
    accumulatedPitch = glm::clamp(accumulatedPitch, -89.0f, 89.0f);
    orientation = glm::quat(glm::vec3(glm::radians(accumulatedPitch),
        glm::radians(accumulatedYaw),
        0.0f));
}

// New method: Orbit the camera around a fixed target based on key input.
void Camera::orbitAroundTarget(glm::vec3 target, float deltaYaw, float deltaPitch) {
    // Update orbit angles based on key input.
    orbitYaw += deltaYaw * sensitivity;
    orbitPitch += deltaPitch * sensitivity;
    orbitPitch = glm::clamp(orbitPitch, -89.0f, 89.0f);

    // Convert spherical coordinates to Cartesian.
    float radYaw = glm::radians(orbitYaw);
    float radPitch = glm::radians(orbitPitch);
    glm::vec3 offset;
    offset.x = orbitRadius * cos(radPitch) * sin(radYaw);
    offset.y = orbitRadius * sin(radPitch);
    offset.z = orbitRadius * cos(radPitch) * cos(radYaw);

    // Update the camera position relative to the target.
    position = target + offset;

    // Compute the forward vector from the camera to the target.
    glm::vec3 forward = glm::normalize(target - position);
    // We'll assume the world up vector is (0, 1, 0).
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    // Update the orientation so that the camera always looks at the target.
    orientation = glm::quatLookAt(forward, up);
}

// The view matrix uses glm::lookAt based on the camera's position and forward vector.
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + getForwardVector(), getUpVector());
}

// Perspective projection.
glm::mat4 Camera::getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

glm::vec3 Camera::getPosition() const {
    return position;
}

glm::vec3 Camera::getForwardVector() const {
    return glm::normalize(orientation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Camera::getRightVector() const {
    return glm::normalize(orientation * glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Camera::getUpVector() const {
    return glm::normalize(orientation * glm::vec3(0.0f, 1.0f, 0.0f));
}
