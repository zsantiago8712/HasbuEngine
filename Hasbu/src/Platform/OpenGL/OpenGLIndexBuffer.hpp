#pragma once
#include "Render/VertexIndexBuffer.hpp"
#include "defines.hpp"

namespace Hasbu {

struct OpenGLVertexBufferIndex : public VertexBufferIndex {
    OpenGLVertexBufferIndex(unsigned int* indices, unsigned int count);
    unsigned int m_IdVIO;
};

void binOpenGLVertexBufferIndex(Shared<VertexBufferIndex>& vio);
void unbindOpenGLVertexBufferIndex();

}
