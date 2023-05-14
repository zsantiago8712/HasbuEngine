#pragma once
#include "Render/GraphicContext.hpp"
#include "core/Window.hpp"
#include "core/WindowData.hpp"
#include "defines.hpp"

struct WindowData;

struct GLFWwindow;

namespace Hasbu {

struct MacWindow : public Window {
    explicit MacWindow(WindowData& data);

    ~MacWindow() override;

    WindowData m_Data;
    GLFWwindow* m_NativeWindow;
};

void macWindowPollEvents();
void macWindowUpdate(Unique<Window>& window);
bool macWindowShouldClose(Unique<Window>& window);
void macWindowSetTile(Unique<Window>& window, const std::string_view& title);
float macWindowGetAspectRatio(Unique<Window>& window);
float macWindowGetDeltaTime(Unique<Window>& window);
}
