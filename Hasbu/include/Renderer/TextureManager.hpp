#pragma once
#include "Utilities/DynamicAllocator.hpp"

namespace Hasbu::ApiContext {

struct TextureData;

};

namespace Hasbu::Render {

enum class TextureType : unsigned int {

    DIFFUSE = 0,
    SPECULAR = 1,
    NORMAL = 2,
    HEIGHT = 3,
};

struct TextureManager {

    static unsigned int createTexture(const std::string_view& fileTexture, TextureType type);
    static void activate(const unsigned int id, const unsigned int textureUnite);
    static void deactivate();
    static void destroy(unsigned int& id);

    static TextureType getType(const unsigned int id);
    static unsigned int isLoaded(const std::string_view& textureFile);


private:
    static TextureManager& getInstance();

    TextureManager();
    Utils::Unique<ApiContext::TextureData> data;
};

}
