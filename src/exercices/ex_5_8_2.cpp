// Now create the same 2 triangles using two different VAOs and VBOs for their data

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define UNUSED(x) (void)(x)

void exit_with_error();

void check_shader_errors(uint32_t shader);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

using namespace std;

const float triangle_data[] = {
    // first triangle
    -0.55f, 0.45f, 0.0f,
    0.45f, -0.55f, 0.0f,
    -0.55f, -0.55f, 0.0f,
    //second triangle
    -0.45f, 0.55f, 0.0f,
    0.55f, -0.45f, 0.0f,
    0.55f, 0.55f, 0.0f,
};

const char* vertexShaderSource = 
    "#version 400 core\n"
    "layout (location = 0) in vec3 vPos;\n"
    "void main() { gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0); }";

const char* fragmentShaderSource =
    "#version 400 core\n"
    "out vec4 fg_color;\n"
    "void main() { fg_color = vec4(0.5, 0.0, 1.0, 1.0); }";

int main () {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "Exercise 5.8 - 1", NULL, NULL);
    if (window == NULL)
        exit_with_error();
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        exit_with_error();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    check_shader_errors(vertexShader);
    check_shader_errors(fragmentShader);

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[BUFSIZ];
        glGetProgramInfoLog(shaderProgram, BUFSIZ, NULL, errLog);
        cout << "shaderProgram ERROR:\n" << errLog << endl;
    }

    uint32_t VBO1, VAO1;
    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, triangle_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);

    glBindVertexArray(GL_ZERO);

    uint32_t VBO2, VAO2;
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, triangle_data + 3 * 3, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);

    glBindVertexArray(GL_ZERO);

    while (!glfwWindowShouldClose(window)) {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void check_shader_errors(uint32_t shader) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[BUFSIZ];
        glGetShaderInfoLog(shader, BUFSIZ, NULL, errLog);
        cout << "Shader ERROR:\n" << errLog << endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    UNUSED(window);
    glViewport(0, 0, width, height);
}

void exit_with_error() {
    glfwTerminate();
    exit(1);
}