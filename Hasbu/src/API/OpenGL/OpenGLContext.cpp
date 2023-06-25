
#include "Application/Window.hpp"
#include "Renderer/Render.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>
#include <string_view>

static void createOpenGLContext();

namespace Hasbu::Render {

double Renderer::m_lastFrame = 0.0f;

Renderer::Renderer()
{
    m_api = Renderer::API::GL;
    createOpenGLContext();
}

void Renderer::clearWindow()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::checkError(const char* file, const int& line)
{
    unsigned int severity;
    do {
        severity = glGetError();
        switch (severity) {
        case GL_INVALID_ENUM:
            HASBU_ERROR("[OPENGL]: INVALID_ENUM [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_VALUE:
            HASBU_ERROR("[OPENGL]: INVALID_VALUE [FILE: {}; LINE: {}], file, line");
            break;
        case GL_STACK_OVERFLOW:
            HASBU_WARNING("[OPENGL]: STACK_OVERFLOW [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_OUT_OF_MEMORY:
            HASBU_ERROR("[OPENGL]: STACK_UNDERFLOW [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_OPERATION:
            HASBU_ERROR("[OPENGL]: INVALID_OPERATION [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            HASBU_ERROR("[OPENGL]: INVALID_FRAMEBUFFER [FILE: {}; LINE: {}]", file, line);
            break;
        }
    } while (severity != GL_NO_ERROR);
}

double Renderer::getDeltaTime()
{
    double current_time = Core::getTime();
    double delta_time = current_time - m_lastFrame;
    m_lastFrame = current_time;
    return delta_time;
}

}

static void createOpenGLContext()
{
    HASBU_ASSERT(GLEW_OK != glewInit(), "GLEW (OpenGL) failed to load")

    glEnable(GL_DEPTH_TEST);

    HASBU_INFO("OPENGL succes to load {}", reinterpret_cast<const char*>((glGetString(GL_VERSION))));
}
