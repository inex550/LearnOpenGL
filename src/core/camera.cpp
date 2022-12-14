#include "camera.h"

glm::vec3 upBasic = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 rightBasic = glm::vec3(1.0f, 0.0f, 0.0f);

Camera::Camera(glm::vec3 startPosition, float sensitivity) {
    position = -startPosition;
    pitch = 0.0f;
    yaw =-90.0f;
    lastX = lastY = -1;
    zoom = 45.0f;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->sensitivity = sensitivity;
}

glm::vec3 Camera::getPosition() {
    return position;
}

glm::vec3 Camera::forward() {
    return front;
}

glm::vec3 Camera::right() {
    glm::vec3 right = glm::normalize(glm::cross(front, upBasic));
    if (right.x == 0 && right.y == 0 && right.z == 0)
        right.x = rightBasic.x;
    return right;
}

glm::vec3 Camera::up() {
    glm::vec3 up = glm::normalize(glm::cross(front, rightBasic));
    if (up.x == 0 && up.y == 0 && up.z == 0)
        up.y = upBasic.y;
    return up;
}

void Camera::processFrame(GLFWwindow* const& window, float deltaTime) {
    float shift;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        shift = 2.0f;
    else
        shift = 1.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += forward() * deltaTime * CAMERA_SPEED * shift;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= forward() * deltaTime * CAMERA_SPEED * shift;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right() * deltaTime * CAMERA_SPEED * shift;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right() * deltaTime * CAMERA_SPEED * shift;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position.y += deltaTime * CAMERA_SPEED * shift;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position.y -= deltaTime * CAMERA_SPEED * shift;
}

void Camera::mouseCallback(float x, float y) {
    if (lastX < 0 && lastY < 0) {
        lastX = x;
        lastY = y;
    }

    pitch -= (y - lastY) * sensitivity;
    yaw += (x - lastX) * sensitivity;

    lastX = x;
    lastY = y;

    if (pitch > 85.0f)
        pitch = 85.0f;
    if (pitch < -85.0f)
        pitch = -85.0f;

    direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(direction);
}

void Camera::scrollCallback(float yoffset) {
    zoom -= yoffset * ZOOM_SPEED;
}

float Camera::getZoom() {
    return zoom;
}

glm::mat4 Camera::getView() {
    return glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}