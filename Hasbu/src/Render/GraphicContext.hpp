#pragma once

#include "Render/Render.hpp"
#include "defines.hpp"

namespace Hasbu {

struct GraphicsContext {
    GraphicsContext() = default;

#ifdef OpenGL
    GraphicApi api = GraphicApi::OPENGL;
#elif defined Vulkan
    GraphicApi api = GraphicApi::VULKAN;
#endif
};

Shared<GraphicsContext> createGraphicsContext(void* window);

void initializeGraphicsContext(Shared<GraphicsContext>& context);
void swapBuffers(Shared<GraphicsContext>& context);

// class GraphicsContext {

// public:
//     GraphicsContext() = default;
//     virtual ~GraphicsContext() = default;

//     virtual void initialize() = 0;
//     virtual void swapBuffers() = 0;

//     static Shared<GraphicsContext> create(GraphicApi api, void* window);
// };

}