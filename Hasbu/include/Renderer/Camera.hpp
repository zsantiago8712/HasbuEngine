#pragma once
#include <glm/glm.hpp>
namespace Hasbu::Render {

struct Camera {

    explicit Camera();

    void proccesKeyBoard(const double delta);
    void proccesMouseInput(const double xpos, const double ypos);
    void processScroll(const double xpos, const double ypos);

    glm::vec3 m_position { 0.0f, 0.0f, 3.0f };
    glm::vec3 m_front { 0.0f, 0.0f, -1.0f };
    glm::vec3 m_right;
    glm::vec3 m_up { 0.0f, 1.0f, 0.0f };

    glm::mat4 getViewMatrix() const;

    float m_speed = 0.5f;
    float m_sensitivity = 0.1f;
    float m_fov = 45.0f;

    enum class MovementType : unsigned int {
        STATIC = 0,
        FPS = 1,
        FREE = 2
    };

private:
    void updateVectors();
    void updatePosition();

    static MovementType m_movementType;

    float m_yaw
        = -90.0f;
    float m_pitch = 0.0f;

    float m_lastX = 400.0f;
    float m_lastY = 300.0f;

    glm::vec3 m_worldUp { 0.0, 1.0, 0.0f };
};

}
