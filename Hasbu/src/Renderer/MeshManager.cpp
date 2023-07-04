#include "Renderer/MeshManager.hpp"
#include "Renderer/RenderManager.hpp"
#include "Renderer/TextureManager.hpp"
#include "ShaderManager.hpp"
#include "Utilities/DynamicAllocator.hpp"
#include <fmt/core.h>

namespace Hasbu::Render {

struct MeshManager {

    static MeshManager& getInstance();

    Utils::Vector<Utils::Vector<Vertex>> m_vertex;
    Utils::Vector<Utils::Vector<unsigned int>> m_indices;
    Utils::Vector<Utils::Vector<unsigned int>> m_texturesID;

    Utils::Vector<unsigned int> m_VAOs;
    Utils::Vector<unsigned int> m_VBOs;
    Utils::Vector<unsigned int> m_EBOs;
};

MeshManager& MeshManager::getInstance()
{
    static MeshManager manager;
    return manager;
}

unsigned int createMesh(Utils::Vector<Vertex>& vertices, Utils::Vector<unsigned int>& indices, Utils::Vector<unsigned int>& textures)
{
    auto& manager = MeshManager::getInstance();

    const unsigned int vao = RenderManager::createVAO();
    const unsigned int vbo = RenderManager::createVBO(vertices);
    const unsigned int ebo = RenderManager::createEBO(indices);

    RenderManager::attribPointer(VertexAttrib::POSITIONS);
    RenderManager::attribPointer(VertexAttrib::NORMALS);
    RenderManager::attribPointer(VertexAttrib::TEXTURES_COORDS);

    manager.m_indices.push_back(indices);
    manager.m_vertex.push_back(vertices);
    manager.m_texturesID.push_back(textures);

    manager.m_VAOs.push_back(vao);
    manager.m_VBOs.push_back(vbo);
    manager.m_EBOs.push_back(ebo);

    return static_cast<unsigned int>(manager.m_vertex.size());
}

void drawMesh(const unsigned int meshID, const unsigned int shaderID)
{
    const auto& manager = MeshManager::getInstance();
    unsigned int unitTexture = 0;
    unsigned int diffuseNumber = 0;
    unsigned int specularNumber = 0;

    for (const auto& textureID : manager.m_texturesID[meshID - 1]) {

        TextureManager::activate(textureID, unitTexture);

        const auto textureType = TextureManager::getType(textureID);
        std::string name;
        if (textureType == TextureType::DIFFUSE) {
            name = fmt::format("material.diffuse");
            diffuseNumber++;
        } else if (textureType == TextureType::SPECULAR) {
            name = fmt::format("material.specular");
            specularNumber++;
        }

        if (unitTexture <= 1) {
            ShaderManager::setInt(shaderID, name, unitTexture);
        }
        unitTexture++;
    }

    RenderManager::bindVAO(manager.m_VAOs[meshID - 1]);
    RenderManager::drawElements(static_cast<unsigned int>(manager.m_indices[meshID - 1].size()));
    RenderManager::unbindVAO();
    TextureManager::deactivate();
}

};
