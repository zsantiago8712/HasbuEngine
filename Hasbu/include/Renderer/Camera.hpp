#pragma once
#include "LA/la.hpp"

namespace Hasbu::Render {

struct Camera {

    // Camera() { Camera::speed = 0.5f; };

    la::vec3 m_position { 0.0f, 0.0f, 3.0f };
    la::vec3 m_front { 0.0f, 0.0f, -1.0f };
    la::vec3 m_right;
    la::vec3 m_up { 0.0f, 1.0f, 0.0f };

    void proccesKeyBoard(const double delta);
    void proccesMouseInput(const double xpos, const double ypos);

    la::mat4 getViewMatrix() const;

    float m_speed = 0.5f;
    float m_sensitivity = 0.1f;

private:
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;

    float m_lastX = 400.0f;
    float m_lastY = 450.0f;
};

}
