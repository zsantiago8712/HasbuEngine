#pragma once

#include "Application/KeyCodes.hpp"
#include "DynamicAllocator.hpp"
#include <array>
#include <functional>

namespace Hasbu::Render {
struct Camera;
};

namespace Hasbu::Core {

enum class Event : unsigned int {

    CAMARA = 1,
    APPLCATION = 2,
    UNKNOWN_EVENT,
};

enum class MouseEvent : unsigned int {
    CURSOR = 0,
    SCROLL = 1
};

struct EventDispatcher {

    using EventKeyFn = std::function<void()>;
    using EventMouseFn = std::function<void(double xpos, double ypos)>;

    explicit EventDispatcher(Render::Camera& camera);

    static void dispatchKeyEvent(Event event);
    static void dispatchMousEvent(MouseEvent event, const double xpos, const double ypos);

    static std::array<EventKeyFn, 3> key_events_functions;

    // TODO: acabar de hacer las funcinoes para el mouse input
    static std::array<EventMouseFn, 2> mouse_events_functions;
};

Event getEvent(Hasbu::KeyCode key);

}
