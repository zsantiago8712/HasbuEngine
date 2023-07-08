#pragma once
#include "Components/CamaraComponents.hpp"

namespace Hasbu::Render {

struct CamaraSystem {

    static void initCamaraSystem();

    static unsigned int createCamera();

    static const Hasbu::Components::CamaraComponents& getComponents(const unsigned int camaraID);
    static const Hasbu::Components::CamaraComponents& getActiveCamaraComponents();

    static const Hasbu::Components::CamaraComponents& updateActiveCamara();

    static void processKeyBoardInputCamera(const double delta);
    static void processMauseInputCamera(const double xpos, const double ypos);
    static void processMauseInputScrollCamera([[maybe_unused]] const double xpos, const double ypos);

    static unsigned int m_activeCamera;
};

}