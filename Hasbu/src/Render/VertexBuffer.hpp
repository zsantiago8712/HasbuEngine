#pragma once
// TODO: update the contyextGraphics class#pragma once
#include "Render/VertexBufferLayout.hpp"
#include "defines.hpp"

namespace Hasbu {

// Interfaz
struct VertexBuffer { };

Shared<VertexBuffer> createVertexBuffer(float* data, const unsigned int size);

void bindVertexBuffer(Shared<VertexBuffer>& vbo);
void unbindVertexBuffer(const Shared<VertexBuffer>& vbo);
void setLayout(Shared<VertexBuffer>& vbo, const VertexBufferLayout& layout);

}
