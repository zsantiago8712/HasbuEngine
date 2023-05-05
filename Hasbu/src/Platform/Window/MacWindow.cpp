#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include "Platform/Window/MacWindow.hpp"
#include "Render/GraphicContext.hpp"
#include <GLFW/glfw3.h>
#include <Glad/glad.h>
#include <fmt/core.h>

namespace Hasbu {

void macWindowInitialize(MacWindow& window);
static void callBackError(int id, const char* description);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void sizeCallback(GLFWwindow* window, int width, int height);

MacWindow::MacWindow(const WindowData& data)
    : m_Data(data)
{
    macWindowInitialize(*this);
};

void macWindowInitialize(MacWindow& window)
{
    glfwSetErrorCallback(&callBackError);
    const int statusGLFW = glfwInit();
    if (!statusGLFW) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window.m_NativeWindow = glfwCreateWindow(window.m_Data.width, window.m_Data.height, window.m_Data.name.data(), nullptr, nullptr);
    if (window.m_NativeWindow == nullptr) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    window.m_Data.m_Context = createGraphicsContext(window.m_NativeWindow);
    initializeGraphicsContext(window.m_Data.m_Context);

    glfwSetWindowUserPointer(window.m_NativeWindow, (void*)&window.m_Data);
    glfwSetFramebufferSizeCallback(window.m_NativeWindow, sizeCallback);
    glfwSetKeyCallback(window.m_NativeWindow, keyCallback);
}

void macWindowPollEvents()
{
    glfwPollEvents();
}

void macWindowUpdate(void* window)
{
    auto macWindow = static_cast<MacWindow*>(window);
    glfwPollEvents();
    swapBuffers(macWindow->m_Data.m_Context);
}

bool macWindowShouldClose(void* window)
{
    auto macWindow = static_cast<MacWindow*>(window);
    return glfwWindowShouldClose(macWindow->m_NativeWindow);
}

void macWindowSetTile(void* window, const std::string_view& title)
{
    auto macWindow = static_cast<MacWindow*>(window);
    macWindow->m_Data.name = title;
    glfwSetWindowTitle(macWindow->m_NativeWindow, macWindow->m_Data.name.data());
}

float macWindowGetAspectRatio(void* window)
{
    auto macWindow = static_cast<MacWindow*>(window);
    return static_cast<float>(macWindow->m_Data.width) / static_cast<float>(macWindow->m_Data.height);
}

float macWindowGetDeltaTime(void* window)
{
    auto macWindow = static_cast<MacWindow*>(window);
    return getDeltaTime(macWindow->m_Data.m_Context);
}

static void callBackError(int id, const char* description)
{
    fmt::print(stderr, "[Error]:{} {}\n", id, description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void sizeCallback(GLFWwindow* window, int width, int height)
{

    WindowData& attr = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    attr.width = width;
    attr.height = height;
    fmt::print("Window Resize to: Width: [{}], Heigth: [{}]\n", attr.width, attr.height);
    glViewport(0, 0, attr.width, attr.height);
}

// MacWindow::MacWindow(const WindowData& data)
//     : Window(data)
// {
//     initialized();
// };

// MacWindow::~MacWindow()
// {
// }

// void MacWindow::initialized()
// {
//     glfwSetErrorCallback(&callBackError);

//     const int statusGLFW = glfwInit();
//     if (!statusGLFW) {
//         glfwTerminate();
//         exit(EXIT_FAILURE);
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

//     m_NativeWindow = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.name.data(), nullptr, nullptr);
//     if (m_NativeWindow == nullptr) {
//         glfwTerminate();
//         exit(EXIT_FAILURE);
//     }

//     m_Context = GraphicsContext::create(GraphicApi::OpenGL, m_NativeWindow);
//     m_Context->initialize();

//     glfwSetWindowUserPointer(m_NativeWindow, (void*)&m_Data);
//     glfwSetFramebufferSizeCallback(m_NativeWindow, sizeCallback);
//     glfwSetKeyCallback(m_NativeWindow, keyCallback);
// }

// void MacWindow::update()
// {
//     glfwPollEvents();
//     m_Context->swapBuffers();
// }

// bool MacWindow::shouldClose()
// {
//     return glfwWindowShouldClose(m_NativeWindow);
// }

}