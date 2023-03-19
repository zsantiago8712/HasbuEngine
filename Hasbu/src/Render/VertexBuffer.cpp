#include "Render/VertexBuffer.hpp"
#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"
#include "defines.hpp"

namespace Hasbu {

using BindFn = void (*)(void* vbo);
using UnbindFn = void (*)();
using setLayoutFn = void (*)(void* vbo, const VertexBufferLayout& layout);

struct VertexBufferFunctions {
    BindFn bind;
    UnbindFn unbind;
    setLayoutFn setLayout;
};

static const VertexBufferFunctions vertexBufferFunctions[] = {
    { openGLVertexBufferBind, openGLVertexBufferUnbind, openGLSetLayout }
};

Shared<VertexBuffer> createVertexBuffer(float* data, const unsigned int size)
{
#ifdef OpenGL
    return createShared<OpenGLVertexBuffer>(data, size);
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
}

void bindVertexBuffer(Shared<VertexBuffer>& vbo)
{
    const auto& functions = vertexBufferFunctions[static_cast<int>(vbo->api)];
    functions.bind(vbo.get());
}

void unbindVertexBuffer(const Shared<VertexBuffer>& vbo)
{
    const auto& functions = vertexBufferFunctions[static_cast<int>(vbo->api)];
    functions.unbind();
}

void setLayout(Shared<VertexBuffer>& vbo, const VertexBufferLayout& layout)
{
    const auto& functions = vertexBufferFunctions[static_cast<int>(vbo->api)];
    functions.setLayout(vbo.get(), layout);
}

// Shared<VertexBuffer> VertexBuffer::create(void* data, const unsigned int size)
// {
//     return createShared<OpenGLVertexBuffer>(data, size);
// }

}