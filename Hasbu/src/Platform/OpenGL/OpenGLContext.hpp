#pragma once
#include "Render/GraphicContext.hpp"

struct GLFWwindow;

namespace Hasbu {

struct OpenGLContext : public GraphicsContext {
    OpenGLContext() = default;
    explicit OpenGLContext(void* window);
    ~OpenGLContext();

    GLFWwindow* m_Window;
};

void initializeOpenGL(void* context);
void swapBuffersOpenGL(void* context);

// class OpenGLContext : public GraphicsContext {
// public:
//     explicit OpenGLContext(void* window);
//     ~OpenGLContext() override;

//     void initialize() override;
//     void swapBuffers() override;

//     GLFWwindow* m_Window;
// };

}