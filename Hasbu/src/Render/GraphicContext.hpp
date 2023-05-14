#pragma once

#include "Render/Render.hpp"
#include "defines.hpp"

namespace Hasbu {

struct GraphicsContext {
    GraphicsContext() = default;
};

Unique<GraphicsContext> createGraphicsContext(void* window);
void initializeGraphicsContext(Unique<GraphicsContext>& context);
void swapBuffers(Unique<GraphicsContext>& context);
float getDeltaTime(Unique<GraphicsContext>& context);
}
