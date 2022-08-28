#include "program.h"

ShaderProgram::ShaderProgram() {
    program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    clear();
}

void ShaderProgram::use() const {
    glUseProgram(program);
}

void ShaderProgram::link() {
    glLinkProgram(program);
}

GLuint ShaderProgram::id() const {
    return program;
}

void ShaderProgram::addShader(const Shader& shader) {
    shader.compile();
    glAttachShader(program, shader.id());
}

void ShaderProgram::setFloat(const char* name, float value) {
    glUniform1f(glGetUniformLocation(program, name), value);
}

void ShaderProgram::setInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(program, name), value);
}

void ShaderProgram::clear() {
    glDeleteProgram(program);
}

void ShaderProgram::printErrorIfHas() const {
    GLint success;
    glGetProgramiv(program, GL_COMPILE, &success);
    if (!success) {
        char errLog[BUFSIZ];
        glGetProgramInfoLog(program, BUFSIZ, NULL, errLog);
        std::cout << "Program linking failed:\n" << errLog << std::endl;
    }
}