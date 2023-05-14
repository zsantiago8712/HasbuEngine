#include "Render/VertexBuffer.hpp"
#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"
#include "core/Configuration.hpp"
#include "defines.hpp"
#include <fmt/core.h>

using BindFn = void (*)(Hasbu::Shared<Hasbu::VertexBuffer>& vbo);
using UnbindFn = void (*)();
using setLayoutFn = void (*)(Hasbu::Shared<Hasbu::VertexBuffer>& vbo, const Hasbu::VertexBufferLayout& layout);

struct VertexBufferFunctions {

    VertexBufferFunctions();
    BindFn bind;
    UnbindFn unbind;
    setLayoutFn setLayout;
};

static const VertexBufferFunctions vbo_functions;

namespace Hasbu {

Shared<VertexBuffer> createVertexBuffer(float* data, const unsigned int size)
{
    auto& configs = HasbuConfig::Configurations::getInstance();
    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:
        return createShared<OpenGLVertexBuffer>(data, size);
        break;
    case HasbuConfig::GraphicApi::VULKAN:
        fmt::print("Platfor is not available right now");
        return nullptr;
        break;
    }
}

void bindVertexBuffer(Shared<VertexBuffer>& vbo)
{
    vbo_functions.bind(vbo);
}

void unbindVertexBuffer(const Shared<VertexBuffer>& vbo)
{
    vbo_functions.unbind();
}

void setLayout(Shared<VertexBuffer>& vbo, const VertexBufferLayout& layout)
{
    vbo_functions.setLayout(vbo, layout);
}

}

VertexBufferFunctions::VertexBufferFunctions()
{

    auto& configs = HasbuConfig::Configurations::getInstance();
    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:
        this->bind = Hasbu::openGLVertexBufferBind;
        this->unbind = Hasbu::openGLVertexBufferUnbind;
        this->setLayout = Hasbu::openGLSetLayout;
        break;
    case HasbuConfig::GraphicApi::VULKAN:
        fmt::print("Platfor is not available right now");
        break;
    }
}
