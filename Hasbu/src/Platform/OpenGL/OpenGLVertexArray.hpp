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

void bindOpenGLVertexArray(Shared<VertexArray>& vao);
void unbindOpenGLVertexArray();
void addVertexBufferOpenGLVertexArray(Shared<VertexArray>& vao, Shared<Hasbu::VertexBuffer>& vbo);
void setOpenGLVertexBufferIndex(Shared<VertexArray>& vao, Shared<VertexBufferIndex>& vio);


}
