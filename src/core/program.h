#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    GLuint id() const;

    void use() const;
    void link();

    void addShader(const Shader& shader);

    void setFloat(const char* name, float value);
    void setInt(const char* name, int value);

    void setMat4(const char* name, const glm::mat4& value);

    void clear();

    void printErrorIfHas() const;

private:
    GLuint program;
};

#endif // __PROGRAM_H__