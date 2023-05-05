#pragma once
#include "Render/GraphicContext.hpp"
#include "core/Window.hpp"
#include "core/WindowData.hpp"
#include "defines.hpp"

struct WindowData;

struct GLFWwindow;

namespace Hasbu {

struct MacWindow : public Window {
    MacWindow() = default;
    MacWindow(const WindowData& data);

    WindowData m_Data;
    GLFWwindow* m_NativeWindow;
};

void macWindowPollEvents();
void macWindowUpdate(void* window);
bool macWindowShouldClose(void* window);
void macWindowSetTile(void* window, const std::string_view& title);
float macWindowGetAspectRatio(void* window);

float macWindowGetDeltaTime(void* window);

// class MacWindow : public Window {
// public:
//     MacWindow(const WindowData& data);
//     ~MacWindow();
//     void update() override;
//     bool shouldClose() override;

// private:
//     void initialized();

//     GLFWwindow* m_NativeWindow;
//     Shared<GraphicsContext> m_Context;
// };
}