#include "Render/Render.hpp"
#include "defines.hpp"

namespace HasbuConfig {

enum class GraphicApi : int {

    OPENGL = 0,
    VULKAN = 1,

};

enum class Platform : int {
    MACOS = 0,
    WINDOWS = 1,
    LINUX = 2,
};





class Configurations {

public:
    static Configurations& getInstance();

    Configurations(const Configurations&) = delete; // Evita la copia
    Configurations& operator=(const Configurations&) = delete; // Evita la asignación
    Configurations(Configurations&&) = delete; // Evita el movimiento
    Configurations& operator=(Configurations&&) = delete;

    GraphicApi getGraphicsApi();
    Platform getPlatform();

private:
    Configurations();
    void configurateFromFile(const std::string_view& file_name = "config.json");

    GraphicApi graphics_api;
    Platform platform;
};

}
