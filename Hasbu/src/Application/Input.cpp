#include "Application/Input.hpp"
#include "Application/Application.hpp"
#include <GLFW/glfw3.h>

namespace Hasbu::Core {

bool isKeyBeenPressed(KeyCode key)
{
    auto window = static_cast<GLFWwindow*>(Application::getNativeWindow());

    auto state = glfwGetKey(window, static_cast<int>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

}