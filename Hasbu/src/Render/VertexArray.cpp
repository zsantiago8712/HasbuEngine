#include "Render/VertexArray.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include "defines.hpp"

namespace Hasbu {

using BindFn = void (*)(void* vao);
using UnbindFn = void (*)();
using AddVertexBufferFn = void (*)(void* vao, void* vbo);
using SetVertexBufferIndexFn = void (*)(void* vao, Shared<VertexBufferIndex>& vio);

struct VertexArrayFunctions {
    BindFn bind;
    UnbindFn unbind;
    AddVertexBufferFn addVertexBuffer;
    SetVertexBufferIndexFn setVertexBufferIndex;
};

static const VertexArrayFunctions vertexArrayFunctions[] = {
    { bindOpenGLVertexArray, unbindOpenGLVertexArray,
        addVertexBufferOpenGLVertexArray, setOpenGLVertexBufferIndex }
};

Shared<VertexArray>
createVertexArray()
{
#ifdef OpenGL
    return createShared<OpenGLVertexArray>();
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
}

void bindVertexArray(Shared<VertexArray>& vao)
{
    const auto& functions = vertexArrayFunctions[static_cast<int>(vao->api)];
    functions.bind(vao.get());
}
void unbindVertexArray(const Shared<VertexArray>& vao)
{
    const auto& functions = vertexArrayFunctions[static_cast<int>(vao->api)];
    functions.unbind();
}
void addVertexBuffer(Shared<VertexArray>& vao, Shared<VertexBuffer>& vbo)
{
    const auto& functions = vertexArrayFunctions[static_cast<int>(vao->api)];
    functions.addVertexBuffer(vao.get(), vbo.get());
}

void setVertexBufferIndex(Shared<VertexArray>& vao, Shared<VertexBufferIndex>& vbi)
{
    const auto& functions = vertexArrayFunctions[static_cast<int>(vao->api)];
    functions.setVertexBufferIndex(vao.get(), vbi);
}

// Shared<VertexArray> VertexArray::create()
// {
//     return createShared<OpenGLVertexArray>();
// }

}