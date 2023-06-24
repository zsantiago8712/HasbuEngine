#include "Application/Window.hpp"
#include "Application/EventDispatcher.hpp"
#include "Application/WindowData.hpp"
#include "KeyCodes.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/Context.hpp"
#include "Utilities/Logger.hpp"
#include <GLFW/glfw3.h>
namespace Hasbu {

Window::Window(const unsigned int width, const unsigned int height)
    : data(WindowData(width, height))
{
    this->native_window = HasbuRender::getNativeWindow(*this->data.context);
}

Window::Window()
    : data(WindowData())
{
    this->native_window = HasbuRender::getNativeWindow(*this->data.context);

    glfwSetKeyCallback(this->native_window, []([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode, [[maybe_unused]] int action, [[maybe_unused]] int mods) {
        const char* keyname = glfwGetKeyName(key, scancode);
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            HASBU_DEBUG("KEY {} IS HAS BEEN PRESSED", (keyname != nullptr) ? keyname : "");
            // const Hasbu::Event event = Hasbu::getEvent(static_cast<Hasbu::KeyCode>(key));
            // EventDispatcher::dispatchKeyEvent(event);
        } else {
            HASBU_DEBUG("KEY {} IS HAS BEEN RELEASED", (keyname != nullptr) ? keyname : "");
        }
    });
}

void Window::close()
{
    glfwSetWindowShouldClose(this->native_window, GLFW_TRUE);
}

void windowUpdate(GLFWwindow* native_window)
{

    double time_diff = HasbuRender::Camera::getDeltaTime();
    static double counter = 0;
    counter++;
    if (time_diff >= (1.0 / 60.0)) {
        const std::string FPS = std::to_string((1.0 / time_diff) * counter);
        const std::string ms = std::to_string((time_diff / counter) * 1000);
        const std::string newTitle = FPS + " FPS / " + ms + " ms";
        glfwSetWindowTitle(native_window, newTitle.data());
        counter = 0;
    }
    HasbuRender::swapBuffers(native_window);
}

// TODO: manejar los callbacks (inputs, tamaño, etc)
void processInput(void)
{
    glfwPollEvents();
}

double getTime()
{
    return glfwGetTime();
}

bool shouldClose(GLFWwindow* native_window)
{
    return !glfwWindowShouldClose(native_window);
}

}
