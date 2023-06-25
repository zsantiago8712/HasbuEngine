#pragma once

struct GLFWwindow;

namespace Hasbu::Render {
struct Renderer {

    Renderer();
    static void clearWindow();
    static void checkError(const char* file, const int& line);
    static double getDeltaTime();

    enum class API {
        GL = 0X0,
        VK = 0X1,
    };

    API m_api;
    static double m_lastFrame;
};

}

#define CHECK_ERROR() Hasbu::Render::Renderer::checkError(__FILE__, __LINE__);