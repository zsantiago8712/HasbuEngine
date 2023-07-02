#pragma once
#include "Utilities/DynamicAllocator.hpp"

namespace Hasbu::ApiContext {

struct TextureData;

};

namespace Hasbu::Render {

struct TextureManager {


    static unsigned int createTexture(const std::string_view& fileTexture);
    static void activate(const unsigned int id, const unsigned int textureUnite);
    static void deactivate();
    static void destroy(unsigned int& id);


private:
    static TextureManager& getInstance();

    TextureManager();
    Utils::Unique<ApiContext::TextureData> data;
};

}
