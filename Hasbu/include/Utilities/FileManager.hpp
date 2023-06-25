#pragma once
#include <string_view>

namespace Hasbu::Utils {

unsigned char* loadTexture(const std::string_view& file_name, int& image_width, int& image_height, int& image_nr_chanels);

void freeTexture(unsigned char* texture_data);

std::string loadShader(const std::string_view& file_name);
}
