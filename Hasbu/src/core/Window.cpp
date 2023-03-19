#include "core/Window.hpp"
#include "Platform/Window/MacWindow.hpp"
#include "core/WindowData.hpp"
#include "defines.hpp"
#include <fmt/core.h>
#include <string_view>

using PollEventsFn = void (*)();
using UpdateFn = void (*)(void* window);
using ShouldCloseFn = bool (*)(void* window);
using SetTileFn = void (*)(void* window, const std::string_view& new_title);
using GetAspectRatio = float (*)(void* window);

struct WindowPlatformFunctions {
    PollEventsFn pollEvents;
    UpdateFn update;
    ShouldCloseFn shouldClose;
    SetTileFn setTile;
    GetAspectRatio getAspectRatio;
    // otras funciones específicas de la plataforma
};

namespace Hasbu {

static const WindowPlatformFunctions windowPlatformFunctions[] = {
    { macWindowPollEvents,
        macWindowUpdate, macWindowShouldClose, macWindowSetTile, macWindowGetAspectRatio }
};

Unique<Window>
createWindow(const unsigned int width, const unsigned int height, const std::string_view& name)
{
    WindowData attr { width, height, name };
    return createUnique<MacWindow>(attr);
}

void windowPollEvents(Unique<Window>& window)
{
    const auto& functions = windowPlatformFunctions[static_cast<int>(window->platform)];
    functions.pollEvents();
}

void windowUpdate(Unique<Window>& window)
{
    const auto& functions = windowPlatformFunctions[static_cast<int>(window->platform)];
    functions.update(window.get());
}

bool windowShouldClose(Unique<Window>& window)
{
    const auto& functions = windowPlatformFunctions[static_cast<int>(window->platform)];
    return functions.shouldClose(window.get());
}

void windowSetTitle(Unique<Window>& window, const std::string_view& title)
{
    const auto& functions = windowPlatformFunctions[static_cast<int>(window->platform)];
    functions.setTile(window.get(), title);
}

float windowGetAspectRatio(Unique<Window>& window)
{
    const auto& functions = windowPlatformFunctions[static_cast<int>(window->platform)];
    return functions.getAspectRatio(window.get());
}

}