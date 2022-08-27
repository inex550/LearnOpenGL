#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef unsigned int ui32;

uint32_t loadShader(const char* shaderFilename, GLenum type);

void check_shader_errors(uint32_t shader, const char* shaderName);

void check_program_errors(uint32_t program, const char* programName);

void exit_with_error(const char* error);