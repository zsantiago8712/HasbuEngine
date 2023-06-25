#pragma once
#include <string_view>

struct GLFWwindow;

namespace Hasbu::Core {

struct WindowData {

    explicit WindowData(const unsigned int height, const unsigned int width);
    explicit WindowData();
    ~WindowData();

    unsigned int m_width = 800;
    unsigned int m_height = 900;
    const std::string_view m_name = "Hasbu Engine";
    GLFWwindow* m_window;
};

}
