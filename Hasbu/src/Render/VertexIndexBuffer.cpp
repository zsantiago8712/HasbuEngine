#include "Render/VertexIndexBuffer.hpp"
#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"
#include "defines.hpp"

namespace Hasbu {

using BindFn = void (*)(void* vio);
using UnbindFn = void (*)();

struct VertexBufferIndexFunctions {

    BindFn bind;
    UnbindFn unbind;
};

static const VertexBufferIndexFunctions vertexBufferIndexFunctions[] = {
    { binOpenGLVertexBufferIndex, unbindOpenGLVertexBufferIndex }
};

Shared<VertexBufferIndex>
createVertexBufferIndex(unsigned int* indices, const unsigned int count)
{
#ifdef OpenGL
    return createShared<OpenGLVertexBufferIndex>(indices, count);
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
}

void bindVertexBufferIndex(Shared<VertexBufferIndex>& vio)
{
    const auto& functions = vertexBufferIndexFunctions[static_cast<int>(vio->api)];
    functions.bind(vio.get());
}

void unbindVertexBufferIndex(const Shared<VertexBufferIndex>& vio)
{
    const auto& functions = vertexBufferIndexFunctions[static_cast<int>(vio->api)];
    functions.unbind();
}

}
