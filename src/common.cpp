#include "common.h"

using namespace std;

uint32_t loadShader(const char* shaderFilename, GLenum type) {
    ifstream shaderFile;
    uint32_t shader = 0;

    shaderFile.open(shaderFilename);
    if (!shaderFile.is_open()) {
        basic_stringstream<char> ss;
        ss << "\"" << string(shaderFilename) << "\"" << " not exists" << endl;
        throw runtime_error(ss.str());
    }

    string sourceStr = string(istreambuf_iterator<char>(shaderFile), istreambuf_iterator<char>());
    const char* source = sourceStr.c_str();

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    return shader;
}

void check_shader_errors(uint32_t shader, const char* shaderName) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[512];
        glGetShaderInfoLog(shader, 512, NULL, errLog);
        cerr << shaderName << " Shader compilation ERROR:\n" << errLog << endl;
    }
}

void check_program_errors(uint32_t program, const char* programName) {
    int success;
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errLog[512];
        glGetProgramInfoLog(program, 512, NULL, errLog);
        cerr << programName << " Program compilation ERROR:\n" << errLog << endl;
    }
}

void exit_with_error(const char* error) {
    cout << error << endl;
    glfwTerminate();
    exit(1);
}