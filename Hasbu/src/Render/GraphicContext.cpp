#include "Render/GraphicContext.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"
#include "core/Configuration.hpp"
#include "defines.hpp"
#include <fmt/core.h>

using InitializeFn = void (*)(Hasbu::Unique<Hasbu::GraphicsContext>& context);
using SwapBuffersFn = void (*)(Hasbu::Unique<Hasbu::GraphicsContext>& context);
using GetDeltaTime = float (*)(Hasbu::Unique<Hasbu::GraphicsContext>& context);

/**
 * @brief Function tables
 **/
struct GraphicsContextApiFunctions {

    GraphicsContextApiFunctions();
    InitializeFn initialize;
    SwapBuffersFn swapBuffers;
    GetDeltaTime getDeltaTime;
};

static const GraphicsContextApiFunctions graphics_context_functions;

namespace Hasbu {

Unique<GraphicsContext> createGraphicsContext(void* window)
{
    auto& configs = HasbuConfig::Configurations::getInstance();

    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:
        return createUnique<OpenGLContext>(static_cast<GLFWwindow*>(window));
        break;
    case HasbuConfig::GraphicApi::VULKAN:
        return nullptr;
        break;

    default:
        return nullptr;
        break;
    }
}

void initializeGraphicsContext(Unique<GraphicsContext>& context)
{
    graphics_context_functions.initialize(context);
}

void swapBuffers(Unique<GraphicsContext>& context)
{
    graphics_context_functions.swapBuffers(context);
}

float getDeltaTime(Unique<GraphicsContext>& context)
{
    return graphics_context_functions.getDeltaTime(context);
}

} // namespace Hasbu

GraphicsContextApiFunctions::GraphicsContextApiFunctions()
{
    auto& configs = HasbuConfig::Configurations::getInstance();

    switch (configs.getGraphicsApi()) {
    case HasbuConfig::GraphicApi::OPENGL:

        this->initialize = Hasbu::initializeOpenGL;
        this->swapBuffers = Hasbu::swapBuffersOpenGL;
        this->getDeltaTime = Hasbu::getDeltaTimeOpenGL;
        break;
    case HasbuConfig::GraphicApi::VULKAN:
        this->initialize = Hasbu::initializeOpenGL;
        this->swapBuffers = Hasbu::swapBuffersOpenGL;
        this->getDeltaTime = Hasbu::getDeltaTimeOpenGL;
        break;
    }
}
