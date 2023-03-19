#pragma once

#include "Render/VertexArray.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexIndexBuffer.hpp"
#include "defines.hpp"
#include <vector>

namespace Hasbu {

struct OpenGLVertexArray : public VertexArray {

    OpenGLVertexArray();
    unsigned int m_IdVAO;
    std::vector<Shared<VertexBuffer>> m_BuffersLayouts;
    unsigned int m_Count = 0;
    Shared<VertexBufferIndex> m_VBI;
};

void bindOpenGLVertexArray(void* vao);
void unbindOpenGLVertexArray();
void addVertexBufferOpenGLVertexArray(void* vao, void* vbo);
void setOpenGLVertexBufferIndex(void* vao, Shared<VertexBufferIndex>& vio);

// class OpenGLVertexArray : public VertexArray {
// public:
//     OpenGLVertexArray();
//     ~OpenGLVertexArray() = default;

//     void bind() override;
//     void unbind() override;
//     // void addBuffer() override;

// private:
//     unsigned int m_IdVAO;
//     std::vector<VertexBuffer> m_BuffersLayouts;
// };

}