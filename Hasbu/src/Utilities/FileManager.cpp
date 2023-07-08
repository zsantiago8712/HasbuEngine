#include "Utilities/FileManager.hpp"
#include "DynamicAllocator.hpp"
#include "Utilities/Logger.hpp"

#include <FreeImage.h>

#include <fstream>
#include <sstream>

namespace Hasbu::Utils {

unsigned char* loadTexture(const std::string_view& file_name, int& image_width, int& image_height, int& image_nr_chanels)
{

    FREE_IMAGE_FORMAT fileFormate = FreeImage_GetFIFFromFilename(file_name.data());
    HASBU_ASSERT(fileFormate == FIF_UNKNOWN, "UNKNOW FILE FORMAT")

    FIBITMAP* bitmap = FreeImage_Load(fileFormate, file_name.data(), 0);
    HASBU_ASSERT(bitmap == nullptr, "FILE NOT FOUND")
    FIBITMAP* bitmap32 = FreeImage_ConvertTo32Bits(bitmap);

    image_width = FreeImage_GetWidth(bitmap32);
    image_height = FreeImage_GetHeight(bitmap32);
    image_nr_chanels = (FreeImage_GetBPP(bitmap32) / 8);

    BYTE* image_data = FreeImage_GetBits(bitmap32);

    FreeImage_Unload(bitmap);
    FreeImage_Unload(bitmap32);

    return image_data;
}

std::string loadShader(const std::string_view& file_name)
{
    std::ifstream shader_file(file_name.data());

    HASBU_ASSERT(shader_file.good() == false, "Shader File not found")
    std::stringstream buffer;
    buffer << shader_file.rdbuf();
    shader_file.close();

    return buffer.str();
}

}
