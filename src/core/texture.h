#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <iostream>

#include <glad/glad.h>
#include "std_image.h"

#include "..\common.h"

class Texture {
public:
    Texture(std::string source);

    ~Texture();

    GLuint id();

    void makeData();
    void clearData();

    void make(bool withMipmap);
    void clear();

    void use();

    void setParamInt(int name, int value);

private:
    GLuint texture;

    uint8* data;
    std::string source;

    int width, height, channels;
};

#endif // _TEXTURE_H_