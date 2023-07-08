#include "Application/EventDispatcher.hpp"
#include "Application/Application.hpp"
#include "Application/KeyCodes.hpp"
#include "RenderManager.hpp"
// #include "Renderer/Camera.hpp"
#include "Renderer/CamaraSystem.hpp"

namespace Hasbu::Core {

std::array<EventDispatcher::EventKeyFn, 3> EventDispatcher::key_events_functions;
std::array<EventDispatcher::EventMouseFn, 2> EventDispatcher::mouse_events_functions;

EventDispatcher::EventDispatcher()
{

    EventDispatcher::mouse_events_functions = {

        [](const double xpos, const double ypos) {
            Render::CamaraSystem::processMauseInputCamera(xpos, ypos);
        },
        [](const double xpos, const double ypos) {
            Render::CamaraSystem::processMauseInputScrollCamera(xpos, ypos);
        }

    };

    // auto& app = Application::getInstace();
    EventDispatcher::key_events_functions = {
        []() {
            Render::CamaraSystem::processKeyBoardInputCamera(Render::RenderManager::getLastDelta());
        },

        // [&camera]() {
        //     camera.proccesKeyBoard();
        // },
        // [&app](const int& key) {
        //     app.proccesInput(key);
        // },

        // [&app]() {
        //     app.proccesInput();
        // }
    };
}

void EventDispatcher::dispatchKeyEvent(Event event)
{
    if (event != Event::UNKNOWN_EVENT) {
        EventDispatcher::key_events_functions[static_cast<unsigned int>(event)]();
    }
}

void EventDispatcher::dispatchMousEvent(MouseEvent event, const double xpos, const double ypos)
{
    EventDispatcher::mouse_events_functions[static_cast<unsigned int>(event)](xpos, ypos);
}

Event getEvent(Hasbu::KeyCode key)
{
    switch (key) {
    case Hasbu::KeyCode::W:
    case Hasbu::KeyCode::S:
    case Hasbu::KeyCode::D:
    case Hasbu::KeyCode::A:
    case Hasbu::KeyCode::KEY_1:
    case Hasbu::KeyCode::KEY_2:
    case Hasbu::KeyCode::KEY_3:
        return Event::CAMARA;

    case Hasbu::KeyCode::ESCAPE:
        return Event::APPLCATION;
    }

    return Event::UNKNOWN_EVENT;
}

}
