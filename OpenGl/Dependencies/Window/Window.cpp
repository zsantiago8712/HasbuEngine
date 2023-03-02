#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(unsigned int _width, unsigned int _height, std::string_view const& window_name)
    : width(_width)
    , height(_height)
    , name(window_name) {};

Window::Window(std::string_view const& window_name)
    : name(window_name) {};

Window::~Window()
{
    glfwDestroyWindow(this->glfw_window);
    glfwTerminate();
}

void Window::create()
{
    this->init();
    this->glfw_window = glfwCreateWindow(this->width, this->height, this->name.cbegin(), nullptr, nullptr);

    if (this->glfw_window == nullptr) {
        std::cerr << "Failed to create Window\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->glfw_window);
}

WindowState Window::should_close()
{
    return glfwWindowShouldClose(this->glfw_window) ? WindowState::CLOSE : WindowState::OPEN;
}

void Window::swap_buffers()
{
    glfwSwapBuffers(this->glfw_window);
}

void Window::poll_events() const
{
    glfwPollEvents();
}

unsigned int Window::get_width() const
{
    return this->width;
}

unsigned int Window::get_height() const
{
    return this->height;
}

void Window::process_input()
{
    if (glfwGetKey(this->glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->glfw_window, true);
    }
}

void Window::init() const
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Window::setFramebufferSizeCallback(void* callback)
{
    glfwSetFramebufferSizeCallback(this->glfw_window, (GLFWframebuffersizefun)callback);
}