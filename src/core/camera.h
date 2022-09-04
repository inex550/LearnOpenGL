#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#define CAMERA_SPEED 10.0f

class Camera {
public:
    Camera(glm::vec3 startPosition, float sensitivity);

    void processFrame(GLFWwindow* const& window, float deltaTime);

    void mouseCallback(float x, float y);

    glm::mat4 getView();

    glm::vec3 forward();
    glm::vec3 right();
    glm::vec3 up();

private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 front;

    float sensitivity;

    float pitch;
    float yaw;
};

#endif // _CAMERA_H_