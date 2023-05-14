#pragma once
#include "Render/GraphicContext.hpp"
#include "defines.hpp"

struct GLFWwindow;

namespace Hasbu {

struct OpenGLContext : public GraphicsContext {

    explicit OpenGLContext(GLFWwindow* window);

    GLFWwindow* m_Window;
    float m_delta_time;
    float m_last_frame_time;
};

void initializeOpenGL(Unique<GraphicsContext>& context);
void swapBuffersOpenGL(Unique<GraphicsContext>& context);
float getDeltaTimeOpenGL(Unique<GraphicsContext>& context);

}
