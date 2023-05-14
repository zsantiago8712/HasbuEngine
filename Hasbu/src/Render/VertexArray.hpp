#pragma once

#include "Render/Render.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexIndexBuffer.hpp"
#include "defines.hpp"

namespace Hasbu {

struct VertexArray { };

Shared<VertexArray> createVertexArray();
void bindVertexArray(Shared<VertexArray>& vao);
void unbindVertexArray(const Shared<VertexArray>& vao);
void addVertexBuffer(Shared<VertexArray>& vao, Shared<VertexBuffer>& vbo);
void setVertexBufferIndex(Shared<VertexArray>& vao, Shared<VertexBufferIndex>& vbi);

}
