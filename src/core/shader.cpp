#include "shader.h"

Shader::Shader(const char* source, GLenum type) {
    this->source = source;
    this->shader = glCreateShader(type);
}

Shader::~Shader() {
    clear();
}

void Shader::compile() const {
    std::ifstream shaderFile;
    std::stringstream ss;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    shaderFile.open(source);
    ss << shaderFile.rdbuf();
    shaderFile.close();

    std::string strShaderCode = ss.str();
    const char* shaderCode = strShaderCode.c_str();

    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    printErrorIfHas();
}

void Shader::clear() {
    glDeleteShader(shader);
}

void Shader::printErrorIfHas() const {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[BUFSIZ];
        glGetShaderInfoLog(shader, BUFSIZ, NULL, errLog);
        std::cout << "Shader \"" << source << "\"" << " failed:\n" << errLog << std::endl; 
    }
}

uint32_t Shader::id() const {
    return shader;
}

const char* Shader::getSource() const {
    return source;
}