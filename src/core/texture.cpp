#include "texture.h"

Texture::Texture(std::string source) {
    this->source = source;
    data = nullptr;
    width = height = channels = 0;
    
    glGenTextures(1, &texture);
    this->use();
}

Texture::~Texture() {
    clear();
}

void Texture::makeData() {
    clearData();
    data = stbi_load(source.c_str(), &width, &height, &channels, 0);
}

void Texture::clearData() {
    if (data == nullptr) {
        stbi_image_free(data);
    }
}

void Texture::make(bool withMipmap) {
    if (data == nullptr)
        makeData();

    if (data == nullptr) {
        std::cout << "Failed to load texture \"" << source << '"' << std::endl;
        return;
    }

    GLenum format;
    if (channels == 4)
        format = GL_RGBA;
    else
        format = GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    if (withMipmap)
        glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::clear() {
    clearData();
    glDeleteTextures(1, &texture);
}

void Texture::use() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::setParamInt(int name, int value) {
    glTexParameteri(GL_TEXTURE_2D, name, value);
}