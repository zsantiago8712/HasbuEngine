#include "Renderer/CamaraSystem.hpp"
#include "Application/EntityManager.hpp"
#include "Application/Input.hpp"
#include "ImGuiLayer/ImguiLayer.hpp"
#include "Utilities/Logger.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Hasbu::Render {

void updateCamaraPosition(Components::CamaraComponents& camaraComponents);
static void updateCameraVectors(Components::CamaraComponents& camaraComponents);

unsigned int CamaraSystem::m_activeCamera = 0;

void CamaraSystem::initCamaraSystem()
{
    CamaraSystem::m_activeCamera = 0;
}

unsigned int CamaraSystem::createCamera()
{
    auto& entityManager = Core::EntityManager::getInstance();

    entt::entity newCamara = entityManager.registry.create();
    entityManager.registry.emplace<Components::CamaraComponents>(newCamara);

    CamaraSystem::m_activeCamera = static_cast<unsigned>(newCamara);
    return static_cast<unsigned int>(newCamara);
}

const Components::CamaraComponents& CamaraSystem::getComponents(const unsigned int camaraID)
{
    const auto& entityManager = Core::EntityManager::getInstance();
    return entityManager.registry.get<Components::CamaraComponents>(static_cast<entt::entity>(camaraID));
}

const Components::CamaraComponents& CamaraSystem::getActiveCamaraComponents()
{
    const auto& entityManager = Core::EntityManager::getInstance();
    return entityManager.registry.get<Components::CamaraComponents>(static_cast<entt::entity>(CamaraSystem::m_activeCamera));
}

const Components::CamaraComponents& CamaraSystem::updateActiveCamara()
{
    auto& entityManager = Core::EntityManager::getInstance();
    auto& components = entityManager.registry.get<Components::CamaraComponents>(static_cast<entt::entity>(CamaraSystem::m_activeCamera));

    components.viewMatrix = glm::lookAt(components.position, components.position + components.front, components.up);
    return components;
}

void CamaraSystem::processKeyBoardInputCamera(const double delta)
{

    auto& entityManager = Core::EntityManager::getInstance();
    auto& components = entityManager.registry.get<Components::CamaraComponents>(static_cast<entt::entity>(CamaraSystem::m_activeCamera));

    if (Core::isKeyBeenPressed(KeyCode::KEY_1)) {
        components.movementType = Components::CamaraComponents::MovementType::STATIC;
        return;
    } else if (Core::isKeyBeenPressed(KeyCode::KEY_2)) {
        components.movementType = Components::CamaraComponents::MovementType::FPS;
        return;
    } else if (Core::isKeyBeenPressed(KeyCode::KEY_3)) {
        components.movementType = Components::CamaraComponents::MovementType::FREE;
        return;
    }

    if (components.movementType != Components::CamaraComponents::MovementType::STATIC && !Gui::ImGuiLayer::wantCaptureKeyboard()) {
        components.speed = static_cast<float>(2.5 * delta);
        updateCamaraPosition(components);
    }
}

void CamaraSystem::processMauseInputCamera(const double xpos, const double ypos)
{
    auto& entityManager = Core::EntityManager::getInstance();
    auto& components = entityManager.registry.get<Components::CamaraComponents>(static_cast<entt::entity>(CamaraSystem::m_activeCamera));

    if (components.movementType != Components::CamaraComponents::MovementType::STATIC) {
        static bool first = true;

        const auto new_xpos = static_cast<float>(xpos);
        const auto new_ypos = static_cast<float>(ypos);

        if (first) {
            components.lastX = new_xpos;
            components.lastY = new_ypos;
            first = false;
        }

        float xoffset = new_xpos - components.lastX;
        float yoffset = components.lastY - new_ypos;

        components.lastX = new_xpos;
        components.lastY = new_ypos;

        xoffset *= components.sensitivity;
        yoffset *= components.sensitivity;

        components.yaw += xoffset;
        components.pitch += yoffset;

        if (components.pitch > 89.0f) {
            components.pitch = 89.0f;
        } else if (components.pitch < -89.0f) {
            components.pitch = -89.0f;
        }

        updateCameraVectors(components);
    }
}

void CamaraSystem::processMauseInputScrollCamera([[maybe_unused]] const double xpos, const double ypos)
{
    auto& entityManager = Core::EntityManager::getInstance();
    auto& components = entityManager.registry.get<Components::CamaraComponents>(static_cast<entt::entity>(CamaraSystem::m_activeCamera));

    components.fov -= static_cast<float>(ypos);
    if (components.fov < 1.0f) {
        components.fov = 1.0f;
    } else if (components.fov > 45.0f) {
        components.fov = 45.0f;
    }
}

// TODO: checar si seria mejor hacerlo una funcion parte de la clase
void updateCamaraPosition(Components::CamaraComponents& camaraComponents)
{

    if (Core::isKeyBeenPressed(KeyCode::W)) {
        camaraComponents.position += camaraComponents.speed * camaraComponents.front;
        HASBU_DEBUG("Move forward");
    } else if (Core::isKeyBeenPressed(KeyCode::S)) {
        camaraComponents.position -= camaraComponents.speed * camaraComponents.front;
        HASBU_DEBUG("Move backards");
    } else if (Core::isKeyBeenPressed(KeyCode::A)) {
        camaraComponents.position -= camaraComponents.right * camaraComponents.speed;
        HASBU_DEBUG("Move to the Left");
    } else if (Core::isKeyBeenPressed(KeyCode::D)) {
        camaraComponents.position += camaraComponents.right * camaraComponents.speed;
        HASBU_DEBUG("Move to the Left");
    } else if (Core::isKeyBeenPressed(KeyCode::SPACE)) {
        camaraComponents.position += camaraComponents.speed * camaraComponents.up;
        HASBU_DEBUG("Move up");
    } else if (Core::isKeyBeenPressed(KeyCode::LEFT_SHIFT)) {
        camaraComponents.position -= camaraComponents.up * camaraComponents.speed;
        HASBU_DEBUG("Move Down");
    }

    // NOTE: Con esto mantienes al jugador sobre el piso
    if (camaraComponents.movementType == Components::CamaraComponents::MovementType::FPS) {
        camaraComponents.position.y = 0;
    }
}

// TODO: checar si seria mejor hacerlo una funcion parte de la clase
static void updateCameraVectors(Components::CamaraComponents& camaraComponents)
{

    const glm::vec3 direction {
        cos(glm::radians(camaraComponents.yaw)) * cos(glm::radians(camaraComponents.pitch)),
        sin(glm::radians(camaraComponents.pitch)),
        sin(glm::radians(camaraComponents.yaw)) * cos(glm::radians(camaraComponents.pitch))
    };

    camaraComponents.front = glm::normalize(direction);

    camaraComponents.right = glm::normalize(glm::cross(camaraComponents.front, camaraComponents.worldUp));
    camaraComponents.up = glm::normalize(glm::cross(camaraComponents.right, camaraComponents.front));
}

}