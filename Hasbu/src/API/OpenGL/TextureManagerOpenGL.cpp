#include "Renderer/TextureManager.hpp"
#include "Utilities/FileManager.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

static int getTextureType(const int nrChanels);

namespace Hasbu::ApiContext {

struct TextureData {
    Utils::Vector<unsigned int> ids;
};

}

namespace Hasbu::Render {

TextureManager::TextureManager()
    : data(Utils::createUnique<ApiContext::TextureData>()) {};

TextureManager& TextureManager::getInstance()
{
    static TextureManager manager;
    return manager;
}

unsigned int TextureManager::createTexture(const std::string_view& fileTexture)
{
    unsigned int newID;
    glGenTextures(1, &newID);
    glBindTexture(GL_TEXTURE_2D, newID);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* textureData = Utils::loadTexture(fileTexture.data(), width, height, nrChannels);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, getTextureType(nrChannels), GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    Utils::freeTexture(textureData);

    TextureManager& manager = TextureManager::getInstance();
    manager.data->ids.push_back(newID);

    return static_cast<unsigned int>(manager.data->ids.size());
}

void TextureManager::activate(const unsigned int id, const unsigned int textureUnite)
{
    auto& manager = TextureManager::getInstance();

    glActiveTexture(GL_TEXTURE0 + (textureUnite - 1));
    glBindTexture(GL_TEXTURE_2D, manager.data->ids[id - 1]);
}

void TextureManager::deactivate()
{
    glActiveTexture(GL_TEXTURE0);
}

void TextureManager::destroy(unsigned int& id)
{
    auto& manager = TextureManager::getInstance();

    glDeleteTextures(1, &manager.data->ids[id - 1]);
    manager.data->ids.erase(manager.data->ids.begin() + (id - 1));
    id = 0;
}

}

static int getTextureType(const int nrChanels)
{
    switch (nrChanels) {
    case 1:
        return GL_RED;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        HASBU_FATAL("INvalid NR channels {} \n", nrChanels);
        return -1;
    }
}
