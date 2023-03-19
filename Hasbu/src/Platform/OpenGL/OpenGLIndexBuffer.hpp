#pragma once
#include "Render/VertexIndexBuffer.hpp"

namespace Hasbu {

struct OpenGLVertexBufferIndex : public VertexBufferIndex {
    OpenGLVertexBufferIndex(unsigned int* indices, unsigned int count);
    unsigned int m_IdVIO;
};

void binOpenGLVertexBufferIndex(void* vio);
void unbindOpenGLVertexBufferIndex();

}