#include "Renderer/Texture.hpp"
#include "Utilities/FileManager.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

static int getTextureType(const int image_nr_chanels);

namespace Hasbu::ApiContex {

struct TextureData {
    unsigned int id;
    Render::TextureType type;
};

}

namespace Hasbu::Render {

Texture::Texture()
    : data(Utils::createShared<ApiContex::TextureData>()) {};

Texture::Texture(const std::string_view& file_name)
    : data(Utils::createShared<ApiContex::TextureData>())
{
    this->create(file_name);
}

Texture::~Texture()
{
    this->data.reset();
}

void Texture::create(const std::string_view& file_name)
{
    glGenTextures(1, &this->data->id);
    glBindTexture(GL_TEXTURE_2D, this->data->id);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nr_channels;
    unsigned char* texture_data = Utils::loadTexture(file_name.data(), width, height, nr_channels);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, getTextureType(nr_channels), GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    Utils::freeTexture(texture_data);
}

void Texture::bind(const int& num) const
{
    glActiveTexture(GL_TEXTURE0 + (num - 1));
    glBindTexture(GL_TEXTURE_2D, this->data->id);
}

void Texture::unbind()
{
    glActiveTexture(GL_TEXTURE0);
}

}

// TODO: change this functions to TextureOpenGL.cpp
static int getTextureType(const int image_nr_chanels)
{
    switch (image_nr_chanels) {
    case 1:
        return GL_RED;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        HASBU_FATAL("INvalid NR channels {} \n", image_nr_chanels);
        return -1;
    }
}
