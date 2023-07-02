#include "Application/Window.hpp"
#include "DynamicAllocator.hpp"
#include "EventDispatcher.hpp"
#include "ImGuiLayer/ImguiLayer.hpp"
#include "Utilities/Logger.hpp"
#include "WindowData.hpp"
#include "imgui.h"
#include <GLFW/glfw3.h>

static void initializedGLFW();
namespace Hasbu::Core {

Window::Window(const unsigned int width, const unsigned int height)
{
    initializedGLFW();
    m_data = Utils::createUnique<WindowData>(width, height);

    glfwSetCursorPosCallback(this->m_data->m_window, []([[maybe_unused]] GLFWwindow* window, const double xpos, const double ypos) {
        if (!Gui::ImGuiLayer::wantCaptureMouse()) {
            HASBU_DEBUG("Curosr Postion: [X: {}, Y: {}]", xpos, ypos);
            EventDispatcher::dispatchMousEvent(MouseEvent::CURSOR, xpos, ypos);
        }
    });

    glfwSetScrollCallback(this->m_data->m_window, []([[maybe_unused]] GLFWwindow* window, const double xpos, const double ypos) {
        HASBU_DEBUG("SCROLL Curosr Postion: [X: {}, Y: {}]", xpos, ypos);
        EventDispatcher::dispatchMousEvent(MouseEvent::SCROLL, xpos, ypos);
    });
};

Window::Window()
{
    initializedGLFW();
    m_data = Utils::createUnique<WindowData>();

    glfwSetCursorPosCallback(this->m_data->m_window, []([[maybe_unused]] GLFWwindow* window, const double xpos, const double ypos) {
        if (!Gui::ImGuiLayer::wantCaptureMouse()) {
            HASBU_DEBUG("Curosr Postion: [X: {}, Y: {}]", xpos, ypos);
            EventDispatcher::dispatchMousEvent(MouseEvent::CURSOR, xpos, ypos);
        }
    });

    glfwSetScrollCallback(this->m_data->m_window, []([[maybe_unused]] GLFWwindow* window, const double xpos, const double ypos) {
        HASBU_DEBUG("Scroll Curosr  Postion: [X: {}, Y: {}]", xpos, ypos);
        EventDispatcher::dispatchMousEvent(MouseEvent::SCROLL, xpos, ypos);
    });

    // TODO: make a better keyclalback
    //  glfwSetKeyCallback(this->native_window, []([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode, [[maybe_unused]] int action, [[maybe_unused]] int mods) {
    //      const char* keyname = glfwGetKeyName(key, scancode);
    //      if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    //          HASBU_DEBUG("KEY {} IS HAS BEEN PRESSED", (keyname != nullptr) ? keyname : "");
    //          // const Hasbu::Event event = Hasbu::getEvent(static_cast<Hasbu::KeyCode>(key));
    //          // EventDispatcher::dispatchKeyEvent(event);
    //      } else {
    //          HASBU_DEBUG("KEY {} IS HAS BEEN RELEASED", (keyname != nullptr) ? keyname : "");
    //      }
    //  });
}

void Window::update()
{
    glfwSwapBuffers(m_data->m_window);
}

// TODO: manejar los callbacks (inputs, tamaño, etc)
void Window::processInput() const
{
    glfwPollEvents();
}

bool Window::shouldClose() const
{
    return !glfwWindowShouldClose(m_data->m_window);
}

void Window::close()
{
    glfwSetWindowShouldClose(m_data->m_window, GLFW_TRUE);
}

double getTime()
{
    return glfwGetTime();
}
}

// TODO: implement a better way to use the versioning
static void initializedGLFW()
{
    static constexpr unsigned int OPENGL_MAJOR_VERSION = 4;
    static constexpr unsigned int OPENGL_MINOR_VERSION = 1;

    HASBU_ASSERT(!glfwInit(), "GLFW failed to initilized")

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
