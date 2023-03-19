#pragma once
// TODO: update the contyextGraphics class#pragma once
#include "Render/Render.hpp"
#include "Render/VertexBufferLayout.hpp"
#include "defines.hpp"

namespace Hasbu {

struct VertexBuffer {
#ifdef OpenGL
    GraphicApi api = GraphicApi::OPENGL;
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
};

Shared<VertexBuffer> createVertexBuffer(float* data, const unsigned int size);

void bindVertexBuffer(Shared<VertexBuffer>& vbo);
void unbindVertexBuffer(const Shared<VertexBuffer>& vbo);
void setLayout(Shared<VertexBuffer>& vbo, const VertexBufferLayout& layout);

// class VertexBuffer {
// public:
//     VertexBuffer() = default;
//     virtual ~VertexBuffer() = default;

//     virtual void bind() = 0;
//     virtual void unbind() = 0;

//     virtual void setLayout(const VertexBufferLayout& layout) = 0;

//     static Shared<VertexBuffer> create(void* data, const unsigned int size);
// };

}