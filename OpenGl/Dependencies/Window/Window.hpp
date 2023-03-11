#pragma once

#include "../../defines.hpp"
#include <string_view>

// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;

enum class WindowState {
    CLOSE = 0x0,
    OPEN = 0x1,
};

class HB_API Window {

public:
    Window() = default;
    Window(unsigned int width, unsigned int height, std::string_view const& window_name);
    explicit Window(std::string_view const& window_name);
    ~Window();

    GLFWwindow* glfw_window;
    void create();
    WindowState shouldClose();
    void swapBuffers();
    void pollEvents() const;
    void setFramebufferSizeCallback(void* callback);
    void processInput();

    unsigned int getHeight() const;
    unsigned int getWidth() const;
    static double getTime();

private:
    unsigned int width = 900;
    unsigned int height = 600;
    const std::string_view name = "App";
    void init() const;
};
