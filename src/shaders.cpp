#include <iostream>
#include <fstream>

#include "common.h"

#define UNUSED(x) (void)(x)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

using namespace std;

const char* vertexShaderSource = 
    "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }";

const char* fragmentShaderSource =
    "#version 400 core\n"
    "out vec4 FragColor;"
    "void main() { FragColor = vec4(0.5, 0.0, 1.0, 1.0); }";

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
    uint32_t fragmentShader = loadShader("src\\shaders\\fragment_shader_purple.glsl", GL_FRAGMENT_SHADER);

    check_shader_errors(vertexShader, "Vertex");
    check_shader_errors(fragmentShader, "Fragment");

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    check_program_errors(shaderProgram, "Shader");

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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    UNUSED(window);
    glViewport(0, 0, width, height);
}