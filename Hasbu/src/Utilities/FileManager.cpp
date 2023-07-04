#include "Utilities/FileManager.hpp"
#include "Utilities/Logger.hpp"

#include <FreeImage.h>

#include <fstream>
#include <sstream>

namespace Hasbu::Utils {

// TODO: probar freeImage. Necesitamos mejorar el rendimeinto al cargar las texturas.
unsigned char* loadTexture(const std::string_view& file_name, int& image_width, int& image_height, int& image_nr_chanels)
{

    FreeImage_Initialise();

    FREE_IMAGE_FORMAT fileFormate = FreeImage_GetFIFFromFilename(file_name.data());
    HASBU_ASSERT(fileFormate == FIF_UNKNOWN, "UNKNOW FILE FORMAT")

    FIBITMAP* bitmap = FreeImage_Load(fileFormate, file_name.data(), 0);
    HASBU_ASSERT(bitmap == nullptr, "FILE NOT FOUND")
    // FreeImage_FlipVertical(bitmap);
    bitmap = FreeImage_ConvertTo32Bits(bitmap);

    image_width = FreeImage_GetWidth(bitmap);
    image_height = FreeImage_GetHeight(bitmap);
    image_nr_chanels = (FreeImage_GetBPP(bitmap) / 8);

    BYTE* image_data = FreeImage_GetBits(bitmap);
    FreeImage_Unload(bitmap);
    FreeImage_DeInitialise();
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
