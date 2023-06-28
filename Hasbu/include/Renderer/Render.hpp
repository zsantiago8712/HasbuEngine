#pragma once

struct GLFWwindow;

namespace Hasbu::Render {
struct Renderer {

    Renderer();
    static void clearWindow(const float red = 0.2f, const float green = 0.3f, const float blue = 0.3f, const float alpha = 1.0f);
    static void checkError(const char* file, const int line);
    static double getDeltaTime();
    static void drawElements(const unsigned int size);



    enum class API {
        GL = 0X0,
        VK = 0X1,
    };

    API m_api;
    static double m_lastFrame;
};

}

#define CHECK_ERROR() Hasbu::Render::Renderer::checkError(__FILE__, __LINE__);
