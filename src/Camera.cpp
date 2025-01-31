//// Camera.cpp
//#include "Camera.h"
//
//Vec3 Vec3::operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
//Vec3 Vec3::operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }
//Vec3 Vec3::operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
//Vec3 Vec3::normalize() const {
//    float length = std::sqrt(x * x + y * y + z * z);
//    return { x / length, y / length, z / length };
//}
//
//Quaternion Quaternion::normalize() const {
//    float length = std::sqrt(w * w + x * x + y * y + z * z);
//    return { w / length, x / length, y / length, z / length };
//}
//
//Quaternion Quaternion::operator*(const Quaternion& other) const {
//    return {
//        w * other.w - x * other.x - y * other.y - z * other.z,
//        w * other.x + x * other.w + y * other.z - z * other.y,
//        w * other.y - x * other.z + y * other.w + z * other.x,
//        w * other.z + x * other.y - y * other.x + z * other.w
//    };
//}
//
//Vec3 Quaternion::rotate(const Vec3& v) const {
//    Quaternion vecQuat = { 0, v.x, v.y, v.z };
//    Quaternion resQuat = (*this) * vecQuat * Quaternion{ w, -x, -y, -z };
//    return { resQuat.x, resQuat.y, resQuat.z };
//}
//
//Camera::Camera(Vec3 position, Vec3 up) : position(position), up(up), orientation({ 1, 0, 0, 0 }) {
//    front = { 0.0f, 0.0f, -1.0f };
//    right = { 1.0f, 0.0f, 0.0f };
//    UpdateCameraVectors();
//}
//
//std::array<std::array<float, 4>, 4> Camera::GetViewMatrix() const {
//    Vec3 center = position + front;
//    return { {{1, 0, 0, -position.x}, {0, 1, 0, -position.y}, {0, 0, 1, -position.z}, {0, 0, 0, 1}} };
//}
//
//void Camera::ProcessRotation(float angle, Vec3 axis) {
//    float halfAngle = angle * 0.5f;
//    float sinHalf = std::sin(halfAngle);
//    Quaternion deltaQuat = { std::cos(halfAngle), axis.x * sinHalf, axis.y * sinHalf, axis.z * sinHalf };
//    orientation = (deltaQuat * orientation).normalize();
//    UpdateCameraVectors();
//}
//
//void Camera::ProcessMovement(Vec3 direction, float deltaTime) {
//    float velocity = 5.0f * deltaTime;
//    position = position + (direction * velocity);
//}
//
//void Camera::UpdateCameraVectors() {
//    front = orientation.rotate({ 0.0f, 0.0f, -1.0f });
//    right = orientation.rotate({ 1.0f, 0.0f, 0.0f });
//    up = orientation.rotate({ 0.0f, 1.0f, 0.0f });
//}


//#include "Camera.h"
//
//// Constructor to initialize camera position, speed, and sensitivity
//Camera::Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity)
//    : position(startPos), yaw(0.0f), pitch(0.0f), speed(movementSpeed), sensitivity(mouseSensitivity) {
//    orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));  // No initial rotation
//}
//
//// Update the camera's position based on keyboard input (W, A, S, D)
//void Camera::move(const glm::vec3& direction, float deltaTime) {
//    position += direction * speed * deltaTime;
//}
//
//// Update the camera's orientation based on mouse input
//void Camera::rotate(float deltaX, float deltaY) {
//    yaw += deltaX * sensitivity;
//    pitch -= deltaY * sensitivity;
//
//    // Limit the pitch to prevent gimbal lock
//    if (pitch > 89.0f) pitch = 89.0f;
//    if (pitch < -89.0f) pitch = -89.0f;
//
//    // Create quaternion rotations for yaw and pitch
//    glm::quat yawQuat = glm::angleAxis(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
//    glm::quat pitchQuat = glm::angleAxis(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
//
//    // Combine rotations: yaw -> pitch
//    orientation = yawQuat * pitchQuat;
//}
//
//
//// Get the current view matrix based on the camera's position and orientation
//glm::mat4 Camera::getViewMatrix() const {
//    glm::mat4 rotationMatrix = glm::mat4_cast(orientation);  // Convert quaternion to rotation matrix
//    glm::vec3 forward = glm::normalize(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
//    glm::vec3 up = glm::normalize(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
//
//    // Use glm::lookAt to generate the view matrix
//    return glm::lookAt(position, position + forward, up);
//}
//
//// Get the current projection matrix (perspective projection)
//glm::mat4 Camera::getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const {
//    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
//}
//
//// Get the camera's position
//glm::vec3 Camera::getPosition() const {
//    return position;
//}




#include "Camera.h"

Camera::Camera(glm::vec3 startPos, float movementSpeed, float mouseSensitivity, float dampingFactor)
    : position(startPos), speed(movementSpeed), sensitivity(mouseSensitivity), damping(dampingFactor),
    velocity(0.0f), angularVelocity(0.0f),
    orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}  // Identity quaternion

void Camera::move(const glm::vec3& direction, float deltaTime) {
    glm::vec3 forward = getForwardVector();
    glm::vec3 right = getRightVector();
    glm::vec3 up = getUpVector();

    // Compute desired velocity
    glm::vec3 desiredVelocity = forward * direction.z + right * direction.x + up * direction.y;
    desiredVelocity *= speed;

    // Apply smoothing (lerp velocity towards target)
    velocity = glm::mix(velocity, desiredVelocity, 1.0f - glm::exp(-damping * deltaTime));

    // Update position
    position += velocity * deltaTime;
}

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
//    // Create quaternion rotations
//    glm::quat yawQuat = glm::angleAxis(angularVelocity.y, getUpVector());
//    glm::quat pitchQuat = glm::angleAxis(angularVelocity.x, getRightVector());
//    glm::quat rollQuat = glm::angleAxis(angularVelocity.z, getForwardVector());
//
//    // Apply rotations: yaw ? pitch ? roll
//    orientation = glm::normalize(yawQuat * pitchQuat * rollQuat * orientation);
//}

void Camera::rotate(float deltaYaw, float deltaPitch, float deltaRoll, float deltaTime) {
    // Convert input angles to radians
    float yawRad = glm::radians(deltaYaw * sensitivity);
    float pitchRad = glm::radians(deltaPitch * sensitivity);
    float rollRad = glm::radians(deltaRoll * sensitivity);

    // Compute desired angular velocity
    glm::vec3 desiredAngularVelocity = glm::vec3(pitchRad, yawRad, rollRad);

    // Apply smoothing (lerp angular velocity towards target)
    angularVelocity = glm::mix(angularVelocity, desiredAngularVelocity, 1.0f - glm::exp(-damping * deltaTime));

    // Get the rotation axis for each component (yaw, pitch, roll)
    glm::quat yawQuat = glm::angleAxis(angularVelocity.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis (world-space yaw)
    glm::quat pitchQuat = glm::angleAxis(angularVelocity.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis (world-space pitch)
    glm::quat rollQuat = glm::angleAxis(angularVelocity.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis (world-space roll)

    // Combine the rotations: yaw ? pitch ? roll
    // Apply to the existing orientation in the right order: yaw ? pitch ? roll
    orientation = glm::normalize(yawQuat * pitchQuat * rollQuat * orientation);
}


void Camera::rotateAroundPoint(glm::vec3 target, float deltaX, float deltaY, float deltaTime) {
    // Convert mouse movement to rotation angles
    float yawRad = glm::radians(deltaX * sensitivity);
    float pitchRad = glm::radians(deltaY * sensitivity);

    // Adjust yaw and pitch based on mouse movement
    yaw += yawRad;
    pitch -= pitchRad;

    // Clamp pitch to avoid gimbal lock
    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    // Calculate the new camera position based on yaw and pitch
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    // Update camera position relative to the target (pyramid)
    position = target + direction * distanceFromTarget;

    // Update the orientation (rotation) of the camera
    orientation = glm::quat(glm::vec3(pitch, yaw, roll));  // Only yaw and pitch are used for rotation
}





glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + getForwardVector(), getUpVector());
}

glm::mat4 Camera::getProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip) const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

glm::vec3 Camera::getPosition() const {
    return position;
}

// Get camera forward vector
glm::vec3 Camera::getForwardVector() const {
    return glm::normalize(orientation * glm::vec3(0.0f, 0.0f, -1.0f));
}

// Get camera right vector
glm::vec3 Camera::getRightVector() const {
    return glm::normalize(orientation * glm::vec3(1.0f, 0.0f, 0.0f));
}

// Get camera up vector
glm::vec3 Camera::getUpVector() const {
    return glm::normalize(orientation * glm::vec3(0.0f, 1.0f, 0.0f));
}






