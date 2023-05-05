#pragma once
#include "LA/la.hpp"
#include "details/_vec3_f.hpp"

namespace Hasbu {

struct Camera {

    la::vec3 m_postion;
    la::vec3 m_camera_view_target;
    la::vec3 m_camera_up;
};

}