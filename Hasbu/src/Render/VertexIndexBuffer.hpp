#pragma once

#include "Render/Render.hpp"
#include "defines.hpp"

namespace Hasbu {

struct VertexBufferIndex {};

Shared<VertexBufferIndex> createVertexBufferIndex(unsigned int* indices, unsigned int count);

void bindVertexBufferIndex(Shared<VertexBufferIndex>& vio);
void unbindVertexBufferIndex(const Shared<VertexBufferIndex>& vio);

}
