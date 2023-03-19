#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"
#include "Render/VertexArray.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexIndexBuffer.hpp"
#include "defines.hpp"
#include <Glad/glad.h>

namespace Hasbu {

static GLenum getGLType(BufferElementType type);

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_IdVAO);
    glBindVertexArray(m_IdVAO);
}

void bindOpenGLVertexArray(void* vao)
{
    auto opengl_vao = static_cast<OpenGLVertexArray*>(vao);
    glBindVertexArray(opengl_vao->m_IdVAO);
}

void unbindOpenGLVertexArray()
{
    glBindVertexArray(0);
}

void addVertexBufferOpenGLVertexArray(void* vao, void* vbo)
{
    using enum BufferElementType;
    auto opengl_vao = static_cast<OpenGLVertexArray*>(vao);
    auto opengl_vbo = static_cast<OpenGLVertexBuffer*>(vbo);

    glBindVertexArray(opengl_vao->m_IdVAO);
    openGLVertexBufferBind(vbo);

    const auto& layout = opengl_vbo->m_Layout;
    for (auto& element : layout.m_BufferElements) {
        switch (element.type) {
        case FLOAT:
        case FLOAT_2:
        case FLOAT_3:
        case FLOAT_4:
            glEnableVertexAttribArray(opengl_vao->m_Count);
            glVertexAttribPointer(opengl_vao->m_Count, element.count, getGLType(element.type), element.normalized, layout.m_Stride, (void*)element.offset);
            opengl_vao->m_Count++;
            break;

        default:
            break;
        }
    }
    opengl_vao->m_BuffersLayouts.emplace_back(opengl_vbo);
}

void setOpenGLVertexBufferIndex(void* vao, Shared<VertexBufferIndex>& vio)
{
    auto opengl_vao = static_cast<OpenGLVertexArray*>(vao);
    glBindVertexArray(opengl_vao->m_IdVAO);
    bindVertexBufferIndex(vio);
    opengl_vao->m_VBI = vio;
}
static GLenum getGLType(BufferElementType type)
{
    using enum BufferElementType;
    switch (type) {
    case FLOAT:
    case FLOAT_2:
    case FLOAT_3:
    case FLOAT_4:
        return GL_FLOAT;
    case UNSIGNED_INT:
    case UNSIGNED_INT_2:
    case UNSIGNED_INT_3:
    case UNSIGNED_INT_4:
        return GL_UNSIGNED_INT;
    case UNSIGNED_CHAR:
    case UNSIGNED_CHAR_2:
    case UNSIGNED_CHAR_3:
    case UNSIGNED_CHAR_4:
        return GL_UNSIGNED_BYTE;
    default:
        return GL_FLOAT;
    }
}

// void OpenGLVertexArray::bind()
// {
//     glBindVertexArray(m_IdVAO);
// }

// void OpenGLVertexArray::unbind()
// {
//     glBindVertexArray(0);
// }
}