#pragma once

#include <string_view>

// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;

enum class WindowState {
    CLOSE = 0x0,
    OPEN = 0x1,
};

class Window {

public:
    Window() = default;
    Window(unsigned int width, unsigned int height, std::string_view const& window_name);
    explicit Window(std::string_view const& window_name);
    ~Window();

    GLFWwindow* glfw_window;
    void create();
    WindowState should_close();
    void swap_buffers();
    void poll_events() const;
    void setFramebufferSizeCallback(void* callback);
    void process_input();

    unsigned int get_height() const;
    unsigned int get_width() const;

private:
    unsigned int width = 900;
    unsigned int height = 600;
    const std::string_view name = "App";
    void init() const;
};
