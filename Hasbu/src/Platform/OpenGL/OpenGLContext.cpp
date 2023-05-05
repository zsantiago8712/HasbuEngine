#define GLFW_INCLUDE_NONE
#include "Platform/OpenGL/OpenGLContext.hpp"
#include <GLFW/glfw3.h>
#include <Glad/glad.h>
#include <fmt/core.h>

namespace Hasbu {

OpenGLContext::OpenGLContext(void* window)
    : m_Window(static_cast<GLFWwindow*>(window)) {};

OpenGLContext::~OpenGLContext()
{
    fmt::print("OPENGL CONTEXT DESTROYED\n");
    glfwDestroyWindow(m_Window);
}

void initializeOpenGL(void* context)
{
    auto GL_context = static_cast<OpenGLContext*>(context);
    glfwMakeContextCurrent(GL_context->m_Window);
    const int statusGLAD = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!statusGLAD) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}


void swapBuffersOpenGL(void* context)
{
    auto GL_context = static_cast<OpenGLContext*>(context);
    glfwSwapBuffers(GL_context->m_Window);
}

float getDeltaTimeOpenGL(void* context)
{
    auto GL_context = static_cast<OpenGLContext*>(context);

    const auto current_frame = static_cast<float>(glfwGetTime());
    GL_context->m_delta_time = current_frame - GL_context->m_last_frame_time;
    GL_context->m_last_frame_time = current_frame;

    return GL_context->m_delta_time;
}

// OpenGLContext::OpenGLContext(void* window)
//     : m_Window(static_cast<GLFWwindow*>(window)) {};

// OpenGLContext::~OpenGLContext()
// {
//     fmt::print("OPENGL CONTEXT DESTROYED\n");
//     glfwDestroyWindow(m_Window);
// }

// void OpenGLContext::initialize()
// {
//     glfwMakeContextCurrent(m_Window);
//     const int statusGLAD = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//     if (!statusGLAD) {
//         glfwTerminate();
//         exit(EXIT_FAILURE);
//     }
// }

// void OpenGLContext::swapBuffers()
// {
//     glfwSwapBuffers(m_Window);
// }

}
