#include "Render/VertexIndexBuffer.hpp"
#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include "core/Configuration.hpp"
#include "defines.hpp"
#include <fmt/core.h>

using BindFn = void (*)(Hasbu::Shared<Hasbu::VertexBufferIndex>& vio);
using UnbindFn = void (*)();

struct VertexBufferIndexFunctions {

    VertexBufferIndexFunctions();

    BindFn bind;
    UnbindFn unbind;
};

static const VertexBufferIndexFunctions vbi_functions;

namespace Hasbu {

Shared<VertexBufferIndex>
createVertexBufferIndex(unsigned int* indices, const unsigned int count)
{
    auto& configs = HasbuConfig::Configurations::getInstance();
    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:
        return createShared<OpenGLVertexBufferIndex>(indices, count);
        break;
    case HasbuConfig::GraphicApi::VULKAN:
        fmt::print("Vulkan is not available right now");
        return nullptr;
        break;
    }
}

void bindVertexBufferIndex(Shared<VertexBufferIndex>& vio)
{
    vbi_functions.bind(vio);
}

void unbindVertexBufferIndex(const Shared<VertexBufferIndex>& vio)
{
    vbi_functions.unbind();
}

}

VertexBufferIndexFunctions::VertexBufferIndexFunctions()
{

    auto& configs = HasbuConfig::Configurations::getInstance();
    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:
        this->bind = Hasbu::binOpenGLVertexBufferIndex;
        this->unbind = Hasbu::unbindOpenGLVertexBufferIndex;
        break;
    case HasbuConfig::GraphicApi::VULKAN:
        fmt::print("Vulkan is not available right now");
        break;
    }
}
