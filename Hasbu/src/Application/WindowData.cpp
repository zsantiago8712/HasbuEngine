#include "Application/WindowData.hpp"
#include "Utilities/Logger.hpp"
#include <GLFW/glfw3.h>

static GLFWwindow* createNativeWindow(const unsigned int width, const unsigned int height, const std::string_view& name);

namespace Hasbu::Core {

WindowData::WindowData(const unsigned int height, const unsigned int width)
    : m_width(width)
    , m_height(height)
{
    this->m_window = createNativeWindow(m_width, m_height, m_name);
}

WindowData::WindowData()
{
    m_window = createNativeWindow(m_width, m_height, m_name);
}

WindowData::~WindowData()
{
    glfwDestroyWindow(this->m_window);
    glfwTerminate();
};

}

// TODO: SEPARAR EL INIT DE GLFW EN WINDOW.CPP
static GLFWwindow* createNativeWindow(const unsigned int width, const unsigned int height, const std::string_view& name)
{
    GLFWwindow* window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
    HASBU_ASSERT(window == nullptr, "GLFW filaed to create a window")

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);
    HASBU_INFO("GLFW SUCCES TO INITIAZED AND CREATE A WINDOW");
    return window;
}
