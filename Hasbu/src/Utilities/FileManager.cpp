#include "Utilities/FileManager.hpp"
#include "Utilities/Logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>

namespace HasbuUtils {

unsigned char* loadTexture(const std::string_view& file_name, int& image_width, int& image_height, int& image_nr_chanels)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image_data = stbi_load(file_name.data(), &image_width, &image_height, &image_nr_chanels, 0);

    if (image_data == nullptr) {
        const char* error = stbi_failure_reason();
        HASBU_FATAL("Texture {} file not found {}\n", file_name, error);
    }
    return image_data;
}

void freeTexture(unsigned char* texture_data)
{
    stbi_image_free(texture_data);
}

int getTextureType(const int& image_nr_chanels)
{
    switch (image_nr_chanels) {
    case 1:
        return GL_RED;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        HASBU_FATAL("INvalid NR channels {} \n", image_nr_chanels);
        return -1;
    }
}

std::string loadShader(const std::string_view& file_name)
{
    std::ifstream shader_file(file_name.data());
    if (!shader_file.good()) {
        HASBU_FATAL("Shader File {} not found!!\n", file_name);
        return nullptr;
    }

    std::stringstream buffer;
    buffer << shader_file.rdbuf();
    shader_file.close();

    return buffer.str();
}

}
