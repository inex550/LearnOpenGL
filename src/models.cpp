#include <string>

#include "common.h"
#include "core/core.h"

#include "core/model.h"

void frameBufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);
void cursorPositionCallback(GLFWwindow* window, double x, double y);
void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);

void setupProjection();

Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 0.1f);

glm::mat4 model;
glm::mat4 projection;

int width = 800;
int height = 600;

#define MAX_FPS 60

#define UNUSED(a) (void)(a)

float cubeVertices[] = {
    // Forward square
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    // Backward square
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    // Top square
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    // Bottom square
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    // Left square
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    // Right square
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};

uint32 indices[] = {
    // Forward square
    0, 1, 2,
    0, 2, 3,
    // Backward square
    4, 5, 6,
    4, 6, 7,
    // Top square
    8, 9, 10,
    8, 10, 11,
    // Bottom square
    12, 13, 14,
    12, 14, 15,
    // Left square
    16, 17, 18,
    16, 18, 19,
    // Right square
    20, 21, 22,
    20, 22, 23,
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL - Light", nullptr, nullptr);
    if (window == nullptr) {
        exit_with_error("glfwCreateWindow error");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        exit_with_error("gladLoadGLLoader error");
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)frameBufferSizeCallback);
    glfwSetCursorPosCallback(window, (GLFWcursorposfun)cursorPositionCallback);
    glfwSetScrollCallback(window, (GLFWscrollfun)scrollCallback);

    frameBufferSizeCallback(window, width, height);

    ShaderProgram program;
    program.addShader(Shader(VSC_BACK"src/shaders/vertex_shader_model.glsl", GL_VERTEX_SHADER));
    program.addShader(Shader(VSC_BACK"src/shaders/fragment_shader_model.glsl", GL_FRAGMENT_SHADER));
    program.link();

    program.printErrorIfHas();

    program.use();
    program.setVec3("light.direction", glm::vec3(1.0f, -1.0f, 1.0f));
    program.setVec3("light.color", glm::vec3(1.0f, 1.0f, 1.0f));
    program.setInt("material.texture_diffuse0", 0);

    stbi_set_flip_vertically_on_load(true);

    Texture texture(VSC_BACK"res/models/backpack/diffuse.jpg");
    texture.make(true);

    Model carModel(VSC_BACK"res/models/backpack/backpack.obj");

    float currentTime = 0.0f;
    float lastTime = 0.0f;
    float deltaTime = 0.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastTime;

        if (deltaTime < 1.0f / MAX_FPS)
            continue;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        texture.use();

        camera.processFrame(window, deltaTime);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));

        program.use();
        program.setMat4("model", model);
        program.setMat4("view", camera.getView());
        program.setMat4("projection", projection);

        carModel.draw(program);

        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = currentTime;
    }
}

void frameBufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight) {
    UNUSED(window);
    width = newWidth;
    height = newHeight;
    glViewport(0, 0, width, height);
    setupProjection();
}

void cursorPositionCallback(GLFWwindow* window, double x, double y) {
    UNUSED(window);
    camera.mouseCallback(x, y);
}

void scrollCallback(GLFWwindow* window, double offsetX, double offsetY) {
    UNUSED(window);
    UNUSED(offsetX);
    camera.scrollCallback(offsetY);
    setupProjection();
}

void setupProjection() {
    projection = glm::perspective(glm::radians(camera.getZoom()), (float)width / (float)height, 0.1f, 100.0f);
}
