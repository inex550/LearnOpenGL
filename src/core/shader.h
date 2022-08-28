#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
public:
    Shader(const char* source, GLenum type);
    ~Shader();

    uint32_t id() const;
    const char* getSource() const;

    void compile() const;

    void printErrorIfHas() const;

    void clear();

private:
    uint32_t shader;
    const char* source;
};

#endif // __SHADER_H__