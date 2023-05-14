#include "defines.hpp"
#define GLFW_INCLUDE_NONE
#include "Platform/OpenGL/OpenGLContext.hpp"
#include <GLFW/glfw3.h>
#include <Glad/glad.h>
#include <fmt/core.h>

namespace Hasbu {

OpenGLContext::OpenGLContext(GLFWwindow* window)
    : m_Window(window) {};

void initializeOpenGL(Unique<GraphicsContext>& context)
{
    auto GL_context = static_cast<OpenGLContext*>(context.get());

    glfwMakeContextCurrent(GL_context->m_Window);
    const int statusGLAD = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!statusGLAD) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void swapBuffersOpenGL(Unique<GraphicsContext>& context)
{
    auto GL_context = static_cast<OpenGLContext*>(context.get());
    glfwSwapBuffers(GL_context->m_Window);
}

float getDeltaTimeOpenGL(Unique<GraphicsContext>& context)
{
    auto GL_context = static_cast<OpenGLContext*>(context.get());

    const auto current_frame = static_cast<float>(glfwGetTime());
    GL_context->m_delta_time = current_frame - GL_context->m_last_frame_time;
    GL_context->m_last_frame_time = current_frame;

    return GL_context->m_delta_time;
}

}
