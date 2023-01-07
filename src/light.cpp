#include <string>

#include "common.h"
#include "core/core.h"

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

    GLuint VBO, EBO, VAO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(GL_ZERO);

    Texture diffuseTexture(VSC_BACK"res/img/container2.png");
    diffuseTexture.make(true);
    Texture specularTexture(VSC_BACK"res/img/container2_specular.png");
    specularTexture.make(true);

    ShaderProgram objProgram;
    objProgram.addShader(Shader(VSC_BACK"src/shaders/vertex_shader_light_obj.glsl", GL_VERTEX_SHADER));
    objProgram.addShader(Shader(VSC_BACK"src/shaders/fragment_shader_light_obj.glsl", GL_FRAGMENT_SHADER));
    objProgram.link();

    ShaderProgram lightProgram;
    lightProgram.addShader(Shader(VSC_BACK"src/shaders/vertex_shader_light_light.glsl", GL_VERTEX_SHADER));
    lightProgram.addShader(Shader(VSC_BACK"src/shaders/fragment_shader_light_light.glsl", GL_FRAGMENT_SHADER));
    lightProgram.link();

    objProgram.printErrorIfHas();
    lightProgram.printErrorIfHas();

    glm::vec3 objPosition = glm::vec3(-2.0f, 0.0f, 3.0f);
    glm::vec3 lightPosition = glm::vec3(2.0f, 0.0f, 3.0f);

    objProgram.use();
    objProgram.setVec3("objColor", glm::vec3(1.0f, 1.0f, 1.0f));
    // objProgram.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    // objProgram.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    // objProgram.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    objProgram.setFloat("material.shininess", 35.0f);
    objProgram.setInt("material.lightTex", 0);
    objProgram.setInt("material.specularTex", 1);
    objProgram.setVec3("light.ambient", glm::vec3(0.2f));
    objProgram.setVec3("light.diffuse", glm::vec3(0.5f));
    objProgram.setVec3("light.specular", glm::vec3(1.0f));

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

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            lightPosition = camera.getPosition() - camera.forward() * 3.0f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.processFrame(window, deltaTime);

        glBindVertexArray(VAO);

        glActiveTexture(GL_TEXTURE0);
        diffuseTexture.use();
        glActiveTexture(GL_TEXTURE1);
        specularTexture.use();

        model = glm::mat4(1.0f);
        model = glm::translate(model, objPosition);
        model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));

        objProgram.use();
        objProgram.setMat4("projection", projection);
        objProgram.setMat4("view", camera.getView());
        objProgram.setMat4("model", model);
        objProgram.setVec3("viewPos", camera.getPosition());
        objProgram.setVec3("light.position", lightPosition);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);

        lightProgram.use();
        lightProgram.setMat4("projection", projection);
        lightProgram.setMat4("view", camera.getView());
        lightProgram.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

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
