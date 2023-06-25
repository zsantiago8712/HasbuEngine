#include "Renderer/Camera.hpp"
#include "Application/Input.hpp"
#include "Application/KeyCodes.hpp"
#include "Renderer/Render.hpp"
#include "Utilities/Logger.hpp"
namespace Hasbu::Render {

void Camera::proccesKeyBoard(const double delta)
{

    // this->speed = 2.5 * Renderer::getDeltaTime();
    this->m_speed = 2.5 * delta;

    if (Core::isKeyBeenPressed(Hasbu::KeyCode::W)) {
        this->m_position += Camera::m_speed * this->m_front;
        HASBU_DEBUG("Move forward");
    } else if (Core::isKeyBeenPressed(Hasbu::KeyCode::S)) {
        this->m_position -= Camera::m_speed * this->m_front;
        HASBU_DEBUG("Move backards");
    } else if (Core::isKeyBeenPressed(Hasbu::KeyCode::A)) {
        this->m_position -= la::normalize(la::cross(this->m_front, this->m_up)) * Camera::m_speed;
        HASBU_DEBUG("Move to the Left");
    } else if (Core::isKeyBeenPressed(Hasbu::KeyCode::D)) {
        this->m_position += la::normalize(la::cross(this->m_front, this->m_up)) * Camera::m_speed;
        HASBU_DEBUG("Move to the Left");
    }
}

la::mat4 Camera::getViewMatrix() const
{
    // NOTE: Se suman los vectores para asegurar que la camara siga viendo
    //  al target (front)
    //
    return la::lookAt(this->m_position, this->m_position + this->m_front, this->m_up);
}

void Camera::proccesMouseInput(const double xpos, const double ypos)
{
    static bool first = true;
    const auto new_xpos = static_cast<float>(xpos);
    const auto new_ypos = static_cast<float>(ypos);

    if (first) {
        m_lastX = new_xpos;
        m_lastY = new_ypos;
        first = false;
    }

    auto xoffset = (new_xpos - m_lastX) * m_sensitivity;
    auto yoffset = (new_ypos - m_lastY) * m_sensitivity;

    m_lastX = new_xpos;
    m_lastY = new_ypos;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (m_pitch > 89.0f) {
        m_pitch = 89.0f;
    }

    if (m_pitch < -89.0f) {
        m_pitch = -89.0f;
    }

    la::vec3 direction;

    direction.x = cos(la::to_radians(m_yaw)) * cos(la::to_radians(m_pitch));
    direction.y = sin(la::to_radians(m_pitch));
    direction.z = sin(la::to_radians(m_yaw)) * cos(la::to_radians(m_pitch));
    this->m_front = la::normalize(direction);

    HASBU_DEBUG("CAMERA FRONT X:{}, Y:{}, Z:{}", direction.x, direction.y, direction.z);
}

}
