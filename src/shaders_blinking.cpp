#include <iostream>
#include <fstream>
#include <math.h>

#include "common.h"

#define UNUSED(x) (void)(x)

#define MAX_FPS 60

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

using namespace std;

float verices[] = {
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

uint32_t indices[] = {
    0, 1, 2,
    0, 2, 3,
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
    
    uint32_t vertexShader = loadShader("src\\shaders\\vertex_shader_common.glsl", GL_VERTEX_SHADER);
    uint32_t fragmentShader = loadShader("src\\shaders\\fragment_shader_uniform_purple.glsl", GL_FRAGMENT_SHADER);

    check_shader_errors(vertexShader, "VertexShader");
    check_shader_errors(fragmentShader, "FragmentShader");

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    check_program_errors(shaderProgram, "ShaderProgram");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    uint32_t VBO, EBO, VAO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verices), verices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);

    glBindVertexArray(GL_ZERO);

    float lastTime = 0;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();

        if (currentTime - lastTime < 1.0 / MAX_FPS) {
            glfwPollEvents();
            continue;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();
        float purpleValue = (sin(time) / 2.0f) + 0.5f;
        int uniformColorLocation = glGetUniformLocation(shaderProgram, "color");
        glUseProgram(shaderProgram);
        glUniform4f(uniformColorLocation, purpleValue / 2.0f, 0.0f, purpleValue, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

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