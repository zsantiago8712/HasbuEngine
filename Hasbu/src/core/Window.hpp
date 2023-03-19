#pragma once

#include "defines.hpp"
#include <memory>
#include <string_view>

namespace Hasbu {

enum class Platform {
    MACOS = 0,
    WINDOW = 1,
    LINUX = 2,
};

struct Window {
    Window() = default;
#ifdef __APPLE__
    Platform platform = Platform::MACOS;
#elif defined __WINDOW__
    Platform platform = Platform::WINDOWS;
#else
    Platform platform = Platform::LINUX;
#endif // DEBUG
};

Unique<Window> createWindow(unsigned int width = 800, unsigned int height = 900, const std::string_view& name = "Hasbu Engine");

void windowPollEvents(Unique<Window>& window);
void windowUpdate(Unique<Window>& window);
bool windowShouldClose(Unique<Window>& window);
void windowSetTitle(Unique<Window>& window, const std::string_view& new_title);
float windowGetAspectRatio(Unique<Window>& window);

}