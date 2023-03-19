#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"
#include <Glad/glad.h>
#include <memory>

namespace Hasbu {

OpenGLVertexBufferIndex::OpenGLVertexBufferIndex(unsigned int* indices, const unsigned int count)
{
    glGenBuffers(1, &m_IdVIO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IdVIO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}

void binOpenGLVertexBufferIndex(void* vio)
{
    auto opengl_vio = static_cast<OpenGLVertexBufferIndex*>(vio);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl_vio->m_IdVIO);
}

void unbindOpenGLVertexBufferIndex()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}