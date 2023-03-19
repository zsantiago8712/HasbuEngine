#pragma once

#include "Render/Render.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexIndexBuffer.hpp"
#include "defines.hpp"

namespace Hasbu {

struct VertexArray {
#ifdef OpenGL
    GraphicApi api = GraphicApi::OPENGL;
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
};

Shared<VertexArray> createVertexArray();
void bindVertexArray(Shared<VertexArray>& vao);
void unbindVertexArray(const Shared<VertexArray>& vao);
void addVertexBuffer(Shared<VertexArray>& vao, Shared<VertexBuffer>& vbo);
void setVertexBufferIndex(Shared<VertexArray>& vao, Shared<VertexBufferIndex>& vbi);

// class VertexArray {

// public:
//     VertexArray() = default;
//     virtual ~VertexArray() = default;

//     virtual void bind() = 0;
//     virtual void unbind() = 0;
//     // virtual void addBuffer() = 0;

//     static Shared<VertexArray> create();
// };

}