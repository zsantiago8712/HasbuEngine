#pragma once

#include "Render/Render.hpp"
#include "defines.hpp"

namespace Hasbu {

struct VertexBufferIndex {
#ifdef OpenGL
    GraphicApi api = GraphicApi::OPENGL;
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
};

Shared<VertexBufferIndex> createVertexBufferIndex(unsigned int* indices, unsigned int count);

void bindVertexBufferIndex(Shared<VertexBufferIndex>& vio);
void unbindVertexBufferIndex(const Shared<VertexBufferIndex>& vio);

}