#pragma once
#include <glm/glm.hpp>

namespace Hasbu::Components {

struct CamaraComponents {

    enum class MovementType : unsigned int {
        STATIC = 0,
        FPS = 1,
        FREE = 2
    };

    glm::vec3 position = glm::vec3 { 0.0f, 0.0f, 3.0f };
    glm::vec3 front = glm::vec3 { 0.0f, 0.0f, -1.0f };
    glm::vec3 right;
    glm::vec3 up = glm::vec3 { 0.0f, 1.0f, 0.0f };
    glm::vec3 worldUp = glm::vec3 { 0.0, 1.0, 0.0f };

    glm::mat4 viewMatrix;

    float speed = 0.5f;
    float sensitivity = 0.1f;
    float fov = 45.0f;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 450.0f;
    float lastY = 450.0f;

    MovementType movementType = MovementType::STATIC;
};

}