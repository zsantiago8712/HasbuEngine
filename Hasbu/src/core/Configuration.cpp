#include "Configuration.hpp"
#include "defines.hpp"
#include "Json/json.hpp"
#include <exception>
#include <fmt/core.h>
#include <fstream>
#include <stdexcept>

namespace HasbuConfig {

Configurations::Configurations()
{
#ifdef __APPLE__
    this->platform = Platform::MACOS;
#elif defined __WINDOW__
    this->platform = Platform::WINDOWS;
#else
    this->platform = Platform::LINUX;
#endif // DEBUG
    this->configurateFromFile();
}

void Configurations::configurateFromFile(const std::string_view& file_name)
{

    try {

        std::ifstream config_file(file_name);
        nlohmann::json configurations;

        if (!config_file.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo de configuración.");
        }

        config_file >> configurations;
        switch (static_cast<int>(configurations["application"]["api_graphic"])) {

        case static_cast<int>(GraphicApi::OPENGL):
            this->graphics_api = GraphicApi::OPENGL;
            break;

        case static_cast<int>(GraphicApi::VULKAN):
            this->graphics_api = GraphicApi::VULKAN;
            break;

        default:
            throw std::runtime_error("Api grafica invalida");
            break;
        }

    } catch (const std::exception& ex) {
        fmt::print("[ERROR]: {}", ex.what());
    }
}

Configurations& Configurations::getInstance()
{
    static Configurations configs;
    return configs;
}

GraphicApi Configurations::getGraphicsApi()
{
    return this->graphics_api;
}

Platform Configurations::getPlatform()
{
    return this->platform;
}

}
