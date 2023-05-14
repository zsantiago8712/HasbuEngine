#include "core/Window.hpp"
#include "Configuration.hpp"
#include "Platform/Window/MacWindow.hpp"
#include "Render/Render.hpp"
#include "core/WindowData.hpp"
#include "defines.hpp"
#include <fmt/core.h>

using PollEventsFn = void (*)();
using UpdateFn = void (*)(Hasbu::Unique<Hasbu::Window>& window);
using ShouldCloseFn = bool (*)(Hasbu::Unique<Hasbu::Window>& window);
using SetTileFn = void (*)(Hasbu::Unique<Hasbu::Window>& window, const std::string_view& new_title);
using GetAspectRatio = float (*)(Hasbu::Unique<Hasbu::Window>& window);
using GetDeltaTime = float (*)(Hasbu::Unique<Hasbu::Window>& window);

struct WindowPlatformFunctions {

    WindowPlatformFunctions();
    PollEventsFn pollEvents;
    UpdateFn update;
    ShouldCloseFn shouldClose;
    SetTileFn setTile;
    GetAspectRatio getAspectRatio;
    GetDeltaTime getDeltaTime;

    // otras funciones específicas de la plataforma
};

static const WindowPlatformFunctions windowPlatformFunctions;

namespace Hasbu {

Window::~Window()
{
    fmt::print("Window destructor called\n");
};

Unique<Window>
createWindow(const unsigned int width, const unsigned int height, const std::string_view& name)
{
    auto& configs = HasbuConfig::Configurations::getInstance();
    WindowData attr { width, height, name };

    switch (configs.getPlatform()) {
    case HasbuConfig::Platform::MACOS:
        return createUnique<MacWindow>(attr);
        break;

    case HasbuConfig::Platform::WINDOWS:
        fmt::print("Platfor is not available right now");
        return nullptr;
        break;

    case HasbuConfig::Platform::LINUX:
        fmt::print("Platfor is not available right now");
        return nullptr;
        break;
    }
}

void windowPollEvents(Unique<Window>& window)
{
    windowPlatformFunctions.pollEvents();
}

void windowUpdate(Unique<Window>& window)
{
    windowPlatformFunctions.update(window);
}

bool windowShouldClose(Unique<Window>& window)
{
    return windowPlatformFunctions.shouldClose(window);
}

void windowSetTitle(Unique<Window>& window, const std::string_view& title)
{
    windowPlatformFunctions.setTile(window, title);
}

float windowGetAspectRatio(Unique<Window>& window)
{
    return windowPlatformFunctions.getAspectRatio(window);
}

float windowGetDeltaTime(Unique<Window>& window)
{
    return windowPlatformFunctions.getDeltaTime(window);
}

}

WindowPlatformFunctions::WindowPlatformFunctions()
{
    auto& configs = HasbuConfig::Configurations::getInstance();

    switch (configs.getPlatform()) {
    case HasbuConfig::Platform::MACOS:
        this->pollEvents = Hasbu::macWindowPollEvents;
        this->getDeltaTime = Hasbu::macWindowGetDeltaTime;
        this->getAspectRatio = Hasbu::macWindowGetAspectRatio;
        this->setTile = Hasbu::macWindowSetTile;
        this->shouldClose = Hasbu::macWindowShouldClose;
        this->update = Hasbu::macWindowUpdate;
        break;
    case HasbuConfig::Platform::LINUX:
        fmt::print("Platfor is not available right now");
        break;
    case HasbuConfig::Platform::WINDOWS:
        fmt::print("Platfor is not available right now");
        break;
    }
}
