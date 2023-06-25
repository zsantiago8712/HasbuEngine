#pragma once
#include "LA/la.hpp"

namespace Hasbu::Render {

struct Vertex {
    la::vec3 m_position;
    // // la::vec3 normal;
    la::vec2 m_textCoords;
};

}
