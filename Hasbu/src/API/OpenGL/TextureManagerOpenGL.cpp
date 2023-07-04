#include "Renderer/TextureManager.hpp"
#include "Utilities/FileManager.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

static int getTextureType(const int nrChanels);

namespace Hasbu::ApiContext {

struct TextureData {
    Utils::Vector<unsigned int> m_ids;
    Utils::Vector<std::string> m_textureFiles;
    Utils::Vector<Render::TextureType> m_types;
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

unsigned int TextureManager::createTexture(const std::string_view& fileTexture, TextureType type)
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
    HASBU_DEBUG("TEXTURE {} is loading", fileTexture);
    unsigned char* textureData = Utils::loadTexture(fileTexture.data(), width, height, nrChannels);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, getTextureType(nrChannels), GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    TextureManager& manager = TextureManager::getInstance();
    manager.data->m_ids.push_back(newID);
    manager.data->m_textureFiles.push_back(fileTexture.data());
    manager.data->m_types.push_back(type);

    return static_cast<unsigned int>(manager.data->m_ids.size());
}

void TextureManager::activate(const unsigned int id, const unsigned int textureUnite)
{
    auto& manager = TextureManager::getInstance();

    glActiveTexture(GL_TEXTURE0 + textureUnite);
    glBindTexture(GL_TEXTURE_2D, manager.data->m_ids[id - 1]);
}

void TextureManager::deactivate()
{
    glActiveTexture(GL_TEXTURE0);
}

void TextureManager::destroy(unsigned int& id)
{
    auto& manager = TextureManager::getInstance();

    glDeleteTextures(1, &manager.data->m_ids[id - 1]);
    manager.data->m_ids.erase(manager.data->m_ids.begin() + (id - 1));
    id = 0;
}

TextureType TextureManager::getType(const unsigned int id)
{
    const auto& manager = TextureManager::getInstance();
    return manager.data->m_types[id - 1];
}

unsigned int TextureManager::isLoaded(const std::string_view& textureFile)
{
    const auto& manager = TextureManager::getInstance();
    unsigned int index = 0;

    for (const auto& fileTexture : manager.data->m_textureFiles) {
        if (textureFile == fileTexture) {
            return index + 1;
        }

        index++;
    }

    return 0;
}
}
static int getTextureType(const int nrChanels)
{
    switch (nrChanels) {
    case 1:
        return GL_RED;
    case 3:
        return GL_BGR;
    case 4:
        return GL_BGRA;
    default:
        HASBU_FATAL("INvalid NR channels {} \n", nrChanels);
        return -1;
    }
}
