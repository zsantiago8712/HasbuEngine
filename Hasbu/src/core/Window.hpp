#pragma once

#include "defines.hpp"

namespace Hasbu {

struct Window {
    Window() = default;
    virtual ~Window() = 0;
};

Unique<Window> createWindow(unsigned int width = 800, unsigned int height = 900, const std::string_view& name = "Hasbu Engine");

void windowPollEvents(Unique<Window>& window);
void windowUpdate(Unique<Window>& window);
bool windowShouldClose(Unique<Window>& window);
void windowSetTitle(Unique<Window>& window, const std::string_view& new_title);

float windowGetAspectRatio(Unique<Window>& window);
float windowGetDeltaTime(Unique<Window>& window);

}
