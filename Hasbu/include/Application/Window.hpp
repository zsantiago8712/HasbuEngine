#pragma once
#include "WindowData.hpp"
#include "defines.hpp"

struct GLFWwindow;

namespace Hasbu {

class Window {
public:
    Window(const unsigned int width, const unsigned int height);
    Window();

    ~Window() = default;

    void close();

    GLFWwindow* native_window;
    WindowData data;
};

void clearWindow();
bool shouldClose(GLFWwindow* native_window);

void windowUpdate(GLFWwindow* native_window);

void processInput(void);

double getTime();

constexpr float getAspectRatio(const WindowData& window_data)
{
    return static_cast<float>(window_data.width) / static_cast<float>(window_data.height);
}
}
