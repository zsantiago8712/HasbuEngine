#pragma once
#include "DynamicAllocator.hpp"
#include <string_view>

namespace Hasbu::ApiContex {
struct TextureData;
}

namespace Hasbu::Render {

enum class TextureType : unsigned int {
    DIFUSE = 1,
    SPECULAR = 2,
};

struct Texture {
    Texture();
    explicit Texture(const std::string_view& file_name);
    ~Texture();

    void create(const std::string_view& file_name);
    void bind(const int& num) const;
    static void unbind();

    Utils::Shared<ApiContex::TextureData> data;
};

}
