#pragma once
#include "Render/VertexBuffer.hpp"
#include "defines.hpp"

namespace Hasbu {

struct OpenGLVertexBuffer : public VertexBuffer {
    explicit OpenGLVertexBuffer(float* data, unsigned int size);
    unsigned int m_IdVBO;
    VertexBufferLayout m_Layout;
};

void openGLVertexBufferBind(Shared<VertexBuffer>& vbo);
void openGLVertexBufferUnbind();
void openGLSetLayout(Shared<VertexBuffer>& vbo, const VertexBufferLayout& layout);

}
