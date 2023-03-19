#pragma once
#include "Render/VertexBuffer.hpp"

namespace Hasbu {

struct OpenGLVertexBuffer : public VertexBuffer {
    explicit OpenGLVertexBuffer(float* data, unsigned int size);
    unsigned int m_IdVBO;
    VertexBufferLayout m_Layout;
};

void openGLVertexBufferBind(void* vbo);
void openGLVertexBufferUnbind();
void openGLSetLayout(void* vbo, const VertexBufferLayout& layout);

// class OpenGLVertexBuffer : public VertexBuffer {

// public:
//     OpenGLVertexBuffer(void* data, unsigned int size);
//     ~OpenGLVertexBuffer() = default;

//     void bind() override;
//     void unbind() override;
//     void setLayout(const VertexBufferLayout& layout) override;

// private:
//     unsigned int m_IdVBO;
//     VertexBufferLayout m_Layout;
// };

}