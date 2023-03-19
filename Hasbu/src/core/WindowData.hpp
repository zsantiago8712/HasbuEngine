#pragma once
#include "Render/GraphicContext.hpp"
#include "defines.hpp"
#include <string_view>

namespace Hasbu {
struct WindowData {

    WindowData() = default;
    WindowData(unsigned int width, unsigned int height, const std::string_view& name)
        : width(width)
        , height(height)
        , name(name) {};

    unsigned int width = 900;
    unsigned int height = 800;
    std::string_view name = "Habu ENgine";

    Shared<GraphicsContext> m_Context;
};

}
