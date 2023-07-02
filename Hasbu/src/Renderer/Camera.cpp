#include "Renderer/Camera.hpp"
#include "Application/Input.hpp"
#include "ImGuiLayer/ImguiLayer.hpp"
#include "Utilities/Logger.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Hasbu::Render {

Camera::MovementType Camera::m_movementType = Camera::MovementType::STATIC;

Camera::Camera()
{
    this->updateVectors();
}

void Camera::proccesKeyBoard(const double delta)
{

    if (Core::isKeyBeenPressed(KeyCode::KEY_1)) {
        Camera::m_movementType = Camera::MovementType::STATIC;
    } else if (Core::isKeyBeenPressed(KeyCode::KEY_2)) {
        Camera::m_movementType = Camera::MovementType::FPS;
    } else if (Core::isKeyBeenPressed(KeyCode::KEY_3)) {
        Camera::m_movementType = Camera::MovementType::FREE;
    }

    if ((Camera::m_movementType != Camera::MovementType::STATIC) && (!Gui::ImGuiLayer::wantCaptureKeyboard())) {
        m_speed = static_cast<float>(2.5 * delta);
        this->updatePosition();
    }
}

glm::mat4 Camera::getViewMatrix() const
{
    // NOTE: Se suman los vectores para asegurar que la camara siga viendo
    //  al target (front)
    //
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::proccesMouseInput(const double xpos, const double ypos)
{

    if (Camera::m_movementType != Camera::MovementType::STATIC) {
        static bool first = true;

        const auto new_xpos = static_cast<float>(xpos);
        const auto new_ypos = static_cast<float>(ypos);

        if (first) {
            m_lastX = new_xpos;
            m_lastY = new_ypos;
            first = false;
        }

        float xoffset = new_xpos - m_lastX;
        float yoffset = m_lastY - new_ypos;

        m_lastX = new_xpos;
        m_lastY = new_ypos;

        xoffset *= m_sensitivity;
        yoffset *= m_sensitivity;

        m_yaw += xoffset;
        m_pitch += yoffset;

        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        } else if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }

        this->updateVectors();
    }
}

void Camera::processScroll([[maybe_unused]] const double xpos, const double ypos)
{

    m_fov -= static_cast<float>(ypos);
    if (m_fov < 1.0f) {
        m_fov = 1.0f;
    } else if (m_fov > 45.0f) {
        m_fov = 45.0f;
    }
}

void Camera::updatePosition()
{
    if (Core::isKeyBeenPressed(KeyCode::W)) {
        m_position += m_speed * m_front;
        HASBU_DEBUG("Move forward");
    } else if (Core::isKeyBeenPressed(KeyCode::S)) {
        m_position -= m_speed * m_front;
        HASBU_DEBUG("Move backards");
    } else if (Core::isKeyBeenPressed(KeyCode::A)) {
        m_position -= m_right * m_speed;
        HASBU_DEBUG("Move to the Left");
    } else if (Core::isKeyBeenPressed(KeyCode::D)) {
        m_position += m_right * m_speed;
        HASBU_DEBUG("Move to the Left");
    }else if(Core::isKeyBeenPressed(KeyCode::SPACE)) {
        m_position += m_speed * m_up;
        HASBU_DEBUG("Move up");
    }else if(Core::isKeyBeenPressed(KeyCode::LEFT_SHIFT)) {
        m_position -= m_up * m_speed;
        HASBU_DEBUG("Move Down");
    }

    // NOTE: Con esto mantienes al jugador sobre el piso
    if (Camera::m_movementType == Camera::MovementType::FPS) {
        m_position.y = 0;
    }
}

void Camera::updateVectors()
{
    const glm::vec3 direction {
        cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
        sin(glm::radians(m_pitch)),
        sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))
    };

    m_front = glm::normalize(direction);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

}
