#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"
#include <Glad/glad.h>

namespace Hasbu {

OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, const unsigned int size)
{
    glGenBuffers(1, &m_IdVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_IdVBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void openGLVertexBufferBind(void* vbo)
{
    auto openGL_vbo = static_cast<OpenGLVertexBuffer*>(vbo);
    glBindBuffer(1, openGL_vbo->m_IdVBO);
}

void openGLVertexBufferUnbind()
{
    glBindBuffer(1, 0);
}

void openGLSetLayout(void* vbo, const VertexBufferLayout& layout)
{
    auto openGL_vbo = static_cast<OpenGLVertexBuffer*>(vbo);
    openGL_vbo->m_Layout = layout;
}

// OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, const unsigned int size)
// {
//     glGenBuffers(1, &m_IdVBO);
//     glBindBuffer(1, m_IdVBO);
//     glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
// }

// void OpenGLVertexBuffer::bind()
// {
//     glBindBuffer(1, m_IdVBO);
// }

// void OpenGLVertexBuffer::unbind()
// {
//     glBindBuffer(1, 0);
// }

// void OpenGLVertexBuffer::setLayout(const VertexBufferLayout& layout)
// {
//     m_Layout = layout;
// }

}