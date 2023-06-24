#pragma once

#include <string_view>

namespace HasbuUtils {

unsigned char* loadTexture(const std::string_view& file_name, int& image_width, int& image_height, int& image_nr_chanels);

void freeTexture(unsigned char* texture_data);

int getTextureType(const int& image_nr_chanels);

std::string loadShader(const std::string_view& file_name);
}
