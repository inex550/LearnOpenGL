#include <iostream>
#include <fstream>
#include <math.h>

#include "../core/shader.h"
#include "../core/program.h"
#include "../core/std_image.h"

#include "../common.h"

#define UNUSED(x) (void)(x)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#define MAX_FPS 60

using namespace std;

float verices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 2.0f, 2.0f,
};

uint32 indices[] {
    0, 1, 2,
    1, 2, 3,
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

    ShaderProgram program;
    program.addShader(Shader(VSC_BACK"src\\shaders\\vertex_shader_texture.glsl", GL_VERTEX_SHADER));
    program.addShader(Shader(VSC_BACK"src\\shaders\\fragment_shader_texture.glsl", GL_FRAGMENT_SHADER));
    program.link();

    GLuint texture1, texture2;
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);

    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width, height, channels;
    const char* textureSource1 = VSC_BACK"res\\img\\texture.jpg";
    uint8* data = stbi_load(textureSource1, &width, &height, &channels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        cout << "Failed to load texture \"" << textureSource1 << "\"" << endl;
    }

    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(true);

    const char* textureSource2 = VSC_BACK"res\\img\\awesomeface.png";
    data = stbi_load(textureSource2, &width, &height, &channels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "Failed to load texture \"" << textureSource2 << "\"" << endl;
    }

    program.use();
    program.setInt("texture1", 0);
    program.setInt("texture2", 1);

    GLuint VBO, EBO, VAO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verices), verices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);

    glBindVertexArray(GL_ZERO);

    float lastTime = 0;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();

        if (currentTime - lastTime < 1.0 / MAX_FPS)
            continue;

        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        program.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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