#pragma once
#include <string_view>

namespace hasbu {

class Texture {

public:
    explicit Texture(std::string_view const& filename);
    void bind() const;
    void activate(int numGlTexture) const;

private:
    unsigned int texture_id;
    static unsigned char* load(std::string_view const& filename, int& width, int& height, int& nr_chanels);
    static int getTextureType(int nr_chanels);
};

}