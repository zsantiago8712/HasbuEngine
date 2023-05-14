#include "Render/VertexArray.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include "Render/VertexBuffer.hpp"
#include "core/Configuration.hpp"
#include "defines.hpp"
#include <fmt/core.h>

using BindFn = void (*)(Hasbu::Shared<Hasbu::VertexArray>& vao);
using UnbindFn = void (*)();
using AddVertexBufferFn = void (*)(Hasbu::Shared<Hasbu::VertexArray>& vao, Hasbu::Shared<Hasbu::VertexBuffer>& vbo);
using SetVertexBufferIndexFn = void (*)(Hasbu::Shared<Hasbu::VertexArray>& vao, Hasbu::Shared<Hasbu::VertexBufferIndex>& vio);

struct VertexArrayFunctions {

    VertexArrayFunctions();
    BindFn bind;
    UnbindFn unbind;
    AddVertexBufferFn addVertexBuffer;
    SetVertexBufferIndexFn setVertexBufferIndex;
};

static const VertexArrayFunctions varray_functions;

namespace Hasbu {

Shared<VertexArray>
createVertexArray()
{
    auto& configs = HasbuConfig::Configurations::getInstance();
    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:
        return createShared<OpenGLVertexArray>();
        break;
    case HasbuConfig::GraphicApi::VULKAN:
        fmt::print("Vulkan is not available right now");
        return nullptr;
        break;
    }
}

void bindVertexArray(Shared<VertexArray>& vao)
{
    varray_functions.bind(vao);
}
void unbindVertexArray(const Shared<VertexArray>& vao)
{
    varray_functions.unbind();
}
void addVertexBuffer(Shared<VertexArray>& vao, Shared<VertexBuffer>& vbo)
{
    varray_functions.addVertexBuffer(vao, vbo);
}

void setVertexBufferIndex(Shared<VertexArray>& vao, Shared<VertexBufferIndex>& vbi)
{
    varray_functions.setVertexBufferIndex(vao, vbi);
}

}

VertexArrayFunctions::VertexArrayFunctions()
{
    auto& configs = HasbuConfig::Configurations::getInstance();
    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:
        this->bind = Hasbu::bindOpenGLVertexArray;
        this->unbind = Hasbu::unbindOpenGLVertexArray;
        this->addVertexBuffer = Hasbu::addVertexBufferOpenGLVertexArray;
        this->setVertexBufferIndex = Hasbu::setOpenGLVertexBufferIndex;
        break;

    case HasbuConfig::GraphicApi::VULKAN:
        fmt::print("Vulkan is not available right now");
        break;
    }
}
