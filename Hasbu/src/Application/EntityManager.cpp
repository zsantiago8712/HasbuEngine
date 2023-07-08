#include "Application/EntityManager.hpp"
#include "Components/MaterailComponents.hpp"
#include "Components/MeshComponents.hpp"
#include "Components/RenderComponents.hpp"
#include "RenderManager.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/ShaderManager.hpp"
#include "Renderer/TextureManager.hpp"
#include "Utilities/Logger.hpp"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include <fmt/core.h>

namespace Hasbu::Core {

EntityManager& EntityManager::getInstance()
{
    static EntityManager manager;
    return manager;
}

void EntityManager::drawEntities()
{
    const auto& entityManager = EntityManager::getInstance();
    const auto view = entityManager.registry.view<Components::RenderComponents, Components::MeshComponents, Components::MaterialComponents>();

    for (const auto& entity : view) {

        const auto& renderComponent = view.get<Components::RenderComponents>(entity);
        const auto& meshComponent = view.get<Components::MeshComponents>(entity);
        const auto& materialComponent = view.get<Components::MaterialComponents>(entity);

        Render::ShaderManager::bind(materialComponent.shaderID);
        unsigned int unitTexture = 0;
        for (const auto texture : materialComponent.textures) {
            Render::TextureManager::activate(texture, unitTexture);
            const auto textureType = Render::TextureManager::getType(texture);
            std::string name;
            if (textureType == Render::TextureType::DIFFUSE) {
                name = fmt::format("material.diffuse");
                // diffuseNumber++;
            } else if (textureType == Render::TextureType::SPECULAR) {
                name = fmt::format("material.specular");
                // specularNumber++;
            }

            if (unitTexture <= 1) {
                Render::ShaderManager::setInt(materialComponent.shaderID, name, unitTexture);
            }
            unitTexture++;
        }

        Render::RenderManager::bindVAO(renderComponent.vao);
        Render::RenderManager::drawElements(meshComponent.totalIndexCount);
        // Render::RenderManager::unbindVAO();
        Render::TextureManager::deactivate();
    }
}

void EntityManager::clear(unsigned int e)
{
    auto& entityManager = EntityManager::getInstance();

    entityManager.registry.destroy(static_cast<entt::entity>(e));

    entityManager.registry.clear<Components::RenderComponents>();
    // entityManager.registry.clear();
    // if (entityManager.registry.empty()) {
    //     HASBU_DEBUG("EntityManager::clear");
    // }
}

}
