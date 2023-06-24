#pragma once
#include "DynamicAllocator.hpp"
#include "defines.hpp"
#include <string_view>

namespace HasbuAPIContext {
struct TextureData;
}

namespace HasbuRender {

enum class TextureType : unsigned int {
    DIFUSE = 1,
    SPECULAR = 2,
};

struct Texture {
    Texture();
    Texture(const std::string_view& file_name);
    ~Texture();

    void create(const std::string_view& file_name);
    void bind(const int& num) const;
    static void unbind();

    HasbuUtils::Shared<HasbuAPIContext::TextureData> data;
};

}
