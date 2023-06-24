#include "Renderer/Texture.hpp"
#include "Utilities/FileManager.hpp"
#include <GL/glew.h>

namespace HasbuAPIContext {

struct TextureData {
    unsigned int id;
    HasbuRender::TextureType type;
};

}

namespace HasbuRender {

Texture::Texture()
    : data(HasbuUtils::createShared<HasbuAPIContext::TextureData>()) {};

Texture::Texture(const std::string_view& file_name)
    : data(HasbuUtils::createShared<HasbuAPIContext::TextureData>())
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
    unsigned char* texture_data = HasbuUtils::loadTexture(file_name.data(), width, height, nr_channels);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, HasbuUtils::getTextureType(nr_channels), GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    HasbuUtils::freeTexture(texture_data);
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
