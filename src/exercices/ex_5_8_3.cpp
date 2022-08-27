// Create two shader programs where the second program uses a different fragment shader
// that outputs the color yellow; draw both triangles again where one outputs the color yellow


#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define UNUSED(x) (void)(x)

void exit_with_error();

void check_shader_errors(uint32_t shader, const char* shaderName);

void check_program_errors(uint32_t program, const char* programName);

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

const char* fragmentShaderYellowSource =
    "#version 400 core\n"
    "out vec4 fg_color;\n"
    "void main() { fg_color = vec4(1.0, 1.0, 0.0, 1.0); }";

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

    uint32_t fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader1);

    uint32_t fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderYellowSource, NULL);
    glCompileShader(fragmentShader2);

    check_shader_errors(vertexShader, "Vertex");
    check_shader_errors(fragmentShader1, "Fragment1");
    check_shader_errors(fragmentShader2, "Fragment2");

    uint32_t shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    uint32_t shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    int success;
    glGetProgramiv(shaderProgram1, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[BUFSIZ];
        glGetProgramInfoLog(shaderProgram1, BUFSIZ, NULL, errLog);
        cout << "shaderProgram ERROR:\n" << errLog << endl;
    }

    uint32_t VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);

    glBindVertexArray(GL_ZERO);

    while (!glfwWindowShouldClose(window)) {
        glBindVertexArray(VAO);

        glUseProgram(shaderProgram1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glDrawArrays(GL_TRIANGLES, 3, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void check_shader_errors(uint32_t shader, const char* shaderName) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[BUFSIZ];
        glGetShaderInfoLog(shader, BUFSIZ, NULL, errLog);
        cout << shaderName << " Shader ERROR:\n" << errLog << endl;
    }
}

void check_program_errors(uint32_t program, const char* programName) {
    int success;
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[BUFSIZ];
        glGetProgramInfoLog(program, BUFSIZ, NULL, errLog);
        cout << programName << " Program ERROR:\n" << errLog << endl;
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