#include <iostream>
#include <fstream>
#include <math.h>

#include "core/shader.h"
#include "core/program.h"

#include "common.h"

#define UNUSED(x) (void)(x)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#define MAX_FPS 60

using namespace std;

float verices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "LearnOpenGL - Shaders", NULL, NULL);
    if (window == NULL)
        exit_with_error("GLFW Window creation failed");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        exit_with_error("Glad load failed");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    Shader vertexShader = Shader("src\\shaders\\vertex_shader_colored_with_offset.glsl", GL_VERTEX_SHADER);
    Shader fragmentShader = Shader("src\\shaders\\fragment_shader_color_in.glsl", GL_FRAGMENT_SHADER);

    ShaderProgram program;
    program.addShader(vertexShader);
    program.addShader(fragmentShader);
    program.link();

    uint32_t VBO, EBO, VAO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verices), verices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);

    glBindVertexArray(GL_ZERO);

    float lastTime = 0;
    float currentTime = 0;

    float offset = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();

        if (currentTime - lastTime < 1.0 / MAX_FPS)
            continue;

        glClear(GL_COLOR_BUFFER_BIT);

        offset = sin(currentTime) / 2;

        program.use();
        program.setFloat("offset", offset);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = currentTime;
    }
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    UNUSED(window);
    glViewport(0, 0, width, height);
}