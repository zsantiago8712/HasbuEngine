#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "TextureManager.hpp"
#include "stb_image.h"
#include <Glad/glad.h>
#include <fmt/core.h>

namespace hasbu {

Texture::Texture(std::string_view const& filename)
{
    int width;
    int height;
    int nr_chanels;
    unsigned char* texture_data = Texture::load(filename, width, height, nr_chanels);

    glGenTextures(1, &this->texture_id);
    glBindTexture(GL_TEXTURE_2D, this->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, Texture::getTextureType(nr_chanels), GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texture_data);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

unsigned char* Texture::load(std::string_view const& filename, int& width, int& height, int& nr_chanels)
{

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename.data(), &width, &height, &nr_chanels, 0);

    if (data == nullptr) {
        fmt::print(stderr, "Texture {} file not found\n", filename);
        exit(EXIT_FAILURE);
    }

    return data;
}

void Texture::activate(const int numGlTexture) const
{
    glActiveTexture(numGlTexture);
    this->bind();
}

int Texture::getTextureType(const int nr_chanels)
{
    switch (nr_chanels) {
    case 1:
        return GL_RED;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        fmt::print(stderr, "Unknown format!!\n");
        return -1;
    }
}

}