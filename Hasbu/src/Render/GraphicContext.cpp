#include "Render/GraphicContext.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"
#include "defines.hpp"
#include <fmt/core.h>

using InitializeFn = void (*)(void* context);
using SwapBuffersFn = void (*)(void* context);
using GetDeltaTime = float (*)(void* context);

struct GraphicsContextApiFunctions {
    InitializeFn initialize;
    SwapBuffersFn swapBuffers;
    GetDeltaTime getDeltaTime;
};

namespace Hasbu {

static const GraphicsContextApiFunctions graphicsContextApiFunctions[] = {
    { initializeOpenGL, swapBuffersOpenGL, getDeltaTimeOpenGL }
};

Shared<GraphicsContext> createGraphicsContext(void* window)
{
#ifdef OpenGL
    return createShared<OpenGLContext>(window);
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
}

void initializeGraphicsContext(Shared<GraphicsContext>& context)
{
    const auto& function = graphicsContextApiFunctions[static_cast<int>(context->api)];
    function.initialize(context.get());
}

void swapBuffers(Shared<GraphicsContext>& context)
{
    const auto& function = graphicsContextApiFunctions[static_cast<int>(context->api)];
    function.swapBuffers(context.get());
}

float getDeltaTime(Shared<GraphicsContext>& context)
{
    const auto& function = graphicsContextApiFunctions[static_cast<int>(context->api)];
    return function.getDeltaTime(context.get());
}

// Shared<GraphicsContext> GraphicsContext::create(GraphicApi api, void* window)
// {

//     switch (api) {
//     case GraphicApi::OpenGL:
//         return createShared<OpenGLContext>(window);
//     case GraphicApi::Vulkan:
//         fmt::print(stderr, "Vulkan is not as Graphic Api yet");
//         return nullptr;

//     default:
//         fmt::print(stderr, "Unknown Graphic Api");
//         return nullptr;
//     }
// }

}  // namespace Hasbu
