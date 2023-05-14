#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"
#include <Glad/glad.h>
#include <memory>

namespace Hasbu {

OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, const unsigned int size)
{
    glGenBuffers(1, &m_IdVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_IdVBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void openGLVertexBufferBind(Shared<VertexBuffer>& vbo)
{
    auto openGL_vbo = std::static_pointer_cast<OpenGLVertexBuffer>(vbo);
    glBindBuffer(1, openGL_vbo->m_IdVBO);
}

void openGLVertexBufferUnbind()
{
    glBindBuffer(1, 0);
}

void openGLSetLayout(Shared<VertexBuffer>& vbo, const VertexBufferLayout& layout)
{
    auto openGL_vbo = std::static_pointer_cast<OpenGLVertexBuffer>(vbo);
    openGL_vbo->m_Layout = layout;
}

}
